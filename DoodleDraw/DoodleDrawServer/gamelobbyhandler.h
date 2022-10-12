#ifndef GAMELOBBYHANDLER_H
#define GAMELOBBYHANDLER_H

#include <QObject>

class GameLobbyHandler : public QObject
{
    Q_OBJECT
private:
    QString m_gameLobbyID;
    QList<QString> m_gameLobbyClientsList;
public:
    explicit GameLobbyHandler(QString gameID, QObject *parent = nullptr);
    void addClientID(QString clientID);

signals:

};

#endif // GAMELOBBYHANDLER_H
