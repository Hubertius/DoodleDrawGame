#include "websockethandler.h"
#include <QDebug>
#include <random>
#include <QRandomGenerator>

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
    std::random_device rd;

    std::uniform_int_distribution<int> idGenerator(1000, 9999);
    QString newClientId = QString::number(idGenerator(*QRandomGenerator::global()));

    while(m_clientsList.keys().contains(newClientId))
    {
        newClientId = QString::number(idGenerator(*QRandomGenerator::global()));
    }
    qDebug() << "New client ID: " << newClientId;
    auto nextClient = m_socketServer->nextPendingConnection();
    connect(nextClient, &QWebSocket::textMessageReceived, this, &WebSocketHandler::onTextMessageRecevied);
    connect(nextClient, &QWebSocket::disconnected, this, &WebSocketHandler::onSocketDisconnect);

    nextClient->setParent(this);

    m_clientsList[newClientId] = nextClient;
}

void WebSocketHandler::onTextMessageRecevied(QString messageReceived)
{
    qDebug() << "Received new client message: " << messageReceived;
}

void WebSocketHandler::onSocketDisconnect()
{
    auto clientToDisconnect = qobject_cast<QWebSocket *>(sender());
    if(clientToDisconnect)
    {
        for(QMap<QString, QWebSocket *>::iterator itr = m_clientsList.begin(); itr != m_clientsList.end(); ++itr)
        {
            if(itr.value() == clientToDisconnect)
                m_clientsList.remove(itr.key());
            clientToDisconnect->deleteLater();
        }
    }
}
