#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSizePolicy>

#include "MenuScreen.hpp"

MenuScreen::MenuScreen(QWidget* parent) : QWidget(parent){
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(18);
    layout->setContentsMargins(40, 36, 40, 32);

    QLabel* TextLogo = new QLabel("GLADIATORS", this);
    TextLogo->setStyleSheet("QLabel { font-size: 56px; color: white; }");
    TextLogo->setFixedHeight(50);
    TextLogo->setAlignment(Qt::AlignmentFlag::AlignCenter);
    TextLogo->setAttribute(Qt::WA_TranslucentBackground);

    QPushButton *startBtn = new QPushButton("Создать игру", this);
    startBtn->setFixedHeight(48);
    startBtn->setFixedWidth(240);
    startBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QPushButton *connectBtn = new QPushButton("Подключиться к игре", this);
    connectBtn->setFixedHeight(48);
    connectBtn->setFixedWidth(280);
    connectBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QPushButton *exitBtn = new QPushButton("Выход", this);
    exitBtn->setFixedHeight(48);
    exitBtn->setFixedWidth(180);
    exitBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    startBtn->setStyleSheet("QPushButton { background-color: #6dbf6b; color: white; font-weight: 700; font-size: 16px; border-radius: 10px; padding: 0 16px; }");
    connectBtn->setStyleSheet("QPushButton { background-color: #6b71bf; color: white; font-weight: 700; font-size: 16px; border-radius: 10px; padding: 0 16px; }");
    exitBtn->setStyleSheet("QPushButton { background-color: #AF505A; color: white; font-weight: 700; font-size: 16px; border-radius: 10px; padding: 0 16px; }");

    layout->addStretch();
    layout->addWidget(TextLogo, Qt::AlignCenter);
    layout->addStretch(1);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->setSpacing(12);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(startBtn);
    buttonsLayout->addWidget(connectBtn);
    buttonsLayout->addWidget(exitBtn);
    buttonsLayout->addStretch();
    layout->addLayout(buttonsLayout);
    layout->addSpacing(8);

    connect(startBtn, &QPushButton::clicked, this, &MenuScreen::createLobbyClicked);
    connect(connectBtn, &QPushButton::clicked, this, &MenuScreen::connectLobbyClicked);
    connect(exitBtn, &QPushButton::clicked, this, &MenuScreen::exitBtnClicked);
}

MenuScreen::~MenuScreen() = default;