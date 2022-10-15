#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <QObject>
#include <QWebSocket>

class WebSocketHandler : public QObject
{
    Q_OBJECT
private:
    QWebSocket * m_clientSocket;
    QString m_clientID;
public:
    explicit WebSocketHandler(QObject *parent = nullptr);
    Q_INVOKABLE void connectToServer(QString hostAddress);
    ~WebSocketHandler();

signals:
    void newMessageToProcess(QString messageToProcess);

public slots:
    void onConnected();
    void onTextMessageReceived(QString messageReceived);
    void sendMessageToServer(QString message);
};

#endif // WEBSOCKETHANDLER_H
