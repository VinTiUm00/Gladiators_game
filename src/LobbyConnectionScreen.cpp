#include <QVBoxLayout>
#include <QPushButton>

#include "LobbyConnectionScreen.hpp"

LobbyConnectionScreen::LobbyConnectionScreen(QWidget* parent) : QWidget(parent){
    QVBoxLayout* layout = new QVBoxLayout(this); // Группировка кнопок

    // Инициализация кнопок
    QPushButton *connectionBtn = new QPushButton("Подключиться к игре", this);
    connectionBtn->setFixedHeight(50);

    QPushButton *backBtn = new QPushButton("Назад", this);
    backBtn->setFixedHeight(50);

    // Кастомизация
    connectionBtn->setStyleSheet("QPushButton { background-color: #6b71bf; color: white; font-weight: 700; font-size: 16px; }");
    backBtn->setStyleSheet("QPushButton { background-color: #AF505A; color: white; font-weight: 700; font-size: 16px; }");

    // Добавление в группировку
    layout->addWidget(connectionBtn);
    layout->addWidget(backBtn);

    // Подключение сигналов
    connect(connectionBtn, &QPushButton::clicked, this, &LobbyConnectionScreen::connectToGame);
    connect(backBtn, &QPushButton::clicked, this, &LobbyConnectionScreen::backClicked);
}

LobbyConnectionScreen::~LobbyConnectionScreen() = default;