#include <QVBoxLayout>
#include <QMessageBox>
#include <QDebug>

#include "MainWindow.hpp"
#include "NetworkManager.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), networkManager(nullptr){
    setWindowTitle("Gladiators"); // Название окна

    // Создаем сетевой менеджер
    networkManager = new NetworkManager(this);

    // Создаем контейнер
    stack = new QStackedWidget(this);
    setCentralWidget(stack);

    // Создаем экраны
    menuScreen = new MenuScreen();
    lobbyCreatorScreen = new LobbyCreatorScreen();
    lobbyConnectionScreen = new LobbyConnectionScreen();
    paintingScreen = new PaintingScreen();
    votingScreen = new VotingScreen();

    // Передаем NetworkManager экранам
    paintingScreen->setNetworkManager(networkManager);
    votingScreen->setNetworkManager(networkManager);

    // Добавляем экраны в стек
    stack->addWidget(menuScreen);
    stack->addWidget(lobbyCreatorScreen);
    stack->addWidget(lobbyConnectionScreen);
    stack->addWidget(paintingScreen);
    stack->addWidget(votingScreen);

    // Показываем главное меню по умолчанию
    stack->setCurrentWidget(menuScreen);

    // Подключаем сигналы от кнопок меню
    connect(menuScreen, &MenuScreen::startGameClicked, this, &MainWindow::createGame);
    connect(menuScreen, &MenuScreen::connectGameClicked, this, &MainWindow::connectGame);
    connect(menuScreen, &MenuScreen::exitBtnClicked, this, &MainWindow::exit);
    
    connect(lobbyCreatorScreen, &LobbyCreatorScreen::createGameClicked, this, &MainWindow::openCanvas);
    connect(lobbyCreatorScreen, &LobbyCreatorScreen::backToMenuClicked, this, &MainWindow::backToMenu);

    connect(lobbyConnectionScreen, &LobbyConnectionScreen::connectToGame, this, [this] (QString ip){
        try {
            this->networkManager->connectToServer(ip, 5555);
            this->stack->setCurrentWidget(lobbyCreatorScreen);
        }
        catch (std::exception) {
            // Временное решение
        }
    });
    connect(lobbyConnectionScreen, &LobbyConnectionScreen::backClicked, this, &MainWindow::backToMenu);
    connect(networkManager, &NetworkManager::playerConnected, lobbyCreatorScreen, &LobbyCreatorScreen::playerConnected);

    connect(paintingScreen, &PaintingScreen::exitLobbyClicked, this, &MainWindow::backToMenu);
    connect(votingScreen, &VotingScreen::exitVotingClicked, this, &MainWindow::backToMenu);

    // Подключаем сигналы от NetworkManager
    connect(networkManager, QOverload<int, const QString &>::of(&NetworkManager::playerConnected),
            this, &MainWindow::onPlayerConnected);
}

void MainWindow::createGame(){
    networkManager->startServer();
    networkManager->setPlayerId(0);
    networkManager->setPlayerNickname("Host");
    networkManager->beginLobby();
    lobbyCreatorScreen->setLobbyStatus("Лобби создано. Ожидаем подключения игроков.");
    lobbyCreatorScreen->setPlayers({"Host"});
    lobbyCreatorScreen->setStartEnabled(false);
    stack->setCurrentWidget(lobbyCreatorScreen);
}

void MainWindow::connectGame(){
    /*
    networkManager->connectToServer("127.0.0.1", 5555);
    networkManager->setPlayerId(1);
    networkManager->setPlayerNickname("Player");
    networkManager->beginLobby();
    */
    stack->setCurrentWidget(lobbyConnectionScreen);
}

void MainWindow::backToMenu(){
    networkManager->stopServer();
    networkManager->disconnectFromServer();
    stack->setCurrentWidget(menuScreen);
}

void MainWindow::exit(){
    networkManager->stopServer();
    networkManager->disconnectFromServer();
    this->close();
}

void MainWindow::openCanvas(){
    if (networkManager->isHost()) {
        networkManager->addConnectedPlayer(1, "Player");
        networkManager->startGameSession();
    } else {
        networkManager->startGameSession();
    }
    paintingScreen->newCanvas();
    stack->setCurrentWidget(paintingScreen);
}

void MainWindow::onPlayerConnected(int playerId, const QString &nickname) {
    qDebug() << "Player connected:" << playerId << nickname;
    if (networkManager->isHost()) {
        lobbyCreatorScreen->setLobbyStatus("Игрок подключился. Можно запускать игру.");
        lobbyCreatorScreen->setPlayers({"Host", nickname});
        lobbyCreatorScreen->setStartEnabled(true);
        stack->setCurrentWidget(lobbyCreatorScreen);
    }
}

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

void MainWindow::onDrawingEventReceived(const DrawingEvent &event) {
    paintingScreen->onStartVoting(QList<int>());
}

void MainWindow::onVotingStarted(const QList<int> &playerIds) {
    votingScreen->startVoting(playerIds, playerDrawings);
    stack->setCurrentWidget(votingScreen);
}

void MainWindow::onConnectionError(const QString &error) {
    QMessageBox::critical(this, "Connection Error", error);
}