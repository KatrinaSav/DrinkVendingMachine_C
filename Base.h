#pragma once

class Balance
{
public:
    double deposited_money;

    Balance();

    void add_money(double value);

    void take_away(double value);

};
class DrinkVendingMachine;
class Receiver
{
public:
    DrinkVendingMachine* machine;
    Receiver();
    virtual void process_input(double money);
    void set_machine(DrinkVendingMachine* machine);
};
class DrinkVendingMachine
{
public:

    Balance* balance;
    Receiver* receiver;
    DrinkVendingMachine();
    DrinkVendingMachine(Balance* balance, Receiver* receiver);
    void run();
    virtual void show_main_screen();
    virtual void show_service_screen();
    void show_ready_drink_screen();
    void on_drink_choosen();
    void on_transfer_to_service();
    void on_complite_service();

};





class Application
{
protected:
    DrinkVendingMachine build();
public:

    virtual void main();
};