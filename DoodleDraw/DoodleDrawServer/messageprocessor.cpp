#include "messageprocessor.h"
#include <QDebug>

MessageProcessor::MessageProcessor(QObject *parent)
    : QObject{parent}
{

}

void MessageProcessor::MessageProcessor::processClientMessage(QString messageFromClient)
{
    qDebug() << "Server App. Message to process: " << messageFromClient;
    //type:login;payload:0;sender:5555;user:....;password:...
    //type:createGame;payload:0;sender:5555
    //type:joinGame;payload:4000;sender:5555 -> payload as game code
    //type:message;payload:HelloWorld;lobbyID:9999;sender:5555
    //type:readyToPlay;payload:1;sender:5555
    //type:doodleData;payload:imageContent;sender:5555
    QStringList separatedInfos = messageFromClient.split(";");
    if(separatedInfos.first() == "type:login")
    {
        qDebug() << "Client login request";
        separatedInfos.pop_front();
        separatedInfos.pop_front();
        if(separatedInfos.first().contains("sender:"))
        {
            QString clientID = separatedInfos.first().remove("sender:");
            separatedInfos.pop_front();
            if(separatedInfos.first().contains("user:") && separatedInfos.last().contains("password:"))
            {
                QString userName = separatedInfos.first().remove("user:");
                QString userPassword = separatedInfos.last().remove("password:");
                emit loginRequest(clientID, userName, userPassword);
            }
        }
    }
    else if(separatedInfos.first() == "type:createGame")
    {
        qDebug() << "Create game request";
        separatedInfos.pop_front();
        separatedInfos.pop_front();
        if(separatedInfos.first().contains("sender:"))
        {
            QString senderID = separatedInfos.first().remove("sender:");
            emit createGameLobbyRequest(senderID);
        }

    }
    else if(separatedInfos.first() == "type:joinGame")
    {
        qDebug() << "Join game request";
        separatedInfos.pop_front();
        QString lobbyID = QString();
        QString senderID = QString();
        if(separatedInfos.first().contains("payload:"))
        {
            lobbyID = separatedInfos.first().remove("payload:");
            separatedInfos.pop_front();
            if(separatedInfos.first().contains("sender:"))
            {
                senderID = separatedInfos.first().remove("sender:");
                if(lobbyID != QString() && senderID != QString())
                    emit joinGameLobbyRequest(lobbyID, senderID);
            }
        }
    }
    else if(separatedInfos.first() == "type:message")
    {
        // message to lobby
        //type:message;payload:HelloWorld;lobbyID:9999;sender:5555
        qDebug() << "Server App. Lobby Message request";
        separatedInfos.pop_front();
        QString messageContent = QString();
        QString lobbyID = QString();
        QString senderID = QString();
        if(separatedInfos.first().contains("payload:"))
        {
            messageContent = separatedInfos.first().remove("payload:");
            separatedInfos.pop_front();
            if(separatedInfos.first().contains("lobbyID:"))
            {
                lobbyID = separatedInfos.first().remove("lobbyID:");
                separatedInfos.pop_front();
                if(separatedInfos.first().contains("sender:"))
                {
                    senderID = separatedInfos.first().remove("sender:");
                    if(messageContent != QString() && lobbyID != QString() && senderID != QString())
                    {
                        qDebug() << "Server App. Before emiting message lobby request";
                        emit messageLobbyRequest(messageContent, lobbyID, senderID);
                    }
                }
            }
        }
    }
    else if(separatedInfos.first() == "type:readyToPlay")
    {
        qDebug() << "Server App. Client declared readinees in lobby";
        if(separatedInfos.back().contains("sender:"))
        {
            QString clientID = separatedInfos.back().remove("sender:");
            qDebug() << "Server App. Client declared readinees, his ID: " << clientID;
            emit userReadyToPlay(clientID);
        }
    }
    else if(separatedInfos.first() == "type:doodleDrawData")
    {
        QString fileData = QString();
        QString clientID = QString();
        separatedInfos.pop_front();
        if(separatedInfos.first().contains("payload:"))
        {
            fileData = separatedInfos.first().remove("payload:");
            separatedInfos.pop_front();
            if(separatedInfos.first().contains("sender:"))
            {
                clientID = separatedInfos.first().remove("sender:");
                if(fileData != QString() && clientID != QString())
                    emit clientNewDoodleDrawing(fileData, clientID);
            }
        }
    }

}
