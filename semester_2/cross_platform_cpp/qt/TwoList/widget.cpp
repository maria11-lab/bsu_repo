#include "widget.h"
#include "ui_widget.h"
#include <QInputDialog>
#include <QMessageBox>

Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);

    connect(ui->listLeft, &QListWidget::itemClicked, ui->listRight, &QListWidget::clearSelection);
    connect(ui->listRight, &QListWidget::itemClicked, ui->listLeft, &QListWidget::clearSelection);

    setupDefaultListSettings(ui->listLeft);
    setupDefaultListSettings(ui->listRight);
}

Widget::~Widget() {
    delete ui;
}

void Widget::setupDefaultListSettings(QListWidget *list) {
    list->setDragEnabled(true);
    list->setAcceptDrops(true);
    list->setDropIndicatorShown(true);
    list->setDefaultDropAction(Qt::MoveAction);
    list->setDragDropMode(QAbstractItemView::DragDrop);
}

void Widget::on_btnAdd_clicked() {
    bool ok;
    QString text = QInputDialog::getText(this, "Добавить", "Текст:", QLineEdit::Normal, "", &ok);
    if (ok && !text.isEmpty()) {
        QListWidgetItem *item = new QListWidgetItem(QIcon(":/icon.png"), text);
        item->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled);
        ui->listLeft->addItem(item);
    }
}

void Widget::on_btnEdit_clicked() {
    if (ui->listLeft->selectedItems().size() > 1) {
        QMessageBox::warning(this, "Ошибка", "Выберите только один элемент");
        return;
    }

    if (!ui->listRight->selectedItems().isEmpty()) {
        QMessageBox::warning(this, "Внимание", "Редактирование доступно только для элементов в левом списке");
        return;
    }

    QListWidgetItem *item = ui->listLeft->currentItem();
    if (!item || !item->isSelected()) return;

    bool ok;
    QString text = QInputDialog::getText(this, "Правка", "Текст:", QLineEdit::Normal, item->text(), &ok);
    if (ok && !text.isEmpty()) item->setText(text);
}

void Widget::on_btnDelete_clicked() {
    QList<QListWidgetItem*> left = ui->listLeft->selectedItems();
    QList<QListWidgetItem*> right = ui->listRight->selectedItems();

    for (QListWidgetItem* item : left) delete ui->listLeft->takeItem(ui->listLeft->row(item));
    for (QListWidgetItem* item : right) delete ui->listRight->takeItem(ui->listRight->row(item));
}

void Widget::on_btnClear_clicked() {
    ui->listLeft->clear();
    ui->listRight->clear();
}

void Widget::on_btnToRight_clicked() {
    QList<QListWidgetItem*> items = ui->listLeft->selectedItems();
    for (QListWidgetItem* item : items) {
        ui->listRight->addItem(ui->listLeft->takeItem(ui->listLeft->row(item)));
    }
}

void Widget::on_btnToLeft_clicked() {
    QList<QListWidgetItem*> items = ui->listRight->selectedItems();
    for (QListWidgetItem* item : items) {
        ui->listLeft->addItem(ui->listRight->takeItem(ui->listRight->row(item)));
    }
}

void Widget::on_btnSort_clicked() {
    ui->listLeft->sortItems(Qt::AscendingOrder);
    ui->listRight->sortItems(Qt::DescendingOrder);
}

void Widget::on_checkMulti_toggled(bool checked) {
    auto mode = checked ? QAbstractItemView::MultiSelection : QAbstractItemView::SingleSelection;

    ui->listLeft->setSelectionMode(mode);
    ui->listRight->setSelectionMode(mode);

    setupDefaultListSettings(ui->listLeft);
    setupDefaultListSettings(ui->listRight);
}

void Widget::on_checkIconMode_toggled(bool checked) {
    auto viewMode = checked ? QListView::IconMode : QListView::ListMode;

    ui->listLeft->setViewMode(viewMode);
    ui->listRight->setViewMode(viewMode);

    setupDefaultListSettings(ui->listLeft);
    setupDefaultListSettings(ui->listRight);
}