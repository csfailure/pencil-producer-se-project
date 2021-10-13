#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include "wallet.h"


/**
 * @brief wallet::wallet constuctor
 */
wallet::wallet()
{
    money = 145;
    intelligence = 0;
}

/**
 * @brief wallet::getMoney returns money
 * @return amount
 */
double wallet::getMoney()
{
    return money;
}

/**
 * @brief wallet::getIntelligence returns intel level
 * @return intel level
 */
int wallet::getIntelligence() const
{
    return intelligence;
}

/**
 * @brief wallet::debitWallet
 * checks if there is enough money to debit the account if true it debits it
 * @param amount
 * @return Returns true if there is enough money and debits money. Returns false if param amount cannot be debited from account.
 **/
bool wallet::debitWallet(double amount)
{
    bool check = false;
    if(amount < 0.0)
        return check;
    if(money >= amount)
    {
        money -= amount;
        check = true;
    }

    return check;
}

/**
 * @brief wallet::creditWallet
 * credits bank account by @amount
 **/
void wallet::creditWallet(double amount)
{
    money += amount;
}

/**
 * @brief wallet::setMoney debug to set money
 * @param amount
 */
void wallet::setMoney(double amount)
{
    money = amount;
}

/**
 * @brief wallet::debitIntelligence
 * checks if there is enough intelligence to debit the account if true it debits it
 * @param amount
 * @return Returns true if there is enough intelligence and debits intelligence. Returns false if param amount cannot be debited from account.
 **/
bool wallet::debitIntelligence(int amount)
{
    bool check = false;
    if(amount < 0)
        return check;
    if (intelligence >= amount)
    {
        intelligence -= amount;
        check = true;
    }

    return check;
}

/**
 * @brief wallet::incIntelligence
 * increments intelligence by one while intelligence
 * is less than 200.
 **/
void wallet::incIntelligence()
{
    if (intelligence < 200)
        intelligence += 1;
}

/**
 * @brief wallet::setIntelligence function used for debugging purposes to set intel level
 * @param amount
 */
void wallet::setIntelligence(int amount)
{
    if (amount > 0 && amount< 201)
        intelligence = amount;
}

/**
 * @brief wallet::k_grantonethousand debug to incease money by 1000
 */
void wallet::k_grantonethousand()
{
    money = money + 1000;
}
