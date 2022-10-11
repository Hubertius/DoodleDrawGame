#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <QObject>
#include <QWebSocket>

class WebSocketHandler : public QObject
{
    Q_OBJECT
private:
    QWebSocket * m_clientSocket;
public:
    explicit WebSocketHandler(QObject *parent = nullptr);
    Q_INVOKABLE void connectToServer(QString hostAddress);
    ~WebSocketHandler();

public slots:
    void onConnected();
    void onTextMessageReceived(QString messageReceived);

signals:

};

#endif // WEBSOCKETHANDLER_H
