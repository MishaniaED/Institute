#include <iostream>
#include <fstream>
#include <forward_list>
#include "parser.h"
#include "relation.h"
using namespace std;

StratagyComparator<contract_info*>	*comp_fullname_id = new Comparator_fullname_id; // перетащить в main
StratagyComparator<contract_info*>	*comp_contract_time = new Comparator_contract_time;
StratagyComparator<contract_info*>	*comp_cost = new Comparator_cost;

int	main()
{	
	setlocale(LC_ALL, "Russian");
	forward_list<contract_info>	contracts_flist;
	ifstream input_file("test.txt");

	if (input_file.fail()) {
		cerr << "Can't open file.";
		return 0;
	}
		
	read_from_file(input_file, contracts_flist);
	for (auto it : contracts_flist)
	{
		it.print();
		cout << endl;
	}
	
	RB_tree<contract_info*>		avl_tree_name_id(comp_fullname_id);
	AVL_tree<contract_info*>	rb_tree_contract_time(comp_contract_time);
	AVL_tree<contract_info*>	avl_tree_cost(comp_cost);
	Relation<contract_info>		relations;

	for (auto it = contracts_flist.begin(); it != contracts_flist.end(); it++)
		relations.insert_data(*it);

	relations.insert_index(&avl_tree_cost);
	relations.insert_index(&avl_tree_name_id);
	relations.insert_index(&rb_tree_contract_time);
	
	int choice;
	int	id;
	int duration;
	struct human owner;
	struct contract_info contr_info;
	
	while (true)
	{
		cout << "\nSearch by:\n";
		cout << "  1. Full name (and contract ID)\n";
		cout << "  2. Duration of the contract (in days)\n";
		cout << "  3. Contract cost\n";
		cout << "  0. Exit\n";
		cout << "Enter operation number: ";
		cin >> choice;
		if (choice == 0)
			break;
		switch(choice)
		{
			case 0:
				return 0;
			case 1:
				cout << "\nEnter:\nLastname: ";
				getline(cin, owner.lastname);
				cout << "Name: ";
				getline(cin, owner.name);
				cout << "Middlename: ";
				getline(cin, owner.middlename);
				cout << "Contract ID: ";
				cin >> id;
				contr_info.owner = owner;
				contr_info.id = id;
				if (relations.search_data(contr_info, comp_fullname_id))
					cout << "[SUCCESS]: Given full name was found" << endl;
				else
					cout << "[FAIL]" << endl;
				break;
			case 2:
				cout << "Enter duration of contract in days: ";
				cin >> duration;
				contr_info.lasting = duration;
				if (relations.search_data(contr_info, comp_contract_time))
					cout << "[SUCCESS]: Contract with given parameter [duration] was found" << endl;
				else
					cout << "[FAIL]" << endl;
				break;
			case 3:
				cout << "Enter contract cost: ";
				cin >> contr_info.price;
				if (relations.search_data(contr_info, comp_cost))
					cout << "[SUCCESS]: Contract with given parameter [cost] was found" << endl;
				else
					cout << "[FAIL]" << endl;
				break;
			default:
				cout << "\nIncorrect operation number. Try again." << endl;
				break;
		};
		contr_info.clear();
	}
	return 0;
}