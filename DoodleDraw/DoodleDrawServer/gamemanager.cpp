#include "gamemanager.h"
#include <random>
#include <QRandomGenerator>

GameManager::GameManager(QObject *parent)
    : QObject{parent}
{
    m_webSocketHandler = new WebSocketHandler(this);
    m_messageProcessHandler = new MessageProcessor(this);
    connect(m_webSocketHandler, &WebSocketHandler::newMessageToProcess, m_messageProcessHandler, &MessageProcessor::MessageProcessor::processClientMessage);
    connect(m_messageProcessHandler, &MessageProcessor::loginRequest, m_webSocketHandler, &WebSocketHandler::onLoginCheckDataRequest);

    connect(m_messageProcessHandler, &MessageProcessor::createGameLobbyRequest, this, &GameManager::createGameLobbyRequest);
    connect(m_messageProcessHandler, &MessageProcessor::joinGameLobbyRequest, this, &GameManager::joinGameLobbyRequest);
}

GameManager::~GameManager()
{
    m_webSocketHandler->deleteLater();
}

void GameManager::createGameLobbyRequest(QString clientID)
{
    std::random_device rd;

    std::uniform_int_distribution<int> idGenerator(1000, 9999);
    QString newGameID = QString::number(idGenerator(*QRandomGenerator::global()));

    while(m_gameLobbys.keys().contains(newGameID))
    {
        newGameID = QString::number(idGenerator(*QRandomGenerator::global()));
    }
    GameLobbyHandler * m_gameLobby = new GameLobbyHandler(newGameID, this);
    m_gameLobby->addClientID(clientID);
    m_gameLobbys[newGameID] = m_gameLobby;
}

void GameManager::joinGameLobbyRequest(QString lobbyID, QString clientID)
{
    if(m_gameLobbys.contains(lobbyID))
        m_gameLobbys[lobbyID]->addClientID(clientID);
    else
        m_webSocketHandler->sendTextMessageToClient("type:joinLobbyError:payload:" + lobbyID,clientID);
}
