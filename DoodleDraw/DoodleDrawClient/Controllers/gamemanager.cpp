#include "gamemanager.h"
#include <QDebug>
#include <QFile>
#include <QDir>

GameManager::GameManager(QObject *parent)
    : QObject{parent}
    , m_roomLobbyCode{QString()}
    , m_clientID{QString()}
    , m_lobbyClientsIDs(QStringList())
    , m_clientsReadineesList(QStringList())
    , m_drawingInstruction(QString())
{
    m_messageProcessHandler = new MessageProcessorHandler(this);
    connect(m_messageProcessHandler, &MessageProcessorHandler::newClientIdRegistration, this, &GameManager::registerClientID);
    connect(m_messageProcessHandler, &MessageProcessorHandler::newLobby, this, &GameManager::joinLobby);
    connect(m_messageProcessHandler, &MessageProcessorHandler::updatedClientsList, this, &GameManager::setLobbyClientsIDs);
    connect(m_messageProcessHandler, &MessageProcessorHandler::newMessageForLobby, this, &GameManager::newMessageForLobby);
    connect(m_messageProcessHandler, &MessageProcessorHandler::newClientsReadyList, this, &GameManager::newClientsReadyList);
    connect(m_messageProcessHandler, &MessageProcessorHandler::newGameBegins, this, &GameManager::newGameBegins);
    connect(m_messageProcessHandler, &MessageProcessorHandler::clientReceivedDrawForContinuation, this, &GameManager::onClientReceivedDrawForContinuation);
}

void GameManager::createGameRequest()
{
    emit newMessageToSend("type:createGame;payload:0;sender:" + m_clientID);
}

void GameManager::joinLobbyRequest(QString lobbyToJoinID)
{
    emit newMessageToSend("type:joinGame;payload:" + lobbyToJoinID + ";sender:" + m_clientID);
}

void GameManager::sendMessageToLobby(QString messageToSend)
{
    qDebug() << "Message to send for server (m_roomLobbyCode): " << m_roomLobbyCode;
    emit newMessageToSend("type:message;payload:"+ messageToSend + ";lobbyID:" + m_roomLobbyCode + ";sender:" + m_clientID);
}

bool GameManager::isClientReady(QString clientID)
{
    return m_clientsReadineesList.contains(clientID);
}

void GameManager::readyToPlay()
{
    emit newMessageToSend("type:readyToPlay;payload:1;sender:" + m_clientID);
}

void GameManager::doodleDone()
{
    // opening image file done by client
    // loading it into QByteArray
    // send data to server
    QFile clientImageFIle(QDir::currentPath() + "/../../DoodleDraw/DoodleDrawClient/ui/tmp.png");
    if(!clientImageFIle.open(QIODevice::ReadOnly))
        return;
    QByteArray imageContent = clientImageFIle.readAll();
    clientImageFIle.close();

    //type:doodleDrawData;payload:imageContent;sender:clientID
    emit newMessageToSend("type:doodleDrawData;payload:" + imageContent.toHex() + ";sender:" + m_clientID);
}

QString GameManager::getRoomLobbyCode()
{
    qDebug() << "Client App (GameManager). Get Lobby code: " << m_roomLobbyCode;
    return m_roomLobbyCode;
}

QStringList GameManager::getLobbyClientsIDs()
{
    return m_lobbyClientsIDs;
}

QString GameManager::getDrawingInstruction()
{
    return m_drawingInstruction;
}

void GameManager::setLobbyClientsIDs(QStringList newClientsOfLobbyList)
{
    if(m_lobbyClientsIDs != newClientsOfLobbyList)
    {
        m_lobbyClientsIDs = newClientsOfLobbyList;
        emit lobbyClientsIDsChanged();
    }
}

void GameManager::setRoomLobbyCode(QString lobbyCode)
{
    if(m_roomLobbyCode != lobbyCode)
    {
        m_roomLobbyCode = lobbyCode;
        emit roomLobbyCodeChanged();
    }
    qDebug() << "Client App (GameManager). Set Lobby code: " << lobbyCode;
}

void GameManager::processSocketMessage(QString message)
{
    m_messageProcessHandler->processMessage(message);
}

void GameManager::setDrawingInstruction(QString drawOrder)
{
    m_drawingInstruction = drawOrder;
    emit newDrawingInstruction();
}

void GameManager::registerClientID(QString clientID)
{
    qDebug() << "Client App. Registering client id";
    m_clientID = clientID;
}

void GameManager::joinLobby(QString lobbyCode, QStringList clientsIDsList)
{
    setRoomLobbyCode(lobbyCode);
    setLobbyClientsIDs(clientsIDsList);
    emit changeOfGameLobby();
}

void GameManager::newClientsReadyList(QStringList clientsListReadinees)
{
    if(m_clientsReadineesList != clientsListReadinees)
    {
        m_clientsReadineesList = clientsListReadinees;
        emit updatedClientsListReadinees();
    }
}

void GameManager::onClientReceivedDrawForContinuation(QString imageFileData, QString drawOrder)
{
    qDebug() << "OVER HERE!";
    setDrawingInstruction(drawOrder);
    qDebug() << QDir::currentPath() + "/../../DoodleDraw/DoodleDrawClient/ui/" + m_clientID + ".png";
    QFile tmpImage(QDir::currentPath() + "/../../DoodleDraw/DoodleDrawClient/ui/" + m_clientID + ".png");
    if(!tmpImage.open(QIODevice::WriteOnly))
        return;
    QByteArray byteData = QByteArray::fromHex(imageFileData.toLocal8Bit());
    tmpImage.write(byteData);
    tmpImage.flush();
    tmpImage.close();
}

GameManager::~GameManager()
{
    m_messageProcessHandler->deleteLater();
}
