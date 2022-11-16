#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSql>
#include "websockethandler.h"
#include "messageprocessor.h"
#include "gamelobbyhandler.h"

class GameManager : public QObject
{
    Q_OBJECT
private:
    WebSocketHandler * m_webSocketHandler;
    MessageProcessor * m_messageProcessHandler;
    QSqlDatabase m_sqlDatabase;
    QMap<QString, GameLobbyHandler *> m_gameLobbys;
    QStringList m_drawingTypes;
public:
    explicit GameManager(QObject *parent = nullptr);
    const QString& generateSthForDrawing();
    ~GameManager();
public slots:
    void onLoginCheckDataRequest(QString clientID, QString name, QString password);
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
    void onNewVote(QString vote, QString clientID);
    void onAllClientsVoted(QString winnerClientID);
signals:

};

#endif // GAMEMANAGER_H
