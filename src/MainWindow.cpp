#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>

#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle("Gladiators"); // Название окна
    
    // Инициализация сети
    server = new Server();
    client = new Client();

    // Создаем контейнер для экранов
    stackScreens = new QStackedWidget(this);
    setCentralWidget(stackScreens);

    // Создаем экраны
    menuScreen = new MenuScreen();
    lobbyScreen = new LobbyScreen();
    connectionScreen = new ConnectionScreen();
    paintingScreen = new PaintingScreen();
    // votingScreen = new VotingScreen();

    // Добавляем экраны в стек
    stackScreens->addWidget(menuScreen);
    stackScreens->addWidget(lobbyScreen);
    stackScreens->addWidget(connectionScreen);
    stackScreens->addWidget(paintingScreen);
    // stack->addWidget(votingScreen);

    // Показываем главное меню по умолчанию
    stackScreens->setCurrentWidget(menuScreen);

    // Подключаем сигналы от кнопок меню
    connect(menuScreen, &MenuScreen::createLobbyClicked, this, &MainWindow::createGame);
    connect(menuScreen, &MenuScreen::connectLobbyClicked, this, &MainWindow::connectGame);
    connect(menuScreen, &MenuScreen::exitBtnClicked, this, &MainWindow::exit);
    
    connect(lobbyScreen, &LobbyScreen::createGameClicked, server, &Server::firstRoundStarts);
    connect(lobbyScreen, &LobbyScreen::backToMenuClicked, this, &MainWindow::backToMenu);

    connect(connectionScreen, &ConnectionScreen::connectToGame, client, &Client::connectToServer);
    connect(connectionScreen, &ConnectionScreen::backClicked, this, &MainWindow::backToMenu);

    connect(client, &Client::connectedToServer, lobbyScreen, [this]() {
        stackScreens->setCurrentWidget(lobbyScreen);});
    connect(client, &Client::disconnectedFromServer, this, &MainWindow::backToMenu);
    connect(client, &Client::receivedLobbyIp, lobbyScreen, &LobbyScreen::setIpLabel);
    connect(client, &Client::clearListOfPlayers, lobbyScreen, &LobbyScreen::clearPlayersList);
    connect(client, &Client::addInfoToPlayerList, lobbyScreen, &LobbyScreen::addPlayerToList);

    connect(client, &Client::firstRoundThemeAccepted, [this](const QString &theme) {
        paintingScreen->setThemeLabel(theme);
        openCanvas();
    });

    connect(server, &Server::playerListPosted, lobbyScreen, &LobbyScreen::checkStartConditions);

    connect(paintingScreen, &PaintingScreen::exitLobbyClicked, this, &MainWindow::backToMenu);
    // connect(votingScreen, &VotingScreen::exitVotingClicked, this, &MainWindow::backToMenu);
}

void MainWindow::createGame(){
    lobbyScreen->setLobbyStatus("Лобби создано. Ожидаем подключения игроков.");
    lobbyScreen->setStartEnabled(false);

    lobbyScreen->setHostRole(true);

    server->startServer();
    client->connectToServer(server->getAddress(), "Хост");
}

void MainWindow::connectGame(){
    lobbyScreen->setHostRole(false);
    stackScreens->setCurrentWidget(connectionScreen);
}

void MainWindow::backToMenu(){
    stackScreens->setCurrentWidget(menuScreen);
    lobbyScreen->clearPlayersList();

    server->closeServer();
    client->disconnectFromServer();
}

void MainWindow::exit(){
    this->close();
}

void MainWindow::openCanvas(){
    paintingScreen->newCanvas();
    stackScreens->setCurrentWidget(paintingScreen);
}

/*
void MainWindow::onGameStateChanged(int state) {
    GameState gameState = static_cast<GameState>(state);
    
    if (gameState == GameState::DRAWING) {
        paintingScreen->onGameStateChanged(state);
    } else if (gameState == GameState::VOTING) {
        paintingScreen->onGameStateChanged(state);
        QList<int> playerIds;
        for (int i = 0; i < networkManager->getPlayerCount(); ++i) {
            playerIds.append(i);
        }
        votingScreen->startVoting(playerIds, playerDrawings);
        stack->setCurrentWidget(votingScreen);
    }
}
*/

/*
void MainWindow::onVotingStarted(const QList<int> &playerIds) {
    votingScreen->startVoting(playerIds, playerDrawings);
    stack->setCurrentWidget(votingScreen);
}
*/