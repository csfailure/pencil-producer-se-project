/**
 * \class Wallet
 * This class defines the customer wallet with all the methods
 *
 * \author Fezile Manana and Hammad Imran
 *
 * $Date: 2019/04/2  $
 *
 */
#ifndef WALLET_H
#define WALLET_H

#include <QJsonObject>

class wallet{
private:
    double money;
    int intelligence;

public:
    /// default constructor
    wallet();
    /// returns bank balance
    double getMoney();
    /// returns amount of intelligence in bank
    int getIntelligence() const;

    bool debitWallet(double);
    void creditWallet(double);
    bool debitIntelligence(int);
    void incIntelligence();
    void setIntelligence(int);

    /// used for debugging purposes
    void setMoney(double);
    
    void read(const QJsonObject &);
    void write(QJsonObject &);
    void k_grantonethousand();
};


#endif // WALLET_H
