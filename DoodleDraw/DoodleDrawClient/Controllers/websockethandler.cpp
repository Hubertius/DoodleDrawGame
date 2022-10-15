#include "websockethandler.h"
#include <QDebug>

WebSocketHandler::WebSocketHandler(QObject *parent)
    : QObject{parent}
{
    m_clientSocket = new QWebSocket;

    connect(m_clientSocket, &QWebSocket::connected, this, &WebSocketHandler::onConnected);
    connect(m_clientSocket, &QWebSocket::textMessageReceived, this, &WebSocketHandler::onTextMessageReceived);

}

void WebSocketHandler::connectToServer(QString hostAddress)
{
    qDebug() << "Client App. Connecting to Server." << hostAddress;
    m_clientSocket->open(hostAddress);
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
    emit newMessageToProcess(messageReceived);
}

void WebSocketHandler::sendMessageToServer(QString message)
{
    m_clientSocket->sendTextMessage(message);
}

WebSocketHandler::~WebSocketHandler()
{
    m_clientSocket->deleteLater();
}
