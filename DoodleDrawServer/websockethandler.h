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
    QList<QWebSocket *> m_clientsList;
public:
    explicit WebSocketHandler(QObject *parent = nullptr);
    ~WebSocketHandler();

signals:

public slots:
    void onNewSocketConnection();
    void onTextMessageRecevied(QString messageReceived);
    void onSocketDisconnect();
};

#endif // WEBSOCKETHANDLER_H
