#pragma once
#include "Base.h"

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

class BillCell : public Cell
{
public:
    BillValues value;

    BillCell();

    BillCell(BillValues value);
};

class CoinCell : public Cell
{
public:
    CoinValues value;

    CoinCell();

    CoinCell(CoinValues value);
};

class Storage
{
public:

    CoinCell coin_cells[2];
    BillCell bill_cells[3];

    Storage();

    void define_change(double amount);

    void add_money(double amount);

    void clear();

};
class BillReceiver : public Receiver
{
public:
    Storage* storage;
    BillReceiver();
    BillReceiver(Storage* storage);
    void process_input(double money);
  
private:
    double define_bill_value(double money);
    void return_bill();
    bool bill_authenticity_check();
};

class CoinReceiver : public Receiver
{
public:
    Storage storage;
    CoinReceiver();
    CoinReceiver(Storage storage);
    void process_input(double money);
private:
    double define_coin_value(double money);

    void return_coin();
    bool coin_authenticity_check();
};



class Balance1 : public Balance
{
public:
    Balance1();
    void reset();
};

class DrinkVendingMachine1 : public DrinkVendingMachine
{
public:
    CoinReceiver* coin_receiver;
    DrinkVendingMachine1(Balance1* balance, BillReceiver* bill_receiver, CoinReceiver* coin_receiver);
    void show_main_screen();
    void show_service_screen();
    void on_take_change();
    void give_money();

};

class Application1 : public Application
{
protected:
    DrinkVendingMachine1 build();
public:
    void main();
};
