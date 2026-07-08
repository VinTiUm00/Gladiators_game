#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QStackedWidget>

#include "MenuScreen.hpp"
#include "LobbyCreatorScreen.hpp"
#include "LobbyConnectionScreen.hpp"
#include "PaintingScreen.hpp"
// Другие окна

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

private slots:
    void createGame();
    void connectGame();
    void backToMenu();
    void exit();
    void openCanvas();
};

#endif