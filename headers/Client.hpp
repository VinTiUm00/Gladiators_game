#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QTcpSocket>

class Client : public QObject {

    Q_OBJECT

public:
    Client();
    ~Client() = default;

    void disconnectFromServer();

public slots:
    void connectToServer(const QString &ip, const QString &newName);

signals:
    void connectedToServer();
    void disconnectedFromServer();
    void receivedLobbyIp(const QString &lobbyIp);
    void clearListOfPlayers();
    void addInfoToPlayerList(int playerId, QString nickname);

private slots:
    void onConnected();
    void readServerData();
    void onDisconnected();
    void onError();

    void setNickname(const QString &nickname);

private:
    QTcpSocket* socket;

    QString myName;
    void sendMessage(const QJsonObject &msg);
    void sendNickname();
    void handleMessage(const QByteArray &data);
};

#endif