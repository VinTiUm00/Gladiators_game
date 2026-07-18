#ifndef NETWORKMANAGER_HPP
#define NETWORKMANAGER_HPP

#include <QObject>
#include <QList>
#include <QColor>
#include <QPoint>
#include <QString>

enum class GameState {
    WAITING_FOR_PLAYERS,
    DRAWING,
    VOTING,
    FINISHED
};

struct DrawingEvent {
    int playerId;
    QPoint from;
    QPoint to;
    QColor color;
    int width;
};

class NetworkManager : public QObject {
    Q_OBJECT

public:
    explicit NetworkManager(QObject *parent = nullptr);
    ~NetworkManager();

    void startServer(int port = 5555);
    void stopServer();
    void connectToServer(const QString &host, int port = 5555);
    void disconnectFromServer();

    void setPlayerId(int id);
    void setPlayerNickname(const QString &nickname);
    void broadcastDrawingEvent(const DrawingEvent &event);
    void startGameSession();
    void beginLobby();
    void changeGameState(GameState state);
    void broadcastVote(int votedPlayerId);
    void addConnectedPlayer(int playerId, const QString &nickname);
    void removeConnectedPlayer(int playerId);

    bool isHost() const { return isHostMode; }
    bool isConnected() const { return playerCount > 0; }
    GameState getCurrentGameState() const { return currentGameState; }
    int getPlayerId() const { return playerId; }
    int getPlayerCount() const { return playerCount; }

signals:
    void playerConnected(int playerId, const QString &nickname);
    void playerDisconnected(int playerId);
    void drawingEventReceived(const DrawingEvent &event);
    void gameStateChanged(int state);
    void gameStarted();
    void votingStarted(const QList<int> &playerIds);
    void votesReceived(int playerId, int votes);
    void connectionError(const QString &error);

private:
    bool isHostMode;
    int playerId;
    int playerCount;
    QString playerNickname;
    GameState currentGameState;
};

#endif
