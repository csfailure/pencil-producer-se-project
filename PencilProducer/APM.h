#ifndef APM_H
#define APM_H

class APM
{
private:
    int numberOfAPMs;
    double priceOfAPM;
    double rate;
    bool upgradeAvailable;
    int numberOfUpgrades;


public:
    /**
     * @brief APM Consturctor of apm class
     */
    APM();

    /**
     * @brief getNumberOfAPMs number of amps currently in use
     * @return number of apms
     */
    int getNumberOfAPMs() const;
    /**
     * @brief getPriceOfAPM current price to buy one apm
     * @return price
     */
    double getPriceOfAPM() const;
    /**
     * @brief getRate rate of pencile produces by the apms
     * @return production rate
     */
    double getRate() const;
    /**
     * @brief canUpgradeAPM checks if the apms can be upgraded or if they are alreay max level
     * @return true if upgradable
     */
    bool canUpgradeAPM() const;
    /**
     * @brief getNumberOfUpgrades current number of upgrades bought
     * @return nr of upgrades in use
     */
    int getNumberOfUpgrades() const;


    /**
     * @brief setPriceOfAPM adjust current price of apm
     */
    void setPriceOfAPM(double);
    /**
     * @brief setAPM set the amount of apms currently in use
     * @param amount total amount of apms
     */
    void setAPM(int amount = 1);
    /**
     * @brief setRate set productionrate of penciles by apms
     */
    void setRate(double);
    /**
     * @brief upgradeAPM upgrade the apm
     */
    void upgradeAPM();
    /**
     * @brief unlockAPMUpgrade if the prereqs are met
     */
    void unlockAPMUpgrade();
    /**
     * @brief lockAPMUpgrade if the prereqs are not met
     */
    void lockAPMUpgrade();
};

#endif // APM_H
