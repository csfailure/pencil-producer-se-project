#include "scoreboard.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QTextStream>
#include <QDebug>

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
    data->append((char*) ptr, size * nmemb);
    return size * nmemb;
}



ScoreBoard::ScoreBoard() {
    setup();
    QString response_string = QString::fromLocal8Bit(getRequest(var_url).c_str());
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response_string.toUtf8());
    QJsonObject json = jsonDoc.object();
    
    QJsonArray highscore = json["highscores"].toArray();

    // multimap is automatically sorted and is more stable
    QJsonArray::iterator it;
    for (it = highscore.begin(); it != highscore.end(); ++it) {
        int score = it->toObject()["score"].toInt();
        QString username = it->toObject()["game-username"].toString();
        scoreMap.insert(std::pair<int, QString>(score, username));
    }

    //qDebug() << response_string << "\n";
    //qDebug() << highscore[0];
}


ScoreBoard::ScoreBoard(QJsonObject json) {
    QJsonArray highscore = json["highscores"].toArray();

    // multimap is automatically sorted and more stable
    QJsonArray::iterator it;
    for (it = highscore.begin(); it != highscore.end(); ++it) {
        int score = it->toObject()["score"].toString().toInt();
        QString username = it->toObject()["game-username"].toString();
        scoreMap.insert(std::pair<int, QString>(score, username));
    }
}

ScoreBoard::~ScoreBoard() {}

void ScoreBoard::refresh() {
    QString response_string = QString::fromLocal8Bit(getRequest(var_url).c_str());
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response_string.toUtf8());
    QJsonObject json = jsonDoc.object();
    
    QJsonArray highscore = json["highscores"].toArray();

    scoreMap.clear();
    QJsonArray::iterator it;
    for (it = highscore.begin(); it != highscore.end(); ++it) {
        int score = it->toObject()["score"].toInt();
        QString username = it->toObject()["game-username"].toString();
        scoreMap.insert(std::pair<int, QString>(score, username));
    }    
}

void ScoreBoard::upload() {
    char *JACOBS_ID = std::getenv("JACOBS_ID");
    char *GAME_USERNAME = std::getenv("GAME_USERNAME");
    char *SE_TOKEN = std::getenv("SE_TOKEN");
    if(JACOBS_ID && GAME_USERNAME && SE_TOKEN) {
        postRequest(JACOBS_ID, GAME_USERNAME, SE_TOKEN);
    } else {
        qDebug() << QString("SESSION PARAMETER NOT SET");
    }
}

void ScoreBoard::setup() {
    QString response_string = QString::fromLocal8Bit(getRequest(ref_url).c_str());
    QJsonDocument jsonDoc = QJsonDocument::fromJson(response_string.toUtf8());
    QJsonObject link = jsonDoc.object();
    var_url = link["link"].toString().toLocal8Bit().constData();
    var_url += "/getscores";
}

std::string ScoreBoard::getRequest(const std::string &url) {
    CURL *curl = curl_easy_init();
    std::string response_string;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        
        std::string header_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
        
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl = NULL;
    }
    return response_string;
}

void ScoreBoard::postRequest(char *JACOBS_ID, char *GAME_USERNAME, char *SE_TOKEN) {
    CURL *curl = curl_easy_init();
    std::string response_string;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        curl_easy_setopt(curl, CURLOPT_URL, var_url.c_str());
        
        struct curl_slist *headers = NULL;
        curl_slist_append(headers, "Content-Type: application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

//        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "{\n    \"jacobs-id\": \"" + JACOBS_ID + "\",\n    \"se-token\": \"" + SE_TOKEN + "\",\n    \"game-username\": \"" + GAME_USERNAME + "\",\n    \"score\": 3000000\n}");

        std::string header_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);
        
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        curl = NULL;
    }    
}


std::multimap<int, QString> &ScoreBoard::fetch() {
    return scoreMap;
}
