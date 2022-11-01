//
// Created by ASUS on 30.10.2022.
//

#ifndef UNTITLED_CARDMACHINE_H
#define UNTITLED_CARDMACHINE_H
\
#include <fstream>
#include "Card.h"

using namespace std;

class CashMachine {
private:
    ofstream fout;
    ifstream fin;
    Card cardNow;
    void save(string path, Card card);
    void setCardNow(string path);
    Card getCardNow();
    string deleteSpaces(string path);
    void withdrawal(string path, double money);
    void replenishment(string path, double money);
    void transfer(string pathFrom, string pathTo, double money);
    void registerNewCard(int id, string name, double balance, int password);
    bool exists(string name);
    Card operations();
    bool authorization();
public:
    void start();
};

#endif //UNTITLED_CARDMACHINE_H
