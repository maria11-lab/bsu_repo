#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

typedef pair<string, string> ss;
typedef vector <ss> W_N_S;
typedef map <string, W_N_S> MAP;
typedef MAP::iterator IT;
typedef set<ss> UNQ;

MAP data0;

void HotelInCity(const string&);
void NumberOfCitiesWithHotel(const string&);
void LoadInfoFromFile(ifstream&);
void Query(ifstream&);
void UniquePairs();

int main (){
	ifstream fin1("DATA.TXT");
	ifstream fin2("QUERY.TXT");
	if (!fin1){
		cerr << "File DATA.TXT not open\n";
		return 1;
	}
	if (fin1.peek() == std::fstream::traits_type::eof()) {
		cerr << "File DATA.TXT empty\n";
		return 1;
	}
	
	LoadInfoFromFile(fin1);

	if (!fin2){
		cerr << "File QUERY.TXT not open\n";
		return 1;
	}
	if (fin2.peek() == EOF) {
		cerr << "File QUERY.TXT empty\n";
		return 1;
	}

	Query(fin2);
}

void LoadInfoFromFile (ifstream& fin){
	int t1 = 0, t2 = 0;
	string  city, hotel, stars, line;
	W_N_S hotel_stars;
	IT it;
	while (getline(fin,line)){
		t1 = line.find(';');
		t2 = line.find(';', t1 + 1);
		city = line.substr(0, t1);
		hotel = line.substr(t1 + 1, t2 - t1 - 1);
		stars = line.substr(t2 + 1);

		it = data0.find(city);
		if (it == data0.end()) {
			hotel_stars.clear();
			hotel_stars.push_back(make_pair(hotel, stars));
			data0.insert(MAP::value_type(city, hotel_stars));
		}else {
			it -> second.push_back(make_pair(hotel, stars));
		}
	}
	fin.close();

	/*for (it = data0.begin(); it != data0.end(); ++it) {
		cout << it->first << ": \n";
		for (int i = 0; i < it->second.size(); ++i) {
			cout << it->second[i].first << ' ' << it->second[i].second << '\n';
		}
	}*/
}

void Query(ifstream& in){
	string line;
	while (getline(in, line)) {
		if (line[0] == '1') {
			cout << "Hotels in the city: " << line.substr(2) << '\n';
			HotelInCity(line.substr(2));
		}
		else if (line[0] == '2') {
			cout << "Number of cities with the hotel: " << line.substr(2) << '\n';
			NumberOfCitiesWithHotel(line.substr(2));
		}
		else {
			cout << "Unique pairs:\n";
			UniquePairs();
		}
	}
}

void HotelInCity(const string& line) {
	IT ptr = data0.find(line);
	if (ptr == data0.end()) {
		cout << "City not found.\n";
	}
	else {
		for (int i=0; i < ptr->second.size(); ++i) {
			cout << ptr->second[i].first << ' ' << ptr->second[i].second << '\n';
		}
	}
}
void NumberOfCitiesWithHotel(const string& line){
	int count = 0;
	IT ptr = data0.begin();
	for (ptr; ptr != data0.end();++ptr) {
		for (int i = 0; i < ptr->second.size(); ++i) {
			if (ptr->second[i].first == line) {
				++count;
				break;
			}
		}
	}
	if (count) cout << "Amount of cities, that has " << line << ": " << count;
	else cout << "Hotel not found";
}

void UniquePairs() {
	UNQ uniq;
	IT ptr = data0.begin();
	for (ptr; ptr != data0.end(); ++ptr) {
		for (int i = 0; i < ptr->second.size(); ++i) {
			uniq.insert(make_pair(ptr->first, ptr->second[i].second));
		}
	}
	set<ss>::iterator it = uniq.begin();
	for (; it != uniq.end(); ++it) {
		cout << it->first << ": " << it->second << '\n';
	}
}