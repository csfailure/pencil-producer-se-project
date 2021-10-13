#include "APM.h"

APM::APM()
{
    numberOfAPMs = 0;
    priceOfAPM = 150.0;
    upgradeAvailable = false;
    numberOfUpgrades = 0;
    // pencils produced per second
    rate = 2;
}

int APM::getNumberOfAPMs() const
{
    return numberOfAPMs;
}

double APM::getPriceOfAPM() const
{
    return priceOfAPM;
}

double APM::getRate() const
{
    return rate;
}

bool APM::canUpgradeAPM() const
{
    return upgradeAvailable;
}

int APM::getNumberOfUpgrades() const
{
    return numberOfUpgrades;
}


void APM::setPriceOfAPM(double price)
{
    priceOfAPM = price;
}

void APM::setAPM(int amount)
{
    if(amount <= 10)
        numberOfAPMs = amount;    
}


void APM::upgradeAPM()
{
    if(numberOfUpgrades < 2)
    {
        rate = rate*1.1;
        numberOfUpgrades++;
    }
    lockAPMUpgrade();
}

void APM::unlockAPMUpgrade()
{
    upgradeAvailable = true;
}

void APM::lockAPMUpgrade()
{
    upgradeAvailable = false;
}