#include "game.h"
#include<QEventLoop>


Game::Game()
{
    std::srand(time(NULL));     // для генерации случайных чисел при каждом запуске
}


// функция реализует основную логику игры
void Game::processGame()
{
    Boxer P1 (100);     // игрок-"сервер"
    Boxer P2 (100);     // игрок-"клиент"

    qDebug() << "Информация о здоровье игроков:";
    TxText("Информация о здоровье игроков:");
    PrintPlayHealth(&P1, getUserNameSrvGame());
    PrintPlayHealth(&P2, getUserNameClGame());

    qDebug() << "ГОНГ!!! Бой начался !!!";
    TxText("ГОНГ!!! Бой начался !!!");
    // бой начинает Игрок № 1
    TxText("Выберите тип удара...");



    delayfunc();
    qDebug() << "AFTER DELAY";
    while ((P1.getHealth() > 0) && (P2.getHealth() > 0))
    {
        // атака игрока №1
        if ((P1.getHealth() > 0) && (P2.getHealth() > 0))
        {
            PrintFightStartInfo(getUserNameSrvGame(), getUserNameClGame());
            FightPunch(&P1, &P2);
            PrintFightEndInfo(&P2, getUserNameSrvGame(), getUserNameClGame());
        }

        // атака игрока №2
        if ((P1.getHealth() > 0) && (P2.getHealth() > 0))
        {
            PrintFightStartInfo(getUserNameClGame(), getUserNameSrvGame());
            FightPunch(&P2, &P1);
            PrintFightEndInfo(&P1, getUserNameClGame(), getUserNameSrvGame());
        }
    }


    // результат боя
    qDebug() << "= Результат поединка: =";
    TxText("= Результат поединка: =");
    if (P1.getHealth() == 0)
    {
        qDebug() << "Игрок № 2 победил !!!";
        TxText("Игрок № 2 победил !!!");
    }
    else if (P2.getHealth() == 0)
    {
        qDebug() << "Игрок № 1 победил !!!";
        TxText("Игрок № 1 победил !!!");
    }
    qDebug() << "\n = Итоговый счет =";
    TxText("\n = Итоговый счет =");
    PrintPlayHealth(&P1, getUserNameSrvGame());
    PrintPlayHealth(&P2, getUserNameClGame());
    qDebug() << "\n = Поединок окончен. =";
    TxText("\n = Поединок окончен. =");
}

