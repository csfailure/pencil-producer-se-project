#include <random>
#include <QFileDialog>
#include <QMovie>
#include <QApplication>
#include <QTextStream>
#include <QMessageBox>
#include <QProcess>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QDebug>
#include "mainwindow.h"
#include "wallet.h"
#include "inventory.h"
#include "APM.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(sell_pencils()));
    timer->start(200/gameInventory.getRate());

    //starting timer for changing material prices every 5 seconds
    connect(materials, SIGNAL(timeout()), this, SLOT(generate_price()));
    materials->start(5000);
    
    connect(apm, SIGNAL(timeout()), this, SLOT(on_makePencil_clicked()));
    connect(intelligence, SIGNAL(timeout()), this, SLOT(incIntelligence()));

    setup();
    update();



    model = new QStringListModel(this);
    QStringList List;
    ui->Scoreboard->setModel(model);

    updateScoreboard();

    ui->stackedWidget->setCurrentIndex(2);

    ui->kc_grant1000->setVisible(false);
    ui->kc_inventory1000->setVisible(false);
    ui->kc_pencil1000->setVisible(false);
    ui->kc_pencil1000_2->setVisible(false);
    ui->aboutt->setVisible(false);
    ui->kc_pencil1000_3->setVisible(false);
    ui->kc_pencil1000_4->setVisible(false);
    ui->kc_pencil1000_5->setVisible(false);
    ui->error->setVisible(false);



    QMovie* movie2 = new QMovie(":/2.gif");
    ui->intro->setMovie(movie2);
    movie2->start();

    QMovie* movie = new QMovie(":/cc.gif");
    ui->congrats->setMovie(movie);
    movie->start();



}

MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * \brief MainWindow::setup
 * sets up the static (non-changing) elements of the GUI
 **/
void MainWindow::setup(){

    //generating the initial prices for wood and graphite
    generate_price();
    gameInventory.setRate();

    //adding text to labels
    ui->label->setText("Pencil Produced");
    QFont f( "Arial", 15, QFont::Bold);
    ui->label->setFont( f);

    ui->Balance->setStyleSheet("QLabel { color : #2D6D0F; }");
    QFont x( "Arial", 15, QFont::Bold);
    ui->Balance->setFont( x);

    ui->Intelligence->setText("Intelligence:");
    ui->MarketingPrice->setText("Marketing Price: $500");
    ui->marketing->setText("Unlock marketing");
    ui->Intelligence->hide();
    ui->IntelligenceAmount->hide();
    ui->MarketingPrice->hide();
    ui->marketing->setVisible(false);
    ui->upgradeAPM->setEnabled(false);

}

/** 
 * \brief MainWindow::update
 * updates dynamic elements of the GUI
 **/
