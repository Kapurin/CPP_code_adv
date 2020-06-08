#include <QDebug>
#include <QTime>
#include <QThread>
#include "backend.h"



Backend::Backend()
{
    qDebug() << "Constructor Backend!";

}


QString Backend::getUserNameSrv()
{
    return m_UserNameSrv;
}

void Backend::setUserNameSrv(QString name)
{
    m_UserNameSrv = name;
    emit updUserNameSrv(m_UserNameSrv);

    // отправка клиенту изменений
    if (SrvPtr !=nullptr)
    {
        emit sendText("UNS"+m_UserNameSrv);
    }
}

QString Backend::getUserNameCl()
{
    return m_UserNameCl;
}

void Backend::setUserNameCl(QString name)
{
    m_UserNameCl = name;
    emit updUserNameCl(m_UserNameCl);
    // отправка серверу изменений
    if (SrvPtr == nullptr)
    {
        emit sendTextCl("UNC"+m_UserNameCl);
    }
}

QString Backend::getIpGame()
{
    return m_IpGame;
}

void Backend::setIpGame(QString ip_add)
{
    m_IpGame = ip_add;
    qDebug() << m_IpGame;
}

QString Backend::getTxTextToQML()
{
    return m_TxTextToQML;
}

void Backend::setTxTextToQML(QString TxText)
{
    m_TxTextToQML = TxText;
}

QString Backend::getRxTextFromQML()
{
    return m_RxTextFromQML;
}

void Backend::setRxTextFromQML(QString RxText)
{
    m_RxTextFromQML = RxText;
}



QString Backend::getHPSrv()
{
    return m_HPSrv;
}

void Backend::setHPSrv(QString HPSrv)
{
    m_HPSrv = HPSrv;
    emit updHPSrv(m_HPSrv);

    // отправка клиенту изменений
    if (SrvPtr !=nullptr)
    {
        emit sendText("HP1"+m_HPSrv);
    }
}

QString Backend::getHPCl()
{
    return m_HPCl;
}

QString Backend::getStatusGame()
{
    return m_StatusGame;
}

void Backend::setStatusGame(QString status)
{
    m_StatusGame = status;
    emit updStatusGame(m_StatusGame);
}


void Backend::setHPCl(QString HPCl)
{
    m_HPCl = HPCl;
    emit updHPCl(m_HPCl);

    // отправка клиенту изменений
    if (SrvPtr !=nullptr)
    {
        emit sendText("HP2"+m_HPCl);
    }
}

void Backend::sendText2()
{
    emit punchTestBack();
    qDebug() << "punchTestBack()";
}

// == инициализация данных ==
void Backend::initData()
{
    // для сервера
    if (SrvPtr !=nullptr)
    {
        setUserNameSrv(m_UserNameSrv);
    }

    // для клиента
    if (SrvPtr == nullptr)
    {
        setUserNameCl(m_UserNameCl);
    }
}



// кнопки (GUI QML)
// для игрока-"сервер"
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


// для игрока-"клиент"
void Backend::buttClPunchHead()
{
    // отправка серверу
    emit sendTextCl("PHC111");
    //emit sigClPunchHead("111");
}

void Backend::buttClPunchBody()
{
    // отправка серверу
    emit sendTextCl("PBC112");
    //emit sigClPunchBody("112");
}

void Backend::buttClBlockHead()
{
    // отправка серверу
    emit sendTextCl("BHC101");
    //emit sigClBlockHead("101");
}

void Backend::buttClBlockBody()
{
    // отправка серверу
    emit sendTextCl("BBC102");
    //emit sigClBlockBody("102");
}


// СЕРВЕР ИГРЫ
void Backend::buttCreateGame()
{
    SrvPtr = new Server("127.0.0.1", 12345);
    QObject::connect(this, &Backend::sendText, SrvPtr, &Server::sendMsgSrv,Qt::DirectConnection);
    QObject::connect(SrvPtr, &Server::PrintText, this, &Backend::PrintText);
    QObject::connect(SrvPtr, &Server::sigNewConnection, this, &Backend::initData);

    PrintText("Server running...");
    qDebug() << "Server running...";

    G1 = new Game;

    // === ИНФОРМАЦИЯ ОТ "ИГРЫ ==="
    QObject::connect(G1, &Game::TxText, this, &Backend::sendText, Qt::DirectConnection);
    QObject::connect(G1, &Game::TxText, this, &Backend::PrintText);

    QObject::connect(G1, &Game::TxHPSrvGame, this, &Backend::setHPSrv);
    QObject::connect(G1, &Game::TxHPClGame, this, &Backend::setHPCl);

    // === ИНФОРМАЦИЯ В "ИГРУ ==="
    QObject::connect(this, &Backend::punchTestBack, G1, &Game::punchTest, Qt::UniqueConnection);
    // кнопки
    // для игрока-"сервер"
    QObject::connect(this, &Backend::sigSrvPunchHead, G1, &Game::setSrvPunchHead);
    QObject::connect(this, &Backend::sigSrvPunchBody, G1, &Game::setSrvPunchBody);
    QObject::connect(this, &Backend::sigSrvBlockHead, G1, &Game::setSrvBlockHead);
    QObject::connect(this, &Backend::sigSrvBlockBody, G1, &Game::setSrvBlockBody);
    QObject::connect(this, &Backend::updUserNameSrv, G1, &Game::setUserNameSrvGame);

    // для игрока-"клиент"
    QObject::connect(this, &Backend::sigClPunchHead, G1, &Game::setClPunchHead);
    QObject::connect(this, &Backend::sigClPunchBody, G1, &Game::setClPunchBody);
    QObject::connect(this, &Backend::sigClBlockHead, G1, &Game::setClBlockHead);
    QObject::connect(this, &Backend::sigClBlockBody, G1, &Game::setClBlockBody);
    QObject::connect(this, &Backend::updUserNameCl, G1, &Game::setUserNameClGame);
}

