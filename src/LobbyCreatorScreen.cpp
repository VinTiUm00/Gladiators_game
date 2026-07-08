#include <QVBoxLayout>
#include <QPushButton>

#include "LobbyCreatorScreen.hpp"

LobbyCreatorScreen::LobbyCreatorScreen(QWidget* parent) : QWidget(parent){
    QVBoxLayout* layout = new QVBoxLayout(this); // Группировка кнопок

    // Инициализация кнопок
    QPushButton *createGameBtn = new QPushButton("Запуск игры", this);
    createGameBtn->setFixedHeight(50);

    QPushButton *backToMenuBtn = new QPushButton("Назад в меню", this);
    backToMenuBtn->setFixedHeight(50);

    // Кастомизация
    createGameBtn->setStyleSheet("QPushButton { background-color: #6dbf6b; color: white; font-weight: 700; font-size: 16px; }");
    backToMenuBtn->setStyleSheet("QPushButton { background-color: #AF505A; color: white; font-weight: 700; font-size: 16px; }");

    // Добавление в группировку
    layout->addWidget(createGameBtn);
    layout->addWidget(backToMenuBtn);

    // Подключение сигналов
    connect(createGameBtn, &QPushButton::clicked, this, &LobbyCreatorScreen::createGameClicked);
    connect(backToMenuBtn, &QPushButton::clicked, this, &LobbyCreatorScreen::backToMenuClicked);
}

LobbyCreatorScreen::~LobbyCreatorScreen() = default;