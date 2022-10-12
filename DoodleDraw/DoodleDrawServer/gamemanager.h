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
public:
    explicit GameManager(QObject *parent = nullptr);
    ~GameManager();
public slots:
    void createGameLobbyRequest(QString clientID);
    void joinGameLobbyRequest(QString lobbyID, QString clientID);
signals:

};

#endif // GAMEMANAGER_H
