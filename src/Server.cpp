#include <QNetworkInterface>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "Server.hpp"

Server::Server() {
    server = new QTcpServer(this);

    // Настройка сервера
    connect(server, &QTcpServer::newConnection, this, &Server::handleNewConnection);

    qDebug() << "Server is initialized";
}

void Server::startServer() {
    server->listen(this->getPcAddress(), 5555);
    currentId = 0;

    if (server->isListening()) {
        qDebug() << "Server is running";
    }
    else {
        qDebug() << "Server could not be started";
    }
}

void Server::closeServer() {
    for (QTcpSocket *clientSocket : socketToId.keys()) {
        clientSocket->disconnectFromHost();
        clientSocket->deleteLater();
    }

    idToNickname.clear();
    socketToId.clear();
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
    socketToId[clientSocket] = currentId++;

    // Настраиваем реакцию на действия клиента
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::readClientData);
    connect(clientSocket, &QTcpSocket::disconnected, this, &Server::clientDisconnected);

    // Отправляем ip лобби клиенту
    sendLobbyIp(clientSocket);
    
    qDebug() << "New connection. Total clients: " << socketToId.size();
}

void Server::clientDisconnected() {
    // Получаем указатель на отправителя сигнала
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());

    // Освобождаем память
    idToNickname.remove(socketToId[clientSocket]);
    socketToId.remove(clientSocket);
    clientSocket->deleteLater();

    // Отправляем изменение списка игроков
    sendChangedPlayerList();

    qDebug() << "Client has disconnected";
}

void Server::readClientData() {
    // Получаем указатель на отправителя сигнала
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket*>(sender());
    
    // Читаем все присланные данные
    QByteArray data = clientSocket->readAll();

    // Отправляем для определения и манипуляций
    processMessage(data, clientSocket);

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

void Server::postMessage(const QJsonObject &msg, QTcpSocket *target) {
    if (target && target->state() == QAbstractSocket::ConnectedState) {
        target->write(QJsonDocument(msg).toJson(QJsonDocument::Compact));
    }
}

void Server::sendToAll(const QJsonObject &msg) {
    for (QTcpSocket *clientSocket : socketToId.keys()) {
        postMessage(msg, clientSocket);
    }
}

void Server::sendLobbyIp(QTcpSocket *clientSocket) {
    QJsonObject msg;

    msg["type"] = "lobbyIp";
    msg["ip"] = getAddress();

    postMessage(msg, clientSocket);
}

void Server::sendChangedPlayerList() {
    QJsonObject msg;
    msg["type"] = "player_list";
    
    QJsonArray playerArray;
    for (int playerId : idToNickname.keys()) {
        QJsonObject playerObj;
        playerObj["playerId"] = playerId;
        playerObj["nickname"] = idToNickname[playerId];
        playerArray.append(playerObj);
    }
    
    msg["players"] = playerArray;
    sendToAll(msg);
}

void Server::processMessage(const QByteArray &data, QTcpSocket *sender) {
    // Проверяем данные
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull() || !doc.isObject()) return;
    
    // Получаем тип объекта из данных
    QJsonObject msg = doc.object();
    QString type = msg["type"].toString();

    // Смотрим тип и решаем что делать с данными
    if (type == "playerName") { // Клиент отправил свой nickname
        QString nickname = msg["nickname"].toString();
        
        // Присваиваем id nickname
        idToNickname[socketToId[sender]] = nickname;

        // Теперь можно его добавить в список игроков
        sendChangedPlayerList();
        
        qDebug() << "New player: " << socketToId[sender] << nickname;
    }
}