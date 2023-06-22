#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <forward_list>
using namespace std;


struct	date
{
	unsigned int day = 0;
	unsigned int month = 0;
	unsigned int year = 0;

	void clear()
	{
		day = year = month = 0;
	}
};

struct	human
{
	string	name;
	string	middlename;
	string	lastname;

	void clear()
	{
		name.clear();
		lastname.clear();
		middlename.clear();
	}
};

struct 	contract_info
{
	bool valid = false;
	struct date end_date;
	struct date	start_date;
	int	id = 0;
	int	price = 0;
	int	lasting = 0; //длительность
	struct human owner;

	void clear()
	{
		id = price = lasting = 0;
		valid = false;
		owner.clear();
		end_date.clear();
		start_date.clear();
	}

	void print()
	{
		cout << "Owner: " << owner.lastname << " " << owner.name << " " << owner.middlename << ", ID = " << id
				<< ", price = " << price << ", validity: " << start_date.day << "." << start_date.month << "."
				<< start_date.year << " - ";
		if (valid == true)
			cout << "present";
		else
			cout << end_date.day << "." << end_date.month << "." << end_date.year << " (" << lasting << " days)";
	}	
};

void	read_from_file(ifstream& instream, forward_list<contract_info>& contrarct_flist);
void 	split_to_vector(vector<string>& vec, string dlm, const string& src);
bool	is_string_is_number(const string& str);
bool	get_date(const string& str, struct date& date);
bool	get_contract_info(const vector<string>& vec, forward_list<contract_info>& contrarct_flist);


void read_from_file(ifstream& instream, forward_list<contract_info>& contrarct_flist)
{
	string buf_str;
	vector<string>	text_vec;

	while (!instream.eof())
	{
		getline(instream, buf_str);
		if (buf_str != "}" && !buf_str.empty())
			text_vec.push_back(buf_str);
		else
		{
			text_vec.push_back(buf_str);
			if (!get_contract_info(text_vec, contrarct_flist))
			{
				text_vec.clear();
				buf_str.clear();
				continue;
			}
			text_vec.clear();
		}
		buf_str.clear();
	}
}

void split_to_vector(vector<string>& vec, string dlm, const string& src)
{
	size_t	p;
	size_t	start = 0;
	size_t	len = src.length();

	vec.clear();
	start = src.find_first_not_of(dlm);
	p = src.find_first_of(dlm, start);
	while (p != string::npos)
	{
		vec.push_back(src.substr(start, p - start));
		start = src.find_first_not_of(dlm, p);
		p = src.find_first_of(dlm, start);
	}
	if (len > start)
		vec.push_back(src.substr(start, len - start));
}

bool is_string_is_number(const string& str)
{
	for (int i = 0; i < str.size(); i++)
	{
		if (!isdigit(str[i]))
			return false;
	}
	return true;
}

bool get_date(const string& str, struct date& date)
{
	vector<string>	date_vec;

	split_to_vector(date_vec, ".", str);
	if (date_vec.size() != 3)
		return (false);
	if (!is_string_is_number(date_vec[0]) || !is_string_is_number(date_vec[1]) || !is_string_is_number(date_vec[2]))
		return false;
	date.day	= atoi(date_vec[0].c_str());
	date.month	= atoi(date_vec[1].c_str());
	date.year	= atoi(date_vec[2].c_str());
	if ((date.day < 1 || date.day > 30) && (date.month == 4 || date.month == 6 || date.month == 9 || date.month == 11))
		return false;
	else if ((date.day < 1 || date.day > 31) && (date.month == 1 || date.month == 3 || date.month == 5 || date.month == 7 ||
		date.month == 8 || date.month == 10 || date.month == 12))
		return false;
	else if (date.month == 2)
	{
		if (date.year % 4 == 0)
			if (date.day < 1 || date.day > 29)
				return false;
			else if (date.year % 4 != 0)
				if (date.day < 1 || date.day > 28)
					return false;
	}
	return true;
}

bool get_contract_info(const vector<string>& vec, forward_list<contract_info>& contrarct_flist)
{
	struct date					end_date;
	struct date					start_date;
	struct human				owner;
	struct contract_info		contr_info;
	vector<string>				tmp_vec;

	if (vec.size() < 4)
		return false;
	if (!(vec[1] == "{" &&vec[vec.size() - 1] == "}"))
		return false;

	split_to_vector(tmp_vec, " \t", vec[0]);
	if (tmp_vec.size() != 3)
		return false;
	owner.lastname = tmp_vec[0];
	owner.name = tmp_vec[1];
	owner.middlename = tmp_vec[2];
	tmp_vec.clear();

	auto it = vec.begin() + 2;
	for (it; it != vec.end() - 1; it++)
	{
		tmp_vec.clear();
		if ((*it).empty())
			continue;
		split_to_vector(tmp_vec, " \t<>", *it);
		if (tmp_vec.size() != 6)
			continue;
		if (!is_string_is_number(tmp_vec[0]))
			continue;
		if (!is_string_is_number(tmp_vec[5]))
			continue;
		if (!get_date(tmp_vec[2], start_date))
			continue;
		if (tmp_vec[4] == "нв")
		{
			contr_info.valid = true;
			end_date = { 99, 99, 9999 };
		}
		else
			if (!get_date(tmp_vec[4], end_date))
				continue;
		contr_info.id	= atoi(tmp_vec[0].c_str());
		contr_info.price = atoi(tmp_vec[5].c_str());
		contr_info.owner = owner;
		contr_info.start_date = start_date;
		contr_info.end_date = end_date;
		contr_info.lasting = (end_date.year * 365 + end_date.month * 12 + end_date.day) - (start_date.year * 365 + start_date.month * 12
			+ start_date.day);
		contrarct_flist.push_front(contr_info);
		contr_info.clear();
		tmp_vec.clear();
		end_date.clear();
		start_date.clear();
	}
	return true;
}

