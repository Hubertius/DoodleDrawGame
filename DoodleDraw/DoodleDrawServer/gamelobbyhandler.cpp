#include "gamelobbyhandler.h"

GameLobbyHandler::GameLobbyHandler(QObject *parent)
    : QObject{parent}
{

}

void GameLobbyHandler::addClientID(QString clientID)
{
    if(!m_gameClientsList.contains(clientID))
        m_gameClientsList.append(clientID);

}
