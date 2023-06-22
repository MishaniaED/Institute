#pragma once

#include "parser.h"

template <typename T>
class	StratagyComparator
{
public:
	virtual ~StratagyComparator() {}
	virtual int compare(const T& obj1, const T& obj2) const = 0;
};

/* fullname and id */

class Comparator_fullname_id : public StratagyComparator<contract_info*>
{
	int compare(contract_info* const& obj1, contract_info* const& obj2) const override
	{
		if ((*obj1).owner.lastname > (*obj2).owner.lastname)
			return 1;
		else if ((*obj1).owner.lastname < (*obj2).owner.lastname)
			return -1;
		else
		{
			if ((*obj1).owner.name > (*obj2).owner.name)
				return 1;
			else if ((*obj1).owner.name < (*obj2).owner.name)
				return -1;
			else
			{
				if ((*obj1).owner.middlename > (*obj2).owner.middlename)
					return 1;
				else if ((*obj1).owner.middlename < (*obj2).owner.middlename)
					return -1;
				else
				{
					if ((*obj1).id > (*obj2).id)
						return 1;
					else if ((*obj1).id < (*obj2).id)
						return -1;
				}
			}
		}
		return 0;
	}
};

/* contract time */

class Comparator_contract_time : public StratagyComparator<contract_info*>
{
	int compare(contract_info* const& obj1, contract_info* const& obj2) const override
	{
		if ((*obj1).lasting > (*obj2).lasting)
			return (1);
		else if ((*obj1).lasting < (*obj2).lasting)
			return (-1);
		return (0);
	}
};

/* for cost */

class Comparator_cost : public StratagyComparator<contract_info*>
{
	int compare(contract_info* const& obj1, contract_info* const& obj2) const override
	{
		if ((*obj1).price > (*obj2).price)
			return 1;
		else if ((*obj1).price < (*obj2).price)
			return -1;
		return 0;
	}
};

template <typename T>
class	Binary_tree
{
public:
	StratagyComparator<T>		*comparator;

	Binary_tree(StratagyComparator<T> *compare = nullptr) : comparator(compare)
	{}

	virtual ~Binary_tree()
	{}

	virtual bool		find_node(T &&val) = 0;
	virtual void		add_node(T &&val) = 0;
	virtual void		delete_node(T &&val) = 0;
};

