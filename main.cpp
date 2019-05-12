#include <QGuiApplication>
#include<QQmlContext>
#include <QQmlApplicationEngine>

#include "dataobject.h"
#include"manager.h"
#include"valuelist.h"


void registerMyType();

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    registerMyType();
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}


void registerMyType(){
//    qmlRegisterType<DataObject>("objects", 1, 0, "DataObject");
    qmlRegisterType<ValueList>("objects", 1, 0,"ValueList");
    qmlRegisterType<Manager>("objects", 1, 0,"Manager");
}
