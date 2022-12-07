#include <iostream>
#include "Base.h"

Balance::Balance()
{
    this->deposited_money = 0;
}

void Balance::draw()
{
    std::cout << "Balance :"  << this->deposited_money << "\n";
}

void Balance::add_money(double value)
{
    this->deposited_money += value;
}

void Balance::take_away(double value)
{
    this->deposited_money -= value;
}

double Balance::take_all()
{
    double money = this->deposited_money;
    this->deposited_money = 0;
    return money;
}


void PutMoneyCommand::draw() const
{
    std::cout << "Deposite money";
}


void PutMoneyCommand::process()
{
    double money;
    std::cin >> money;
    this->receiver->process_input(money);
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
    this->balance->draw();
    for (int i = 0; i < main_commands.size(); ++i) {
        std::cout << i << ". ";
        main_commands[i].draw();
    }
    std::cout << "choose command";
    int select = 0;
    std::cin >> select;
    if (select >= 0 && select < main_commands.size()) {
        main_commands[select].process();
    }
}


void DrinkVendingMachine::show_service_screen() {}
void DrinkVendingMachine::show_ready_drink_screen() {}
void DrinkVendingMachine::on_drink_choosen() {}
void DrinkVendingMachine::on_transfer_to_service() { this->show_service_screen(); }
void DrinkVendingMachine::on_complite_service() { this->show_main_screen(); }



void Receiver::process_input(double money)
{
    this->balance->add_money(money);
}




DrinkVendingMachine Application::build()
{
    Balance balance = Balance();
    Receiver receiver = Receiver(&balance);
    std::vector<Command> main_commands = { PutMoneyCommand(&balance, &receiver) };
    std::vector<Command> service_commands = {};
    DrinkVendingMachine machine = DrinkVendingMachine(main_commands, service_commands);
    return machine;
}

void Application::main()
{
    this->build().run();
}
