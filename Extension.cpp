#pragma once
#include "Extension.h"
#include <iostream>
#include <vector>



Cell::Cell()
{
    this->number = 0;
}

void Cell::take_away()
{
    this->number -= 1;
}

void Cell::add()
{
    this->number += 1;
}


Storage::Storage(){}

void Storage::define_change(double amount)
{
    amount = round(amount * 100) / 100;
    while (amount != 0)
    {
        for (int i = 0; i < 5; i++)
        {
            switch (i)
            {
            case 0:
            {
                if (this->bill_cells[0].number != 0 && amount >= 100)
                {
                    amount -= 100;
                    this->bill_cells[0].take_away();
                }
                break;
            }
            case 1:
            {
                if (this->bill_cells[1].number != 0 && amount >= 50)
                {
                    amount -= 50;
                    this->bill_cells[1].take_away();
                }
                break;
            }
            case 2:
            {
                if (this->bill_cells[2].number != 0 && amount >= 20)
                {
                    amount -= 20;
                    this->bill_cells[2].take_away();
                }
                break;
            }
            case 3:
            {
                if (this->coin_cells[0].number != 0 && amount >= 0.5)
                {
                    amount -= 0.5;
                    this->coin_cells[0].take_away();
                }
                break;
            }
            case 4:
            {
                if (this->coin_cells[1].number != 0 && amount >= 0.2)
                {
                    amount -= 0,2;
                    this->coin_cells[1].take_away();
                }
                break;
            }
            }
        }
    }
}

void Storage::add_money(double amount)
{
    if (amount == BillValues::hundred)
    {
        this->bill_cells[0].add();
    }
    else if (amount == BillValues::fifty)
    {
        this->bill_cells[1].add();
    }
    else if (amount == BillValues::twenty)
    {
        this->bill_cells[2].add();
    }
    else if (amount == CoinValues::fifty_copeck / 100.)
    {
        this->coin_cells[0].add();
    }
    else if (amount == CoinValues::twenty_copeck / 100.)
    {
        this->coin_cells[1].add();
    }
}

void Storage::clear()
{
    for (int i = 0; i < 3; i++)
    {
        bill_cells[i].number = 0;
    }
    for (int i = 0; i < 2; i++)
    {
        coin_cells[i].number = 0;
    }
}

NewReceiver::NewReceiver() {}
NewReceiver::NewReceiver(Storage* storage, int* values, int number)
{
    this->storage = storage;
    this->list_of_values = values;
    this->number_of_values = number;
    
}
void NewReceiver::process_input(double money)
{
    if (this->authenticity_check())
    {
        this->storage->add_money(this->define_value(money));
        this->machine->balance->add_money(money);
    }
    else
    {
        this->return_money();
    }
}
double NewReceiver::define_value(double money)
{
    money = round(money * 100)/ 100.;
    for (int i = 0; i < this->number_of_values; i++)
    {
        if (this->list_of_values[i] == money)
            return list_of_values[i];
    }
    for (int i = 0; i < this->number_of_values; i++)
    {
        if (this->list_of_values[i]/100 == money )
            return list_of_values[i]/100;
    }
}

void NewReceiver::return_money() {}
bool NewReceiver::authenticity_check()
{
    return true;
}

void PutCoinCommand::draw() const
{
    std::cout << "Deposite coin" << std::endl;
}

void PutCoinCommand::process() 
{
    double money;
    std::cin >> money;
    this->receiver->process_input(money);
}

void PutBillCommand::draw() const
{
    std::cout << "Deposite bill" << std::endl;
}

void PutBillCommand::process() 
{
    double money;
    std::cin >> money;
    this->receiver->process_input(money);
}

void TakeChangeCommand::draw() const
{
    std::cout << "Take change" << std::endl;
}

void TakeChangeCommand::process() 
{
    this->balance->take_all();
}

DrinkVendingMachine Application1::build()
{
    Balance balance = Balance();
    Storage storage = Storage();
    int coin_values[] = { CoinValues::fifty_copeck, CoinValues::twenty_copeck };
    int bill_values[] = { BillValues::hundred, BillValues::fifty, BillValues::twenty };
    NewReceiver coin_receiver = NewReceiver(&storage, coin_values, 2);
    NewReceiver bill_receiver = NewReceiver(coin_receiver.storage, bill_values, 3);

    std::vector<Command> main_commands = { 
        PutCoinCommand(&coin_receiver), 
        PutBillCommand(&bill_receiver),
        TakeChangeCommand(&balance) };
    std::vector<Command> service_commands = {};
    DrinkVendingMachine machine = DrinkVendingMachine(main_commands, service_commands);
    return machine;

}
void Application1::main()
{
    this->build().run();
}