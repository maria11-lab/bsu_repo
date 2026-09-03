#include "calculator.h"
#include "ui_calculator.h"
#include <cmath>
#include <stdexcept>
#include <QRegularExpression>

Calculator::Calculator(QWidget *parent)
    : QWidget(parent), ui(new Ui::Calculator) {
    ui->setupUi(this);
    ui->result->setReadOnly(true);

    connect(ui->pushButton_0, &QPushButton::clicked, this, &Calculator::on_button_clicked);
    connect(ui->pushButton_1, &QPushButton::clicked, this, &Calculator::on_button_clicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Calculator::on_button_clicked);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &Calculator::on_button_clicked);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &Calculator::on_button_clicked);
    connect(ui->pushButton_5, &QPushButton::clicked, this, &Calculator::on_button_clicked);
    connect(ui->pushButton_6, &QPushButton::clicked, this, &Calculator::on_button_clicked);
    connect(ui->pushButton_7, &QPushButton::clicked, this, &Calculator::on_button_clicked);
    connect(ui->pushButton_8, &QPushButton::clicked, this, &Calculator::on_button_clicked);
    connect(ui->pushButton_9, &QPushButton::clicked, this, &Calculator::on_button_clicked);
    connect(ui->pushButton_Add, &QPushButton::clicked, this, &Calculator::on_button_clicked);
    connect(ui->pushButton_Sub, &QPushButton::clicked, this, &Calculator::on_button_clicked);
    connect(ui->pushButton_Mul, &QPushButton::clicked, this, &Calculator::on_button_clicked);
    connect(ui->pushButton_Div, &QPushButton::clicked, this, &Calculator::on_button_clicked);
    connect(ui->pushButton_Dot, &QPushButton::clicked, this, &Calculator::on_button_clicked);
    connect(ui->pushButton_Pow, &QPushButton::clicked, this, &Calculator::on_button_clicked);
    connect(ui->pushButton_OpenBracket, &QPushButton::clicked, this, &Calculator::on_button_clicked);
    connect(ui->pushButton_CloseBracket, &QPushButton::clicked, this, &Calculator::on_button_clicked);
}

Calculator::~Calculator() { delete ui; }

void Calculator::on_button_clicked() {
    QString current = ui->result->text();
    if (current == "Invalid value" || current.contains("Error") || current == "Division by zero") {
        ui->result->clear();
    }
    QPushButton *button = qobject_cast<QPushButton*>(sender());
    if (button) {
        ui->result->setText(ui->result->text() + button->text());
    }
}

void Calculator::on_PushButton_AC_clicked() { ui->result->clear(); }

void Calculator::on_pushButton_Del_clicked() {
    QString text = ui->result->text();
    if (text.isEmpty() || text == "Invalid value") {
        ui->result->clear();
        return;
    }
    text.chop(1);
    ui->result->setText(text);
}

void Calculator::on_pushButton_PM_clicked() {
    QString text = ui->result->text();
    if (text.isEmpty() || text == "Invalid value") return;

    static QRegularExpression negRe("\\(-(\\d*\\.?\\d+)\\)$");
    static QRegularExpression numRe("(\\d*\\.?\\d+)$");

    QRegularExpressionMatch negMatch = negRe.match(text);
    if (negMatch.hasMatch() && text.endsWith(negMatch.captured(0))) {
        int start = text.lastIndexOf(negMatch.captured(0));
        text.replace(start, negMatch.captured(0).length(), negMatch.captured(1));
    } else {
        QRegularExpressionMatch numMatch = numRe.match(text);
        if (numMatch.hasMatch()) {
            QString val = numMatch.captured(0);
            int start = numMatch.capturedStart();
            text.replace(start, val.length(), "(-" + val + ")");
        }
    }
    ui->result->setText(text);
}

void Calculator::on_pushButton_Pr_clicked() {
    QString text = ui->result->text();
    if (text.isEmpty() || text == "Invalid value" || text.endsWith("%")) return;
    ui->result->setText(text + "%");
}

void Calculator::on_pushButton_Equal_clicked() {
    QString exp = ui->result->text();
    if (exp.isEmpty()) return;

    try {
        RPNCalculator calc;
        double res = calc.calculate(exp);

        if (std::isinf(res)) throw std::runtime_error("Division by zero");
        if (std::isnan(res)) throw std::runtime_error("Invalid value");

        ui->result->setText(QString::number(res, 'g', 10));
    } catch (const std::runtime_error& e) {
        ui->result->setText(e.what());
    } catch (...) {
        ui->result->setText("Invalid value");
    }
}

// --- ЛОГИКА RPN ---

int RPNCalculator::getPriority(QString op) {
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    if (op == "%" || op == "u-") return 4;
    return 0;
}

QStringList RPNCalculator::tokenize(QString exp) {
    QStringList tokens;
    QString num;
    for (int i = 0; i < exp.length(); ++i) {
        QChar c = exp[i];
        if (c.isDigit() || c == '.') {
            num += c;
        } else {
            if (!num.isEmpty()) {
                tokens << num;
                num.clear();
            }
            if (c.isSpace()) continue;
            if (c == '-' && (tokens.isEmpty() || tokens.last() == "(" ||
                             (getPriority(tokens.last()) > 0 && tokens.last() != "%"))) {
                tokens << "u-";
            } else {
                tokens << QString(c);
            }
        }
    }
    if (!num.isEmpty()) tokens << num;
    return tokens;
}

double RPNCalculator::calculate(QString expression) {
    QStringList tokens = tokenize(expression);
    if (tokens.isEmpty()) return 0;

    QStack<double> values;
    QStack<QString> ops;

    auto applyOp = [&]() {
        if (ops.isEmpty()) return;
        QString op = ops.pop();

        if (op == "u-") {
            if (values.isEmpty()) throw std::runtime_error("Invalid syntax");
            values.push(-values.pop());
            return;
        }
        if (op == "%") {
            if (values.isEmpty()) throw std::runtime_error("Invalid syntax");
            values.push(values.pop() / 100.0);
            return;
        }

        if (values.size() < 2) throw std::runtime_error("Missing operator");
        double r = values.pop();
        double l = values.pop();

        if (op == "+") values.push(l + r);
        else if (op == "-") values.push(l - r);
        else if (op == "*") values.push(l * r);
        else if (op == "/") {
            if (r == 0) throw std::runtime_error("Division by zero");
            values.push(l / r);
        }
        else if (op == "^") values.push(std::pow(l, r));
    };

    for (const QString& t : tokens) {
        bool ok;
        double v = t.toDouble(&ok);
        if (ok) {
            values.push(v);
        } else if (t == "(") {
            ops.push(t);
        } else if (t == ")") {
            while (!ops.isEmpty() && ops.top() != "(") applyOp();
            if (ops.isEmpty()) throw std::runtime_error("Bracket error");
            ops.pop();
        } else {
            while (!ops.isEmpty() && ops.top() != "(" && getPriority(ops.top()) >= getPriority(t)) {
                applyOp();
            }
            ops.push(t);
        }
    }

    while (!ops.isEmpty()) {
        if (ops.top() == "(") throw std::runtime_error("Bracket error");
        applyOp();
    }

    if (values.size() > 1) throw std::runtime_error("Missing operator");
    if (values.isEmpty()) throw std::runtime_error("Invalid value");

    return values.top();
}