#include <iostream>
#include <deque>
#include <map>
#include <fstream>
#include <string>
#include<sstream>
#include<exception>
#include <vector>
#include <algorithm>
#include <numeric>
#include <set>

std::string to_low (std::string s){
	for (size_t i = 0; i < s.size(); ++i) {
		s[i] = tolower(s[i]);
	}
	return s;
}

class Database {
private:
	std::map < std::string, std::deque<std::pair<std::string, int>>> data;
public:
	void loadFromFile(std::string inFileName) {
		std::ifstream in(inFileName);
		if (!in) { throw std::exception("\nОшибка открытия входного файла ");}
		if (in.peek() == EOF) { throw std::exception("\nОшибка, входной файл пуст"); }

		std::string line, sub, student, markStr;
		int mark;
		while (getline(in, line)) {
			std::stringstream ss(line);

			getline(ss, sub, ';');
			getline(ss, student, ';');
			getline(ss, markStr, ';');
			
			mark = stoi(markStr);
			
			data[sub].push_back(make_pair(student,mark));
		}
		std::cout << "Данные были успешно прочитаны из файла: " << inFileName << '\n';
		in.close();
	}
	void task1(std::string& sub) {
		std::cout << "\n1:" << sub;
		std::string lowSub = to_low(sub);
		bool findSub = 0;
		for (auto& x : data) {
			if (lowSub == to_low(x.first)) {
				findSub = 1;
				bool findNerd = 0;
				for (auto& y : x.second) {
					if (y.second == 9 || y.second == 10) {
						std::cout << "\nНайден отличник " << y.first << " по предмету: " 
							<< sub << " с отметкой " << y.second;
						findNerd = 1;
					}
				}
				if (!findNerd) { std::cerr << "\nНе найдены отличники по предмету " << sub; }
			}
		}
		if (!findSub) { std::cout << "\nНе найдено такого предмета: " << sub; }
	}
	void task2(std::string& student) {
		std::cout << "\n2:" << student;
		std::string studentLow = to_low(student);
		std::vector<int> marks;

		for (auto& x : data) {
			for (auto& y : x.second) {
				if (to_low(y.first) == studentLow) {
					marks.push_back(y.second);
				}
			}
		}

		if (marks.empty()) { std::cout << "\nНе найден студент " << student; }
		else {

			double sum = std::accumulate(marks.begin(), marks.end(), 0.0);
			double avarage = sum / marks.size();
			std::cout << "\nУ студента " << student << " средний балл равен: " << avarage;
		}
	}
	void task3() {
		std::cout << "\n3:\n";
		std::set<std::pair<int, std::string>> uniquePairs;

		for (const auto& subjectItem : data) {
			for (const auto& entry : subjectItem.second) {
				uniquePairs.insert({ entry.second, subjectItem.first });
			}
		}

		std::cout << "Уникальные пары <оценка, предмет>:\n";
		for (const auto& p : uniquePairs) {
			std::cout << "  Оценка " << p.first << " - предмет " << p.second << '\n';
		}
	}
};

void ReadQuery(std::string& filename, Database& data){
	std::ifstream in(filename);
	if (!in) { throw std::exception("\nОшибка открытия входного файла ");}
	if (in.peek() == EOF) { throw std::exception("\nОшибка, входной файл пуст"); }
	std::string line;
	while (getline(in,line)){
		if (line[0] == '1') {

			std::string sub = line.substr(2);
			data.task1(sub);

		}else if(line[0]=='2'){

			std::string student = line.substr(2);
			data.task2(student);

		}
		else if (line[0] == '3') {

			data.task3();

		}else throw(std::exception("\nОшибка, неверный формат файла запросов"));
	}
	in.close();
}

int main() {
	setlocale(LC_ALL,"Russian");
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