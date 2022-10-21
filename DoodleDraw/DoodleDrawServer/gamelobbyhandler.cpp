#include "gamelobbyhandler.h"


GameLobbyHandler::GameLobbyHandler(QString gameID, QObject *parent)
    : QObject{parent}
    , m_gameLobbyID{gameID}
{
    m_clientsReadiness.clear();
}

void GameLobbyHandler::addClientID(QString clientID)
{
    if(!m_gameLobbyClientsList.contains(clientID))
    {
        m_gameLobbyClientsList.append(clientID);
        m_clientsReadiness[clientID] = false;
    }
    emit usersReadineesChanged();
}

void GameLobbyHandler::userReadyToPlay(QString clientID)
{
    if(m_gameLobbyClientsList.contains(clientID))
    {
        m_clientsReadiness[clientID] = true;
        emit usersReadineesChanged();

    }
    bool notAllReady = false;
    foreach(const QString & clientID, m_clientsReadiness.keys())
    {
        if(!m_clientsReadiness[clientID])
            notAllReady = true;
    }

    if(!notAllReady)
        emit gameReadyToBegin();
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

QString GameLobbyHandler::getTrueReadineesOfClients()
{
    QString clientsReadineesTrue = QString();
    foreach(const QString & client, m_gameLobbyClientsList)
    {
        if(m_clientsReadiness[client])
            clientsReadineesTrue += client + ",";
    }
    if(clientsReadineesTrue != QString())
        clientsReadineesTrue.chop(1);
    return clientsReadineesTrue;
}
