#include "messageprocessorhandler.h"
#include <QDebug>

MessageProcessorHandler::MessageProcessorHandler(QObject *parent)
    : QObject{parent}
{

}

void MessageProcessorHandler::processMessage(QString messageFromServer)
{
    //type:uniqueID;payload:5555
    //type:lobbyCreated;payload:1111;clientsList:1234,4444,5555
    //type:lobbyJoinSuccessful;payload:1111
    //type:lobbyJoinFailed;payload:1111
    //type:updatedClientsList;payload:
    //type:message;payload:HelloWorld;sender:5555
    //type:readineesOfClientsChanged;payload:1234,4444
    //type:gameReadyToBegin;payload:1
    QStringList separatedInfos = messageFromServer.split(";");
    if(separatedInfos.first() == "type:uniqueID")
    {
        qDebug() << "Client App. Unique Client ID registration";
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
        QString createdLobbyID = QString();
        QStringList lobbyClients = QStringList();
        if(separatedInfos.first().contains("payload:"))
        {
            createdLobbyID = separatedInfos.first().remove("payload:");
        }
        separatedInfos.pop_front();
        if(separatedInfos.first().contains("clientsList:"))
        {
            QString clients = separatedInfos.first().remove("clientsList:");
            lobbyClients = clients.split(",");
        }
        qDebug() << "Client App. Clients in lobby: " << lobbyClients;
        if(createdLobbyID != QString() && !lobbyClients.isEmpty())
            emit newLobby(createdLobbyID, lobbyClients);

    }
    else if(separatedInfos.first().contains("type:updatedClientsList"))
    {
        qDebug() << "Client App. Updating for client info about other clients";
        separatedInfos.pop_front();
        QStringList updatedLobbyClients = QStringList();
        if(separatedInfos.first().contains("payload:"))
        {
            separatedInfos.first().remove("payload:");
            updatedLobbyClients = separatedInfos.first().split(",");
        }
        qDebug() << "Client App. Updated info list of clients for lobby: " << updatedLobbyClients;
        emit updatedClientsList(updatedLobbyClients);

    }
    else if(separatedInfos.first().contains("type:message"))
    {
        //type:message;payload:HelloWorld;sender:5555
        separatedInfos.pop_front();
        QString message = QString();
        QString senderID = QString();
        if(separatedInfos.first().contains("payload:"))
        {
            message = separatedInfos.first().remove("payload:");
            qDebug() << "Client App. Message received to display: " << message;
            separatedInfos.pop_front();
            if(separatedInfos.first().contains("sender:"))
            {
               senderID = separatedInfos.first().remove("sender:");
               emit newMessageForLobby(senderID + ": " + message);
            }
        }
    }
    else if(separatedInfos.first().contains("type:readineesOfClientsChanged"))
    {
         separatedInfos.pop_front();
         QString clientsReady = QString();
         if(separatedInfos.first().contains("payload:"))
         {
             clientsReady = separatedInfos.first().remove("payload:");
             if(clientsReady != QString())
             {
                QStringList clientsReadyList = clientsReady.split(",");
                emit newClientsReadyList(clientsReadyList);
             }
         }
    }
    else if(separatedInfos.first().contains("type:gameReadyToBegin"))
    {
        emit newGameBegins();
    }

}
