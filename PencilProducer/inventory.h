/**
 * \class Inventory
 * This class gives defines the customer Inventory with all the methods
 *
 * \author Fezile Manana and Hammad Imran
 *
 * $Date: 2019/04/2  $
 *
 */
#ifndef INVENTORY_H
#define INVENTORY_H

class inventory{
private:
    double graphite;
    double wood;
    int pencils;
    int APM;

    double priceOfAPM;
    double priceOfGraphite;
    double priceOfPencil;
    double priceOfWood;
    int marketing;
    double rate;

    bool APMUpgradeAvailable;
    bool marketingUnlocked;
    double marketingPrice;

public:
    /**
     * @brief inventory Constructor
     */
    inventory();

    /**
     * @brief getPencils returns number of pencils in inventory
     * @return nr of penciles
     */
    int getPencils() const;
    /**
     * @brief getWood returns amount of wood in inventory
     * @return amount of wood
     */
    double getWood() const;
    /**
     * @brief getGraphite returns amount of graphite in inventory
     * @return amount of graphite
     */
    double getGraphite() const;
    /**
     * @brief getPriceOfPencil  returns price of pencil
     * @return price
     */
    double getPriceOfPencil() const;
    /**
     * @brief getPriceOfGraphite returns price of graphite
     * @return price
     */
    double getPriceOfGraphite() const;
    /**
     * @brief getPriceOfWood returns price of wood
     * @return price
     */
    double getPriceOfWood() const;
    /**
     * @brief getmarketing returns amount of marketing
     * @return price
     */
    int getmarketing() const;
    /**
     * @brief getmarketingPrice  returns current price of marketing
     * @return price
     */
    double getmarketingPrice() const;
    /**
     * @brief getRate returns rate for public demand
     * @return pub demand rate
     */
    double getRate() const;

    /**
     * @brief setPencils sets the number of pencils
     * @param pencil nr
     */
    void setPencils(int);
    /**
     * @brief setGraphite sets the amount of graphite
     * @param graphit amount
     */
    void setGraphite(double);
    /**
     * @brief setWood sets the amount of wood
     * @param wood amount
     */
    void setWood(double);
    /**
     * @brief setPriceOfPencil sets the price of a pencil
     * @param price
     */
    void setPriceOfPencil(double);
    /**
     * @brief setPriceOfGraphite sets the price of graphite
     * @param price
     */
    void setPriceOfGraphite(double);
    /**
     * @brief setPriceOfWood sets the price of wood
     * @param price
     */
    void setPriceOfWood(double);
    /**
     * @brief setmarketing sets the amount of marketing
     * @param marketing amount
     */
    void setmarketing(int);
    /**
     * @brief setmarketingPrice sets the price of upgrading marketing
     * @param price
     */
    void setmarketingPrice(double);
    /**
     * @brief setRate sets the rate of public demand
     */
    void setRate();
    
    /**
     * @brief unlockMarketing sets marketingUnlocked to true
     */
    void unlockMarketing();
    /**
     * @brief hasMarketing returns true if marketing was unlocked
     * @return marketingUnlocked
     */
    bool hasMarketing();

    /**
     * @brief unlockAPMUpgrade sets APMUpgradeAvailable to true
     */
    void unlockAPMUpgrade();
    /**
     * @brief lockAPMUpgrade sets APMUpgradeAvailable to false
     */
    void lockAPMUpgrade();
    /**
     * @brief canUpgradeAPM true if upgrade is avalables
     * @return APMUpgradeAvailable
     */
    bool canUpgradeAPM();

    /**
     * @brief k_inventory1000 debug methode to increase pencile inventory by 1000
     */
    void k_inventory1000();

    /**
     * @brief k_moregraphite debug methode to increase graphite inventory by 10
     */
    void k_moregraphite();
    /**
     * @brief k_morewood debug methode to increase wood inventory by 10
     */
    void k_morewood();
};

#endif // INVENTORY_H
