#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include <QObject>
#include "websockethandler.h"
#include "messageprocessor.h"

class GameManager : public QObject
{
    Q_OBJECT
private:
    WebSocketHandler * m_webSocketHandler;
    MessageProcessor * m_messageProcessHandler;
public:
    explicit GameManager(QObject *parent = nullptr);
    ~GameManager();
signals:

};

#endif // GAMEMANAGER_H
