#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "Controllers/messageprocessorhandler.h"

class GameManager : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString roomLobbyCode READ getRoomLobbyCode WRITE setRoomLobbyCode NOTIFY roomLobbyCodeChanged)
    Q_PROPERTY(QStringList lobbyClientsIDs READ getLobbyClientsIDs WRITE setLobbyClientsIDs NOTIFY lobbyClientsIDsChanged)
    Q_PROPERTY(QString drawingInstruction READ getDrawingInstruction WRITE setDrawingInstruction NOTIFY newDrawingInstruction)
private:
    QString m_roomLobbyCode;
    QString m_clientID;
    QStringList m_lobbyClientsIDs;
    QStringList m_clientsReadineesList;
    QString m_drawingInstruction;
    bool m_isDrawingFinished;
    MessageProcessorHandler * m_messageProcessHandler;

public:
    explicit GameManager(QObject *parent = nullptr);
    Q_INVOKABLE void createGameRequest();
    Q_INVOKABLE void joinLobbyRequest(QString lobbyToJoinID);
    Q_INVOKABLE void sendMessageToLobby(QString messageToSend);
    Q_INVOKABLE bool isClientReady(QString clientID);
    Q_INVOKABLE void readyToPlay();
    Q_INVOKABLE void doodleDone();
    Q_INVOKABLE QString doodleFilePath();
    ~GameManager();
    QString getRoomLobbyCode();
    QStringList getLobbyClientsIDs();
    QString getDrawingInstruction();

signals:
    void roomLobbyCodeChanged();
    void newMessageToSend(QString messageToSend);
    void changeOfGameLobby();
    void lobbyClientsIDsChanged();
    void newDrawingInstruction();
    void newMessageForLobby(QString messageForDisplaying);
    void updatedClientsListReadinees();
    void newGameBegins();
    void clientDrawingForAddedImageStarted();

public slots:
    void setRoomLobbyCode(QString lobbyCode);
    void setLobbyClientsIDs(QStringList newClientsOfLobbyList);
    void setDrawingInstruction(QString drawOrder);
    void processSocketMessage(QString message);
    void registerClientID(QString clientID);
    void joinLobby(QString lobbyCode, QStringList clientsIDsList);
    void newClientsReadyList(QStringList updatedClientsListReadinees);
    void onClientReceivedDrawForContinuation(QString imageFileData, QString drawOrder);
};

#endif // GAMEMANAGER_H
