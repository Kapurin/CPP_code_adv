#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtMultimedia>
#include "guiworker.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);


    // создание бекэнда игры
    Guiworker back;
    engine.rootContext()->setContextProperty("sideCPPBackend", &back);

    // для выхода из приложения по кнопке "Завершить игру"
    QObject::connect(&engine, &QQmlApplicationEngine::quit, &QGuiApplication::quit);


    // воспроизведение фонового саундтрека (с циклическим повторением)
    // (играет саундтрек из фильма "Рокки 3": "Survivor - Eye Of The Tiger")
    QMediaPlaylist *playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sounds/testaudio.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);
    QMediaPlayer *music = new QMediaPlayer();
    music->setPlaylist(playlist);
    music->setVolume(100);
    music->play();

    // остановка воспроизведения фонового саундтрека, если IP адрес сервера = 127.0.0.1
    // (т.е. игра выполняется на одном устройстве через внутренний виртуальный IP адрес (loopback))
    QObject::connect(&back, &Guiworker::sigStopMusic, music, &QMediaPlayer::stop);


    return app.exec();
}
