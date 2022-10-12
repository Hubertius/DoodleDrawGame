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
