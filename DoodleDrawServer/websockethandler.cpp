#include "websockethandler.h"
#include <QDebug>

WebSocketHandler::WebSocketHandler(QObject *parent)
    : QObject{parent}
{
    m_socketServer = new QWebSocketServer("DoodleDrawServer", QWebSocketServer::NonSecureMode, this);
    if(m_socketServer->listen(QHostAddress::Any, 8585))
        qDebug() << "Server is running!";
    else
        qDebug() << "Server unable to start listening for connections";
    connect(m_socketServer, &QWebSocketServer::newConnection, this, &WebSocketHandler::onNewSocketConnection);

}

WebSocketHandler::~WebSocketHandler()
{
    m_socketServer->deleteLater();
}

void WebSocketHandler::onNewSocketConnection()
{
    qDebug() << "New client connected!";
    auto nextClient = m_socketServer->nextPendingConnection();

    connect(nextClient, &QWebSocket::textMessageReceived, this, &WebSocketHandler::onTextMessageRecevied);
    connect(nextClient, &QWebSocket::disconnected, this, &WebSocketHandler::onSocketDisconnect);

    nextClient->setParent(this);
    m_clientsList.append(nextClient);
}

void WebSocketHandler::onTextMessageRecevied(QString messageReceived)
{
    qDebug() << "Received new client message: " << messageReceived;
}

void WebSocketHandler::onSocketDisconnect()
{
    auto clientToDisconnect = qobject_cast<QWebSocket *>(sender());
    if(clientToDisconnect)
        m_clientsList.removeAll(clientToDisconnect);
}
