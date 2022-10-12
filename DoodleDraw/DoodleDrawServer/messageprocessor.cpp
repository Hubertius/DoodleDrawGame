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
    //type:message;payload:HelloWorld;sender:5555
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
            emit createGameRequest(senderID);
        }

    }
    else if(separatedInfos.first() == "type:joinGame")
    {
        qDebug() << "Join game request";
    }
    else if(separatedInfos.first() == "type:message")
    {
        qDebug() << "Message request";
    }

}
