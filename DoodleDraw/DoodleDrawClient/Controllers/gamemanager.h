#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "Controllers/messageprocessorhandler.h"

class GameManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString roomLobbyCode READ getRoomLobbyCode WRITE setRoomLobbyCode NOTIFY roomLobbyCodeChanged)
private:
    QString m_roomLobbyCode;
    QString m_clientID;
    MessageProcessorHandler * m_messageProcessHandler;

public:
    explicit GameManager(QObject *parent = nullptr);
    Q_INVOKABLE void createGameRequest();
    ~GameManager();
    QString getRoomLobbyCode();

signals:
    void roomLobbyCodeChanged();
    void newMessageToSend(QString messageToSend);
    void changeOfGameLobby();

public slots:
    void setRoomLobbyCode(QString lobbyCode);
    void processSocketMessage(QString message);
    void registerClientID(QString clientID);
    void joinLobby(QString lobbyCode);
};

#endif // GAMEMANAGER_H
