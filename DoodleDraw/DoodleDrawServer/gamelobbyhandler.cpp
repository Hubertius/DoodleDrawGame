#include "gamelobbyhandler.h"


GameLobbyHandler::GameLobbyHandler(QString gameID, QObject *parent)
    : QObject{parent}
    , m_gameLobbyID{gameID}
{

}

void GameLobbyHandler::addClientID(QString clientID)
{
    if(!m_gameLobbyClientsList.contains(clientID))
        m_gameLobbyClientsList.append(clientID);

}

QString GameLobbyHandler::getGameLobbyClientsAsString() const
{
    QString clientsIDs = QString();
    foreach(const QString & clientID, m_gameLobbyClientsList)
    {
        clientsIDs.append(clientID + ",");
    }
    clientsIDs.chop(1);
    return clientsIDs;
}

QList<QString> GameLobbyHandler::getGameLobbyClientsAsList() const
{
    return m_gameLobbyClientsList;
}
