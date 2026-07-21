#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <QTcpSocket>

class Client : public QObject {

    Q_OBJECT

public:
    Client();
    ~Client() = default;

    void connectToServer(const QString &ip);
    void disconnectFromServer();
    void sendAction(const QString &action); // Временно или постоянно QString

private slots:
    void onConnected();
    void onReadyRead();
    void onDisconnected();
    void onError();

private:
    QTcpSocket* socket;
};

#endif