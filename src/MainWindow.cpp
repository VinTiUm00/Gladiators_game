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
    
    connect(lobbyScreen, &LobbyScreen::createGameClicked, this, &MainWindow::openCanvas);
    connect(lobbyScreen, &LobbyScreen::backToMenuClicked, this, &MainWindow::backToMenu);

    connect(connectionScreen, &ConnectionScreen::connectToGame, client, &Client::connectToServer);
    connect(connectionScreen, &ConnectionScreen::backClicked, this, &MainWindow::backToMenu);
    connect(client, &Client::connectedToServer, lobbyScreen, [this]() {
        stackScreens->setCurrentWidget(lobbyScreen);});
    connect(client, &Client::disconnectedFromServer, this, &MainWindow::backToMenu);

    connect(paintingScreen, &PaintingScreen::exitLobbyClicked, this, &MainWindow::backToMenu);
    // connect(votingScreen, &VotingScreen::exitVotingClicked, this, &MainWindow::backToMenu);

    // Подключаем сигналы от NetworkManager
    //connect(networkManager, QOverload<int, const QString &>::of(&NetworkManager::playerConnected),
    //        this, &MainWindow::onPlayerConnected);
}

void MainWindow::createGame(){
    /*
    networkManager->startServer();
    networkManager->setPlayerId(0);
    networkManager->setPlayerNickname("Host");
    networkManager->beginLobby();
    */
    lobbyScreen->setLobbyStatus("Лобби создано. Ожидаем подключения игроков.");
    lobbyScreen->setPlayers({"Host"});
    lobbyScreen->setStartEnabled(false);

    stackScreens->setCurrentWidget(lobbyScreen);

    server->startServer();

    lobbyScreen->setIpLabel(server->getAddress());
}

void MainWindow::connectGame(){
    /*
    networkManager->connectToServer("127.0.0.1", 5555);
    networkManager->setPlayerId(1);
    networkManager->setPlayerNickname("Player");
    networkManager->beginLobby();
    */
    stackScreens->setCurrentWidget(connectionScreen);
}

void MainWindow::backToMenu(){
    /*
    networkManager->stopServer();
    networkManager->disconnectFromServer();
    */
    stackScreens->setCurrentWidget(menuScreen);

    server->closeServer();
    client->disconnectFromServer();
}

void MainWindow::exit(){
    /*
    networkManager->stopServer();
    networkManager->disconnectFromServer();
    */
    this->close();
}

void MainWindow::openCanvas(){
    /*
    if (networkManager->isHost()) {
        networkManager->addConnectedPlayer(1, "Player");
        networkManager->startGameSession();
    } else {
        networkManager->startGameSession();
    }
    */
    paintingScreen->newCanvas();
    stackScreens->setCurrentWidget(paintingScreen);
}

/*
void MainWindow::onPlayerConnected(int playerId, const QString &nickname) {
    qDebug() << "Player connected:" << playerId << nickname;
    if (networkManager->isHost()) {
        lobbyCreatorScreen->setLobbyStatus("Игрок подключился. Можно запускать игру.");
        lobbyCreatorScreen->setPlayers({"Host", nickname});
        lobbyCreatorScreen->setStartEnabled(true);
        stack->setCurrentWidget(lobbyCreatorScreen);
    }
}
*/
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
/*
void MainWindow::onConnectionError(const QString &error) {
    QMessageBox::critical(this, "Connection Error", error);
}
*/