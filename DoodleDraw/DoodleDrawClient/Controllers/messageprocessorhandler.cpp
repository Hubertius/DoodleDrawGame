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
    //type:assignedDrawingData;payload:distrubutedDraws[clientID];drawOrder:drawingChosenForClients
    //type:otherClientsDrawingsForVote;payload:imageFile1,imageFil2,imageFile3;clients:
    //type:winner;payload:1111;sender:5555
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
    else if(separatedInfos.first() == "type:updatedClientsList")
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
    else if(separatedInfos.first() == "type:message")
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
    else if(separatedInfos.first() == "type:readineesOfClientsChanged")
    {
         qDebug() << "OVER HERE 1";
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
    else if(separatedInfos.first() == "type:gameReadyToBegin")
    {
        qDebug() << "OVER HERE 2";
        emit newGameBegins();
    }
    else if(separatedInfos.first() == "type:assignedDrawingData")
    {
        qDebug() << "Client App. Received image file data for client for drawing with instruction what to draw.";
        separatedInfos.pop_front();
        QString imageForDrawingData = QString();
        QString drawOrder = QString();
        if(separatedInfos.first().contains("payload:"))
        {
            imageForDrawingData = separatedInfos.first().remove("payload");
            separatedInfos.pop_front();
            if(separatedInfos.first().contains("drawOrder:"))
            {
                drawOrder = separatedInfos.first().remove("drawOrder:");
                if(imageForDrawingData != QString() && drawOrder != QString())
                    emit clientReceivedDrawForContinuation(imageForDrawingData, drawOrder);
            }
        }
    }
    else if(separatedInfos.first() == "type:otherClientsDrawingsForVote")
    {
        QString otherClientsFinishedDraws = QString();
        QString clientsIDs = QString();
        separatedInfos.pop_front();
        if(separatedInfos.first().contains("payload:"))
        {
            otherClientsFinishedDraws = separatedInfos.first().remove("payload");
            separatedInfos.pop_front();
            if(separatedInfos.first().contains("clients:"))
            {
                clientsIDs = separatedInfos.first().remove("clients:");
                if(otherClientsFinishedDraws != QString() && clientsIDs != QString())
                    emit clientReceivedFinishedDraws(otherClientsFinishedDraws.split(","), clientsIDs.split(","));
            }
        }
    }
    else if(separatedInfos.first() == "type:winner")
    {
        QString winnerClientID = QString();
        QString senderClientID = QString();
        separatedInfos.pop_front();
        if(separatedInfos.first().contains("payload:"))
        {
            winnerClientID = separatedInfos.first().remove("payload:");
            separatedInfos.pop_front();
            if(winnerClientID != QString())
            {
                emit winnerVoted(winnerClientID);
            }

        }
    }

}
