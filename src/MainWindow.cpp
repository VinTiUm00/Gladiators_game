#include <QVBoxLayout>
#include <algorithm>

#include "MainWindow.hpp"
// Другие окна

MainWindow::MainWindow(QWidget* parent) : QWidget(parent){
    QVBoxLayout* layout = new QVBoxLayout(this); // Группировка кнопок

    QLabel* TextLogo = new QLabel("GLADIATORS", this);
    TextLogo->setStyleSheet("QLabel { font-size: 56px; color: white; }");
    TextLogo->setFixedHeight(50);
    TextLogo->setAlignment(Qt::AlignmentFlag::AlignCenter);
    TextLogo->setAttribute(Qt::WA_TranslucentBackground);

    // инициализация кнопок
    btnPlay = new QPushButton("Играть", this);
    btnPlay->setFixedHeight(50);

    btnExit = new QPushButton("Выход", this);
    btnExit->setFixedHeight(50);

    // кастомизация
    btnPlay->setStyleSheet("QPushButton { background-color: #6dbf6b; color: white; font-weight: 700; font-size: 16px; }");
    btnExit->setStyleSheet("QPushButton { background-color: #AF505A; color: white; font-weight: 700; font-size: 16px; }");

    // добавление в группировку
    layout->addWidget(TextLogo, Qt::AlignCenter);
    layout->addWidget(btnPlay);
    layout->addWidget(btnExit);

    // connect(btnPlay, &QPushButton::clicked, this, &MainWindow::***);
    connect(btnExit, &QPushButton::clicked, this, &MainWindow::closeWindow);
}

MainWindow::~MainWindow() = default;


void MainWindow::closeWindow(){
    this->close();
}

void MainWindow::hideWindow(){
    this->hide();
}

void MainWindow::showWindow(){
    this->show();
}