#include<iostream>
#include<iterator>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

int main() {
	vector<string> vec;
    ifstream inFile;
    inFile.open("my.txt");
    if (inFile.fail()) {
        cerr << "Could not find file" << endl;
        return -1;
    }
    copy(istream_iterator<string>(inFile), istream_iterator<string>(), back_inserter(vec));
    for (auto it : vec) {
        cout << it<<"\n";
    }
    inFile.close();
	return 0;
}