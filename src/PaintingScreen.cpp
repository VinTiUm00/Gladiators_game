#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QColorDialog>
#include <QSpinBox>

#include "PaintingScreen.hpp"

PaintingScreen::PaintingScreen(QWidget* parent) : QWidget(parent) {
    // Группировка интерфейса
    QVBoxLayout* mainLayout = new QVBoxLayout(this); // Основной
    QVBoxLayout* vLayoutLeft = new QVBoxLayout; // Левый столбец
    QVBoxLayout* vLayoutRight = new QVBoxLayout; // Правый столбец
    QHBoxLayout* hLayout = new QHBoxLayout; // Объединение верхней части

    // Инициализация холста
    canvas = new Canvas();

    // Инициализация диалога выбора цвета
    QColorDialog* clrDialog = new QColorDialog;

    clrDialog->setCurrentColor(Qt::black);
    clrDialog->setOption(QColorDialog::NoButtons);
    clrDialog->setOption(QColorDialog::ShowAlphaChannel);

    // Инициализация ввода ширины пера
    QSpinBox *widthBox = new QSpinBox(this);

    widthBox->setRange(1, 300);
    widthBox->setSingleStep(1);
    widthBox->setValue(10);
    widthBox->setMaximumWidth(150);
    widthBox->setPrefix("Ширина пера: ");

    // Инициализация кнопок
    QPushButton *exitLobbyBtn = new QPushButton("Покинуть лобби", this);
    exitLobbyBtn->setFixedHeight(50);

    // Кастомизация
    exitLobbyBtn->setStyleSheet("QPushButton { background-color: #AF505A; color: white; font-weight: 700; font-size: 16px; }");

    // Добавление в группировку
    vLayoutLeft->addWidget(canvas);
    
    vLayoutRight->addWidget(clrDialog);
    vLayoutRight->addWidget(widthBox);

    hLayout->addLayout(vLayoutLeft);
    hLayout->addLayout(vLayoutRight);

    mainLayout->addLayout(hLayout);
    mainLayout->addWidget(exitLobbyBtn);

    // Подключение сигналов
    connect(exitLobbyBtn, &QPushButton::clicked, this, &PaintingScreen::exitLobbyClicked);
    connect(clrDialog, &QColorDialog::currentColorChanged, canvas, &Canvas::setPenColor);
    connect(widthBox, &QSpinBox::valueChanged, canvas, &Canvas::setPenWidth);
}

PaintingScreen::~PaintingScreen() = default;

void PaintingScreen::newCanvas(){
    this->canvas->clearCanvas();
}