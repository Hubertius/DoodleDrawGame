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
    void createGameLobbyRequest(QString clientID);
    void joinGameLobbyRequest(QString lobbyID, QString clientID);
    void messageLobbyRequest(QString messageContent, QString lobbyID, QString clientID);
    void userReadyToPlay(QString clientID);
    void clientNewDoodleDrawing(QString fileData, QString clientID);
    void clientFinishedDrawWork(QString fileData, QString clientID);
    void newVote(QString vote, QString clientID);
};

#endif // MESSAGEPROCESSOR_H
