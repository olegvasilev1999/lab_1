# lab_1
// ЗАДАНИЕ 1

#include "stdafx.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <map>
#include <vector>

using namespace std;

struct Student
{
	string Name;
	string GroupId;
	map<string, unsigned> Ratings;

	double srRating() {
		double s = 0;
		for (auto i = Ratings.begin(); i != Ratings.end(); i++) {
			s += i->second;
		}
		return s / Ratings.size();
	}

	bool neud() {
		for (auto i = Ratings.begin(); i != Ratings.end(); i++) {
			if (i->second <= 2) return true;
		}
		return false;
	}

	bool excellent() {
		for (auto i = Ratings.begin(); i != Ratings.end(); i++) {
			if (i->second < 5) return false;
		}
		return true;
	}

	bool Math() {
		if (this->Ratings["Math"] == 5) return true;
		return false;
	}

};

Student Polit(Student st) {
	st.Ratings["Polit"] = 4;
	return st;
}

void print(Student st) {
	cout << st.Name << " " << st.GroupId << ' ' << endl <<
		"Rating: " << st.srRating() << endl;
	for (auto i = st.Ratings.begin(); i != st.Ratings.end(); i++) {
		cout << " " << i->first;
		cout << "\t" << i->second << endl;
	}
	cout << endl;
}

int main()
{
	vector<Student> students{ { "Vasilev Oleg","iu8-32",{ { "Math", 5 },{ "Polit",5 },{ "PE",5 } } },
	{ "Melnikov Anton","iu8-32",{ { "Math",3 },{ "Polit",2 },{ "PE",0 } } },
	{ "Gorbatski Artem","iu8-32",{ { "Math", 4 },{ "Polit",5 },{ "PE",5 } } },
	{ "Martirosyan Vilen","iu8-32",{ { "Math", 5 },{ "Polit",4 },{ "PE",3 } } }
	};

	for (int i = 0; i < students.size(); i++) {
		print(students[i]);
	}
	cout << "\n\n\n";

	sort(students.begin(), students.end(), [](Student a, Student b) {
		return (a.Name.compare(b.Name)<0);
	});
	cout << "SORT ALF:\n";
	for (int i = 0; i < students.size(); i++) {
		print(students[i]);
	}
	cout << "\n\n\n";

	std::sort(students.begin(), students.end(), [](Student a, Student b) {
		return (a.srRating()>b.srRating());
	});
	cout << "SORT RATINGS:\n";
	for (int i = 0; i < students.size(); i++) {
		print(students[i]);
	}
	cout << "\n\n\n";

	int countofneud = count_if(students.begin(), students.end(), [](Student a) {
		return a.neud();
	});
	cout << "Count of neud students: " << countofneud << "\n\n";

	int countofex = count_if(students.begin(), students.end(), [](Student a) {
		return a.excellent();
	});
	cout << "Count of excellent students: " << countofex << "\n\n";
	cout << "\n\n\n";


	int countofM = count_if(students.begin(), students.end(), [](Student a) {
		return a.Math();
	});
	vector<Student> exlents(countofM);
	copy_if(students.begin(), students.end(), exlents.begin(), [](Student a) {
		return a.Math();
	});
	cout << "EXCELLENT MATH:\n";
	for (int i = 0; i < exlents.size(); i++) {
		print(exlents[i]);
	}
	cout << "\n\n\n";

	transform(students.begin(), students.end(), students.begin(), [](Student a) {
		return Polit(a);
	});
	cout << "POLIT HOR:\n";
	for (int i = 0; i < students.size(); i++) {
		print(students[i]);
	}
	cout << "\n\n\n";

	cin.get(); cin.get();
	return 0;
}




// ЗАДАНИЕ 2 

#include "stdafx.h"
#include <locale.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>


using namespace std;

struct Entity
{
	std::string Query;
	float Frequency;
};

using Dict = multimap<std::string, Entity>;

void print(Entity a) {
	std::cout << "   " << a.Query << " - " << a.Frequency << endl;
};


std::vector<Entity> suggest(const Dict & dict, const std::string& currentWord) {
	std::vector<Entity> result;
	for (auto i = (dict.equal_range(currentWord)).first; i != (dict.equal_range(currentWord)).second; i++) {
		result.push_back(i->second);
	}
	std::sort(result.begin(), result.end(), [](Entity a, Entity b) {
		return (a.Frequency > b.Frequency);
	});
	return result;
};


std::multimap<std::string, Entity> load(const std::string& filename) {
	multimap<std::string, Entity> result;
	ifstream file;
	string key;
	string query;
	float frequency;
	file.open("Words.txt");
	while (file >> key) {
		if (!(file >> query)) return result;
		if (!(file >> frequency)) return result;
		
		result.insert({ key,{ query,frequency } });
	}
	file.close();
	return result;
};


int main()
{
	setlocale(LC_ALL, "Russian");
	auto dict = load("Words.txt");
	auto result = suggest(dict, "добрый");
	cout << "Добрый" << endl;
	if (!(result.empty())) {
		for_each(result.begin(), result.end(), print);
	}
	cout << endl;
	result = suggest(dict, "спокойной");
	cout << "Cпокойной" << endl;
	if (!(result.empty())) {
		for_each(result.begin(), result.end(), print);
	}

	cout << endl;
	result = suggest(dict, "спокойного");
	cout << "Cпокойного" << endl;
	if (!(result.empty())) {
		for_each(result.begin(), result.end(), print);
	}

	cin.get(); cin.get();
	return 0;
}

