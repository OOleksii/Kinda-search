#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "backendbase.h"
#include <QtQml>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<BackendBase>("app.backend", 1, 0, "Backendbase");
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