void MainWindow::update()
{
    // updating ui elements
    ui->APMs->setText("AutoPencil200: " + QString::number(gameAPM.getNumberOfAPMs()));
    ui->APMRate->setText("Rate: " + QString::number(gameAPM.getRate()*gameAPM.getNumberOfAPMs()*60)+
                          " pencils/minute");
    ui->Balance->setText("$" + QString::number(gameWallet.getMoney(), 'f', 2));
    ui->Demand->setText("Public Demand: "+QString::number(gameInventory.getRate(), 'f', 2));
    ui->PencilsProduced->setText("Pencil Produced(to Date): "+ QString::number(totalPencils));
    ui->PencilInventory->setText("Penils in Inventory: " + QString::number(gameInventory.getPencils()));
    ui->PencilPrice->setText("Price of pencil: $" + QString::number(gameInventory.getPriceOfPencil(), 'f', 2));
    ui->PriceOfGraphite->setText("$" + QString::number(gameInventory.getPriceOfGraphite(), 'f', 2) + "/100 m");
    ui->PriceOfWood->setText("$" + QString::number(gameInventory.getPriceOfWood(), 'f', 2)+ "/100 m");
    ui->GraphiteLeft->setText(QString::number(gameInventory.getGraphite(), 'f', 2)+" m");
    ui->WoodLeft->setText(QString::number(gameInventory.getWood(), 'f', 2)+" m");
    ui->MarketingPrice->setText("Price: $" + QString::number(gameInventory.getmarketingPrice(), 'f', 2));
    ui->IntelligenceAmount->setText(QString::number(gameWallet.getIntelligence()));


    //disabling buy apm button if needed
    if(gameWallet.getMoney() >= gameAPM.getPriceOfAPM() && gameAPM.getNumberOfAPMs() < 10)
        ui->buyAPM->setEnabled(true);
    else
        ui->buyAPM->setEnabled(false);

    //disable button if not enough materials
    if(gameInventory.getGraphite() < 0.2 || gameInventory.getWood() < 0.21)
        ui->makePencil->setEnabled(false);

    //disable button if not enough money to buy graphite
    if(gameWallet.getMoney() >= gameInventory.getPriceOfGraphite())
        ui->buyGraphite->setEnabled(true);
    else
        ui->buyGraphite->setEnabled(false);

    //disable button if not enough money to buy wood
    if(gameWallet.getMoney() >= gameInventory.getPriceOfWood())
        ui->buyWood->setEnabled(true);
    else
        ui->buyWood->setEnabled(false);

    // check if we can unlock marketing
    if(gameWallet.getIntelligence() >= 100)
    {
        ui->marketing->setEnabled(true);
        ui->MarketingPrice->show();
    }
    else
        ui->marketing->setEnabled(false);

    // check if intelligence is unlocked
    if(!ui->Intelligence->isHidden())
        ui->marketing->setVisible(true);

    // check if marketing is purchasable
    if(gameInventory.hasMarketing() && gameWallet.getMoney() >= 500)
        ui->marketing->setEnabled(true);

    // if rate reaches zero stop timer to avoid arithmetic error in division
    if (gameInventory.getRate() == 0.0)
        timer->stop();

    // unlock intelligence
    if(totalPencils >= 3000)
        intelligence_available();

    // unlock first APM upgrade
    if(gameWallet.getIntelligence() >= 50 && gameAPM.getNumberOfUpgrades() == 0)
        gameAPM.unlockAPMUpgrade();

    // unlock second APM upgrade
    if(totalPencils >= 5000 && gameWallet.getIntelligence() == 200 && gameAPM.getNumberOfUpgrades() == 1)
        gameAPM.unlockAPMUpgrade();

    // check if APM upgrade is available
    if(gameAPM.canUpgradeAPM())
        ui->upgradeAPM->setEnabled(true);
    else
        ui->upgradeAPM->setEnabled(false);

    if(totalPencils >= 25000)
    {
       ui->stackedWidget->setCurrentIndex(3);


    }


}

//function for generating random price for materials
void MainWindow::generate_price()
{
    //obtain a random number from hardware
    std::random_device rd;
    //seed the generator
    std::mt19937 eng(rd());
    //price between 1000 and 2000
    std::uniform_int_distribution<> distr(1000, 2000);
    gameInventory.setPriceOfWood(distr(eng));

    //obtain a random number from hardware
    std::random_device rd2;
    //seed the generator
    std::mt19937 eng2(rd2());
    //price between 1500 and 2500
    std::uniform_int_distribution<> distr2(1500, 2500);
    gameInventory.setPriceOfGraphite(distr2(eng2));

    update();
}

/**
 * \brief MainWindow::on_makePencil_clicked
 * consumes graphite and wood and produces one pencil
 **/
void MainWindow::on_makePencil_clicked()
{
    //return if there are not enough materials
    if(gameInventory.getGraphite() < 0.2 || gameInventory.getWood() < 0.21)
        return;

    //decrease wood from gameInventory
    gameInventory.setWood(gameInventory.getWood() - 0.21);
    
    //decrease graphite from gameInventory
    gameInventory.setGraphite(gameInventory.getGraphite() - 0.20);

    //increasing number of pencils in gameInventory
    gameInventory.setPencils(gameInventory.getPencils() + 1);

    //adding and displaying to total number of pencils created
    totalPencils++;
    
    update();
}

