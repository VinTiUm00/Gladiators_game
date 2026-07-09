#include <QVBoxLayout>
#include <QPushButton>

#include "PaintingScreen.hpp"

PaintingScreen::PaintingScreen(QWidget* parent) : QWidget(parent) {
    QVBoxLayout* layout = new QVBoxLayout(this); // Группировка кнопок

    // Инициализация холста
    canvas = new Canvas();

    // Инициализация кнопок
    QPushButton *exitLobbyBtn = new QPushButton("Покинуть лобби", this);
    exitLobbyBtn->setFixedHeight(50);

    // Кастомизация
    exitLobbyBtn->setStyleSheet("QPushButton { background-color: #AF505A; color: white; font-weight: 700; font-size: 16px; }");

    // Добавление в группировку
    layout->addWidget(canvas);
    layout->addWidget(exitLobbyBtn);

    // Подключение сигналов
    connect(exitLobbyBtn, &QPushButton::clicked, this, &PaintingScreen::exitLobbyClicked);
}

PaintingScreen::~PaintingScreen() = default;

void PaintingScreen::newCanvas(){
    this->canvas->clearCanvas();
}