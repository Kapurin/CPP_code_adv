#ifndef GUIWORKER_H
#define GUIWORKER_H

#include <QObject>
#include "backend.h"

/* Примечания:
 * 1) данный класс Guiworker является классом-"посредником" между
 * GUI QML и классом Backend.
 * 2) объект класса Backend работает в отдельном потоке.
 * В классе Backend реализован весь бекэнд игры.
 */

class Guiworker : public QObject
{
    Q_OBJECT

    // имена игроков
    Q_PROPERTY(QString userNameSrv READ getUserNameSrv WRITE setUserNameSrv NOTIFY updUserNameSrv)
    Q_PROPERTY(QString userNameCl READ getUserNameCl WRITE setUserNameCl NOTIFY updUserNameCl)

    // уровень НР игроков
    Q_PROPERTY(QString userHPSrv READ getHPSrv WRITE setHPSrv NOTIFY updHPSrv)
    Q_PROPERTY(QString userHPCl READ getHPCl WRITE setHPCl NOTIFY updHPCl)

    // IP адрес игрока-"сервер"
    Q_PROPERTY(QString ipAddress READ getIpGame WRITE setIpGame NOTIFY updIpGame)

    // статус игры
    Q_PROPERTY(QString statusGame READ getStatusGame WRITE setStatusGame NOTIFY updStatusGame)

    // информационные сообщения в поле вывода игрового процесса (QML)
    Q_PROPERTY(QString txTextToQML READ getTxTextToQML WRITE setTxTextToQML NOTIFY upTxTextToQML)

public:
    Guiworker();
    ~Guiworker();

    QThread *threadBackend = nullptr;
    Backend *gameback = nullptr;

    // == Функции-геттеры ==
    // имена игроков
    QString getUserNameSrv();
    QString getUserNameCl();

    // текущие уровни НР игроков
    QString getHPSrv();
    QString getHPCl();

    // IP адрес игрока-"сервер"
    QString getIpGame();

    // статус игры
    QString getStatusGame();

    // информационные сообщения в поле вывода игрового процесса (QML)
    QString getTxTextToQML();


    // == Функции-сеттеры ==
    // имена игроков
    void setUserNameSrv(QString name);
    void setUserNameCl(QString name);

    // IP адрес игрока-"сервер"
    void setIpGame(QString ip_add);

    // статус игры
    void setStatusGame(QString status);

    // информационные сообщения в поле вывода игрового процесса (QML)
    void setTxTextToQML(QString TxText);

private:
    QString m_UserNameSrv = "Player Server";
    QString m_UserNameCl = "Player Client";
    QString m_HPSrv = "100";
    QString m_HPCl = "100";
    QString m_IpGame = "0";
    QString m_StatusGame = "[пусто]";
    QString m_TxTextToQML;

public slots:
    // функции-сеттеры текущих уровней НР игроков
    void setHPSrv(QString);
    void setHPCl(QString);

    // функция инициализации данных в начале игры
    void initData();

    // == Кнопки (GUI QML) ==
    // выбор ударов/блоков для игрока-"сервер"
    void buttGWSrvPunchHead();
    void buttGWSrvPunchBody();
    void buttGWSrvBlockHead();
    void buttGWSrvBlockBody();

    // выбор ударов/блоков для игрока-"клиент"
    void buttGWClPunchHead();
    void buttGWClPunchBody();
    void buttGWClBlockHead();
    void buttGWClBlockBody();

    // Кнопки основных действий с игрой
    // кнопка создания игры
    void buttGWCreateGame();

    // кнопка завершения игры
    void buttGWDestroyGame();

    // кнопка подключения к игре
    void buttGWJoinGame();

    // кнопка отключения от игры
    void buttGWDisconGame();

private slots:
    // функция приема данных для игрока-"сервер"
    void GWPrintText(QString);

    // функция приема данных для игрока-"клиент"
    void GWPrintTextCl(QString);

signals:
    // передача данных для игрока-"сервер"
    void sendGWText(QString);

    // передача данных для игрока-"клиент"
    void sendGWTextCl(QString);

    // остановка воспроизведения фонового саундтрека
    void sigStopMusic();

    // == Сигналы обновления параметров в GUI QML ==
    // передача имен игроков
    void updUserNameSrv(QString);
    void updUserNameCl(QString);

    // передача текущих уровней НР игроков
    void updHPSrv(QString);
    void updHPCl(QString);

    // передача IP адреса игрока-"сервер"
    void updIpGame(QString);

    // передача статуса игры
    void updStatusGame(QString);

    // передача информационных сообщений в поле вывода игрового процесса (QML)
    void upTxTextToQML(QString);


    // == Сигналы для отправки в "Backend" ==
    // сигнал создания игры
    void sigGWCreateGame();

    // сигнал завершения игры
    void sigGWDestroyGame();

    // сигнал подключения к игре
    void sigGWJoinGame();

    // сигнал отключения от игры
    void sigGWDisconGame();

    // сигнал запуска игры
    void sigStartGame();

    // == Сигналы от кнопок (GUI QML) ==
    // выбор ударов/блоков для игрока-"сервер"
    void sigGWSrvPunchHead();
    void sigGWSrvPunchBody();
    void sigGWSrvBlockHead();
    void sigGWSrvBlockBody();

    // выбор ударов/блоков для игрока-"клиент"
    void sigGWClPunchHead();
    void sigGWClPunchBody();
    void sigGWClBlockHead();
    void sigGWClBlockBody();
};

#endif // GUIWORKER_H
