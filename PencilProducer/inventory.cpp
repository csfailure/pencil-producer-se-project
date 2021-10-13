#include <cmath>
#include "inventory.h"

inventory::inventory()
{
    graphite = 1000;
    wood = 1000;
    pencils = 0;
    APM = 0;

    priceOfAPM = 150;
    priceOfPencil = 1.0;
    priceOfGraphite = 0.0;
    priceOfWood = 0.0;
    rate = 1.0;
    marketing = 0;
    marketingPrice = 500;
    marketingUnlocked = false;
    APMUpgradeAvailable = false;
}

int inventory::getPencils() const
{
    return pencils;
}

double inventory::getGraphite() const
{
    return graphite;
}

double inventory::getWood() const
{
    return wood;
}

double inventory::getPriceOfPencil() const
{
    return priceOfPencil;
}

double inventory::getPriceOfGraphite() const
{
    return priceOfGraphite;
}

double inventory::getPriceOfWood() const
{
    return priceOfWood;
}

double inventory::getRate() const
{
    return rate;
}

int inventory::getmarketing() const
{
    return marketing;
}

double inventory::getmarketingPrice() const
{
    return marketingPrice;
}

void inventory::setPencils(int amount)
{
    pencils = amount;
}

void inventory::setGraphite(double amount)
{
    graphite = amount;
}

void inventory::setWood(double amount)
{
    wood = amount;
}

void inventory::setPriceOfPencil(double price)
{
    priceOfPencil = price;
}

void inventory::setPriceOfGraphite(double price)
{
    priceOfGraphite = price;
}

void inventory::setPriceOfWood(double price)
{
    priceOfWood = price;
}

void inventory::setmarketing(int price)
{
    if(price > 0 && price < 31)
    {
        marketing = price;
    }
}

void inventory::setmarketingPrice(double price)
{
    marketingPrice = price;
}

void inventory::setRate()
{
    rate = (1 / priceOfPencil) * pow(1.1, marketing);
}



void inventory::unlockMarketing()
{
    marketingUnlocked = true;
}

bool inventory::hasMarketing()
{
    return marketingUnlocked;
}

void inventory::k_inventory1000()
{
    pencils = pencils + 1000;
}

void inventory::k_moregraphite()
{
    graphite = graphite + 10;
}
void inventory::k_morewood()
{
    wood = wood + 10;
}
