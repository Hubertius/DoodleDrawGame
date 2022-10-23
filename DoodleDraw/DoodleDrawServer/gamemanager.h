#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "websockethandler.h"
#include "messageprocessor.h"
#include "gamelobbyhandler.h"

class GameManager : public QObject
{
    Q_OBJECT
private:
    WebSocketHandler * m_webSocketHandler;
    MessageProcessor * m_messageProcessHandler;
private:
    QMap<QString, GameLobbyHandler *> m_gameLobbys;
    QStringList m_drawingTypes;
public:
    explicit GameManager(QObject *parent = nullptr);
    const QString& generateSthForDrawing();
    ~GameManager();
public slots:
    void createGameLobbyRequest(QString clientID);
    void joinGameLobbyRequest(QString lobbyID, QString clientID);
    void messageLobbyRequest(QString messageContent, QString lobbyID, QString clientID);
    void usersReadineesChanged();
    void userReadyToPlay(QString clientID);
    void gameReadyToBegin();
    void onClientNewDoodleDrawing(QString fileData, QString clientID);
    void onAllClientsSendDoodleDraws(QMap<QString, QString> distrubutedDraws);
    void onClientFinishedDrawWork(QString fileData, QString clientID);
    void onAllClientsSendFinishedDraws(QMap<QString, QString> clientsFinishedDraws);
signals:

};

#endif // GAMEMANAGER_H
