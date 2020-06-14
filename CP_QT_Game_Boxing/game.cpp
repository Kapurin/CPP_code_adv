#include "game.h"


Game::Game()
{
    std::srand(time(NULL));     // для генерации случайных чисел при каждом запуске
}


// функция основной логики игры
void Game::processGame()
{
    Boxer P1 (100);     // игрок-"сервер"
    Boxer P2 (100);     // игрок-"клиент"

    TxText("\n\n=== ИГРА <<БОКС>>===");
    TxText("\nГОНГ!!! Бой начался !!!");

    while ((P1.getHealth() > 0) && (P2.getHealth() > 0))
    {
        // атака игрока "сервера"
        if ((P1.getHealth() > 0) && (P2.getHealth() > 0))
        {
            TxText("\nАтакует игрок " + getUserNameSrvGame() + ".");
            TxText("STSSВы атакуете!");
            TxText("STSCВы защищаетесь!");
            TxText("SRVВыберите тип удара...");
            TxText("CLTВыберите тип блока...");

            // ожидание выбора удара (или блока)
            delayfunc();

            // установки ударов и блоков
            SrvSetPunchBlock();
            ClSetPunchBlock();
            PrintFightStartInfo(getUserNameSrvGame(), getUserNameClGame());
            if ((m_SrvPunch == m_ClBlock) && m_SrvPunch != "0" && m_ClBlock != "0")
            {
                TxText("\nУдар блокирован!");
                m_SrvPunch = "0";
                m_ClBlock = "0";
            }
            else if ((m_SrvPunch != m_ClBlock) && m_SrvPunch != "0" && m_ClBlock != "0")
            {
                FightPunch(&P1, &P2);
                emit TxHPSrvGame(QString::number(P1.getHealth()));
                emit TxHPClGame(QString::number(P2.getHealth()));
                TxText("\nУдар пропущен!");
                PrintFightEndInfo(&P2, getUserNameSrvGame(), getUserNameClGame());
                m_SrvPunch = "0";
                m_ClBlock = "0";
            }
        }

        // атака игрока "клиента"
        if ((P1.getHealth() > 0) && (P2.getHealth() > 0))
        {
            TxText("\nАтакует игрок " + getUserNameClGame() + ".");
            TxText("STSCВы атакуете!");
            TxText("STSSВы защищаетесь!");
            TxText("SRVВыберите тип блока...");
            TxText("CLTВыберите тип удара...");

            // ожидание выбора удара (или блока)
            delayfunc();

            // установки ударов и блоков
            SrvSetPunchBlock();
            ClSetPunchBlock();
            PrintFightStartInfo(getUserNameClGame(), getUserNameSrvGame());
            if ((m_ClPunch == m_SrvBlock) && m_ClPunch != "0" && m_SrvBlock != "0")
            {
                TxText("\nУдар блокирован!");
                m_ClPunch = "0";
                m_SrvBlock = "0";
            }
            else if ((m_ClPunch != m_SrvBlock) && m_ClPunch != "0" && m_SrvBlock != "0")
            {
                FightPunch(&P2, &P1);
                emit TxHPSrvGame(QString::number(P1.getHealth()));
                emit TxHPClGame(QString::number(P2.getHealth()));
                TxText("\nУдар пропущен!");
                PrintFightEndInfo(&P1, getUserNameClGame(), getUserNameSrvGame());
                m_SrvPunch = "0";
                m_ClBlock = "0";
            }
        }
    }

    // результат боя
    TxText("\n= Результат поединка: =");
    if (P1.getHealth() == 0)
    {
        TxText("\nИгрок " + getUserNameClGame() + " победил !!!");
        TxText("STSSВы проиграли :(");
        TxText("STSCВы победили :)");
    }
    else if (P2.getHealth() == 0)
    {
        TxText("\nИгрок " + getUserNameSrvGame() + " победил !!!");
        TxText("STSSВы победили :)");
        TxText("STSCВы проиграли :(");
    }
    TxText("\n= Поединок окончен. =");
}



// функция вывода информации в начале атаки
void Game::PrintFightStartInfo(QString Name1, QString Name2)
{
    TxText("\nИгрок " + Name1 + " атакует игрока " + Name2 +" !");
}


// функция вывода информации в конце атаки
void Game::PrintFightEndInfo(Boxer *P2, QString Name1, QString Name2)
{
    TxText("\nИгрок " + Name1 + " атаковал игрока " + Name2 + "!");
    TxText("У игрока " + Name2 + " осталось " + QString::number(P2->getHealth()) + " очков здоровья.");
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
        TxText("*** P-U-N-C-H !!! ***");
    }
}

// функция ожидания пользовательского ввода
void Game::delayfunc()
{
    QEventLoop loop;
    QObject::connect(this, &Game::sigContinueGame, &loop, &QEventLoop::quit);
    loop.exec();
}


// функция установки ударов/блоков для игрока-"сервер"
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


// функция установки ударов/блоков для игрока-"клиент"
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


// == Функции-геттеры ==
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


// == Функции-сеттеры ==
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