void Game::processGameNEW()
{
    Boxer P1 (100);     // игрок-"сервер"
    Boxer P2 (100);     // игрок-"клиент"

    TxText("=== ИГРА 'БОКС'===");


    while ((P1.getHealth() > 0) && (P2.getHealth() > 0))
    {


        // атака игрока "сервера"
        if ((P1.getHealth() > 0) && (P2.getHealth() > 0))
        {
            TxText("Атакует игрок " + getUserNameSrvGame() + ".");
            TxText("Выберите тип удара...");
            TxText("CLTВыберите тип блока...");

            // ожидание выбора удара (или блока)

            // установки ударов и блоков
            SrvSetPunchBlock();
            ClSetPunchBlock();
            PrintFightStartInfo(getUserNameSrvGame(), getUserNameClGame());
            if ((m_SrvPunch == m_ClBlock) && m_SrvPunch != "0" && m_ClBlock != "0")
            {
                TxText("Удар блокирован!");
                m_SrvPunch = "0";
                m_ClBlock = "0";
            }
            else if ((m_SrvPunch != m_ClBlock) && m_SrvPunch != "0" && m_ClBlock != "0")
            {
                FightPunch(&P1, &P2);
                TxText("Удар пропущен!");
                PrintFightEndInfo(&P2, getUserNameSrvGame(), getUserNameClGame());
                m_SrvPunch = "0";
                m_ClBlock = "0";
            }
        }

        // атака игрока "клиента"
        if ((P1.getHealth() > 0) && (P2.getHealth() > 0))
        {
            TxText("Атакует игрок " + getUserNameClGame() + ".");
            TxText("Выберите тип блока...");
            TxText("CLTВыберите тип удара...");

            // ожидание выбора удара (или блока)

            // установки ударов и блоков
            SrvSetPunchBlock();
            ClSetPunchBlock();
            PrintFightStartInfo(getUserNameClGame(), getUserNameSrvGame());
            if ((m_ClPunch == m_SrvBlock) && m_ClPunch != "0" && m_SrvBlock != "0")
            {
                TxText("Удар блокирован!");
                m_ClPunch = "0";
                m_SrvBlock = "0";
            }
            else if ((m_ClPunch != m_SrvBlock) && m_ClPunch != "0" && m_SrvBlock != "0")
            {
                FightPunch(&P2, &P1);
                TxText("Удар пропущен!");
                PrintFightEndInfo(&P1, getUserNameClGame(), getUserNameSrvGame());
                m_SrvPunch = "0";
                m_ClBlock = "0";
            }
        }
    }


    // результат боя
    qDebug() << "= Результат поединка: =";
    TxText("= Результат поединка: =");
    if (P1.getHealth() == 0)
    {
        qDebug() << "Игрок " + getUserNameClGame() + " победил !!!";
        TxText("Игрок " + getUserNameClGame() + " победил !!!");
    }
    else if (P2.getHealth() == 0)
    {
        qDebug() << "Игрок " + getUserNameSrvGame() + " победил !!!";
        TxText("Игрок " + getUserNameSrvGame() + " победил !!!");
    }
    qDebug() << "= Итоговый счет =";
    TxText("= Итоговый счет = ");
    PrintPlayHealth(&P1, getUserNameSrvGame());
    PrintPlayHealth(&P2, getUserNameClGame());
    qDebug() << "= Поединок окончен. =";
    TxText("= Поединок окончен. =");
}

// функция вывода текущего здоровья игрока
void Game::PrintPlayHealth(Boxer *P, QString Name)
{
    qDebug() << "Здоровье игрока " << Name <<": " << P->getHealth() << " очков.";
    TxText("Здоровье игрока " + Name + ": " + P->getHealth() + " очков.");
}


// функция вывода информации в начале атаки
void Game::PrintFightStartInfo(QString Name1, QString Name2)
{
    qDebug() << "Игрок " << Name1 << " атакует игрока " << Name2 << " !";
    TxText("Игрок " + Name1 + " атакует игрока " + Name2 +" !");
}


// функция вывода информации в конце атаки
void Game::PrintFightEndInfo(Boxer *P2, QString Name1, QString Name2)
{
    qDebug() << "Игрок " << Name1 << " атаковал игрока " << Name2 << "!";
    TxText("Игрок " + Name1 + " атаковал игрока " + Name2 + "!");
    qDebug() << "У игрока " << Name2 << " осталось " << P2->getHealth() << " очков здоровья.";
    TxText("У игрока № " + Name2 + " осталось " + P2->getHealth() + " очков здоровья.");
}


// функция нанесения удара
void Game::FightPunch(Boxer *P1, Boxer *P2)
{
    int HealthCurr = 0;
    if (P2->getHealth() > 0)
    {
        HealthCurr = (P2->getHealth() - P1->Punch());

        if (HealthCurr < 0)
            HealthCurr = 0;

        P2->setHealth(HealthCurr);
        emit TxHPSrvGame(QString::number(P1->getHealth()));
        emit TxHPClGame(QString::number(P2->getHealth()));
        qDebug() << "*** P-U-N-C-H !!! ***";
        TxText("*** P-U-N-C-H !!! ***");
    }
}


void Game::RxText(QString)
{

}


// функции-сеттеры
// для игрока-"сервер"
void Game::setSrvPunchHead(QString SrvPunchHead)
{
    m_SrvPunchHead = SrvPunchHead;
}

