#include <QVBoxLayout>

#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent){
    setWindowTitle("Gladiators"); // Название окна

    // Создаем контейнер
    stack = new QStackedWidget(this);
    setCentralWidget(stack);

    // Создаем экраны
    menuScreen = new MenuScreen();
    lobbyCreatorScreen = new LobbyCreatorScreen();
    lobbyConnectionScreen = new LobbyConnectionScreen();
    paintingScreen = new PaintingScreen();

    // Добавляем экраны в стек
    stack->addWidget(menuScreen);
    stack->addWidget(lobbyCreatorScreen);
    stack->addWidget(lobbyConnectionScreen);
    stack->addWidget(paintingScreen);

    // Показываем главное меню по умолчанию
    stack->setCurrentWidget(menuScreen);

    // Подключаем сигналы от кнопок меню
    connect(menuScreen, &MenuScreen::startGameClicked, this, &MainWindow::createGame);
    connect(menuScreen, &MenuScreen::connectGameClicked, this, &MainWindow::connectGame);
    connect(menuScreen, &MenuScreen::exitBtnClicked, this, &MainWindow::exit);
    
    connect(lobbyCreatorScreen, &LobbyCreatorScreen::createGameClicked, this, &MainWindow::openCanvas);
    connect(lobbyCreatorScreen, &LobbyCreatorScreen::backToMenuClicked, this, &MainWindow::backToMenu);

    connect(lobbyConnectionScreen, &LobbyConnectionScreen::backClicked, this, &MainWindow::backToMenu);

    connect(paintingScreen, &PaintingScreen::exitLobbyClicked, this, &MainWindow::backToMenu);
}

void MainWindow::createGame(){
    stack->setCurrentWidget(lobbyCreatorScreen);
}

void MainWindow::connectGame(){
    stack->setCurrentWidget(lobbyConnectionScreen);
}

void MainWindow::backToMenu(){
    stack->setCurrentWidget(menuScreen);
}

void MainWindow::exit(){
    this->close();
}

void MainWindow::openCanvas(){
    stack->setCurrentWidget(paintingScreen);
}