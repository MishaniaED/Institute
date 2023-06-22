#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <random>
#include <unordered_set>
#include "Lottery_ticket.h"
using namespace std;

#define min_gain 50
#define max_gain 50000000

class Generator {
public:
    virtual ~Generator() {}
    virtual Lottery_ticket* Generation(int i, const Lottery_ticket& lot_win) const = 0;
    virtual Lottery_ticket* Generation_win() const = 0;
};

class Generator4_20 : public Generator {  // 4-20
public:
    Lottery_ticket* Generation_win() const override
    {
        Lottery_ticket* ticket = new Lottery_ticket(4);
        unordered_set<unsigned int> ust;
        int num;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<unsigned int> uid1(1, 20);

        while (ust.size() != 4)
        {
            num = uid1(gen);
            ust.insert(num);
        }
        
        for (const auto& it : ust) {
            ticket->set_numbers(it);
        }

        ticket->set_id(0);
        return ticket;
    }

    Lottery_ticket* Generation(int i, const Lottery_ticket& lot_win) const override
    {
        Lottery_ticket* ticket = new Lottery_ticket ;
        vector<unsigned int> tmp;
        unordered_set<unsigned int> ust1;
        unordered_set<unsigned int> ust2;
        int num;
        int counter;
        size_t size_counter = 4;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> uid1(1, 20);
        uniform_int_distribution<int> number1(4, 8);

        tmp = lot_win.get_numbers();
        for (const auto& it : tmp)  
            ust2.insert(it);

        counter = number1(gen);
        while (ust1.size() != counter)
        {
            num = uid1(gen);
            ust1.insert(num);
        }

        for (const auto& elem : ust1) {
            if (ust2.count(elem)) {
                size_counter--;
            }
        }

        ticket->set_size(counter);

        if (size_counter > 0 && size_counter < ust2.size() - 1) {
            ticket->set_gain(min_gain * pow(10, ust2.size() - size_counter - 1) / 10);
        }
        else if (size_counter == 0) {
            ticket->set_gain(max_gain);
        }

        for (const auto& it : ust1) {
            ticket->set_numbers(it);
        }

        ticket->set_id(i);
        return ticket;
    }
};

class Generator7_49 : public Generator { // 7-49
public:
    Lottery_ticket* Generation_win() const override
    {
        Lottery_ticket* ticket = new Lottery_ticket(7);
        unordered_set<unsigned int> ust;
        int num;


        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<unsigned int> uid1(1, 49);

        while (ust.size() != 7)
        {
            num = uid1(gen);
            ust.insert(num);
        }

        for (const auto& it : ust) {
            ticket->set_numbers(it);
        }

        ticket->set_id(0);
        return ticket;
    }

    Lottery_ticket* Generation(int i, const Lottery_ticket& lot_win) const override
    {
        Lottery_ticket* ticket = new Lottery_ticket;
        vector<unsigned int> tmp;
        unordered_set<unsigned int> ust1;
        unordered_set<unsigned int> ust2;
        int num;
        int counter;
        size_t size_counter = 7;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> uid1(1, 49);
        uniform_int_distribution<int> number1(7, 14);

        tmp = lot_win.get_numbers();
        for (const auto& it : tmp)
            ust2.insert(it);

        counter = number1(gen);
        while (ust1.size() != counter)
        {
            num = uid1(gen);
            ust1.insert(num);
        }

        for (const auto& elem : ust1) {
            if (ust2.count(elem)) {
                size_counter--;
            }
        }

        ticket->set_size(counter);

        if (size_counter > 0 && size_counter < ust2.size() - 1) {
            ticket->set_gain(min_gain * pow(10, ust2.size() - size_counter - 1) / 10);
        }
        else if (size_counter == 0) {
            ticket->set_gain(max_gain);
        }

        for (const auto& it : ust1) {
            ticket->set_numbers(it);
        }

        ticket->set_id(i);
        return ticket;
    }
};

