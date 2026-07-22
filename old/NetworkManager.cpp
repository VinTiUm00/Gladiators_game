#include "NetworkManager.hpp"
#include <QDebug>

NetworkManager::NetworkManager(QObject *parent)
    : QObject(parent), isHostMode(false), playerId(-1), playerCount(0), 
      currentGameState(GameState::WAITING_FOR_PLAYERS) {
}

NetworkManager::~NetworkManager() {
}

void NetworkManager::startServer(int port) {
    isHostMode = true;
    playerId = 0;
    playerCount = 1;
    currentGameState = GameState::WAITING_FOR_PLAYERS;
    emit gameStateChanged((int)currentGameState);
    qDebug() << "Server started on port" << port;
}

void NetworkManager::stopServer() {
    if (isHostMode) {
        qDebug() << "Server stopped";
    }
}

void NetworkManager::connectToServer(const QString &host, int port) {
    isHostMode = false;
    playerId = 1;
    playerCount = 2;
    currentGameState = GameState::WAITING_FOR_PLAYERS;
    emit gameStateChanged((int)currentGameState);
    qDebug() << "Connected to server at" << host << ":" << port;
}

void NetworkManager::disconnectFromServer() {
    if (!isHostMode) {
        qDebug() << "Disconnected from server";
    }
}

void NetworkManager::setPlayerId(int id) {
    playerId = id;
}

void NetworkManager::setPlayerNickname(const QString &nickname) {
    playerNickname = nickname;
}

void NetworkManager::broadcastDrawingEvent(const DrawingEvent &event) {
    // For now, just echo locally
    qDebug() << "Drawing event from player" << event.playerId;
}

void NetworkManager::beginLobby() {
    currentGameState = GameState::WAITING_FOR_PLAYERS;
    emit gameStateChanged((int)currentGameState);
}

void NetworkManager::startGameSession() {
    changeGameState(GameState::DRAWING);
    emit gameStarted();
}

void NetworkManager::changeGameState(GameState state) {
    currentGameState = state;
    emit gameStateChanged((int)state);
}

void NetworkManager::broadcastVote(int votedPlayerId) {
    qDebug() << "Vote from player" << playerId << "to player" << votedPlayerId;
}

void NetworkManager::addConnectedPlayer(int playerId, const QString &nickname) {
    playerCount = qMax(playerCount, playerId + 1);
    emit playerConnected(playerId, nickname);
}

void NetworkManager::removeConnectedPlayer(int playerId) {
    emit playerDisconnected(playerId);
}
