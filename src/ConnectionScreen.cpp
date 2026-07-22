#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QSizePolicy>

#include "ConnectionScreen.hpp"

ConnectionScreen::ConnectionScreen(QWidget* parent) : QWidget(parent){
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setSpacing(18);
    layout->setContentsMargins(36, 32, 36, 32);

    QLabel* titleLabel = new QLabel("Лобби Gladiators", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("QLabel { color: #ffffff; font-size: 32px; font-weight: 800; }");

    QLabel* hintLabel = new QLabel("Введите никнейм и подключитесь к лобби. Во время боя вы будете анонимны.", this);
    hintLabel->setWordWrap(true);
    hintLabel->setAlignment(Qt::AlignCenter);
    hintLabel->setMaximumWidth(560);
    hintLabel->setStyleSheet("QLabel { color: #ffffff; font-size: 16px; font-weight: 600; }");

    QLineEdit* nicknameInput = new QLineEdit(this);
    nicknameInput->setPlaceholderText("Ваш никнейм");
    nicknameInput->setFixedHeight(42);
    nicknameInput->setMinimumWidth(280);
    nicknameInput->setMaximumWidth(360);
    nicknameInput->setStyleSheet("QLineEdit { background-color: white; color: #2b2b2b; border-radius: 8px; padding: 6px 10px; font-size: 15px; }");

    // Ввод ip (временное решение)
    QLineEdit* ipInput = new QLineEdit(this);
    ipInput->setPlaceholderText("IP лобби");
    ipInput->setFixedHeight(42);
    ipInput->setMinimumWidth(280);
    ipInput->setMaximumWidth(360);
    ipInput->setStyleSheet("QLineEdit { background-color: white; color: #2b2b2b; border-radius: 8px; padding: 6px 10px; font-size: 15px; }");

    QLabel* anonymityLabel = new QLabel("Скрытая идентичность: соперники увидят только бойца, а не ваше имя.", this);
    anonymityLabel->setWordWrap(true);
    anonymityLabel->setAlignment(Qt::AlignCenter);
    anonymityLabel->setMaximumWidth(540);
    anonymityLabel->setStyleSheet("QLabel { color: #f3f3f7; font-size: 14px; font-weight: 500; }");

    QPushButton *connectionBtn = new QPushButton("Подключиться к лобби", this);
    connectionBtn->setFixedHeight(48);
    connectionBtn->setFixedWidth(260);
    connectionBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    QPushButton *backBtn = new QPushButton("Назад", this);
    backBtn->setFixedHeight(48);
    backBtn->setFixedWidth(180);
    backBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    connectionBtn->setStyleSheet("QPushButton { background-color: #6b71bf; color: white; font-weight: 700; font-size: 16px; border-radius: 10px; padding: 0 16px; }");
    backBtn->setStyleSheet("QPushButton { background-color: #AF505A; color: white; font-weight: 700; font-size: 16px; border-radius: 10px; padding: 0 16px; }");

    layout->addStretch();
    layout->addWidget(titleLabel, 0, Qt::AlignHCenter);
    layout->addWidget(hintLabel, 0, Qt::AlignHCenter);
    layout->addWidget(nicknameInput, 0, Qt::AlignHCenter);
    layout->addWidget(ipInput, 0, Qt::AlignHCenter);
    layout->addWidget(anonymityLabel, 0, Qt::AlignHCenter);

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->setSpacing(14);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(connectionBtn);
    buttonsLayout->addWidget(backBtn);
    buttonsLayout->addStretch();
    layout->addLayout(buttonsLayout);
    layout->addStretch();

    connect(connectionBtn, &QPushButton::clicked, this, [this, nicknameInput, ipInput]() {
        const QString nick = nicknameInput->text().trimmed();
        if (nick.isEmpty()) {
            nicknameInput->setText("Игрок");
        }
        emit connectToGame(ipInput->text());
    });
    connect(backBtn, &QPushButton::clicked, this, &ConnectionScreen::backClicked);
}

ConnectionScreen::~ConnectionScreen() = default;