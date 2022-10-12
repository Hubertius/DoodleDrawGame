#include "gamemanager.h"


GameManager::GameManager(QObject *parent)
    : QObject{parent}
{
    m_webSocketHandler = new WebSocketHandler(this);
    m_messageProcessHandler = new MessageProcessor(this);
    connect(m_webSocketHandler, &WebSocketHandler::newMessageToProcess, m_messageProcessHandler, &MessageProcessor::processMessage);
}

GameManager::~GameManager()
{
    m_webSocketHandler->deleteLater();
}
