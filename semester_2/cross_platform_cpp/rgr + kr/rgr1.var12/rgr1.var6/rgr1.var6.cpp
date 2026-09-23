#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

std::string toLow(std::string s) {
    for (size_t i = 0; i < s.size(); ++i) {
        s[i] = tolower(s[i]);
    }
    return s;
}

struct Activity {
    std::string type_;
    double startSum_;
    double percent_;
    double serviceCost_;

    Activity() : type_(""), startSum_(0), percent_(0), serviceCost_(0) {};

    Activity(const std::string& type, double startSum, double percent, double serviceCost) :
        type_(type), startSum_(startSum), percent_(percent), serviceCost_(serviceCost) {};

    void print(std::ostream& out) const {
        out << type_ << " | Initial amount: " << startSum_ 
            << " | Percent: " << percent_ 
            << " | Service cost: " << serviceCost_ << '\n';
    }
};

class FinanceDirectory {
private:
    std::vector<Activity> activities;

public:
    void loadFromFile(const std::string filename) {
        std::ifstream inFile(filename);
        if (!inFile) {
            throw std::exception("Error, file not open!\n");
        }
        if (inFile.peek() == std::istream::traits_type::eof()) {
            throw std::exception("Error, file is empty!\n");
        }

        std::string line;
        while (std::getline(inFile, line)) {
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string type, startSumStr, percentStr, serviceStr;

            std::getline(ss, type, ';');
            std::getline(ss, startSumStr, ';');
            std::getline(ss, percentStr, ';');
            std::getline(ss, serviceStr);

            double startSum = std::stod(startSumStr);
            double percent = std::stod(percentStr);
            double service = std::stod(serviceStr);

            activities.push_back(Activity(type, startSum, percent, service));
        }
        inFile.close();
        std::cout << "Loaded " << activities.size() << " records\n";
    }

    void saveToFile(const std::string& filename) {
        std::ofstream out(filename);
        if (!out.is_open()) { 
            throw std::exception("Error out file is not open!\n");
        }
        for (size_t i = 0; i < activities.size(); ++i) {
            out << activities[i].type_ << ";" << activities[i].startSum_ << ";" 
                << activities[i].percent_ << ";" << activities[i].serviceCost_ << "\n";
        }
        out.close();
        std::cout << "Saved to " << filename << "\n";
    }

    void findByPercent(double percent) {
        bool found = false;
        for (size_t i = 0; i < activities.size(); ++i) {
            if (activities[i].percent_ == percent) {
                std::cout << "Found: ";
                activities[i].print(std::cout);
                found = true;
            }
        }
        if (!found) {
            std::cout << "No records with percent " << percent << "\n";
        }
    }

    void findByPrefix(std::string prefix) {
        std::string lowPref = toLow(prefix);
        bool found = false;

        for (size_t i = 0; i < activities.size(); ++i) {
            if (toLow(activities[i].type_).substr(0, lowPref.size()) == lowPref) {
                activities[i].print(std::cout);
                found = true;
            }
        }
        if (!found) {
            std::cout << "Nothing found with prefix '" << prefix << "'\n";
        }
    }

    void findByTypeSorted(const std::string& type) {
        std::vector<Activity> results;

        for (size_t i = 0; i < activities.size(); ++i) {
            if (toLow(activities[i].type_) == toLow(type)) {
                results.push_back(activities[i]);
            }
        }

        if (results.empty()) {
            std::cout << "No records with type '" << type << "'\n";
            return;
        }

        std::sort(results.begin(), results.end(), 
            [](const Activity& a, const Activity& b) {
                if (a.startSum_ != b.startSum_) {
                    return a.startSum_ < b.startSum_;
                }
                return a.percent_ < b.percent_;
            });

        std::cout << "Records with type '" << type << "' (sorted by sum and percent):\n";
        for (size_t i = 0; i < results.size(); ++i) {
            results[i].print(std::cout);
        }
    }

    void printByType() {
        std::vector<Activity> sorted = activities;
        std::sort(sorted.begin(), sorted.end(),
            [](const Activity& a, const Activity& b) {
                return toLow(a.type_) < toLow(b.type_);
            });

        std::cout << "\nSorted by activity type:\n";
        for (size_t i = 0; i < sorted.size(); ++i) {
            sorted[i].print(std::cout);
        }
    }

    void addActivity(std::string type, double startSum, double percent, double serviceCost) {
        activities.push_back(Activity(type, startSum, percent, serviceCost));
        std::cout << "Added activity: " << type << "\n";
    }

    void printAll() {
        std::cout << "\nAll records (" << activities.size() << "):\n";
        for (size_t i = 0; i < activities.size(); ++i) {
            activities[i].print(std::cout);
        }
    }
};

int main() {
    try {
        FinanceDirectory dir;

        std::cout << "=== Loading from file ===\n";
        dir.loadFromFile("input.txt");

        std::cout << "\n=== printAll ===\n";
        dir.printAll();

        std::cout << "\n=== findByPercent(5) ===\n";
        dir.findByPercent(5);

        std::cout << "\n=== findByPercent(999) ===\n";
        dir.findByPercent(999);

        std::cout << "\n=== findByPrefix('inv') ===\n";
        dir.findByPrefix("inv");

        std::cout << "\n=== findByTypeSorted('operational') ===\n";
        dir.findByTypeSorted("operational");

        std::cout << "\n=== printByType ===\n";
        dir.printByType();

        std::cout << "\n=== Adding new record ===\n";
        dir.addActivity("financial", 3000, 10, 150);

        std::cout << "\n=== Checking after addition ===\n";
        dir.printByType();

        std::cout << "\n=== Saving to file ===\n";
        dir.saveToFile("output.txt");

        return 0;
    }
    catch (const std::exception& err) {
        std::cout << "Error: " << err.what();
        return 1;
    }
}