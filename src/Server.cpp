#include "Server.hpp"

Server::Server() {
    server = new QTcpServer(this);

    // Настройка сервера
    server->listen(QHostAddress::Any, 5555);
    connect(server, &QTcpServer::newConnection, this, &Server::handleNewConnection);

    qDebug() << "Сервер запущен";
}

void Server::handleNewConnection() {
    // "Ловим" сокет нового клиента
    QTcpSocket *clientSocket = server->nextPendingConnection();

    // Сохраняем его в список
    clients.append(clientSocket);

    // Настраиваем реакцию на действия клиента
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::readClientData);
    connect(clientSocket, &QTcpSocket::disconnected, this, &Server::clientDisconnected);
    
    qDebug() << "Новое подключение. Всего клиентов: " << clients.size();
}

void Server::clientDisconnected() {
    // Получаем указатель на отправителя сигнала
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());

    // Освобождаем память
    clients.removeOne(clientSocket);
    clientSocket->deleteLater();

    qDebug() << "Клиент отключился";
}

void Server::readClientData() {
    // Получаем указатель на отправителя сигнала
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    
    // Читаем все присланные данные
    QByteArray data = clientSocket->readAll();

    qDebug() << "Получено от клиента: " << data;
}