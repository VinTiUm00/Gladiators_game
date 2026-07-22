#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QStackedWidget>
#include <QMap>
#include <QPixmap>

#include "MenuScreen.hpp"
#include "LobbyScreen.hpp"
#include "ConnectionScreen.hpp"
#include "PaintingScreen.hpp"
#include "Server.hpp"
#include "Client.hpp"
// #include "VotingScreen.hpp"

class MainWindow : public QMainWindow {

    Q_OBJECT // Макрос, без которого не работают сигналы

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    QStackedWidget *stackScreens;

    // Экраны
    MenuScreen *menuScreen;
    LobbyScreen *lobbyScreen;
    ConnectionScreen *connectionScreen;
    PaintingScreen *paintingScreen;
    // VotingScreen *votingScreen;

    // Сеть
    Server* server;
    Client* client;

private slots:
    void createGame();
    void connectGame();
    void backToMenu();
    void exit();
    void openCanvas();
    
    // Сетевые слоты
    //void onPlayerConnected(int playerId, const QString &nickname);
    //void onGameStateChanged(int state);
    //void onVotingStarted(const QList<int> &playerIds);
    //void onConnectionError(const QString &error);
};

#endif