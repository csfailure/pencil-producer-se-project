#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QStringList>
#include <QStringListModel>
#include <QUrl>
#include <QMediaPlayer>
#include "APM.h"
#include "wallet.h"
#include "inventory.h"
#include "scoreboard.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    
    wallet gameWallet;
    inventory gameInventory;
    APM gameAPM;
    
    void setup();
    /// qtimer for selling pencils
    QTimer *timer = new QTimer(this);
    /// qtimer for APMs
    QTimer *apm = new QTimer(this);
    /// qtimer for updating price of materials
    QTimer *materials = new QTimer(this);
    /// qtimer for incrementing intelligence
    QTimer *intelligence = new QTimer(this);

    /**
     * @brief read from auto save state
     */
    void read(const QJsonObject &);
    /**
     * @brief write to auto save stace
     */
    void write(QJsonObject &);
    /**
     * @brief intelligence_available makes the intelleges availabe once it is unlocked
     */
    void intelligence_available();
    /**
     * @brief updates all lables and such on the screen
     */
    void update();
    /**
     * @brief updateScoreboard
     */
    void updateScoreboard();
    /**
     * @brief gettotalpencils
     * @return  total amount of pencils
     */
    int gettotalpencils();


private slots:
    /**
     * @brief on_pushButton_2_clicked closes app
     */
    void on_pushButton_2_clicked();

private slots:
    /**
     * @brief on_pushButton_clicked closes app
     */
    void on_pushButton_clicked();

private slots:
    /**
     * @brief on_marketing_clicked
     */
    void on_marketing_clicked();
    /**
     * @brief on_makePencil_clicked
     */
    void on_makePencil_clicked();
    /**
     * @brief on_decreasePrice_clicked
     */
    void on_decreasePrice_clicked();
    /**
     * @brief on_increasePrice_clicked
     */
    void on_increasePrice_clicked();
    /**
     * @brief on_buyAPM_clicked
     */
    void on_buyAPM_clicked();
    /**
     * @brief on_buyWood_clicked
     */
    void on_buyWood_clicked();
    /**
     * @brief on_buyGraphite_clicked
     */
    void on_buyGraphite_clicked();
    /**
     * @brief on_load_clicked
     */
    void on_load_clicked();
    /**
     * @brief on_save_clicked
     */
    void on_save_clicked();
    /**
     * @brief on_upgradeAPM_clicked
     */
    void on_upgradeAPM_clicked();
    /**
     * @brief on_kc_grant1000_clicked
     */
    void on_kc_grant1000_clicked();
    /**
     * @brief on_kc_inventory1000_clicked
     */
    void on_kc_inventory1000_clicked();
    /**
     * @brief on_kc_pencil1000_clicked
     */
    void on_kc_pencil1000_clicked();
    /**
     * @brief on_kc_pencil1000_2_clicked
     */
    void on_kc_pencil1000_2_clicked();
    /**
     * @brief on_home_quitgame_clicked
     */
    void on_home_quitgame_clicked();
    /**
     * @brief on_startgame_clicked
     */
    void on_startgame_clicked();
    /**
     * @brief generate_price
     */
    void generate_price();
    /**
     * @brief sell_pencils
     */
    void sell_pencils();
    /**
     * @brief incIntelligence
     */
    void incIntelligence();



    /**
     * @brief on_checkdebug_4_clicked
     */
    void on_checkdebug_4_clicked();

    /**
     * @brief on_settings_clicked
     */
    void on_settings_clicked();
    /**
     * @brief on_back_clicked
     */
    void on_back_clicked();
    /**
     * @brief on_home_quitgame_2_clicked
     */
    void on_home_quitgame_2_clicked();
    /**
     * @brief on_about_clicked
     */
    void on_about_clicked();
    /**
     * @brief on_kc_pencil1000_4_clicked
     */
    void on_kc_pencil1000_4_clicked();
    /**
     * @brief on_kc_pencil1000_5_clicked
     */
    void on_kc_pencil1000_5_clicked();
    /**
     * @brief on_kc_pencil1000_3_clicked
     */
    void on_kc_pencil1000_3_clicked();

private:
    /// totalPencils keeps track of all pencils produced
    int totalPencils = 0;
    Ui::MainWindow *ui;
    //kc he
    QStringListModel *model;
    ScoreBoard scores;
    bool clicked = false;
    bool clicked1 = false;
    QMediaPlayer* player;


};

#endif // MAINWINDOW_H
