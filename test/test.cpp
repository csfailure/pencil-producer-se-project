#include <QtTest>
#include <QPushButton>
#include "../PencilProducer/mainwindow.h"




class TestPencilProducer: public QObject
{
    Q_OBJECT
private slots:
    void functiontest();
    void buttontest();
};


void TestPencilProducer::functiontest(){
	
	QApplication a();
    MainWindow w;

    /*
    wallet gameWallet;
    inventory gameInventory;
    APM gameAPM;
    */

    //make pencile button
    QPushButton* b = w.findChild<QPushButton*>("makePencil");
    for (int i = 0; i < 50; ++i)
    {
    	b->clicked();
    }
    QCOMPARE(w.gameInventory.getPencils(),50);
	
    //increase price button
	b = w.findChild<QPushButton*>("increasePrice");
	for (int i = 0; i < 5; ++i){
		b->clicked();
	}
	QCOMPARE(w.gameInventory.getPriceOfPencil(),1.25);

	//decrease price button
	b = w.findChild<QPushButton*>("decreasePrice");
	for (int i = 0; i < 2; ++i){
		b->clicked();
	}
	QCOMPARE(w.gameInventory.getPriceOfPencil(),1.15);

	// debug money +1000 button
	double money = w.gameWallet.getMoney();
	b = w.findChild<QPushButton*>("kc_grant1000");
	for (int i = 0; i < 50; ++i){
		b->clicked();
	}
	QCOMPARE(w.gameWallet.getMoney(),money+(1000*50));

	// debug inventory +1000 button
	int pencils = w.gameInventory.getPencils();
	b = w.findChild<QPushButton*>("kc_inventory1000");
	for (int i = 0; i < 50; ++i){
		b->clicked();
	}
	QCOMPARE(w.gameInventory.getPencils(),pencils+(1000*50));


	// debug pencils +1000 button
	int totalpencils = w.gettotalpencils();
	b = w.findChild<QPushButton*>("kc_pencil1000");
	for (int i = 0; i < 50; ++i){
		b->clicked();
	}
	QCOMPARE(w.gettotalpencils(),totalpencils+(1000*50));

	// debug +10 materials button
	double wood = w.gameInventory.getWood();
	double graphite = w.gameInventory.getGraphite();
	b = w.findChild<QPushButton*>("kc_pencil1000_2");
	for (int i = 0; i < 50; ++i){
		b->clicked();
	}
	QCOMPARE(w.gameInventory.getWood(),wood+(10*50));
	QCOMPARE(w.gameInventory.getGraphite(),graphite+(10*50));

	
	
	// debug intel +10
	int intel = w.gameWallet.getIntelligence();
	b = w.findChild<QPushButton*>("kc_pencil1000_4");
	for (int i = 0; i < 17; ++i){
		b->clicked();
	}
	QCOMPARE(w.gameWallet.getIntelligence(),intel+(10*17));


	// debug marketing +3
	int markting = w.gameInventory.getmarketing();
	b = w.findChild<QPushButton*>("kc_pencil1000_5");
	for (int i = 0; i < 4; ++i){
		b->clicked();
	}
	QCOMPARE(w.gameInventory.getmarketing(),markting+(3*4));



	// debug pencils+inv +1000 button
	int pencils2 = w.gameInventory.getPencils();
	int totalpencils2 = w.gettotalpencils();
	b = w.findChild<QPushButton*>("kc_pencil1000_3");
	for (int i = 0; i < 50; ++i){
		b->clicked();
	}
	QCOMPARE(w.gettotalpencils(),totalpencils2+(1000*50));
	QCOMPARE(w.gameInventory.getPencils(),pencils2+(1000*50));


	
	// debug buy graphite button
	double graphite2 = w.gameInventory.getGraphite();
	b = w.findChild<QPushButton*>("buyGraphite");
	for (int i = 0; i < 5; ++i){
		b->clicked();
	}
	QCOMPARE(w.gameInventory.getGraphite(),graphite2+(100*5));
	

	// debug buy wood button
	double wood2 = w.gameInventory.getWood();
	b = w.findChild<QPushButton*>("buyWood");
	for (int i = 0; i < 5; ++i){
		b->clicked();
	}
	QCOMPARE(w.gameInventory.getWood(),wood2+(100*5));


	// debug markeing button
	b = w.findChild<QPushButton*>("marketing");
	b->clicked();
	QVERIFY(w.gameInventory.hasMarketing());
	int markting2 = w.gameInventory.getmarketing();
	for (int i = 0; i < 5; ++i){
		b->clicked();
	}
	QCOMPARE(w.gameInventory.getmarketing(),markting2+(5));


	//debug buy apm button
	b = w.findChild<QPushButton*>("buyAPM");
	int nr_apms = w.gameAPM.getNumberOfAPMs();
	for (int i = 0; i < 2; ++i){
		b->clicked();
	}
	QCOMPARE(w.gameAPM.getNumberOfAPMs(),nr_apms+2);


	//debug upgrade apm
	QPushButton* upgrade_b = w.findChild<QPushButton*>("upgradeAPM");
	QPushButton* intel_b = w.findChild<QPushButton*>("kc_pencil1000_4");
	for (int i = 0; i < 6; ++i)
	{
		intel_b->clicked();
	}
	int upgrades = w.gameAPM.getNumberOfUpgrades();
	upgrade_b->clicked();
	QCOMPARE(w.gameAPM.getNumberOfUpgrades(),upgrades+1);
	for (int i = 0; i < 20; ++i)
	{
		intel_b->clicked();
	}
	upgrades = w.gameAPM.getNumberOfUpgrades();
	upgrade_b->clicked();
	QCOMPARE(w.gameAPM.getNumberOfUpgrades(),upgrades+1);

}



void TestPencilProducer::buttontest(){

	QApplication a();
    MainWindow w;

    QPushButton* b = w.findChild<QPushButton*>("save");
    //b->clicked();
    b = w.findChild<QPushButton*>("settings");
    b->clicked();
    b = w.findChild<QPushButton*>("back");
    b->clicked();
    b = w.findChild<QPushButton*>("checkdebug_4");
    b->clicked();
    //b = w.findChild<QPushButton*>("save");
    //b->clicked();
    b = w.findChild<QPushButton*>("about");
    b->clicked();
    //b = w.findChild<QPushButton*>("load");
    //b->clicked();
    b = w.findChild<QPushButton*>("startgame");
    b->clicked();
    // b = w.findChild<QPushButton*>("pushButton");
    // b->clicked();
    
    b = w.findChild<QPushButton*>("home_quitgame");
    b->clicked();
    b = w.findChild<QPushButton*>("home_quitgame_2");
    b->clicked();
    b = w.findChild<QPushButton*>("pushButton_2");
    b->clicked();
}


QTEST_MAIN(TestPencilProducer)
#include "test.moc"
