#include "gamemanager.h"
#include "gamelobbyhandler.h"
#include <random>
#include <QRandomGenerator>

GameManager::GameManager(QObject *parent)
    : QObject{parent}
{
    m_drawingTypes = QStringList() << "dog" << "cat" << "mouse" << "rhino" << "elephant";
    m_webSocketHandler = new WebSocketHandler(this);
    m_messageProcessHandler = new MessageProcessor(this);
    connect(m_webSocketHandler, &WebSocketHandler::newMessageToProcess, m_messageProcessHandler, &MessageProcessor::processClientMessage);
    connect(m_messageProcessHandler, &MessageProcessor::loginRequest, m_webSocketHandler, &WebSocketHandler::onLoginCheckDataRequest);

    connect(m_messageProcessHandler, &MessageProcessor::createGameLobbyRequest, this, &GameManager::createGameLobbyRequest);
    connect(m_messageProcessHandler, &MessageProcessor::joinGameLobbyRequest, this, &GameManager::joinGameLobbyRequest);
    connect(m_messageProcessHandler, &MessageProcessor::messageLobbyRequest, this, &GameManager::messageLobbyRequest);
    connect(m_messageProcessHandler, &MessageProcessor::userReadyToPlay, this, &GameManager::userReadyToPlay);
    connect(m_messageProcessHandler, &MessageProcessor::clientNewDoodleDrawing, this, &GameManager::onClientNewDoodleDrawing);
    connect(m_messageProcessHandler, &MessageProcessor::clientFinishedDrawWork, this, &GameManager::onClientFinishedDrawWork);
    connect(m_messageProcessHandler, &MessageProcessor::newVote, this, &GameManager::onNewVote);
}

const QString& GameManager::generateSthForDrawing()
{
    std::random_device rd;

    std::uniform_int_distribution<int> indexGenerator(0, m_drawingTypes.size()-1);
    int generatedIndex = indexGenerator(*QRandomGenerator::global());
    return m_drawingTypes.at(generatedIndex);
}

GameManager::~GameManager()
{
    m_webSocketHandler->deleteLater();
}

void GameManager::createGameLobbyRequest(QString clientID)
{
    std::random_device rd;

    std::uniform_int_distribution<int> idGenerator(1000, 9999);
    QString newGameID = QString::number(idGenerator(*QRandomGenerator::global()));

    while(m_gameLobbys.keys().contains(newGameID))
    {
        newGameID = QString::number(idGenerator(*QRandomGenerator::global()));
    }
    GameLobbyHandler * m_gameLobby = new GameLobbyHandler(newGameID, this);
    connect(m_gameLobby, &GameLobbyHandler::usersReadineesChanged, this, &GameManager::usersReadineesChanged);
    connect(m_gameLobby, &GameLobbyHandler::gameReadyToBegin, this, &GameManager::gameReadyToBegin);
    connect(m_gameLobby, &GameLobbyHandler::allClientsSendDoodleDraws, this, &GameManager::onAllClientsSendDoodleDraws);
    connect(m_gameLobby, &GameLobbyHandler::allClientsSendFinishedDraws, this, &GameManager::onAllClientsSendFinishedDraws);
    connect(m_gameLobby, &GameLobbyHandler::allClientsVoted, this, &GameManager::onAllClientsVoted);
    qDebug() << "New game lobby ID: " << newGameID;
    m_gameLobby->addClientID(clientID);
    m_gameLobbys[newGameID] = m_gameLobby;
    m_webSocketHandler->sendTextMessageToClient("type:lobbyCreated;payload:" + newGameID +";clientsList:" + clientID, clientID);
}

void GameManager::joinGameLobbyRequest(QString lobbyID, QString clientID)
{
    if(m_gameLobbys.contains(lobbyID))
    {
        m_gameLobbys[lobbyID]->addClientID(clientID);
        m_webSocketHandler->sendTextMessageToClient("type:lobbyJoinSuccessful;payload:" + lobbyID + ";clientsList:" + m_gameLobbys[lobbyID]->getGameLobbyClientsAsString(), clientID);
        m_webSocketHandler->sendTextMessageToMultipleClients("type:updatedClientsList;payload:" + m_gameLobbys[lobbyID]->getGameLobbyClientsAsString(), m_gameLobbys[lobbyID]->getGameLobbyClientsAsList());
    }
    else
        m_webSocketHandler->sendTextMessageToClient("type:lobbyJoinFailed:payload:" + lobbyID, clientID);
}

