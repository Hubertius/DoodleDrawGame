#include "gamemanager.h"
#include <QDebug>
GameManager::GameManager(QObject *parent)
    : QObject{parent}
    , m_roomLobbyCode{QString()}
    , m_clientID{QString()}
{
    m_messageProcessHandler = new MessageProcessorHandler(this);
    connect(m_messageProcessHandler, &MessageProcessorHandler::newClientIdRegistration, this, &GameManager::registerClientID);
    connect(m_messageProcessHandler, &MessageProcessorHandler::newLobbyIdRegistration, this, &GameManager::joinLobby);
}

void GameManager::createGameRequest()
{
    emit newMessageToSend("type:createGame;payload:0;sender:" + m_clientID);
}

QString GameManager::getRoomLobbyCode()
{
    qDebug() << "Client App (GameManager). Get Lobby code: " << m_roomLobbyCode;
    return m_roomLobbyCode;
}

void GameManager::setRoomLobbyCode(QString lobbyCode)
{
    if(m_roomLobbyCode != lobbyCode)
        m_roomLobbyCode = lobbyCode;
    qDebug() << "Client App (GameManager). Set Lobby code: " << lobbyCode;
}

void GameManager::processSocketMessage(QString message)
{
    m_messageProcessHandler->processMessage(message);
}

void GameManager::registerClientID(QString clientID)
{
    qDebug() << "Client App. Registering client id";
    m_clientID = clientID;
}

void GameManager::joinLobby(QString lobbyCode)
{
    setRoomLobbyCode(lobbyCode);
    emit changeOfGameLobby();
}

GameManager::~GameManager()
{
    m_messageProcessHandler->deleteLater();
}
