#include "Client.hpp"

Client::Client() {
    socket = new QTcpSocket(this);

    // Настраиваем реакцию на события
    connect(socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    connect(socket, &QAbstractSocket::errorOccurred, this, &Client::onError);

    qDebug() << "Клиент инициализирован";
}

void Client::connectToServer(const QString &ip) {
    socket->connectToHost(ip, 5555);
}

void Client::sendAction(const QString &action){
    socket->write(action.toUtf8());
}

void Client::onConnected() {
    // //
    qDebug() << "Подключен к серверу";
}

void Client::onReadyRead() {
    // Чтение сообщения с сервера
    QByteArray data = socket->readAll();

    qDebug() << "Сервер: " << data;
}

void Client::onDisconnected() {
    qDebug() << "Соединение разорвано";
}

void Client::onError() {
    qDebug() << "Ошибка сети:" << socket->errorString();
}