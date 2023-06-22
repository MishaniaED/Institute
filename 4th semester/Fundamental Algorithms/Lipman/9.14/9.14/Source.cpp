#include <iostream>
#include <vector>
#include <list>
#include <cstring>
using namespace std;

int main()
{
	list<const char*> lst = { "first", "second", "third" };
	vector<string> vec;
	string str;
	int size, i, j = 0;

	for (const char* s : lst)
	{
		vec.push_back(str);
		size = strlen(s);
		for (i = 0; i < size; i++)
			vec[j].push_back(s[i]);
		cout<< vec[j]<<'\n';
		j++;
	}
	return 0;
}