void Backend::buttDestroyGame()
{
    delete SrvPtr;
    SrvPtr = nullptr;
    PrintText("Server stopped!");
    qDebug() << "Server stopped!";
}


// КЛИЕНТ ИГРЫ
void Backend::buttJoinGame()
{
    if (getIpGame() != "0")
    {
        //m_client = new Client("127.0.0.1", 12345);
        m_client = new Client(getIpGame(), 12345);
        senderThread = new QThread;
        m_client->moveToThread(senderThread);

        QObject::connect(this, &Backend::sendTextCl, m_client, &Client::sendMsg);
        QObject::connect(m_client, &Client::PrintText, this, &Backend::PrintTextCl);

        QObject::connect(m_client, &Client::connected, this, &Backend::PrintTextCl);
        QObject::connect(m_client, &Client::disconnected, this, &Backend::PrintTextCl);
        QObject::connect(m_client, &Client::sendError, this, &Backend::PrintTextCl);

        QObject::connect(m_client, &Client::connected, this, &Backend::initData);

        QObject::connect(this, &Backend::disconnect, m_client, &Client::deleteLater);
        QObject::connect(m_client, &Client::destroyed, this, [=](){ senderThread->quit(); senderThread->wait();});
        QObject::connect(senderThread, &QThread::finished, senderThread, &QThread::deleteLater);

        senderThread->start();
    }
    else
    {
        qDebug () << "IP incorrect!";
        PrintTextCl("IP incorrect!");
    }
}

void Backend::buttDisconGame()
{
    emit disconnect();
}

void Backend::printTester()
{
//     emit sendText("Server listening you!");
//     emit sendText("Server listening you222!");
    qDebug() << "Server listening you!";
//    setHPSrv("98");
//    setHPCl("55");
//    qDebug() << "getHPSrv:" << getHPSrv();
//    qDebug() << "getHPCl:" << getHPCl();
   G1->processGame();

}


// прием данных для "Сервера"
void Backend::PrintText(QString text)
{
    /* для определения целевого назначения принимаемых данных,
    * выполняется анализ префикса принятой информации, и уже после этого отправка
    * информации в заданное поле (место)
    */

    if (text.startsWith("UNC"))
        setUserNameCl(text.remove(0,3));
    else if (text.startsWith("PHC"))
        emit sigClPunchHead("111");
    else if (text.startsWith("PBC"))
        emit sigClPunchBody("112");
    else if (text.startsWith("BHC"))
        emit sigClBlockHead("101");
    else if (text.startsWith("BBC"))
        emit sigClBlockBody("102");
    else if (text.startsWith("STSS"))
        setStatusGame(text.remove(0,4));
    else
    {
        setTxTextToQML(text);
        emit upTxTextToQML(m_TxTextToQML);
    }
}

// прием данных для "Клиента"
void Backend::PrintTextCl(QString text)
{
    /* для определения целевого назначения принимаемых данных,
    * выполняется анализ префикса принятой информации, и уже после этого отправка
    * информации в заданное поле (место)
    */

    if (text.startsWith("UNS"))
        setUserNameSrv(text.remove(0,3));
    else if (text.startsWith("HP1"))
        setHPSrv(text.remove(0,3));
    else if (text.startsWith("HP2"))
        setHPCl(text.remove(0,3));
    else if (text.startsWith("CLT"))
    {
        setTxTextToQML(text.remove(0,3));
        emit upTxTextToQML(m_TxTextToQML);
    }
    else if (text.startsWith("STSC"))
        setStatusGame(text.remove(0,4));
    else
    {
        setTxTextToQML(text);
        emit upTxTextToQML(m_TxTextToQML);
    }
}


