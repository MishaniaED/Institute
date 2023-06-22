#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	int i = 0;
	vector<string> vec;
	fstream input_file;
	ofstream output_file("output.txt", ios_base::out | ios_base::trunc); // ��������� �������� ���� �� ������, �������������� ������� ���
	string str;
	cout << "������� ��� �����: ";
	cin >> str;
	input_file.open(str, ios_base::in);  // ��������� ������� ���� �� ������
	if (!input_file.is_open() || !output_file.is_open()) // ���� ���� �� ������
		cout << "���� �� ����� ���� ������!\n";
	while (getline(input_file, str))
	{
		i = 0;
		while (str[i]) {
			if ((int)str[i] >= 97 && ((int)str[i] <= 122)) {
				str[i] = str[i] - 32;
			}
			i++;
		}
		vec.push_back(str);
		cout << str <<endl;
	}
	i = 0;
	while (i != vec.size()){
		output_file << vec[i] << '\n';
		i++;
	}
	cout << "�������������� ����: output.txt";
	vec.clear();
	input_file.close();
	output_file.close();
	return 0;
}