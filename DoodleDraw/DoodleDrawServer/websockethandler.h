#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <QObject>
#include <QtWebSockets/QWebSocketServer>
#include <QtWebSockets/QWebSocket>
#include <QList>

class WebSocketHandler : public QObject
{
    Q_OBJECT
private:
    QWebSocketServer * m_socketServer;
    QWebSocket * m_serverSocketToDatabase;
    QMap<QString, QWebSocket  *> m_clientsList;
public:
    explicit WebSocketHandler(QObject *parent = nullptr);
    void sendTextMessageToClient(QString message, QString clientID);
    void sendTextMessageToMultipleClients(QString message, QStringList clientsIDsList);
    ~WebSocketHandler();

    const QMap<QString, QWebSocket *> &getClientsList() const;

signals:
    void newMessageToProcess(QString messageToProcess);
public slots:
    void onNewClientSocketConnection();
    void onClientTextMessageReceived(QString clientMessageReceived);
    void onClientSocketDisconnect();
};

#endif // WEBSOCKETHANDLER_H
