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
   m_clientSocket->sendTextMessage("Hello World!");
}

void WebSocketHandler::onTextMessageReceived(QString messageReceived)
{
    qDebug() << "Client App. Received message: " << messageReceived;
}

WebSocketHandler::~WebSocketHandler()
{
    m_clientSocket->deleteLater();
}
