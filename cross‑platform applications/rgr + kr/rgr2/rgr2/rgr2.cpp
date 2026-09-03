#include <iostream>
#include <exception>
#include <string>
#include <deque>
#include <fstream>
#include <algorithm>
#include <iomanip>

using namespace std;

enum BuildingType { RESIDENTIAL, TECHNICAL };

class Building {
protected:
    string name;
    int yearBuilt;
    BuildingType type;
public:
    Building(string n, int y, BuildingType t) : name(n), yearBuilt(y), type(t) {}
    virtual ~Building() {}

    virtual void printInfo() const {
        cout << left << setw(15) << name 
            << setw(10) << yearBuilt 
            << setw(15) << (type == RESIDENTIAL ? "Residential" : "Technical");
    }

    string getName() const { return name; }
    int getYear() const { return yearBuilt; }
    BuildingType getType() const { return type; }
    virtual string getCategory() const = 0;
};

class House : public Building {
    int floors;
public:
    House(string n, int y, BuildingType t, int f) : Building(n, y, t), floors(f) {}
    void printInfo() const override {
        Building::printInfo();
        cout << "Cat: House, Floors: " << floors << endl;
    }
    string getCategory() const override { return "House"; }
};

class Renovation : public Building {
    int startYear;
    int durationMonths;
public:
    Renovation(string n, int y, BuildingType t, int sy, int dm) 
        : Building(n, y, t), startYear(sy), durationMonths(dm) {}
    void printInfo() const override {
        Building::printInfo();
        cout << "Cat: Renovation, Start: " << startYear << ", Dur: " << durationMonths << "m" << endl;
    }
    string getCategory() const override { return "Renovation"; }
};

class BuildingContainer {
    deque<Building*> items;
public:
    ~BuildingContainer() {
        for (auto b : items) delete b;
    }

    void add(Building* b) { items.push_back(b); }

    void loadData(string filename) {
        ifstream file(filename);

        if (!file.is_open()) {
            throw exception("Error: Could not open inFile!\n");
        }

        if (file.peek() == ifstream::traits_type::eof()) {
            throw exception("Error: inFile is empty!\n");
        }

        string cat, name;
        int year, tIdx, val1, val2;
        while (file >> cat >> name >> year >> tIdx >> val1) {
            BuildingType t = (tIdx == 0) ? RESIDENTIAL : TECHNICAL;
            if (cat == "House") {
                add(new House(name, year, t, val1));
            } else if (cat == "Renovation") {
                if (file >> val2) {
                    add(new Renovation(name, year, t, val1, val2));
                }
            }
        }
        cout << "Data loaded successfully. Total items: " << items.size() << endl;
    }

    void showAll() const {
        if (items.empty()) {
            cout << "Container is empty." << endl;
            return;
        }
        for (const auto& b : items) b->printInfo();
    }

    void countTypes() const {
        int res = 0, tech = 0;
        for (const auto& b : items) {
            (b->getType() == RESIDENTIAL) ? res++ : tech++;
        }
        cout << "Residential: " << res << ", Technical: " << tech << endl;
    }

    void countCategories() const {
        int h = 0, r = 0;
        for (const auto& b : items) {
            (b->getCategory() == "House") ? h++ : r++;
        }
        cout << "Houses: " << h << ", Renovations: " << r << endl;
    }

    void sortAndDisplay() {
        sort(items.begin(), items.end(), [](Building* a, Building* b) {
            if (a->getName() != b->getName())
                return a->getName() < b->getName();
            return a->getYear() < b->getYear();
            });
        showAll();
    }
};

int main() {
    try {
        BuildingContainer city;
        city.loadData("buildings.txt");

        cout << "\n--- LIST ---" << endl;
        city.showAll();

        cout << "\n--- STATS ---" << endl;
        city.countTypes();
        city.countCategories();

        cout << "\n--- SORTED ---" << endl;
        city.sortAndDisplay();

        return 0;
    }
    catch (const exception& e) {
        cerr << e.what();
        return 1;
    }
}