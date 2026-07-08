#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

#include "MenuScreen.hpp"

MenuScreen::MenuScreen(QWidget* parent) : QWidget(parent){
    QVBoxLayout* layout = new QVBoxLayout(this); // Группировка кнопок

    QLabel* TextLogo = new QLabel("GLADIATORS", this);
    TextLogo->setStyleSheet("QLabel { font-size: 56px; color: white; }");
    TextLogo->setFixedHeight(50);
    TextLogo->setAlignment(Qt::AlignmentFlag::AlignCenter);
    TextLogo->setAttribute(Qt::WA_TranslucentBackground);

    // Инициализация кнопок
    QPushButton *startBtn = new QPushButton("Создать игру", this);
    startBtn->setFixedHeight(50);

    QPushButton *connectBtn = new QPushButton("Подключиться к игре", this);
    connectBtn->setFixedHeight(50);

    QPushButton *exitBtn = new QPushButton("Выход", this);
    exitBtn->setFixedHeight(50);

    // Кастомизация
    startBtn->setStyleSheet("QPushButton { background-color: #6dbf6b; color: white; font-weight: 700; font-size: 16px; }");
    connectBtn->setStyleSheet("QPushButton { background-color: #6b71bf; color: white; font-weight: 700; font-size: 16px; }");
    exitBtn->setStyleSheet("QPushButton { background-color: #AF505A; color: white; font-weight: 700; font-size: 16px; }");

    // Добавление в группировку
    layout->addWidget(TextLogo, Qt::AlignCenter);
    layout->addWidget(startBtn);
    layout->addWidget(connectBtn);
    layout->addWidget(exitBtn);

    // Подключение сигналов
    connect(startBtn, &QPushButton::clicked, this, &MenuScreen::startGameClicked);
    connect(connectBtn, &QPushButton::clicked, this, &MenuScreen::connectGameClicked);
    connect(exitBtn, &QPushButton::clicked, this, &MenuScreen::exitBtnClicked);
}

MenuScreen::~MenuScreen() = default;