#include "gamelobbyhandler.h"


GameLobbyHandler::GameLobbyHandler(QString gameID, QObject *parent)
    : QObject{parent}
    , m_gameLobbyID{gameID}
{
    m_clientsReadiness.clear();
    m_clientsDoodlesData.clear();
    m_clientsFinishedDraws.clear();
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

void GameLobbyHandler::clientNewDoodleDraw(QString fileData, QString clientID)
{
    if(m_gameLobbyClientsList.contains(clientID))
        m_clientsDoodlesData[clientID] = fileData;
    QList<QString> m_doodleDrawsClientsIDs = m_clientsDoodlesData.keys();
    if(m_doodleDrawsClientsIDs.size() == m_gameLobbyClientsList.size())
    {
        QMap<QString, QString> distrubutedDraws;
        for(int index = 0; index < m_doodleDrawsClientsIDs.size(); ++index)
        {
            QString client = m_gameLobbyClientsList.at(index);
            QString doodle;

            if(index == m_gameLobbyClientsList.size() - 1)
                doodle = m_clientsDoodlesData[m_gameLobbyClientsList.at(0)];
            else
                doodle = m_clientsDoodlesData[m_gameLobbyClientsList.at(index+1)];
            distrubutedDraws[client] = doodle;
        }
        emit allClientsSendDoodleDraws(distrubutedDraws);

    }
}

void GameLobbyHandler::clientFinishedDrawing(QString fileData, QString clientID)
{
    if(m_gameLobbyClientsList.contains(clientID))
        m_clientsFinishedDraws[clientID] = fileData;
    if(m_clientsFinishedDraws.keys().size() == m_gameLobbyClientsList.size())
        emit allClientsSendFinishedDraws(m_clientsFinishedDraws);
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
