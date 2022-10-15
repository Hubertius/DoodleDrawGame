#include "messageprocessorhandler.h"
#include <QDebug>

MessageProcessorHandler::MessageProcessorHandler(QObject *parent)
    : QObject{parent}
{

}

void MessageProcessorHandler::processMessage(QString messageFromServer)
{
    //type:uniqueID;payload:5555
    //type:lobbyCreated;payload:1111
    //type:lobbyJoinSuccessful;payload:1111
    //type:lobbyJoinFailed;payload:1111
    QStringList separatedInfos = messageFromServer.split(";");
    if(separatedInfos.first() == "type:uniqueID")
    {
        qDebug() << "Client App. Unique ID registration";
        separatedInfos.pop_front();
        if(separatedInfos.first().contains("payload:"))
        {
            QString newClientId = separatedInfos.first();
            newClientId = newClientId.remove("payload:");
            emit newClientIdRegistration(newClientId);
        }
    }
    else if(separatedInfos.first() == "type:lobbyCreated" || separatedInfos.first() == "type:lobbyJoinSuccessful")
    {
        qDebug() << "Client App. Client joined lobby";
        separatedInfos.pop_front();
        if(separatedInfos.first().contains("payload:"))
        {
            QString createdLobbyID = separatedInfos.first().remove("payload:");
            emit newLobbyIdRegistration(createdLobbyID);
        }
    }


}
