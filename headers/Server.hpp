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

private slots:
    void handleNewConnection();
    void clientDisconnected();
    void readClientData();

private:
    QTcpServer* server;
    QList<QTcpSocket*> clients;

};

#endif