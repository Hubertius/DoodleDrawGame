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
    void uniqueIDRegistration(QString idOfClient);
};

#endif // MESSAGEPROCESSORHANDLER_H
