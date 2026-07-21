#include "Client.hpp"

Client::Client() {
    socket = new QTcpSocket(this);

    // Настраиваем реакцию на события
    connect(socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    connect(socket, &QAbstractSocket::errorOccurred, this, &Client::onError);

    qDebug() << "Client is initialized";
}

void Client::connectToServer(const QString &ip) {
    socket->connectToHost(ip, 5555, QAbstractSocket::ReadWrite, QAbstractSocket::IPv4Protocol);

    if (socket->state() == QAbstractSocket::ConnectedState){
        qDebug() << "Client has connected to the server";
    }
    else if (socket->state() == QAbstractSocket::HostLookupState) {
        qDebug() << "Client is looking for a server";
    }
    else if (socket->state() == QAbstractSocket::ConnectingState) {
        qDebug() << "Client is connecting to the server";
    }
    else if (socket->state() == QAbstractSocket::UnconnectedState){
        qDebug() << "Client could not connect to the server";
    }
    else {qDebug() << socket->state();}
}

void Client::disconnectFromServer() {
    socket->disconnectFromHost();

    if (socket->state() == QAbstractSocket::ConnectedState){
        qDebug() << "Client could not disconnect from the server";
    }
    else if (socket->state() == QAbstractSocket::UnconnectedState){
        qDebug() << "Client disconnected from the server";
    }
    else {qDebug() << socket->state();}
}

void Client::sendAction(const QString &action){
    socket->write(action.toUtf8());
}

void Client::onConnected() {
    // //
    qDebug() << "Connected to the server";
}

void Client::onReadyRead() {
    // Чтение сообщения с сервера
    QByteArray data = socket->readAll();

    qDebug() << "Server: " << data;
}

void Client::onDisconnected() {
    qDebug() << "The connection is broken";
}

void Client::onError() {
    qDebug() << "Network error:" << socket->errorString();
}