#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Book {
private:
	string author_surename, author_initials, name;
	int year, inquiries;
public:
	Book(string str) {
		author_surename = strtok((char*)str.c_str(), " ");
		author_initials = strtok(NULL, " ");
		name = strtok(NULL, ",");
		year = atoi(strtok(NULL, " "));
		inquiries = atoi(strtok(NULL, " \n"));
	}
	
	void setData(string date_author_surename, string date_author_initials, string date_name, int date_year, int date_inquiries) {
		author_surename = date_author_surename;
		author_initials = date_author_initials;
		name = date_name;
		year = date_year;
		inquiries = date_inquiries;
	}
	int get_year() {
		return year;
	}
	int get_inquiries() {
		return inquiries;
	}
	void getData() {
		cout << "Фамилия: " << author_surename <<"\nНазвание: " << name << "\n";
	}
};

vector<Book> search(vector<Book> vec, vector<Book> vec_res) {
	int i = 0;
	for (i; i < vec.size(); i++) {
		if ((vec[i].get_year() < 1980) && (vec[i].get_inquiries() == 0)) {
			vec_res.push_back(vec[i]);
		}
	}
	return vec_res;
}

int main() {
	setlocale(LC_ALL, "Russian");
	int buf1, buf2;
	vector<Book> vec, vec_res;
	fstream input_file;
	ofstream output_file("out.txt", ios_base::out | ios_base::trunc); // открываем выходной файл на запись, предварительно очистив его
	if (!output_file.is_open()) // если файл не открыт
		cout << "Файл не может быть открыт!\n";
	string str, str1, str2, str3;
	
	cout << "Введите фамилию и инициалы автора, название, год издания и количество запросовза последние 3 года\nПример ввода:\
Pushkin A.S. Evgenie Onegin, 1831 2\n(для остановки ввода введите 'end')\n!!! запятая после названия произведения обязательна !!!\n";
	while (getline(cin, str))
	{
		if (str == "end") {
			break;
		}
		output_file << str<<"\n";
	}
	output_file.close();
	input_file.open("out.txt", ios_base::in);  // открываем входной файл на чтение
	if (!input_file.is_open())				   // если файл не открыт
		cout << "Файл не может быть открыт!\n";

	while (!input_file.eof()){
		getline(input_file, str);
		if (str.size() <= 2)
			continue;
		Book obj(str);
		vec.push_back(obj);
	}

	vec_res = search(vec, vec_res);
	
	for (int j = 0; j < vec_res.size(); j++) {
		vec_res[j].getData();
	}

	vec.clear();
	vec_res.clear();
	input_file.close();
	return 0;
}