void Game::setSrvPunchBody(QString SrvPunchBody)
{
    m_SrvPunchBody = SrvPunchBody;
}

void Game::setSrvBlockHead(QString SrvBlockHead)
{
    m_SrvBlockHead = SrvBlockHead;
}

void Game::setSrvBlockBody(QString SrvBlockBody)
{
    m_SrvBlockBody = SrvBlockBody;
}

void Game::setUserNameSrvGame(QString name)
{
    m_UserNameSrvGame = name;
}


// для игрока-"клиент"
void Game::setClPunchHead(QString ClPunchHead)
{
    m_ClPunchHead = ClPunchHead;
}

void Game::setClPunchBody(QString ClPunchBody)
{
    m_ClPunchBody = ClPunchBody;
}

void Game::setClBlockHead(QString ClBlockHead)
{
    m_ClBlockHead = ClBlockHead;
}

void Game::setClBlockBody(QString ClBlockBody)
{
    m_ClBlockBody = ClBlockBody;
}

void Game::setUserNameClGame(QString name)
{
    m_UserNameClGame = name;
}





// функции-геттеры
// для игрока-"сервер"
QString Game::getSrvPunchHead()
{
    return m_SrvPunchHead;
}

QString Game::getSrvPunchBody()
{
    return m_SrvPunchBody;
}

QString Game::getSrvBlockHead()
{
    return m_SrvBlockHead;
}

QString Game::getSrvBlockBody()
{
    return m_SrvBlockBody;
}

QString Game::getUserNameSrvGame()
{
    return m_UserNameSrvGame;
}


// для игрока-"клиент"
QString Game::getClPunchHead()
{
    return m_ClPunchHead;
}

QString Game::getClPunchBody()
{
    return m_ClPunchBody;
}

QString Game::getClBlockHead()
{
    return m_ClBlockHead;
}

QString Game::getClBlockBody()
{
    return m_ClBlockBody;
}

QString Game::getUserNameClGame()
{
    return m_UserNameClGame;
}




void Game::delayfunc()
{
    qDebug() << "delayfunc_start";
    QEventLoop loop;
    connect(this, &Game::punchTest, &loop, &QEventLoop::quit, Qt::UniqueConnection);
    //QObject::connect(this, &Game::punchTest, [&](){loop.quit();});
    loop.exec();
    qDebug() << "delayfunc_end";
}

void Game::SrvSetPunchBlock()
{
    if (getSrvPunchHead() != "0" && getSrvPunchBody() == "0")
        m_SrvPunch = getSrvPunchHead();
    else if (getSrvPunchHead() == "0" && getSrvPunchBody() != "0")
         m_SrvPunch = getSrvPunchBody();

    if (getSrvBlockHead() != "0" && getSrvBlockBody() == "0")
        m_SrvBlock = getSrvBlockHead();
    else if (getSrvBlockHead() == "0" && getSrvBlockBody() != "0")
        m_SrvBlock = getSrvBlockBody();

    // сброс ударов и блоков
    setSrvPunchHead("0");
    setSrvPunchBody("0");
    setSrvBlockHead("0");
    setSrvBlockBody("0");
}

void Game::ClSetPunchBlock()
{
    if (getClPunchHead() != "0" && getClPunchBody() == "0")
        m_ClPunch = getClPunchHead();
    else if (getClPunchHead() == "0" && getClPunchBody() != "0")
         m_ClPunch = getClPunchBody();

    if (getClBlockHead() != "0" && getClBlockBody() == "0")
        m_ClBlock = getClBlockHead();
    else if (getClBlockHead() == "0" && getClBlockBody() != "0")
        m_ClBlock = getClBlockBody();

    // сброс ударов и блоков
    setClPunchHead("0");
    setClPunchBody("0");
    setClBlockHead("0");
    setClBlockBody("0");
}
