#include "messageprocessorhandler.h"
#include <QDebug>

MessageProcessorHandler::MessageProcessorHandler(QObject *parent)
    : QObject{parent}
{

}

void MessageProcessorHandler::processMessage(QString messageFromServer)
{
    //type:uniqueID;payload:5555
    QStringList separatedInfos = messageFromServer.split(";");
    if(separatedInfos.first() == "type:uniqueID")
    {
        qDebug() << "Client App. Unique ID registration";
        separatedInfos.pop_front();
        if(separatedInfos.first().contains("payload:"))
        {
            QString newClientId = separatedInfos.first();
            newClientId = newClientId.remove("payload:");
            emit uniqueIDRegistration(newClientId);
        }
    }

}
