#include "websockethandler.h"
#include <QDebug>
#include <random>
#include <QRandomGenerator>

const QMap<QString, QWebSocket *> &WebSocketHandler::getClientsList() const
{
    return m_clientsList;
}

WebSocketHandler::WebSocketHandler(QObject *parent)
    : QObject{parent}
{
//    m_serverSocketToDatabase = new QWebSocket;
//    connect(m_serverSocketToDatabase, &QWebSocket::connected, this, &WebSocketHandler::onConnected);
//    connect(m_serverSocketToDatabase, &QWebSocket::textMessageReceived, this, &WebSocketHandler::onDatabaseTextMessageReceived);

    m_socketServer = new QWebSocketServer("DoodleDrawServer", QWebSocketServer::NonSecureMode, this);
    if(m_socketServer->listen(QHostAddress::Any, 800))
        qDebug() << "Server is running!";
    else
        qDebug() << "Server unable to start listening for connections";
    connect(m_socketServer, &QWebSocketServer::newConnection, this, &WebSocketHandler::onNewClientSocketConnection);

}

void WebSocketHandler::sendTextMessageToClient(QString message, QString clientID)
{
    if(m_clientsList.contains(clientID))
        m_clientsList[clientID]->sendTextMessage(message);
}

void WebSocketHandler::sendTextMessageToMultipleClients(QString message, QStringList clientsIDsList)
{
    foreach(const QString & clientID, clientsIDsList)
    {
        sendTextMessageToClient(message, clientID);
    }
}

WebSocketHandler::~WebSocketHandler()
{
    m_socketServer->deleteLater();
}

void WebSocketHandler::WebSocketHandler::onNewClientSocketConnection()
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
    connect(nextClient, &QWebSocket::textMessageReceived, this, &WebSocketHandler::onClientTextMessageReceived);
    connect(nextClient, &QWebSocket::disconnected, this, &WebSocketHandler::onClientSocketDisconnect);
    connect(nextClient, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error), this, &WebSocketHandler::onClientSocketDisconnect);
    nextClient->setParent(this);

    nextClient->sendTextMessage("type:uniqueID;payload:" + newClientId);

    m_clientsList[newClientId] = nextClient;
}

void WebSocketHandler::WebSocketHandler::onClientTextMessageReceived(QString messageReceived)
{
    qDebug() << "Received new client message: " << messageReceived;
    emit newMessageToProcess(messageReceived);
}

void WebSocketHandler::onClientSocketDisconnect()
{
    auto clientToDisconnect = qobject_cast<QWebSocket *>(sender());
    if(clientToDisconnect)
    {
        for(QMap<QString, QWebSocket *>::iterator itr = m_clientsList.begin(); itr != m_clientsList.end(); ++itr)
        {
            if(itr.value() == clientToDisconnect)
            {
                qDebug() << "Server app: client socket deleted and removed from list of clients!";
                m_clientsList.remove(itr.key());
                clientToDisconnect->deleteLater();
            }
        }
    }
}
