#include <iostream>
#include "Base.h"

Balance::Balance()
{
    this->deposited_money = 0;
}

void Balance::add_money(double value)
{
    this->deposited_money += value;
}

void Balance::take_away(double value)
{
    this->deposited_money -= value;
}


class DrinkVendingMachine;

Receiver::Receiver() {}

void Receiver::set_machine(DrinkVendingMachine* machine)
{
    this->machine = machine;
}


DrinkVendingMachine::DrinkVendingMachine() {}
DrinkVendingMachine::DrinkVendingMachine(Balance *balance, Receiver *receiver)
{
    this->balance = balance;
    receiver->set_machine(this);
    this->receiver = receiver;
}
void DrinkVendingMachine::run()
{
    while (true)
    {
        show_main_screen();
    }
        
}
void DrinkVendingMachine::show_main_screen()
{
    std::cout << "Balance :"  << this->balance->deposited_money<<"\n";
    double money;
    std::cout << "Deposite money";
    std::cin >> money;
    this->receiver->process_input(money);
}
void DrinkVendingMachine::show_service_screen() {}
void DrinkVendingMachine::show_ready_drink_screen() {}
void DrinkVendingMachine::on_drink_choosen() {}
void DrinkVendingMachine::on_transfer_to_service() { this->show_service_screen(); }
void DrinkVendingMachine::on_complite_service() { this->show_main_screen(); }



void Receiver::process_input(double money)
{
    this->machine->balance->add_money(money);
}




DrinkVendingMachine Application::build()
{
    Balance balance = Balance();
    Receiver receiver = Receiver();
    DrinkVendingMachine machine = DrinkVendingMachine(&balance, &receiver);
    return machine;
}

void Application::main()
{
    this->build().run();
}






