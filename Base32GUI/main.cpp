#define __BASE32GUI__

//Qt's includes
//add folder path when including, get folder path from /usr/include/x86_64-linux-gnu/qt5
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "../Base32/Base32.cpp"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));

    return app.exec();
}
