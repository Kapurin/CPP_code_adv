#include "guiworker.h"


Guiworker::Guiworker()
{
    qDebug() << "Constructor Guiworker!";

    threadBackend = new QThread;
    gameback = new Backend();

    // перенос всего бекэнда игры в отдельный поток
    gameback->moveToThread(threadBackend);
    connect(threadBackend, &QThread::finished, threadBackend,   &QThread::deleteLater);
    connect(threadBackend, &QThread::finished, gameback,        &Backend::deleteLater);

    // === ИНФОРМАЦИЯ ОТ "Backend" ==="
    // инициализация данных
    QObject::connect(gameback, &Backend::sigInitData, this, &Guiworker::initData);

    // прием сообщений
    QObject::connect(gameback, &Backend::sigPrintText,  this, &Guiworker::GWPrintText);
    QObject::connect(gameback, &Backend::sigPrintTextCl,this, &Guiworker::GWPrintTextCl);

    // текущий уровень HP
    QObject::connect(gameback, &Backend::updHPSrv,  this, &Guiworker::setHPSrv);
    QObject::connect(gameback, &Backend::updHPCl,   this, &Guiworker::setHPCl);

    // остановка воспроизведения фонового саундтрека
    QObject::connect(gameback, &Backend::sigStopMusic, this, &Guiworker::sigStopMusic);


    // === ИНФОРМАЦИЯ В "Backend" ==="
    //запуск игры
    QObject::connect(this, &Guiworker::sigStartGame,    gameback, &Backend::startGame);

    // основные параметры игры
    QObject::connect(this, &Guiworker::updUserNameSrv,  gameback, &Backend::updUserNameSrv);
    QObject::connect(this, &Guiworker::updUserNameCl,   gameback, &Backend::updUserNameCl);
    QObject::connect(this, &Guiworker::updIpGame,       gameback, &Backend::setIpGame);

    // кнопки основных действий с игрой
    QObject::connect(this, &Guiworker::sigGWCreateGame,  gameback, &Backend::buttCreateGame);
    QObject::connect(this, &Guiworker::sigGWDestroyGame, gameback, &Backend::buttDestroyGame);
    QObject::connect(this, &Guiworker::sigGWJoinGame,    gameback, &Backend::buttJoinGame);
    QObject::connect(this, &Guiworker::sigGWDisconGame,  gameback, &Backend::buttDisconGame);

    // кнопки ударов и блоков
    QObject::connect(this, &Guiworker::sigGWSrvPunchHead,   gameback, &Backend::buttSrvPunchHead);
    QObject::connect(this, &Guiworker::sigGWSrvPunchBody,   gameback, &Backend::buttSrvPunchBody);
    QObject::connect(this, &Guiworker::sigGWSrvBlockHead,   gameback, &Backend::buttSrvBlockHead);
    QObject::connect(this, &Guiworker::sigGWSrvBlockBody,   gameback, &Backend::buttSrvBlockBody);

    QObject::connect(this, &Guiworker::sigGWClPunchHead,  gameback, &Backend::buttClPunchHead);
    QObject::connect(this, &Guiworker::sigGWClPunchBody,  gameback, &Backend::buttClPunchBody);
    QObject::connect(this, &Guiworker::sigGWClBlockHead,  gameback, &Backend::buttClBlockHead);
    QObject::connect(this, &Guiworker::sigGWClBlockBody,  gameback, &Backend::buttClBlockBody);

    // отправка сообщений
    QObject::connect(this, &Guiworker::sendGWText,  gameback, &Backend::sendText);
    QObject::connect(this, &Guiworker::sendGWTextCl,gameback, &Backend::sendTextCl);

    // запуск потока с бекэндом игры
    threadBackend->start();
}


Guiworker::~Guiworker()
{
    //    delete threadBackend;
    //    delete gameback;
}


// == Функции-геттеры ==
// имена игроков
QString Guiworker::getUserNameSrv()
{
    return m_UserNameSrv;
}

QString Guiworker::getUserNameCl()
{
    return m_UserNameCl;
}

