#include<iostream>
#include<vector>
#include <algorithm>
using namespace std;

class Sales_data
{
public:
	int	isbn;
	Sales_data() : isbn(0) {}
	Sales_data(int ISBN) : isbn(ISBN) {}
	friend void	print(const vector<Sales_data> Vect);
};

void print(const vector<Sales_data> Vect) {
	int i;
	for (i = 0; i != Vect.size(); i++) {
		cout << Vect[i].isbn << " ";
	}
	cout << endl;
}

int	main()
{
	vector<Sales_data> vec;
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		Sales_data tmp = -10 + rand() % 20;
		vec.push_back(tmp);
	}

	print(vec);
	sort(vec.begin(), vec.end(), [](Sales_data& first, Sales_data& second)
		{ return first.isbn > second.isbn; });
	print(vec);
	return (0);
}