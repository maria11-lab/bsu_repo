#include <iostream>
#include <deque>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <exception>
#include <vector>
#include <algorithm>
#include <set>
#include <windows.h>

std::string to_low(std::string s) {
    for (size_t i = 0; i < s.size(); ++i) {
        s[i] = tolower(s[i]);
    }
    return s;
}

class Database {
private:
    std::map<int, std::vector<std::pair<std::string, std::string>>> data;

public:
    void loadFromFile(std::string inFileName) {
        std::ifstream in(inFileName);
        if (!in) { throw std::exception("\nОшибка открытия входного файла "); }
        if (in.peek() == EOF) { throw std::exception("\nОшибка, входной файл пуст"); }

        std::string line, boutique, city, yearStr;
        int year;

        while (getline(in, line)) {
            std::stringstream ss(line);

            getline(ss, boutique, ';');
            getline(ss, city, ';');
            getline(ss, yearStr);

            year = stoi(yearStr);

            data[year].push_back(std::make_pair(city, boutique));
        }
        std::cout << "Данные были успешно прочитаны из файла: " << inFileName << '\n';
        in.close();
    }

    void task1(std::string& boutique) {
        std::string lowBoutique = to_low(boutique);
        bool found = false;

        for (auto& yearItem : data) {
            for (auto& cityBoutique : yearItem.second) {
                if (lowBoutique == to_low(cityBoutique.second)) {
                    std::cout << "\nНайден бутик " << cityBoutique.second 
                        << " в городе " << cityBoutique.first 
                        << ", год открытия: " << yearItem.first;
                    found = true;
                }
            }
        }

        if (!found) {
            std::cout << "\nНе найден бутик " << boutique;
        }
    }

    void task2(std::string& city) {
        std::string lowCity = to_low(city);
        int totalCount = 0;

        for (auto& yearItem : data) {
            int yearCount = std::count_if(yearItem.second.begin(), yearItem.second.end(),
                [&lowCity](const std::pair<std::string, std::string>& cityBoutique) {
                    return lowCity == to_low(cityBoutique.first);
                }
            );
            totalCount += yearCount;
        }

        if (totalCount == 0) {
            std::cout << "\nНе найден город " << city;
        }
        else {
            std::cout << "\nВ городе " << city << " открылось бутиков: " << totalCount;
        }
    }

    void task3() {
        std::set<std::pair<std::string, int>> uniquePairs;

        for (const auto& yearItem : data) {
            for (const auto& cityBoutique : yearItem.second) {
                uniquePairs.insert({ to_low(cityBoutique.first), yearItem.first });
            }
        }

        std::cout << "\nУникальные пары <город, год открытия> (в нижнем регистре):";
        for (const auto& p : uniquePairs) {
            std::cout << "\n  Город " << p.first << " - год " << p.second;
        }
    }
};

void ReadQuery(std::string& filename, Database& data) {
    std::ifstream in(filename);
    if (!in) { throw std::exception("\nОшибка открытия входного файла "); }
    if (in.peek() == EOF) { throw std::exception("\nОшибка, входной файл пуст"); }

    std::string line;
    while (getline(in, line)) {
        if (line[0] == '1') {
            std::cout << '\n'<< line;
            std::string boutique = line.substr(2);
            data.task1(boutique);
        }
        else if (line[0] == '2') {
            std::cout << '\n' << line;
            std::string city = line.substr(2);
            data.task2(city);
        }
        else if (line[0] == '3') {
            std::cout << '\n' << line;
            data.task3();
        }
        else throw(std::exception("\nОшибка, неверный формат файла запросов"));
    }
    in.close();
}

int main() {
    setlocale(LC_ALL, "rus");

    Database data;

    try {
        data.loadFromFile("DATA.TXT");
        std::string s("QUERY.TXT");
        ReadQuery(s, data);
        return 0;
    }
    catch (std::exception& e) {
        std::cerr << e.what();
        return 1;
    }
}