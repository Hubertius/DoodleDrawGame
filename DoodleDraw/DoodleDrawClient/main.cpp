#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "Controllers/websockethandler.h"
#include "Controllers/gamemanager.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    WebSocketHandler clientSocketHandler;
    clientSocketHandler.connectToServer("ws://127.0.0.1:8585");

    GameManager gameManager;

    QObject::connect(&clientSocketHandler, &WebSocketHandler::newMessageToProcess, &gameManager, &GameManager::processSocketMessage);
    QObject::connect(&gameManager, &GameManager::newMessageToSend, &clientSocketHandler, &WebSocketHandler::sendMessageToServer);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QQmlContext * context = engine.rootContext();
    context->setContextProperty("clientSocketHandler", &clientSocketHandler);
    context->setContextProperty("applicationDirPath", QGuiApplication::applicationDirPath());
    context->setContextProperty("gameManager", &gameManager);
    return app.exec();
}
