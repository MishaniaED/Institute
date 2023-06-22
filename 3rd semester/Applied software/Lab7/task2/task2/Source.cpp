#include <iostream>
#include <algorithm> 
#include <list>
#include <iterator> 
using namespace std;


template<typename S>
S ariph(list<S> li1) {
	double sum_of_elements = 0;
	double ariphmetical_mean = 0;
	for_each(li1.rbegin(), li1.rend(), [&](S n) { sum_of_elements += n; }); // сумма элементов списка
	ariphmetical_mean = sum_of_elements / li1.size();
	return ariphmetical_mean;
}

int main()
{
	list <double> l1;
	list <double> l2;
	list <double> tmps;
	list <double>::iterator it;
	int i = 0;
	int n1, n2;
	double tmp, negativ = 1;

	cout << "Enter size of 1-st list" << endl;
	cin >> n1;
	cout << "Enter elements of 1-st list" << endl;
	while (i < n1)
		{
			cin >> tmp;
			l1.push_back(tmp);
			i++;
		}
	cout << "Enter size of 2-nd list" << endl;
	cin >> n2;
	cout << "Enter elements of 2-nd list" << endl;	
	i = 0;
	while (i < n2)
	{
		cin >> tmp;
		l2.push_back(tmp);
		i++;
	}

	l1.sort();
	l2.sort();
	l1.merge(l2);
	tmps = l1;
	/*for (it = tmps.begin(); it != tmps.end(); it++)
		cout << (*it) << " ";
	cout << endl;*/
	while (!tmps.empty())
	{
		if (tmps.back() < 0) {
			negativ = tmps.back();
			break;
		}
		tmps.pop_back();
	}
	
	cout << "Ariphmetical mean: " << ariph(l1) << endl;
	if (negativ != 1)
		cout << "The biggest negative element: " << negativ << endl;
	else cout << "No element is negative!\n";
	//cout << residue<int>(l1);
	cin.get();
	return 0;
}