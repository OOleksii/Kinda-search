#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "backendbase.h"
#include <QtQml>
#include "resultsmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    qmlRegisterType<BackendBase>("app.backend", 1, 0, "Backendbase");
    qmlRegisterType<ResultsModel>("app.result", 1, 0, "ResultsModel");
    qmlRegisterType<Result>();
    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
