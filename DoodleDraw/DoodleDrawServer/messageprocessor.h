#ifndef MESSAGEPROCESSOR_H
#define MESSAGEPROCESSOR_H

#include <QObject>

class MessageProcessor : public QObject
{
    Q_OBJECT
public:
    explicit MessageProcessor(QObject *parent = nullptr);
    void processClientMessage(QString messageFromClient);
signals:
    void loginRequest(QString clientID, QString name, QString password);
    void createGameRequest(QString clientID);
    void joinGameRequest(QString lobbyID, QString clientID);
};

#endif // MESSAGEPROCESSOR_H
