#ifndef GAMELOBBYHANDLER_H
#define GAMELOBBYHANDLER_H

#include <QObject>
#include <QMap>

class GameLobbyHandler : public QObject
{
    Q_OBJECT
private:
    QString m_gameLobbyID;
    QList<QString> m_gameLobbyClientsList;
    QMap<QString, bool> m_clientsReadiness;
    QMap<QString, QString> m_clientsDoodlesData;
    QMap<QString, QString> m_clientsFinishedDraws;
public:
    explicit GameLobbyHandler(QString gameID, QObject *parent = nullptr);
    void addClientID(QString clientID);
    void userReadyToPlay(QString clientID);
    void clientNewDoodleDraw(QString fileData, QString clientID);
    void clientFinishedDrawing(QString fileData, QString clientID);
    QString getGameLobbyClientsAsString() const;
    QList<QString> getGameLobbyClientsAsList() const;
    QString getTrueReadineesOfClients();

signals:
    void usersReadineesChanged();
    void gameReadyToBegin();
    void allClientsSendDoodleDraws(QMap<QString, QString> distrubutedDraws);
    void allClientsSendFinishedDraws(QMap<QString, QString> clientsFinishedDraws);
};

#endif // GAMELOBBYHANDLER_H