class Generator6_45 : public Generator { // 6-45
public:
    Lottery_ticket* Generation_win() const override
    {
        Lottery_ticket* ticket = new Lottery_ticket(6);
        unordered_set<unsigned int> ust;
        int num;


        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<unsigned int> uid1(1, 45);

        while (ust.size() != 6)
        {
            num = uid1(gen);
            ust.insert(num);
        }

        for (const auto& it : ust) {
            ticket->set_numbers(it);
        }

        ticket->set_id(0);
        return ticket;
    }

    Lottery_ticket* Generation(int i, const Lottery_ticket& lot_win) const override
    {
        Lottery_ticket* ticket = new Lottery_ticket;
        vector<unsigned int> tmp;
        unordered_set<unsigned int> ust1;
        unordered_set<unsigned int> ust2;
        int num;
        int counter;
        size_t size_counter = 6;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> uid1(1, 45);
        uniform_int_distribution<int> number1(6, 13);

        tmp = lot_win.get_numbers();
        for (const auto& it : tmp)
            ust2.insert(it);

        counter = number1(gen);
        while (ust1.size() != counter)
        {
            num = uid1(gen);
            ust1.insert(num);
        }

        for (const auto& elem : ust1) {
            if (ust2.count(elem)) {
                size_counter--;
            }
        }

        ticket->set_size(counter);

        if (size_counter > 0 && size_counter < ust2.size() - 1) {
            ticket->set_gain(min_gain * pow(10, ust2.size() - size_counter - 1) / 10);
        }
        else if (size_counter == 0) {
            ticket->set_gain(max_gain);
        }

        for (const auto& it : ust1) {
            ticket->set_numbers(it);
        }

        ticket->set_id(i);
        return ticket;
    }
};

class Generator5_36 : public Generator { // 5-36
public:
    random_device rd;
    Lottery_ticket* Generation_win() const override
    {
        Lottery_ticket* ticket = new Lottery_ticket(5);
        unordered_set<unsigned int> ust;
        int num;


        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<unsigned int> uid1(1, 36);

        while (ust.size() != 5)
        {
            num = uid1(gen);
            ust.insert(num);
        }

        for (const auto& it : ust) {
            ticket->set_numbers(it);
        }

        ticket->set_id(0);
        return ticket;
    }

    Lottery_ticket* Generation(int i, const Lottery_ticket& lot_win) const override
    {
        Lottery_ticket* ticket = new Lottery_ticket;
        vector<unsigned int> tmp;
        unordered_set<unsigned int> ust1;
        unordered_set<unsigned int> ust2;
        int num;
        int counter;
        size_t size_counter = 5;

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> uid1(1, 36);
        uniform_int_distribution<int> number1(5, 11);

        tmp = lot_win.get_numbers();
        for (const auto& it : tmp)
            ust2.insert(it);

        counter = number1(gen);
        while (ust1.size() != counter)
        {
            num = uid1(gen);
            ust1.insert(num);
        }

        for (const auto& elem : ust1) {
            if (ust2.count(elem)) {
                size_counter--;
            }
        }

        ticket->set_size(counter);

        if (size_counter > 0 && size_counter < ust2.size() - 1) {
            ticket->set_gain(min_gain * pow(10, ust2.size() - size_counter - 1) / 10);
        }
        else if (size_counter == 0) {
            ticket->set_gain(max_gain);
        }

        for (const auto& it : ust1) {
            ticket->set_numbers(it);
        }

        ticket->set_id(i);
        return ticket;
    }
};

class Creator {
public:
    virtual ~Creator() {};
    virtual Generator* FactoryMethod() const = 0;
};


class ConcreteCreator1 : public Creator {
public:
    Generator* FactoryMethod() const override {
        return new Generator4_20();
    }
};

class ConcreteCreator2 : public Creator {
public:
    Generator* FactoryMethod() const override {
        return new Generator7_49();
    }
};

class ConcreteCreator3 : public Creator {
public:
    Generator* FactoryMethod() const override {
        return new Generator6_45();
    }
};

class ConcreteCreator4 : public Creator {
public:
    Generator* FactoryMethod() const override {
        return new Generator5_36();
    }
};