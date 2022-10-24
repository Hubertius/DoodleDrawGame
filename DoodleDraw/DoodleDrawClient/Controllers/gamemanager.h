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
    Q_PROPERTY(QStringList finishedDrawingsList READ getFinishedDrawingsList WRITE setFinishedDrawingsList NOTIFY finishedDrawingsListChanged)
    Q_PROPERTY(QString winnerClientID READ getWinnerClientID WRITE setWinnerClientID NOTIFY winnerClientIDChanged)
private:
    QString m_roomLobbyCode;
    QString m_clientID;
    QStringList m_lobbyClientsIDs;
    QStringList m_clientsReadineesList;
    QString m_drawingInstruction;
    QString m_winnerClientID;
    QStringList m_finishedDrawingList;
    bool m_isDrawingFinished;
    MessageProcessorHandler * m_messageProcessHandler;
    bool m_isVoteFinished;

public:
    explicit GameManager(QObject *parent = nullptr);
    Q_INVOKABLE void createGameRequest();
    Q_INVOKABLE void joinLobbyRequest(QString lobbyToJoinID);
    Q_INVOKABLE void sendMessageToLobby(QString messageToSend);
    Q_INVOKABLE bool isClientReady(QString clientID);
    Q_INVOKABLE void readyToPlay();
    Q_INVOKABLE void doodleDone();
    Q_INVOKABLE QString doodleFilePath();
    Q_INVOKABLE void voteOfUser(QString imageURL);
    Q_INVOKABLE QString getWinnerImager();
    ~GameManager();
    QString getRoomLobbyCode();
    QStringList getLobbyClientsIDs();
    QString getDrawingInstruction();
    QStringList getFinishedDrawingsList();
    QString getWinnerClientID();
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
    void finishedDrawingsListChanged();
    void votingTime();
    void winnerClientIDChanged();
    void gameOver();

public slots:
    void setRoomLobbyCode(QString lobbyCode);
    void setLobbyClientsIDs(QStringList newClientsOfLobbyList);
    void setDrawingInstruction(QString drawOrder);
    void setWinnerClientID(QString winnerClientID);
    void processSocketMessage(QString message);
    void registerClientID(QString clientID);
    void joinLobby(QString lobbyCode, QStringList clientsIDsList);
    void newClientsReadyList(QStringList updatedClientsListReadinees);
    void onClientReceivedDrawForContinuation(QString imageFileData, QString drawOrder);
    void onClientReceivedFinishedDraws(QStringList imagesData, QStringList clientsIDs);
    void setFinishedDrawingsList(QStringList finishedDrawingList);
    void onWinnerVoted(QString winnerClientID);
};

#endif // GAMEMANAGER_H
