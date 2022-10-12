#ifndef MESSAGEPROCESSOR_H
#define MESSAGEPROCESSOR_H

#include <QObject>

class MessageProcessor : public QObject
{
    Q_OBJECT
public:
    explicit MessageProcessor(QObject *parent = nullptr);
    void processMessage(QString messageFromClient);
signals:

};

#endif // MESSAGEPROCESSOR_H
