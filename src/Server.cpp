#include <QNetworkInterface>

#include "Server.hpp"

Server::Server() {
    server = new QTcpServer(this);

    // Настройка сервера
    connect(server, &QTcpServer::newConnection, this, &Server::handleNewConnection);

    qDebug() << "Server is initialized";
}

void Server::startServer() {
    server->listen(this->getPcAddress(), 5555);

    if (server->isListening()) {
        qDebug() << "Server is running";
    }
    else {
        qDebug() << "Server could not be started";
    }
}

void Server::closeServer() {
    server->close();

    if (server->isListening()) {
        qDebug() << "Server could not be disabled";
    }
    else {
        qDebug() << "Server is turned off";
    }
}

QString Server::getAddress() {
    qDebug() << "Server IP: " << server->serverAddress().toString();

    return server->serverAddress().toString();
}

void Server::handleNewConnection() {
    // "Ловим" сокет нового клиента
    QTcpSocket *clientSocket = server->nextPendingConnection();

    // Сохраняем его в список
    clients.append(clientSocket);

    // Настраиваем реакцию на действия клиента
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::readClientData);
    connect(clientSocket, &QTcpSocket::disconnected, this, &Server::clientDisconnected);
    
    qDebug() << "New connection. Total clients: " << clients.size();
}

void Server::clientDisconnected() {
    // Получаем указатель на отправителя сигнала
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());

    // Освобождаем память
    clients.removeOne(clientSocket);
    clientSocket->deleteLater();

    qDebug() << "Client has disconnected";
}

void Server::readClientData() {
    // Получаем указатель на отправителя сигнала
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    
    // Читаем все присланные данные
    QByteArray data = clientSocket->readAll();

    qDebug() << "Received from the client: " << data;
}

QHostAddress Server::getPcAddress() {
    QList<QHostAddress> list = QNetworkInterface::allAddresses();

    for(int nIter=0; nIter<list.count(); nIter++) {
        if (!list[nIter].isLoopback()) {
            if (list[nIter].protocol() == QAbstractSocket::IPv4Protocol) {
                qDebug() << "IP available: " << list[nIter].toString();

                return list[nIter];
            }
        }
    }

    qDebug() << "No IP available, the standard one will be used (127.0.0.1)";
    
    return QHostAddress("127.0.0.1");
}