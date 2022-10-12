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
    QMap<QString, QWebSocket  *> m_clientsList;
public:
    explicit WebSocketHandler(QObject *parent = nullptr);
    ~WebSocketHandler();

signals:
    void newMessageToProcess(QString messageToProcess);
public slots:
    void onNewSocketConnection();
    void onTextMessageRecevied(QString messageReceived);
    void onSocketDisconnect();
};

#endif // WEBSOCKETHANDLER_H
