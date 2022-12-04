#pragma once
#include "Extension.h"
#include <iostream>



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



BillCell::BillCell() {}

BillCell::BillCell(BillValues value)
{
    this->value = value;
}



CoinCell::CoinCell() {}

CoinCell::CoinCell(CoinValues value)
{
    this->value = value;
}


Storage::Storage()
{
    this->bill_cells[0] = BillCell(BillValues::hundred);
    this->bill_cells[1] = BillCell(BillValues::fifty);
    this->bill_cells[2] = BillCell(BillValues::twenty);
    this->coin_cells[0] = CoinCell(CoinValues::fifty_copeck);
    this->coin_cells[1] = CoinCell(CoinValues::twenty_copeck);
}

void Storage::define_change(double amount)
{
    while (amount != 0)
    {
        for (int i = 0; i < 3; i++)
        {
            if (amount >= this->bill_cells[i].value && bill_cells[i].number != 0)
            {
                amount -= bill_cells[i].value;
                bill_cells[i].take_away();

            }
        }
        for (int i = 0; i < 2; i++)
        {
            if (amount >= this->coin_cells[i].value / 100. && coin_cells[i].number != 0)
            {
                amount -= coin_cells[i].value / 100.;
                coin_cells[i].take_away();
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

BillReceiver::BillReceiver() {}
BillReceiver::BillReceiver(Storage* storage)
{
    this->storage = storage;
}
void BillReceiver::process_input(double money)
{
    if (this->bill_authenticity_check())
    {
        this->storage->add_money(money);
        this->machine->balance->add_money(money);
    }
    else
    {
        this->return_bill();
    }
}
double BillReceiver::define_bill_value(double money) { return money; }

void BillReceiver::return_bill() {}
bool BillReceiver::bill_authenticity_check()
{
    return true;
}


CoinReceiver::CoinReceiver() {}
CoinReceiver::CoinReceiver(Storage storage)
{
    this->storage = storage;
}
void CoinReceiver::process_input(double money)
{
    if (this->coin_authenticity_check())
    {
        this->storage.add_money(money);
        this->machine->balance->add_money(money);
    }
    else
    {
        this->return_coin();
    }
}
double CoinReceiver::define_coin_value(double money) { return money; }

void CoinReceiver::return_coin() {}
bool CoinReceiver::coin_authenticity_check()
{
    return true;
}



Balance1::Balance1():Balance() {}
void Balance1::reset() {}


DrinkVendingMachine1::DrinkVendingMachine1(Balance1* balance, BillReceiver* bill_receiver, CoinReceiver* coin_receiver) : DrinkVendingMachine(balance, bill_receiver)
{
    this->coin_receiver = coin_receiver;
    this->coin_receiver->set_machine(this);
}
void DrinkVendingMachine1::show_main_screen()
{
    std::cout << "Balance :" << this->balance->deposited_money << "\n";
    double money;
    int check;
    std::cin >> check;
    switch (check)
    {
    case 1:
    {
        std::cout << "Deposite money";
        std::cin >> money;
        if (money > 2)
        {
            this->receiver->process_input(money);
        }
        else
        {
            this->coin_receiver->process_input(money);
        }
        break;
    }
    case 2:
    {
        this->on_take_change();
        this->give_money();
        break;
    }
    break;
    }

}
void DrinkVendingMachine1::show_service_screen() {}
void DrinkVendingMachine1::on_take_change()
{
    this->coin_receiver->storage.define_change(this->balance->deposited_money);
    //this->balance->reset();  невозможно вызвать данный метод
    this->balance->deposited_money = 0;
}

void DrinkVendingMachine1::give_money() {}


DrinkVendingMachine1 Application1::build()
{
    Balance1 balance = Balance1();
    Storage storage = Storage();
    CoinReceiver coin_receiver = CoinReceiver(storage);
    BillReceiver bill_receiver = BillReceiver(&coin_receiver.storage);
    DrinkVendingMachine1 machine = DrinkVendingMachine1(&balance, &bill_receiver, &coin_receiver);
    return machine;

}
void Application1::main()
{
    this->build().run();
}