void GameManager::messageLobbyRequest(QString messageContent, QString lobbyID, QString clientID)
{
    if(m_gameLobbys.contains(lobbyID) )
    {
        qDebug()  << "Server App. Message Lobby Request slot in GameManager";
        GameLobbyHandler * lobby = m_gameLobbys[lobbyID];
        qDebug() << "Server App. Message Lobby Request and message content: " << messageContent;
        m_webSocketHandler->sendTextMessageToMultipleClients("type:message;payload:" + messageContent + ";sender:" + clientID, lobby->getGameLobbyClientsAsList());
    }
}

void GameManager::usersReadineesChanged()
{
    GameLobbyHandler * gameLobby = qobject_cast<GameLobbyHandler *>(sender());
    m_webSocketHandler->sendTextMessageToMultipleClients("type:readineesOfClientsChanged;payload:" + gameLobby->getTrueReadineesOfClients(), gameLobby->getGameLobbyClientsAsList());
}

void GameManager::userReadyToPlay(QString clientID)
{
    qDebug() << "Server App. User ready: " << clientID;
    foreach(GameLobbyHandler * gameLobby, m_gameLobbys.values())
        gameLobby->userReadyToPlay(clientID);
}

void GameManager::gameReadyToBegin()
{
    GameLobbyHandler * gameLobby = qobject_cast<GameLobbyHandler *>(sender());
    m_webSocketHandler->sendTextMessageToMultipleClients("type:gameReadyToBegin;payload:1", gameLobby->getGameLobbyClientsAsList());
}

void GameManager::onClientNewDoodleDrawing(QString fileData, QString clientID)
{
    QList<GameLobbyHandler *> gameLobbys = m_gameLobbys.values();
    foreach(GameLobbyHandler * gameLobby, gameLobbys)
        gameLobby->clientNewDoodleDraw(fileData, clientID);
}

void GameManager::onAllClientsSendDoodleDraws(QMap<QString, QString> distrubutedDraws)
{
    const QString& drawingChosenForClients =  this->generateSthForDrawing();
    //type:assignedDrawing;payload:distrubutedDraws;instructionForDrawing:Cat
    foreach(const QString& clientID, distrubutedDraws.keys())
        m_webSocketHandler->sendTextMessageToClient("type:assignedDrawingData;payload:" + distrubutedDraws[clientID] + ";drawOrder:" + drawingChosenForClients, clientID);


}

void GameManager::onClientFinishedDrawWork(QString fileData, QString clientID)
{
    QList<GameLobbyHandler *> gameLobbys = m_gameLobbys.values();
    foreach(GameLobbyHandler * gameLobby, gameLobbys)
        gameLobby->clientFinishedDrawing(fileData, clientID);
}

void GameManager::onAllClientsSendFinishedDraws(QMap<QString, QString> clientsFinishedDraws)
{
    //type:otherClientsDrawingsForVote;payload:imageFile1,imageFil2,imageFile3;clients:
    GameLobbyHandler * gameLobby = qobject_cast<GameLobbyHandler *>(sender());
    QString finishedDrawsData = QString();
    QString clients = QString();
    for(QMap<QString, QString>::iterator itr = clientsFinishedDraws.begin(); itr != clientsFinishedDraws.end(); ++itr)
    {
        clients.append(itr.key() + ",");
        finishedDrawsData.append(itr.value() + ",");
    }
    clients.chop(1);
    finishedDrawsData.chop(1);
    m_webSocketHandler->sendTextMessageToMultipleClients("type:otherClientsDrawingsForVote;payload:" + finishedDrawsData + ";clients:" + clients, gameLobby->getGameLobbyClientsAsList());
}

void GameManager::onNewVote(QString vote, QString clientID)
{
    QList<GameLobbyHandler *> gameLobbys = m_gameLobbys.values();
    foreach(GameLobbyHandler * gameLobby, gameLobbys)
        gameLobby->newVote(vote, clientID);
}

void GameManager::onAllClientsVoted(QString winnerClientID)
{
    GameLobbyHandler * gameLobby = qobject_cast<GameLobbyHandler *>(sender());
    m_webSocketHandler->sendTextMessageToMultipleClients("type:winner;payload:" + winnerClientID, gameLobby->getGameLobbyClientsAsList());
}

