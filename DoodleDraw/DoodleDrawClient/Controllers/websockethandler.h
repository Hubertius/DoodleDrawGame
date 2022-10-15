#ifndef WEBSOCKETHANDLER_H
#define WEBSOCKETHANDLER_H

#include <QObject>
#include <QWebSocket>
#include "Controllers/messageprocessorhandler.h"

class WebSocketHandler : public QObject
{
    Q_OBJECT
private:
    QWebSocket * m_clientSocket;
    MessageProcessorHandler * m_messageProcessorHandler;
    QString m_clientID;
public:
    explicit WebSocketHandler(QObject *parent = nullptr);
    Q_INVOKABLE void connectToServer(QString hostAddress);
    Q_INVOKABLE void createGameRequest();
    void registerID(QString idToRegister);
    ~WebSocketHandler();

public slots:
    void onConnected();
    void onTextMessageReceived(QString messageReceived);

signals:

};

#endif // WEBSOCKETHANDLER_H
