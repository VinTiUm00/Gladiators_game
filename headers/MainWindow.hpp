#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QStackedWidget>
#include <QMap>
#include <QPixmap>

#include "MenuScreen.hpp"
#include "LobbyCreatorScreen.hpp"
#include "LobbyConnectionScreen.hpp"
#include "PaintingScreen.hpp"
#include "VotingScreen.hpp"

class NetworkManager;
struct DrawingEvent;

class MainWindow : public QMainWindow {

    Q_OBJECT // Макрос, без которого не работают сигналы

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    QStackedWidget *stack;

    // Экраны
    MenuScreen *menuScreen;
    LobbyCreatorScreen *lobbyCreatorScreen;
    LobbyConnectionScreen *lobbyConnectionScreen;
    PaintingScreen *paintingScreen;
    VotingScreen *votingScreen;

    // Сетевой менеджер
    NetworkManager *networkManager;

    // Данные игроков
    QMap<int, QPixmap> playerDrawings;

private slots:
    void createGame();
    void connectGame();
    void backToMenu();
    void exit();
    void openCanvas();
    
    // Сетевые слоты
    void onPlayerConnected(int playerId, const QString &nickname);
    void onGameStateChanged(int state);
    void onDrawingEventReceived(const DrawingEvent &event);
    void onVotingStarted(const QList<int> &playerIds);
    void onConnectionError(const QString &error);
};

#endif