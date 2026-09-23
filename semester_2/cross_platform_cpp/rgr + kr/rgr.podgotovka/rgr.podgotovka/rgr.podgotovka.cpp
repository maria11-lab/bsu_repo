#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

string to_low(string s) {
	for (size_t i = 0; i < s.size(); ++i) {
		s[i] = tolower(s[i]);
	}
	return s;
}

typedef multimap <string, int> N_PH;
typedef map <int, string, greater<int>> PH;

typedef N_PH::value_type entry;
typedef PH::value_type sort_entry;

void printEntry(const entry& e) {
	cout << e.first << ' ' << e.second << '\n';
}

void printSort(const sort_entry& e) {
	cout << e.first << ' ' << e.second << '\n';
}

int prefix(const entry& e) {
	return e.second / 10000;
}
bool prefixCompare(const entry& e1, const entry& e2) {
	return prefix(e1) < prefix(e2);
}
class checkPrefix {
	int test;
public:
	checkPrefix(int p):test(p){}
	bool operator ()(const entry& e) {
		return prefix(e) == test;
	}
};


class phoneDir {
	N_PH database;
public:
	void add(string n, int num) {
		database.insert(make_pair(to_low(n), num));
	}
	void printDataBase();
	void printByNumber();
	void printByPrefix(int);
};


void phoneDir::printDataBase() {
	for_each(database.begin(), database.end(), printEntry);
}
void phoneDir::printByNumber() {
	PH sortm;
	for (N_PH::iterator it = database.begin(); it != database.end(); ++it) {
		sortm[it->second] = it->first;
	}
	for_each(sortm.begin(), sortm.end(), printSort);
}
void phoneDir::printByPrefix(int pr) {
	N_PH::iterator pos;
	pos = find_if(database.begin(), database.end(), checkPrefix(pr));
	while (pos != database.end()) {
		printEntry(*pos);
		pos = find_if(++pos, database.end(), checkPrefix(pr));
	}
}

int main() {
	phoneDir phones;
	phones.add("ivanov", 1234567);
	phones.add("Ivanov", 4567893);
	phones.add("Sidorov", 1234000);

	phones.printDataBase();
	cout << "***********\n";
	phones.printByNumber();
	cout << "***********\n";
	phones.printByPrefix(123);

	return 0;
}
