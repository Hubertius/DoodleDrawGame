#ifndef GAMELOBBYHANDLER_H
#define GAMELOBBYHANDLER_H

#include <QObject>

class GameLobbyHandler : public QObject
{
    Q_OBJECT
private:
    QList<QString> m_gameClientsList;
public:
    explicit GameLobbyHandler(QObject *parent = nullptr);
    void addClientID(QString clientID);

signals:

};

#endif // GAMELOBBYHANDLER_H
