#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSizePolicy>

#include "LobbyScreen.hpp"

LobbyScreen::LobbyScreen(QWidget* parent) : QWidget(parent){
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(14);
    layout->setContentsMargins(40, 40, 40, 40);

    QLabel* titleLabel = new QLabel("Лобби", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("QLabel { color: #ffffff; font-size: 32px; font-weight: 800; }");

    QLabel* hintLabel = new QLabel("Сначала создаётся лобби. Когда игроки подключатся, хост сможет начать игру.", this);
    hintLabel->setWordWrap(true);
    hintLabel->setAlignment(Qt::AlignCenter);
    hintLabel->setMaximumWidth(560);
    hintLabel->setStyleSheet("QLabel { color: #ffffff; font-size: 16px; font-weight: 600; }");

    statusLabel = new QLabel("Ожидание игроков...", this);
    statusLabel->setAlignment(Qt::AlignCenter);
    statusLabel->setStyleSheet("QLabel { color: #e7e7ff; font-size: 15px; font-weight: 600; }");

    // IP для подключения к лобби
    ipLabel = new QLabel("IP лобби: ", this);
    ipLabel->setAlignment(Qt::AlignCenter);
    ipLabel->setWordWrap(false);
    ipLabel->setMaximumWidth(560);
    ipLabel->setStyleSheet("QLabel { color: #cfe8ff; font-size: 14px; }");

    // Список подключенных игроков
    playersList = new QListWidget(this);
    playersList->setSortingEnabled(true);
    playersList->setDragEnabled(false);
    playersList->setSelectionMode(QAbstractItemView::NoSelection);

    createGameBtn = new QPushButton("Запуск игры", this);
    createGameBtn->setFixedHeight(48);
    createGameBtn->setFixedWidth(230);
    createGameBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    createGameBtn->setEnabled(false);

    QPushButton *backToMenuBtn = new QPushButton("Назад в меню", this);
    backToMenuBtn->setFixedHeight(48);
    backToMenuBtn->setFixedWidth(200);
    backToMenuBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    createGameBtn->setStyleSheet("QPushButton { background-color: #6dbf6b; color: white; font-weight: 700; font-size: 16px; border-radius: 10px; padding: 0 16px; }");
    backToMenuBtn->setStyleSheet("QPushButton { background-color: #AF505A; color: white; font-weight: 700; font-size: 16px; border-radius: 10px; padding: 0 16px; }");

    layout->addStretch();
    layout->addWidget(titleLabel, 0, Qt::AlignHCenter);
    layout->addWidget(hintLabel, 0, Qt::AlignHCenter);
    layout->addWidget(statusLabel, 0, Qt::AlignHCenter);
    layout->addWidget(ipLabel, 0, Qt::AlignHCenter);
    layout->addWidget(playersList, 0, Qt::AlignHCenter);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->setSpacing(12);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(createGameBtn);
    buttonsLayout->addWidget(backToMenuBtn);
    buttonsLayout->addStretch();
    layout->addLayout(buttonsLayout);
    layout->addStretch();

    connect(createGameBtn, &QPushButton::clicked, this, &LobbyScreen::createGameClicked);
    connect(backToMenuBtn, &QPushButton::clicked, this, &LobbyScreen::backToMenuClicked);
}

void LobbyScreen::setLobbyStatus(const QString &status){
    statusLabel->setText(status);
}

void LobbyScreen::setIpLabel(QString ip) {
    ipLabel->setText(QString("IP лобби: ") + ip);
    ipLabel->update();
}

void LobbyScreen::setStartEnabled(bool enabled){
    createGameBtn->setEnabled(enabled);
}

// Изменение информации о игроках
void LobbyScreen::addPlayerToList(const int &playerId, const QString &playerName){
    QString playerInfo (QString::number(playerId) + ": " + playerName);
    playersList->addItem(playerInfo);
    playersList->update();
}

void LobbyScreen::clearPlayersList() {
    playersList->clear();
}

void LobbyScreen::setHostRole(bool isHost) {
    if (isHost) {
        createGameBtn->show();
    }
    else {createGameBtn->hide();}

    createGameBtn->update();
}

void LobbyScreen::checkStartConditions(int numberPlayers) {
    if (numberPlayers != 0 && numberPlayers > 2) {
        setStartEnabled(true);
    }
    else {setStartEnabled(false);}
}

LobbyScreen::~LobbyScreen() = default;