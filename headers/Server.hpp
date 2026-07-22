#ifndef SERVER_HPP
#define SERVER_HPP

#include <QTcpServer>
#include <QTcpSocket>

class Server : public QObject {

    Q_OBJECT

public:
    Server();
    ~Server() = default;

    QString getAddress();

public slots:
    void startServer();
    void closeServer();

    void firstRoundStarts();

signals:
    void playerListPosted(int playerCount);

private slots:
    void handleNewConnection();
    void clientDisconnected();
    void readClientData();
    void sendChangedPlayerList();

private:
    QTcpServer* server;

    QHash<QTcpSocket*, int> socketToId;
    QHash<int, QString> idToNickname;
    QHash<int, QString> idToTheme;
    int currentId;

    QHostAddress getPcAddress();
    void processMessage(const QByteArray &data, QTcpSocket *sender);
    void postMessage(const QJsonObject &msg, QTcpSocket *target);
    void sendLobbyIp(QTcpSocket *clientSocket);
    void sendToAll(const QJsonObject &msg);
    
    void loadThemes();
    void sendForFirstRound(const QString &theme, QTcpSocket *player);

    QStringList themes;
    QStringList usedThemes;
};

#endif