#include "websockethandler.h"
#include <QDebug>

WebSocketHandler::WebSocketHandler(QObject *parent)
    : QObject{parent}
{
    m_clientSocket = new QWebSocket;

    connect(m_clientSocket, &QWebSocket::connected, this, &WebSocketHandler::onConnected);
    connect(m_clientSocket, &QWebSocket::textMessageReceived, this, &WebSocketHandler::onTextMessageReceived);

    m_messageProcessorHandler = new MessageProcessorHandler(this);

    connect(m_messageProcessorHandler, &MessageProcessorHandler::newClientIdRegistration, this, &WebSocketHandler::registerID);

}

void WebSocketHandler::connectToServer(QString hostAddress)
{
    qDebug() << "Client App. Connecting to Server." << hostAddress;
    m_clientSocket->open(hostAddress);
}

void WebSocketHandler::createGameRequest()
{
    m_clientSocket->sendTextMessage("type:createGame;payload:0;sender:" + m_clientID);
}

void WebSocketHandler::registerID(QString idToRegister)
{
    m_clientID = idToRegister;
    qDebug() << "Unique client ID: " << m_clientID;
}

void WebSocketHandler::onConnected()
{
   qDebug() << "Client App. Connection established.";
   //m_clientSocket->sendTextMessage("type:createGame;payload:0;sender:" + m_clientID);
   //m_clientSocket->sendTextMessage("type:login;payload:0");
}

void WebSocketHandler::onTextMessageReceived(QString messageReceived)
{
    qDebug() << "Client App. Received message: " << messageReceived;
    m_messageProcessorHandler->processMessage(messageReceived);
}

WebSocketHandler::~WebSocketHandler()
{
    m_clientSocket->deleteLater();
}