// текущие уровни НР игроков
QString Guiworker::getHPSrv()
{
    return m_HPSrv;
}

QString Guiworker::getHPCl()
{
    return m_HPCl;
}

// IP адрес игрока-"сервер"
QString Guiworker::getIpGame()
{
    return m_IpGame;
}

// статус игры
QString Guiworker::getStatusGame()
{
    return m_StatusGame;
}

// информационные сообщения в поле вывода игрового процесса (QML)
QString Guiworker::getTxTextToQML()
{
    return m_TxTextToQML;
}



// == Функции-сеттеры ==
// имена игроков
void Guiworker::setUserNameSrv(QString name)
{
    m_UserNameSrv = name;
    emit updUserNameSrv(m_UserNameSrv);

    // отправка клиенту изменений
    if (getIpGame() == "0")
    {
        emit sendGWText("UNS"+m_UserNameSrv);
    }
}

void Guiworker::setUserNameCl(QString name)
{
    m_UserNameCl = name;
    emit updUserNameCl(m_UserNameCl);

    // отправка серверу изменений
    if (getIpGame() != "0")
    {
        emit sendGWTextCl("UNC"+m_UserNameCl);
    }
}

// текущие уровни НР игроков
void Guiworker::setHPSrv(QString HPSrv)
{
    m_HPSrv = HPSrv;
    emit updHPSrv(m_HPSrv);

    // отправка клиенту изменений
    if (getIpGame() == "0")
    {
        emit sendGWText("HP1"+m_HPSrv);
    }
}

void Guiworker::setHPCl(QString HPCl)
{
    m_HPCl = HPCl;
    emit updHPCl(m_HPCl);

    // отправка клиенту изменений
    if (getIpGame() == "0")
    {
        emit sendGWText("HP2"+m_HPCl);
    }
}


// IP адрес игрока-"сервер"
void Guiworker::setIpGame(QString ip_add)
{
    m_IpGame = ip_add;
    emit updIpGame(m_IpGame);
}

// статус игры
void Guiworker::setStatusGame(QString status)
{
    m_StatusGame = status;
    emit updStatusGame(m_StatusGame);
}

// информационные сообщения в поле вывода игрового процесса (QML)
void Guiworker::setTxTextToQML(QString TxText)
{
    m_TxTextToQML = TxText;
}


// функция инициализации данных в начале игры
void Guiworker::initData()
{
    // для сервера
    if (getIpGame() == "0")
    {
        setHPSrv("100");
        setHPCl("100");
        setUserNameSrv(m_UserNameSrv);
        // запуск игры
        emit sigStartGame();
    }

    // для клиента
    if (getIpGame() != "0")
        setUserNameCl(m_UserNameCl);
}



// == Кнопки (GUI QML) ==
// выбор ударов/блоков для игрока-"сервер"
void Guiworker::buttGWSrvPunchHead()
{
    emit sigGWSrvPunchHead();
    setTxTextToQML("Вы выбрали удар в голову!");
    emit upTxTextToQML(m_TxTextToQML);
    setTxTextToQML("Ожидайте выбор действия соперником...");
    emit upTxTextToQML(m_TxTextToQML);
}

void Guiworker::buttGWSrvPunchBody()
{
    emit sigGWSrvPunchBody();
    setTxTextToQML("Вы выбрали удар в корпус!");
    emit upTxTextToQML(m_TxTextToQML);
    setTxTextToQML("Ожидайте выбор действия соперником...");
    emit upTxTextToQML(m_TxTextToQML);
}

void Guiworker::buttGWSrvBlockHead()
{
    emit sigGWSrvBlockHead();
    setTxTextToQML("Вы выбрали блок от удара в голову!");
    emit upTxTextToQML(m_TxTextToQML);
    setTxTextToQML("Ожидайте выбор действия соперником...");
    emit upTxTextToQML(m_TxTextToQML);
}

