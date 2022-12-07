#pragma once
#include <vector>

class Balance
{
public:
    double deposited_money;

    Balance();

    virtual void draw();
    void add_money(double value);
    void take_away(double value);
    double take_all();
};

class DrinkVendingMachine;
class Receiver
{
public:
    Receiver(Balance* balance)
        : balance(balance) {}
    virtual void process_input(double money);

protected:
    Balance* balance;
};


class Command
{
public:
    virtual void draw() const = 0;
    virtual void process() = 0;
};

class PutMoneyCommand : public Command
{
public:
    PutMoneyCommand(Balance* balance, Receiver* receiver)
        : balance(balance), receiver(receiver) {}
    virtual void draw() const;
    virtual void process();

protected:
    Balance* balance;
    Receiver* receiver;
};


class DrinkVendingMachine
{

public:
    DrinkVendingMachine(std::vector<Command>& main_commands, std::vector<Command>& service_commands)
        : main_commands(main_commands), service_commands(service_commands) {}
    void run();
    virtual void show_main_screen();
    virtual void show_service_screen();
    void show_ready_drink_screen();
    void on_drink_choosen();
    void on_transfer_to_service();
    void on_complite_service();

protected:
    Balance* balance;
    Receiver* receiver;
    std::vector<Command> main_commands;
    std::vector<Command> service_commands;
};


class Application
{
protected:
    DrinkVendingMachine build();

public:
    void main();
};

/*



*/