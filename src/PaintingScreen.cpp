#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QColorDialog>
#include <QSpinBox>
#include <QLabel>

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

    // Тема рисунка
    themeLabel = new QLabel(this);
    themeLabel->setAlignment(Qt::AlignCenter);
    themeLabel->setStyleSheet("QLabel { color: #6c6bbf; font-size: 16px; font-weight: 700; }");

    // Инициализация кнопок
    QPushButton *exitLobbyBtn = new QPushButton("Покинуть лобби", this);
    exitLobbyBtn->setFixedHeight(50);
    exitLobbyBtn->setFixedWidth(200);

    // Кастомизация
    exitLobbyBtn->setStyleSheet("QPushButton { background-color: #AF505A; color: white; font-weight: 700; font-size: 16px; border-radius: 10px; }");

    // Добавление в группировку
    vLayoutLeft->addWidget(canvas);
    
    vLayoutRight->addWidget(clrDialog);
    vLayoutRight->addWidget(widthBox);

    hLayout->addLayout(vLayoutLeft);
    hLayout->addLayout(vLayoutRight);

    mainLayout->addWidget(themeLabel);
    mainLayout->addLayout(hLayout);

    QHBoxLayout *exitBtnLayout = new QHBoxLayout();
    exitBtnLayout->addStretch();
    exitBtnLayout->addWidget(exitLobbyBtn);
    exitBtnLayout->addStretch();
    mainLayout->addLayout(exitBtnLayout);

    // Подключение сигналов
    connect(exitLobbyBtn, &QPushButton::clicked, this, &PaintingScreen::exitLobbyClicked);
    connect(clrDialog, &QColorDialog::currentColorChanged, canvas, &Canvas::setPenColor);
    connect(widthBox, &QSpinBox::valueChanged, canvas, &Canvas::setPenWidth);
}

PaintingScreen::~PaintingScreen() = default;

void PaintingScreen::newCanvas(){
    this->canvas->clearCanvas();
}

void PaintingScreen::setThemeLabel(const QString &theme) {
    themeLabel->setText(theme);
}

/*
QPixmap PaintingScreen::getCanvasPixmap() const {
    return canvas->grab(); // ?????
}
*/
/*
void PaintingScreen::onGameStateChanged(int state) {
    GameState gameState = static_cast<GameState>(state);
    
    if (gameState == GameState::DRAWING) {
        canDraw = true;
        statusLabel->setText("Рисуйте вашего бойца!");
        statusLabel->setStyleSheet("QLabel { color: #6dbf6b; font-size: 16px; font-weight: 700; }");
    } else if (gameState == GameState::VOTING) {
        canDraw = false;
        statusLabel->setText("Переход к голосованию...");
        statusLabel->setStyleSheet("QLabel { color: #6b71bf; font-size: 16px; font-weight: 700; }");
        emit readyForVoting();
    }
}
*/
/*
void PaintingScreen::onStartVoting(const QList<int> &playerIds) {
    canDraw = false;
    statusLabel->setText("Голосование начинается!");
    statusLabel->setStyleSheet("QLabel { color: #6b71bf; font-size: 16px; font-weight: 700; }");
}
*/