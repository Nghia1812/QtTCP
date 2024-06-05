#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>
#include "backend.h"
#include "database.h"
#include "chatprotocol.h"

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);
    app.setWindowIcon(QIcon(":/Assets/customer.ico"));
    QQmlApplicationEngine engine;
    qmlRegisterType<Backend>("io.qt.Backend", 1, 0, "Backend");
    qmlRegisterType<DataBase>("io.qt.DataBase", 1, 0, "DataBase");
    qmlRegisterUncreatableMetaObject(ChatProtocol::staticMetaObject,
                                     "io.qt.Chatprotocol", 1, 0,
                                     "ChatProtocol", "Error: only enums");
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreated,
        &app,
        [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        },
        Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
