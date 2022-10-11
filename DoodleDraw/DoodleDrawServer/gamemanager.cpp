#include "gamemanager.h"

GameManager::GameManager(QObject *parent)
    : QObject{parent}
{
    m_webSocketHandler = new WebSocketHandler(this);
}

GameManager::~GameManager()
{
    m_webSocketHandler->deleteLater();
}