//function for decreasing price of function
void MainWindow::on_decreasePrice_clicked()
{
    //disable button if price is 0.05
    if(gameInventory.getPriceOfPencil() <= 0.05)
    {
        ui->decreasePrice->setEnabled(false);
        return;
    }
    //decrease price
    gameInventory.setPriceOfPencil(gameInventory.getPriceOfPencil() - 0.05);
    //set the updated user demand (see setRate function in gameWallet class)
    gameInventory.setRate();
    timer->start(static_cast<int>(200/gameInventory.getRate()));
    
    update();
}

//function for increasing the price of producing pencil
void MainWindow::on_increasePrice_clicked()
{
    //increase price
    gameInventory.setPriceOfPencil(gameInventory.getPriceOfPencil() + 0.05);

    //set the updated user demand (see setRate function in gameWallet class)
    gameInventory.setRate();
    timer->start(static_cast<int>(200/gameInventory.getRate()));

    update();
}

//function to sell pencil (used by qtimer 'timer')
void MainWindow::sell_pencils()
{
    //do nothing if there are no pencils in gameInventory
    if(gameInventory.getPencils() == 0)
        return;
    else{
        //decrease number of pencils from gameInventory
        gameInventory.setPencils(gameInventory.getPencils() - 1);
        //add money to gameWallet
        gameWallet.creditWallet(gameInventory.getPriceOfPencil());
        
        update();
    }
}

//function for buying APM
void MainWindow::on_buyAPM_clicked()
{
    //remove the money from the gameWallet
    if(!gameWallet.debitWallet(gameAPM.getPriceOfAPM()))
        return;

    //increase the number of APMs in gameInventory
    gameAPM.setAPM(gameAPM.getNumberOfAPMs() + 1);
    //adjust price of next apm (10% increase)

    gameAPM.setPriceOfAPM(gameAPM.getPriceOfAPM()*1.1);
    
    //one apm makes 2 pencils a second (one in 0.5 secs)
    //timer decreases according to increasing number of APMs
    //e.g 2 APMs will make one pencil every 0.5/2 = 0.25 seconds
    //which is 4 pencils per second
    apm->start(1000/(gameAPM.getNumberOfAPMs()*gameAPM.getRate()));
    
    update();
}

//function to buy wood
void MainWindow::on_buyWood_clicked()
{
    //remove money from gameWallet
    if(!gameWallet.debitWallet(gameInventory.getPriceOfWood()))
    {
        return;
    }

    double w = gameInventory.getWood();
    //adding wood
    gameInventory.setWood(w+100);

    update();
}

//function for buying graphite
void MainWindow::on_buyGraphite_clicked()
{
    //removing money from gameWallet
    if(!gameWallet.debitWallet(gameInventory.getPriceOfGraphite()))
    {
        return;
    }

    double g = gameInventory.getGraphite();
    //adding graphite in gameInventory
    gameInventory.setGraphite(g+100);
    
    update();
}

void MainWindow::incIntelligence()
{
    gameWallet.incIntelligence();
    update();
}

void MainWindow::intelligence_available()
{
    static int count = 0;
    if(count == 0)
    {
        ui->Intelligence->show();
        ui->IntelligenceAmount->show();
        ui->upgradeAPM->setEnabled(true);
        intelligence->start(500);
        count++;
    }
}

/**
 * \brief MainWindow::read
 * this function reads all the attributes from the game instance to
 * save into a file in Json format
 **/
