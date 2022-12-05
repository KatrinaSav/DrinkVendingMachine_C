#pragma once
#include "Base.h"
#include <vector>

enum BillValues
{
    hundred = 100,
    fifty = 50,
    twenty = 20
};

enum CoinValues
{
    fifty_copeck = 50,
    twenty_copeck = 20
};

class Cell
{
public:
    int number;

    Cell();

    void take_away();

    void add();
};


class Storage
{
public:

    Cell bill_cells[3];
    Cell coin_cells[2];

    Storage();

    void define_change(double amount);

    void add_money(double amount);

    void clear();

};
class NewReceiver : public Receiver
{
public:
    Storage* storage;
    int* list_of_values;
    int number_of_values;
    NewReceiver();
    NewReceiver(Storage* storage, int* values, int number);
    void process_input(double money);
  
private:
    double define_value(double money);
    void return_money();
    bool authenticity_check();
};




class DrinkVendingMachine1 : public DrinkVendingMachine
{
public:
    NewReceiver* coin_receiver;
    DrinkVendingMachine1(Balance* balance, NewReceiver* bill_receiver, NewReceiver* coin_receiver);
    void show_main_screen();
    void show_service_screen();
    void on_take_change();
    void give_money();
    void on_take_all_money();

};

class Application1 : public Application
{
protected:
    DrinkVendingMachine1 build();
public:
    void main();
};
