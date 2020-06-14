#include "backend.h"


Backend::Backend()
{
    qDebug() << "Constructor Backend!";
}


// функция-геттер IP адреса
QString Backend::getIpGame()
{
    return m_IpGame;
}


// функция-сеттер IP адреса
void Backend::setIpGame(QString ip_add)
{
    m_IpGame = ip_add;
}


// кнопки (GUI QML)
// выбор ударов/блоков для игрока-"сервер"
void Backend::buttSrvPunchHead()
{
    emit sigSrvPunchHead("101");
}

void Backend::buttSrvPunchBody()
{
    emit sigSrvPunchBody("102");
}

void Backend::buttSrvBlockHead()
{
    emit sigSrvBlockHead("111");
}

void Backend::buttSrvBlockBody()
{
    emit sigSrvBlockBody("112");
}


// выбор ударов/блоков для игрока-"клиент"
void Backend::buttClPunchHead()
{
    // отправка серверу
    emit sendTextCl("PHC111");
}

void Backend::buttClPunchBody()
{
    // отправка серверу
    emit sendTextCl("PBC112");
}

void Backend::buttClBlockHead()
{
    // отправка серверу
    emit sendTextCl("BHC101");
}

void Backend::buttClBlockBody()
{
    // отправка серверу
    emit sendTextCl("BBC102");
}


// СЕРВЕР ИГРЫ
// функция создания игры
void Backend::buttCreateGame()
{
    SrvPtr = new Server("127.0.0.1", 12345);
    // передача данных
    QObject::connect(this, &Backend::sendText, SrvPtr, &Server::sendMsgSrv);

    // прием данных
    QObject::connect(SrvPtr, &Server::PrintText, this, &Backend::PrintText);

    // инициализации данных при подключении игрока-"клиента"
    QObject::connect(SrvPtr, &Server::sigNewConnection, this, &Backend::sigInitData);

    PrintText("Server running...");
    qDebug() << "Server running...";

    G1 = new Game;

    // === ИНФОРМАЦИЯ ОТ ИГРЫ ==="
    // передача информационных сообщений
    QObject::connect(G1, &Game::TxText, this, &Backend::sendText);
    QObject::connect(G1, &Game::TxText, this, &Backend::PrintText);

    // передача текущих уровней НР игроков
    QObject::connect(G1, &Game::TxHPSrvGame, this, &Backend::updHPSrv);
    QObject::connect(G1, &Game::TxHPClGame,  this, &Backend::updHPCl);

    // === ИНФОРМАЦИЯ В ИГРУ ==="
    // передача сигнала продолжения игры
    QObject::connect(this, &Backend::sigContinueGame, G1, &Game::sigContinueGame);

    // передача имен игроков
    QObject::connect(this, &Backend::updUserNameSrv, G1, &Game::setUserNameSrvGame);
    QObject::connect(this, &Backend::updUserNameCl,  G1, &Game::setUserNameClGame);

    // кнопки
    // выбор ударов/блоков для игрока-"сервер"
    QObject::connect(this, &Backend::sigSrvPunchHead, G1, &Game::setSrvPunchHead);
    QObject::connect(this, &Backend::sigSrvPunchBody, G1, &Game::setSrvPunchBody);
    QObject::connect(this, &Backend::sigSrvBlockHead, G1, &Game::setSrvBlockHead);
    QObject::connect(this, &Backend::sigSrvBlockBody, G1, &Game::setSrvBlockBody);

    // выбор ударов/блоков для игрока-"клиент"
    QObject::connect(this, &Backend::sigClPunchHead, G1, &Game::setClPunchHead);
    QObject::connect(this, &Backend::sigClPunchBody, G1, &Game::setClPunchBody);
    QObject::connect(this, &Backend::sigClBlockHead, G1, &Game::setClBlockHead);
    QObject::connect(this, &Backend::sigClBlockBody, G1, &Game::setClBlockBody);

    // === Служебные коннекты для "Backend" ==="
    // обработка действий от пользователя для продолжения игры (для выхода из QEventLoop)
    QObject::connect(this, &Backend::sigSrvPunchHead, this, &Backend::funcContinueGame);
    QObject::connect(this, &Backend::sigSrvPunchBody, this, &Backend::funcContinueGame);
    QObject::connect(this, &Backend::sigSrvBlockHead, this, &Backend::funcContinueGame);
    QObject::connect(this, &Backend::sigSrvBlockBody, this, &Backend::funcContinueGame);

    QObject::connect(this, &Backend::sigClPunchHead, this, &Backend::funcContinueGame);
    QObject::connect(this, &Backend::sigClPunchBody, this, &Backend::funcContinueGame);
    QObject::connect(this, &Backend::sigClBlockHead, this, &Backend::funcContinueGame);
    QObject::connect(this, &Backend::sigClBlockBody, this, &Backend::funcContinueGame);
}


