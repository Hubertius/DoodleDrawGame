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

    ~WebSocketHandler();

signals:
    void newMessageToProcess(QString messageToProcess);
    void sendTextMessageToClient(QString message, QString clientID);
public slots:
    void onNewClientSocketConnection();
    void onClientTextMessageReceived(QString clientMessageReceived);
    void onClientSocketDisconnect();

    void onLoginCheckDataRequest(QString clientID, QString name, QString password);
    void onDatabaseTextMessageReceived(QString databaseMessageReceived);
};

#endif // WEBSOCKETHANDLER_H
