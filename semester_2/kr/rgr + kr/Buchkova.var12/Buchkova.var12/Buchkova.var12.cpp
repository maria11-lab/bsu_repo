#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <cctype>

std::string toLow(std::string s) {
    for (size_t i = 0; i < s.size(); ++i) {
        s[i] = tolower(s[i]);
    }
    return s;
}

bool isValidType(const std::string& type) {
    std::string lowType = toLow(type);
    return (lowType == "operational" || lowType == "investment" || lowType == "financial");
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
        out << type_ << " | Start Sum: " << startSum_ 
            << " | Percent: " << percent_ 
            << " | Service cost: " << serviceCost_ << '\n';
    }
};

typedef std::map<std::string, std::vector<Activity>>::const_iterator TypeMapConstIter;
typedef std::map<std::string, std::vector<Activity>>::iterator TypeMapIter;
typedef std::multimap<double, Activity>::const_iterator PercentMapConstIter;
typedef std::multimap<double, Activity>::iterator PercentMapIter;
typedef std::pair<PercentMapIter, PercentMapIter> PercentRange;

class FinanceDirectory {
private:
    std::multimap<double, Activity> percentMap;
    std::map<std::string, std::vector<Activity>> typeMap;

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
        size_t lineNum = 0;

        while (std::getline(inFile, line)) {
            ++lineNum;
            if (line.empty()) continue;

            std::stringstream ss(line);
            std::string type, startSumStr, percentStr, serviceStr;

            try {

                if (!std::getline(ss, type, ';')) throw 1;
                if (!std::getline(ss, startSumStr, ';')) throw 1;
                if (!std::getline(ss, percentStr, ';')) throw 1;
                if (!std::getline(ss, serviceStr)) throw 1;

                if (!isValidType(type)) throw 1;


                double startSum = std::stod(startSumStr);
                double percent = std::stod(percentStr);
                double service = std::stod(serviceStr);

                Activity newActivity(type, startSum, percent, service);
                percentMap.insert(std::make_pair(percent, newActivity));

                std::string lowType = toLow(type);
                typeMap[lowType].push_back(newActivity);
            }
            catch (...) {
                std::cout << "Line " << lineNum << " skipped (invalid line format)\n";
            }
        }
        inFile.close();

        std::cout << "Loaded: " << percentMap.size() << " activities\n";
    }

    void saveToFile(const std::string& filename) {
        std::ofstream out(filename);
        if (!out.is_open()) {
            throw std::exception("Error out file is not open!\n");
        }

        TypeMapConstIter itMap;
        for (itMap = typeMap.begin(); itMap != typeMap.end(); ++itMap) {
            const std::vector<Activity>& activities = itMap->second;
            for (size_t i = 0; i < activities.size(); ++i) {
                out << activities[i].type_ << ";" << activities[i].startSum_ << ";"
                    << activities[i].percent_ << ";" << activities[i].serviceCost_ << "\n";
            }
        }
        out.close();
        std::cout << "Saved to " << filename << "\n";
    }

    void findByPercent(double percent) {
        PercentRange range = percentMap.equal_range(percent);

        if (range.first == range.second) {
            std::cout << "No records with percent " << percent << "\n";
            return;
        }

        std::cout << "Found records with percent " << percent << ":\n";
        PercentMapIter it;
        for (it = range.first; it != range.second; ++it) {
            std::cout << "  ";
            it->second.print(std::cout);
        }
    }

    void findByPrefix(std::string prefix) {
        std::string lowPref = toLow(prefix);
        bool found = false;

        TypeMapConstIter itMap;
        for (itMap = typeMap.begin(); itMap != typeMap.end(); ++itMap) {
            if (itMap->first.substr(0, lowPref.size()) == lowPref) {
                const std::vector<Activity>& activities = itMap->second;
                for (size_t i = 0; i < activities.size(); ++i) {
                    activities[i].print(std::cout);
                    found = true;
                }
            }
        }

        if (!found) {
            std::cout << "Nothing found with prefix '" << prefix << "'\n";
        }
    }

    void findByTypeSorted(const std::string& type) {
        std::string lowType = toLow(type);

        TypeMapConstIter it = typeMap.find(lowType);

        if (it == typeMap.end()) {
            std::cout << "No records with type '" << type << "'\n";
            return;
        }

        std::vector<Activity> results = it->second;

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

    /*Не вижу смысла использовать бинарный поиск потому что:
    1. я использую мультимап для поиска по процентам
    2. во втром написано про обычный поиск
    3. в третьем у нас всего 3 вазможных правильных вариантов,
    зачем сюда пихать бинарный поиск и только усложнять код. */

    void printByType() {
        std::cout << "\nSorted by activity type:\n";
        TypeMapConstIter itMap;
        for (itMap = typeMap.begin(); itMap != typeMap.end(); ++itMap) {
            const std::vector<Activity>& activities = itMap->second;
            for (size_t i = 0; i < activities.size(); ++i) {
                activities[i].print(std::cout);
            }
        }
    }

    void addActivity(std::string type, double startSum, double percent, double serviceCost) {
        if (!isValidType(type)) {
            std::cout << "Cannot add activity: invalid type '" << type << "'\n";
            return;
        }

        Activity newActivity(type, startSum, percent, serviceCost);
        percentMap.insert(std::make_pair(percent, newActivity));

        std::string lowType = toLow(type);
        typeMap[lowType].push_back(newActivity);

        std::cout << "Added activity: " << type << "\n";
    }

    void printAll() {
        std::cout << "\nAll activity (" << percentMap.size() << "):\n";
        TypeMapConstIter itMap;
        for (itMap = typeMap.begin(); itMap != typeMap.end(); ++itMap) {
            const std::vector<Activity>& activities = itMap->second;
            for (size_t i = 0; i < activities.size(); ++i) {
                activities[i].print(std::cout);
            }
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