// функция завершения игры
void Backend::buttDestroyGame()
{
    delete SrvPtr;
    delete G1;
    SrvPtr = nullptr;
    G1 = nullptr;
    PrintText("Server stopped!");
    qDebug() << "Server stopped!";
}


// КЛИЕНТ ИГРЫ
// функция подключения к игре
void Backend::buttJoinGame()
{
    if (getIpGame() != "0")
    {
        m_client = new Client(getIpGame(), 12345);
        senderThread = new QThread;
        m_client->moveToThread(senderThread);

        // передача данных
        QObject::connect(this, &Backend::sendTextCl, m_client, &Client::sendMsg);

        // прием данных
        QObject::connect(m_client, &Client::PrintText, this, &Backend::PrintTextCl);

        // прием служебной информации
        QObject::connect(m_client, &Client::connected, this, &Backend::PrintTextCl);
        QObject::connect(m_client, &Client::disconnected, this, &Backend::PrintTextCl);
        QObject::connect(m_client, &Client::sendError, this, &Backend::PrintTextCl);

        // инициализации данных при подключении к игроку-"сервер"
        QObject::connect(m_client, &Client::connected, this, &Backend::sigInitData);

        QObject::connect(this, &Backend::disconnectGame, m_client, &Client::deleteLater);
        QObject::connect(m_client, &Client::destroyed, this, [=](){ senderThread->quit(); senderThread->wait();});
        QObject::connect(senderThread, &QThread::finished, senderThread, &QThread::deleteLater);

        // запуск потока
        senderThread->start();

        // остановка воспроизведения фонового саундтрека, если IP адрес сервера = 127.0.0.1
        // (т.е. игра выполняется на одном устройстве через внутренний виртуальный IP адрес (loopback))
        if (getIpGame() == "127.0.0.1")
            emit sigStopMusic();
    }
    else
    {
        qDebug () << "IP incorrect!";
        PrintTextCl("IP incorrect!");
    }
}


// функция отключения от игры
void Backend::buttDisconGame()
{
    emit disconnectGame();
}


// функция запуска игры
void Backend::startGame()
{
    qDebug() << "Server listening you!";
    G1->processGame();
}


// функция продолжения игры
void Backend::funcContinueGame(QString Ch)
{
    if (Ch_num1 == "0")
        Ch_num1 = Ch;
    else if (Ch_num1 != "0" && Ch_num2 == "0")
        Ch_num2 = Ch;

    // Если выбрано по одному действию от пользователей (удар или блок), продолжается игра и
    // разблокируется QEventLoop в классе "Game"
    if (Ch_num1 != "0" && Ch_num2 != "0")
    {
        emit sigContinueGame();
        Ch_num1 = "0";
        Ch_num2 = "0";
    }
}


// функция приема данных для игрока-"сервер"
void Backend::PrintText(QString text)
{
    /* Для определения целевого назначения принимаемых данных,
     * выполняется анализ префикса принятой информации, и уже после этого отправка
     * информации в заданное поле (место)
    */

    if (text.startsWith("PHC"))
        emit sigClPunchHead("111");
    else if (text.startsWith("PBC"))
        emit sigClPunchBody("112");
    else if (text.startsWith("BHC"))
        emit sigClBlockHead("101");
    else if (text.startsWith("BBC"))
        emit sigClBlockBody("102");
    else
        emit sigPrintText(text);
}


// функция приема данных для игрока-"клиент"
void Backend::PrintTextCl(QString text)
{
    emit sigPrintTextCl(text);
}


