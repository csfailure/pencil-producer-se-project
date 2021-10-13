#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QDebug>
#include <iostream>
#include <map>
#include <curl/curl.h>

class ScoreBoard {
public:
    ScoreBoard();
    ScoreBoard(QJsonObject);
    ~ScoreBoard();
    void refresh();
    void upload();
    std::multimap<int, QString> &fetch();

private:
    std::string ref_url = "https://matiusulung.com/se.json";
    std::string var_url;
    void setup();
    std::string getRequest(const std::string&);
    void postRequest(char*, char*, char*);
    std::multimap<int, QString> scoreMap;
};

#endif // SCOREBOARD_H
