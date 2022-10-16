#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "Controllers/messageprocessorhandler.h"

class GameManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString roomLobbyCode READ getRoomLobbyCode WRITE setRoomLobbyCode NOTIFY roomLobbyCodeChanged)
    Q_PROPERTY(QStringList lobbyClientsIDs READ getLobbyClientsIDs WRITE setLobbyClientsIDs NOTIFY lobbyClientsIDsChanged)
private:
    QString m_roomLobbyCode;
    QString m_clientID;
    QStringList m_lobbyClientsIDs;
    MessageProcessorHandler * m_messageProcessHandler;

public:
    explicit GameManager(QObject *parent = nullptr);
    Q_INVOKABLE void createGameRequest();
    Q_INVOKABLE void joinLobbyRequest(QString lobbyToJoinID);
    ~GameManager();
    QString getRoomLobbyCode();
    QStringList getLobbyClientsIDs();

signals:
    void roomLobbyCodeChanged();
    void newMessageToSend(QString messageToSend);
    void changeOfGameLobby();
    void lobbyClientsIDsChanged();

public slots:
    void setRoomLobbyCode(QString lobbyCode);
    void setLobbyClientsIDs(QStringList newClientsOfLobbyList);
    void processSocketMessage(QString message);

    void registerClientID(QString clientID);
    void joinLobby(QString lobbyCode, QStringList clientsIDsList);
};

#endif // GAMEMANAGER_H