void Guiworker::buttGWSrvBlockBody()
{
    emit sigGWSrvBlockBody();
    setTxTextToQML("Вы выбрали блок от удара в корпус!");
    emit upTxTextToQML(m_TxTextToQML);
    setTxTextToQML("Ожидайте выбор действия соперником...");
    emit upTxTextToQML(m_TxTextToQML);
}


// выбор ударов/блоков для игрока-"клиент"
void Guiworker::buttGWClPunchHead()
{
    emit sigGWClPunchHead();
    setTxTextToQML("Вы выбрали удар в голову!");
    emit upTxTextToQML(m_TxTextToQML);
    setTxTextToQML("Ожидайте выбор действия соперником...");
    emit upTxTextToQML(m_TxTextToQML);
}

void Guiworker::buttGWClPunchBody()
{
    emit sigGWClPunchBody();
    setTxTextToQML("Вы выбрали удар в корпус!");
    emit upTxTextToQML(m_TxTextToQML);
    setTxTextToQML("Ожидайте выбор действия соперником...");
    emit upTxTextToQML(m_TxTextToQML);
}

void Guiworker::buttGWClBlockHead()
{
    emit sigGWClBlockHead();
    setTxTextToQML("Вы выбрали блок от удара в голову!");
    emit upTxTextToQML(m_TxTextToQML);
    setTxTextToQML("Ожидайте выбор действия соперником...");
    emit upTxTextToQML(m_TxTextToQML);
}

void Guiworker::buttGWClBlockBody()
{
    emit sigGWClBlockBody();
    setTxTextToQML("Вы выбрали блок от удара в корпус!");
    emit upTxTextToQML(m_TxTextToQML);
    setTxTextToQML("Ожидайте выбор действия соперником...");
    emit upTxTextToQML(m_TxTextToQML);
}

// Кнопки основных действий с игрой
// кнопка создания игры
void Guiworker::buttGWCreateGame()
{
    emit sigGWCreateGame();
}

// кнопка завершения игры
void Guiworker::buttGWDestroyGame()
{
    emit sigGWDestroyGame();
}

// кнопка подключения к игре
void Guiworker::buttGWJoinGame()
{
    emit sigGWJoinGame();
}

// кнопка отключения от игры
void Guiworker::buttGWDisconGame()
{
    emit sigGWDisconGame();
}



// функция приема данных для игрока-"сервер"
void Guiworker::GWPrintText(QString text)
{
    /* Для определения целевого назначения принимаемых данных,
    * выполняется анализ префикса принятой информации, и уже после этого отправка
    * информации в заданное поле (место)
    */

    if (text.startsWith("UNC"))
        setUserNameCl(text.remove(0,3));
    else if (text.startsWith("STSS"))
        setStatusGame(text.remove(0,4));
    else if (text.startsWith("STSC"))
        emit sendGWText(text);
    else if (text.startsWith("SRV"))
    {
        setTxTextToQML(text.remove(0,3));
        emit upTxTextToQML(m_TxTextToQML);
    }
    else if (text.startsWith("CLT"))
        text.clear();
    else
    {
        setTxTextToQML(text);
        emit upTxTextToQML(m_TxTextToQML);
    }
}

// функция приема данных для игрока-"клиент"
void Guiworker::GWPrintTextCl(QString text)
{
    /* Для определения целевого назначения принимаемых данных,
    * выполняется анализ префикса принятой информации, и уже после этого отправка
    * информации в заданное поле (место)
    */

    if (text.startsWith("UNS"))
        setUserNameSrv(text.remove(0,3));
    else if (text.startsWith("STSS"))
        text.clear();
    else if (text.startsWith("STSC"))
        setStatusGame(text.remove(0,4));
    else if (text.startsWith("HP1"))
        setHPSrv(text.remove(0,3));
    else if (text.startsWith("HP2"))
        setHPCl(text.remove(0,3));
    else if (text.startsWith("SRV"))
        text.clear();
    else if (text.startsWith("CLT"))
    {
        setTxTextToQML(text.remove(0,3));
        emit upTxTextToQML(m_TxTextToQML);
    }
    else
    {
        setTxTextToQML(text);
        emit upTxTextToQML(m_TxTextToQML);
    }
}



