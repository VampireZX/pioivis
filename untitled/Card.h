//
// Created by ASUS on 30.10.2022.
//

#ifndef UNTITLED_CARD_H
#define UNTITLED_CARD_H
#include <string>

using namespace std;

class Card {
private:
    string owner;
    int cardID;
    double balance;
    int password;
public:
    string getOwner();

    void setOwner(const string &owner);

    int getCardId() const;

    void setCardId(int cardId);

    double getBalance() const;

    void setBalance(double balance);

    int getPassword() const;

    void setPassword(int password);

    void setInfo(string path);
};

#endif //UNTITLED_CARD_H