void MainWindow::read(const QJsonObject &state)
{
    gameWallet.setMoney(state["balance"].toDouble());
    gameAPM.setPriceOfAPM(state["PriceOfAPM"].toDouble());
    gameInventory.setPriceOfGraphite(state["PriceOfGraphite"].toDouble());
    gameInventory.setmarketingPrice(state["PriceOfMarketing"].toDouble());
    gameInventory.setPriceOfPencil(state["PriceOfPencil"].toDouble());
    gameInventory.setPriceOfWood(state["PriceOfWood"].toDouble());
    gameWallet.setIntelligence(state["Intelligence"].toInt());

    gameAPM.setAPM(state["APMs"].toInt());
    gameInventory.setGraphite(state["Graphite"].toDouble());
    gameInventory.setPencils(state["PencilInventory"].toInt());
    gameInventory.setWood(state["Wood"].toDouble());

    for (int i = 0; i < state["APMUpgrades"].toInt(); i++)
    {
        gameAPM.upgradeAPM();
    }
    totalPencils = state["PencilsProduced"].toInt();
}

/**
 * \brief MainWindow::write
 * this function writes values from saved file to attributes in
 * game instance. The function assumes Json format for storage.
 **/
void MainWindow::write(QJsonObject &state)
{
    state["balance"] = gameWallet.getMoney();
    state["PriceOfAPM"] = gameAPM.getPriceOfAPM();
    state["PriceOfGraphite"] = gameInventory.getPriceOfGraphite();
    state["PriceOfMarketing"] = gameInventory.getmarketingPrice();
    state["PriceOfPencil"] = gameInventory.getPriceOfPencil();
    state["PriceOfWood"] = gameInventory.getPriceOfWood();
    state["Intelligence"] = gameWallet.getIntelligence();

    state["APMs"] = gameAPM.getNumberOfAPMs();
    state["Graphite"] = gameInventory.getGraphite();
    state["PencilInventory"] = gameInventory.getPencils();
    state["PencilsProduced"] = totalPencils;
    state["Wood"] = gameInventory.getGraphite();
    state["APMUpgrades"] = gameAPM.getNumberOfUpgrades();
}

void MainWindow::on_load_clicked()
{
    QString filename = QFileDialog::getOpenFileName(
                this,
                tr("Open File"),
                tr(".sav files(*.sav)")
                );
    QMessageBox::information(this, tr("File Name"), filename);
    QFile file(filename);

    if(!file.open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, "title", "File not opened");
        return;
    }

    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll());
    QJsonObject state = jsonDoc.object();

    MainWindow::read(state);
    file.close();
    
    if(gameAPM.getNumberOfAPMs() > 0)
    {
        connect(apm, SIGNAL(timeout()), this, SLOT(on_makePencil_clicked()));
        apm->start(1000/(gameAPM.getNumberOfAPMs()*gameAPM.getRate()));
    }
    if(gameWallet.getIntelligence() > 0)
    {
        intelligence->start(1000);
    }

    gameInventory.setRate();

    update();
    on_startgame_clicked();
}

void MainWindow::on_save_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr(".sav"));

    // Check if filename was entered
    if(filename.isEmpty())
        return;
    else
    {
        QFile file(filename);
        if(!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::information(this, tr("Cannot open file"), file.errorString());
            return;
        }

        QJsonObject state;
        MainWindow::write(state);
        QJsonDocument jsonDoc(state);

        file.write(jsonDoc.toJson());
        file.close();
    }
}

void MainWindow::on_marketing_clicked()
{
    static int count = 0;
    if(count == 0)
    {
        if(!gameWallet.debitIntelligence(100))
            return;
        
        gameInventory.unlockMarketing();
        ui->marketing->setText("Upgrade marketing");
        count++;
        return;
    }

    double cost = gameInventory.getmarketingPrice();
    if(!gameWallet.debitWallet(cost))
        return;

    int x = gameInventory.getmarketing();
    x = x + 1;
    if(x < 31)
    {
        gameInventory.setmarketing(x);
        gameInventory.setRate();
        cost = gameInventory.getmarketingPrice();
        cost = cost + (cost*0.1);
        gameInventory.setmarketingPrice(cost);
        update();
        qDebug()<<gameInventory.getmarketing();


    }
    else
    {
        ui->marketing->setEnabled(false);
        ui->error->setVisible(true);
    }


}

