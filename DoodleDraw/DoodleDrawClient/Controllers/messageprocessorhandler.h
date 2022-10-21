#ifndef MESSAGEPROCESSORHANDLER_H
#define MESSAGEPROCESSORHANDLER_H

#include <QObject>

class MessageProcessorHandler : public QObject
{
    Q_OBJECT
public:
    explicit MessageProcessorHandler(QObject *parent = nullptr);
    void processMessage(QString messageFromServer);
signals:
    void newClientIdRegistration(QString idOfClient);
    void newLobby(QString lobbyID, QStringList clients);
    void updatedClientsList(QStringList updatedClientsIDs);
    void newMessageForLobby(QString messageForDisplay);
    void newClientsReadyList(QStringList readyClientsList);
    void newGameBegins();
};

#endif // MESSAGEPROCESSORHANDLER_H
