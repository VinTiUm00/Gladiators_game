#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSizePolicy>

#include "LobbyCreatorScreen.hpp"

LobbyCreatorScreen::LobbyCreatorScreen(QWidget* parent) : QWidget(parent){
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(14);
    layout->setContentsMargins(40, 40, 40, 40);

    QLabel* titleLabel = new QLabel("Создание лобби", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("QLabel { color: #ffffff; font-size: 32px; font-weight: 800; }");

    QLabel* hintLabel = new QLabel("Создайте комнату, и другие игроки смогут подключиться по своему никнейму.", this);
    hintLabel->setWordWrap(true);
    hintLabel->setAlignment(Qt::AlignCenter);
    hintLabel->setMaximumWidth(560);
    hintLabel->setStyleSheet("QLabel { color: #ffffff; font-size: 16px; font-weight: 600; }");

    QPushButton *createGameBtn = new QPushButton("Запуск игры", this);
    createGameBtn->setFixedHeight(48);
    createGameBtn->setFixedWidth(230);
    createGameBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QPushButton *backToMenuBtn = new QPushButton("Назад в меню", this);
    backToMenuBtn->setFixedHeight(48);
    backToMenuBtn->setFixedWidth(200);
    backToMenuBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    createGameBtn->setStyleSheet("QPushButton { background-color: #6dbf6b; color: white; font-weight: 700; font-size: 16px; border-radius: 10px; padding: 0 16px; }");
    backToMenuBtn->setStyleSheet("QPushButton { background-color: #AF505A; color: white; font-weight: 700; font-size: 16px; border-radius: 10px; padding: 0 16px; }");

    layout->addStretch();
    layout->addWidget(titleLabel, 0, Qt::AlignHCenter);
    layout->addWidget(hintLabel, 0, Qt::AlignHCenter);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->setSpacing(12);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(createGameBtn);
    buttonsLayout->addWidget(backToMenuBtn);
    buttonsLayout->addStretch();
    layout->addLayout(buttonsLayout);
    layout->addStretch();

    connect(createGameBtn, &QPushButton::clicked, this, &LobbyCreatorScreen::createGameClicked);
    connect(backToMenuBtn, &QPushButton::clicked, this, &LobbyCreatorScreen::backToMenuClicked);
}

LobbyCreatorScreen::~LobbyCreatorScreen() = default;