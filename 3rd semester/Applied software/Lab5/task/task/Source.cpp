#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <string>
#include <locale.h>

using namespace std;

class Calcmachine {  // класс вычислительная машина
protected:
	int cost;       // стоимость
	int life_time; // срок службы
	int db;         // шум
	float I;       // сила тока
	float EDS;     
	float length, width, height;
	string name;	
public:
	Calcmachine(int cost, int life_time, float I, float EDS, string name_ex, float length, float width, float height, int db)
	{
		this->db = db;
		this->cost = cost;
		this->life_time = life_time;
		this->length = length;
		this->width = width;
		this->height = height;
		name = name_ex;
	}
	virtual void print() const = 0;
	void hello() const
	{
		cout << "Вычислительная машина: компьютер, калькулятор, ноутбук!" << endl << endl;
	}
	virtual void power() = 0;
	virtual void size() = 0;
	virtual void noise_level() = 0;
};

class Computer : public Calcmachine {
private:
	
public:
	Computer(int cost, int life_time, float I, float EDS, string name_ex, float length, float width, float height, int db) : Calcmachine(cost, life_time, I, EDS, name_ex, length, width, height, db)
	{
		this->db = db;
		this->cost = cost;
		this->life_time = life_time;
		this->I = I;
		this->EDS = EDS;
		this->length = length;
		this->width = width;
		this->height = height;
		name = name_ex;
		
	}

	void print() const
	{
		cout << "Название фирмы компьютера: " << this->name << ", срок службы: " << this->life_time << " лет, стоимость: " <<cost<< endl;
		//cout << "Число таблеток в одной упаковке: " << number << "." << endl;
	}

	void power()
	{
		cout << "Мощность БП: " << I * EDS << " Ватт.\n";
	}

	void size()
	{
		cout << "Длина: " << length << ", ширина: " << width << ", высота: " << height << endl;
	}

	void noise_level()
	{
		cout << "Уровень шума: " << db <<" ДБ"<< endl;
	}
};

class Calculater : public Calcmachine {
private:

public:
	Calculater(int cost, int life_time, float I, float EDS,  string name_ex, float length, float width, float height, int db) : Calcmachine(cost, life_time, I, EDS, name_ex, length, width, height, db)
	{
		this->db = db;
		this->I = I;
		this->EDS = EDS;
		this->cost = cost;
		this->life_time = life_time; 
		this->length = length;
		this->width = width;
		this->height = height;
		name = name_ex;
	}

	void print() const
	{
		cout << "\nНазвание фирмы клалькулятора: " << this->name << ", срок службы " << this->life_time << " лет, стоимость: " << cost << endl;
	}

	void power()
	{
		cout << "Мощность БП: " << I * EDS << " Вт" << endl;
	}

	void size()
	{
		cout << "Длина: " << length << ", ширина: " << width << ", высота: " << height << endl;
	}

	void noise_level()
	{
		cout << "Уровень шума: " << db << " ДБ" << endl;
	}
};

class Noutebook : public Computer {
private:

public:
	Noutebook(int cost, int shelf_life, float I, float EDS, string name_ex, float length, float width, float height, int db) : Computer(cost, shelf_life, I, EDS, name_ex, length, width, height, db)
	{
		this->db = db;
		this->I = I;
		this->EDS = EDS;
		this->cost = cost;
		this->life_time = shelf_life;
		this->length = length;
		this->width = width;
		this->height = height;
		name = name_ex;
		
	}

	void print() const
	{
		cout << "\nНазвание фирмы ноутбука: " << this->name << ", срок службы " << this->life_time << " лет, стоимость: " <<cost<<endl;
	}
		
	void power()
	{
		cout << "Мощность БП: " << I * EDS << " Вт" << endl;
	}

	void size()
	{
		cout << "Длина: " << length << ", ширина: " << width << ", высота: " << height << endl;
	}

	void noise_level()
	{
		cout << "Уровень шума: " << db << " ДБ" << endl;
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	Computer a(32000, 20, 110, 5, "Dell", 40, 120, 30, 60);
	Calculater b(1000, 15, 0.5, 1, "Comix", 20, 10, 2, 2);
	Noutebook c(22000, 10, 5, 5, "ASUS", 3, 40, 50, 10);

	c.hello();

	Calcmachine* machines[3] = { &a, &b, &c };
	for (int i = 0; i < 3; i++)
	{
		machines[i]->print();
		machines[i]->power();
		machines[i]->size();
		machines[i]->noise_level();
	}


	return 0;
}
