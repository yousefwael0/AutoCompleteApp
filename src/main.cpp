#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "backend.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    Backend backend;
    if (!backend.loadData("../data/Dictionary.txt")) {
        qFatal("Failed to load dictionary file.");
        return -1;
    }

    engine.rootContext()->setContextProperty("backend", &backend);
    engine.load(QUrl(QStringLiteral("qrc:/qml/ui.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}