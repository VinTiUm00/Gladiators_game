#include <QJsonObject>
#include <QJsonArray>

#include "Client.hpp"

Client::Client() {
    socket = new QTcpSocket(this);

    // Настраиваем реакцию на события
    connect(socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(socket, &QTcpSocket::readyRead, this, &Client::readServerData);
    connect(socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    connect(socket, &QAbstractSocket::errorOccurred, this, &Client::onError);

    qDebug() << "Client is initialized";
}

void Client::connectToServer(const QString &ip, const QString &newName) {
    socket->connectToHost(ip, 5555, QAbstractSocket::ReadWrite, QAbstractSocket::IPv4Protocol);
    setNickname(newName);

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

void Client::onConnected() {
    emit connectedToServer();

    sendNickname();

    qDebug() << "Connected to the server";
}

void Client::readServerData() {
    // Чтение сообщения с сервера
    QByteArray data = socket->readAll();

    // Обрабатываем сообщение
    handleMessage(data);

    qDebug() << "Server: " << data;
}

void Client::onDisconnected() {
    emit disconnectedFromServer();

    qDebug() << "The connection is broken";
}

void Client::onError() {
    qDebug() << "Network error:" << socket->errorString();
}

void Client::setNickname(const QString &nickname) {
    myName = nickname;
}

void Client::sendMessage(const QJsonObject &msg) {
    if (socket && socket->state() == QAbstractSocket::ConnectedState) {
        socket->write(QJsonDocument(msg).toJson(QJsonDocument::Compact));
    }
}

void Client::sendNickname() {
    QJsonObject msg;

    msg["type"] = "playerName";
    msg["nickname"] = myName;

    sendMessage(msg);
}

void Client::handleMessage(const QByteArray &data) {
    // Проверяем данные
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || !doc.isObject()) return;
    
    // Получаем тип объекта из данных
    QJsonObject msg = doc.object();
    QString type = msg["type"].toString();

    // Смотрим тип и решаем что делать с данными
    if (type == "lobbyIp") { // Сервер прислал свой ip
        QString lobbyIp = msg["ip"].toString();
        
        // Отправляем сигнал с полученным ip
        emit receivedLobbyIp(lobbyIp);
        
        qDebug() << "IP received: " << lobbyIp;
    }
    else if (type == "player_list") { // Сервер прислал новый список игроков
        emit clearListOfPlayers();

        QJsonArray playerArray = msg["players"].toArray();
        for (const QJsonValue &value : playerArray) {
            QJsonObject playerObj = value.toObject();
            int playerId = playerObj["playerId"].toInt();
            QString nickname = playerObj["nickname"].toString();
            
            emit addInfoToPlayerList(playerId, nickname);
        }
        qDebug() << "New player list: " << playerArray.size();
    }
    else if (type == "first_round") { // Сервер прислал тему для первого раунда
        QString theme = msg["theme"].toString();
        
        // Отправляем сигнал с полученной темой
        emit firstRoundThemeAccepted(theme);
        
        qDebug() << "Theme received: " << theme;
    }
}