void MainWindow::on_upgradeAPM_clicked()
{
    static int count = 0;
    if(count < 2)
    {
        if(count < 1)
        {
            if(!gameWallet.debitIntelligence(50))
                return;
            gameAPM.upgradeAPM();
            update();
        }
        else
        {
            if(!gameWallet.debitIntelligence(200))
                return;

            gameAPM.upgradeAPM();
            update();
        }
        count++;
    }
}

void MainWindow::on_kc_grant1000_clicked()
{
    gameWallet.k_grantonethousand();
    update();
}

void MainWindow::on_kc_inventory1000_clicked()
{
    gameInventory.k_inventory1000();
    update();
}

void MainWindow::on_kc_pencil1000_clicked()
{
    totalPencils = totalPencils + 1000;
    update();
}

void MainWindow::on_kc_pencil1000_2_clicked()
{
    gameInventory.k_morewood();
    gameInventory.k_moregraphite();
    update();
}


void MainWindow::on_home_quitgame_clicked()
{
    updateScoreboard();
    scores.upload();
    qApp->quit();

}


void MainWindow::on_startgame_clicked()
{
     ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::updateScoreboard()
{
    scores.refresh();
    std::multimap<int, QString> scoreMap = scores.fetch();

    QStringList List;
    
    std::multimap<int, QString>::iterator iter;
    for (iter = scoreMap.begin(); iter != scoreMap.end(); ++iter) {
        List << iter->second + ": \r" + QString::number(iter->first);
    }
    model->setStringList(List);
}


int MainWindow::gettotalpencils(){
    return totalPencils;
}
void MainWindow::on_pushButton_clicked()
{
    qApp->quit();
    QProcess::startDetached(qApp->arguments()[0], qApp->arguments());
    ui->stackedWidget->setCurrentIndex(0);

}

void MainWindow::on_pushButton_2_clicked()
{
    qApp->quit();
}

void MainWindow::on_checkdebug_4_clicked()
{
    if(!clicked)
    {
        ui->kc_grant1000->setVisible(true);
        ui->kc_inventory1000->setVisible(true);
        ui->kc_pencil1000->setVisible(true);
        ui->kc_pencil1000_2->setVisible(true);
        ui->kc_pencil1000_3->setVisible(true);
        ui->kc_pencil1000_4->setVisible(true);
        ui->kc_pencil1000_5->setVisible(true);

    }
    else
    {
        ui->kc_grant1000->setVisible(false);
        ui->kc_inventory1000->setVisible(false);
        ui->kc_pencil1000->setVisible(false);
        ui->kc_pencil1000_2->setVisible(false);
        ui->kc_pencil1000_3->setVisible(false);
        ui->kc_pencil1000_4->setVisible(false);
        ui->kc_pencil1000_5->setVisible(false);

    }

    clicked = !clicked;
}


void MainWindow::on_settings_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_back_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_home_quitgame_2_clicked()
{
    updateScoreboard();
    scores.upload();
    qApp->quit();
}

void MainWindow::on_about_clicked()
{
    if(!clicked1)
    {
        ui->aboutt->setVisible(true);


    }
    else
    {
        ui->aboutt->setVisible(false);

    }

    clicked1 = !clicked1;
}


void MainWindow::on_kc_pencil1000_4_clicked()
{
    gameWallet.setIntelligence(gameWallet.getIntelligence() + 10);
}

void MainWindow::on_kc_pencil1000_5_clicked()
{
    gameInventory.setmarketing(gameInventory.getmarketing() + 3);
}

void MainWindow::on_kc_pencil1000_3_clicked()
{
    gameInventory.k_inventory1000();
    totalPencils = totalPencils + 1000;
    update();

}
