#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <QWidget>

#include "VotingScreen.hpp"
#include "NetworkManager.hpp"

VotingScreen::VotingScreen(QWidget* parent) : QWidget(parent),
    networkManager(nullptr), hasVoted(false) {

    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(16);
    mainLayout->setContentsMargins(40, 32, 40, 32);

    titleLabel = new QLabel("Голосование за лучшего бойца", this);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("QLabel { color: #ffffff; font-size: 28px; font-weight: 800; }");

    mainLayout->addWidget(titleLabel);

    QScrollArea *scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet("QScrollArea { border: none; background-color: transparent; }");

    QWidget *scrollWidget = new QWidget();
    QVBoxLayout *scrollLayout = new QVBoxLayout(scrollWidget);
    scrollLayout->setSpacing(20);
    scrollLayout->setContentsMargins(0, 0, 0, 0);
    scrollWidget->setLayout(scrollLayout);
    scrollArea->setWidget(scrollWidget);

    mainLayout->addWidget(scrollArea, 1);

    QPushButton *backBtn = new QPushButton("Вернуться в лобби", this);
    backBtn->setFixedHeight(48);
    backBtn->setFixedWidth(240);
    backBtn->setStyleSheet("QPushButton { background-color: #AF505A; color: white; font-weight: 700; font-size: 16px; border-radius: 10px; padding: 0 16px; }");

    QHBoxLayout *backBtnLayout = new QHBoxLayout();
    backBtnLayout->addStretch();
    backBtnLayout->addWidget(backBtn);
    backBtnLayout->addStretch();
    mainLayout->addLayout(backBtnLayout);

    connect(backBtn, &QPushButton::clicked, this, &VotingScreen::exitVotingClicked);
}

VotingScreen::~VotingScreen() = default;

void VotingScreen::startVoting(const QList<int> &playerIds, const QMap<int, QPixmap> &drawings) {
    clearVotingUI();
    activePlayerIds = playerIds;
    hasVoted = false;

    QWidget *scrollWidget = qobject_cast<QScrollArea *>(mainLayout->itemAt(1)->widget())->widget();
    QVBoxLayout *scrollLayout = qobject_cast<QVBoxLayout *>(scrollWidget->layout());

    for (int playerId : playerIds) {
        QHBoxLayout *playerLayout = new QHBoxLayout();
        playerLayout->setSpacing(16);

        if (drawings.contains(playerId)) {
            QLabel *drawingLabel = new QLabel();
            QPixmap scaledDrawing = drawings[playerId].scaledToHeight(150, Qt::SmoothTransformation);
            drawingLabel->setPixmap(scaledDrawing);
            drawingLabel->setStyleSheet("border: 2px solid #6b71bf; border-radius: 8px;");
            playerLayout->addWidget(drawingLabel);
        }

        QVBoxLayout *infoLayout = new QVBoxLayout();
        infoLayout->setSpacing(8);

        QLabel *playerLabel = new QLabel(QString("Боец #%1").arg(playerId + 1));
        playerLabel->setStyleSheet("QLabel { color: #ffffff; font-size: 16px; font-weight: 700; }");
        infoLayout->addWidget(playerLabel);

        QLabel *voteCountLabel = new QLabel("Голосов: 0");
        voteCountLabel->setStyleSheet("QLabel { color: #ececff; font-size: 14px; }");
        voteCountLabels[playerId] = voteCountLabel;
        infoLayout->addWidget(voteCountLabel);

        QPushButton *voteBtn = new QPushButton("Голосовать");
        voteBtn->setFixedHeight(40);
        voteBtn->setFixedWidth(140);
        voteBtn->setStyleSheet("QPushButton { background-color: #6dbf6b; color: white; font-weight: 700; font-size: 14px; border-radius: 8px; }");
        voteButtons[playerId] = voteBtn;
        connect(voteBtn, &QPushButton::clicked, this, [this, playerId]() { onVoteButtonClicked(playerId); });
        infoLayout->addWidget(voteBtn);

        infoLayout->addStretch();
        playerLayout->addLayout(infoLayout, 1);

        scrollLayout->addLayout(playerLayout);
    }

    scrollLayout->addStretch();
}

void VotingScreen::updateVoteCount(int playerId, int votes) {
    if (voteCountLabels.contains(playerId)) {
        voteCountLabels[playerId]->setText(QString("Голосов: %1").arg(votes));
    }
}

void VotingScreen::onVoteButtonClicked(int playerId) {
    if (!hasVoted && networkManager) {
        hasVoted = true;
        networkManager->broadcastVote(playerId);
        emit voteCasted(playerId);

        for (auto btn : voteButtons) {
            btn->setEnabled(false);
            btn->setStyleSheet("QPushButton { background-color: #888888; color: white; font-weight: 700; font-size: 14px; border-radius: 8px; }");
        }

        QLabel *statusLabel = new QLabel("Ваш голос учтен!");
        statusLabel->setAlignment(Qt::AlignCenter);
        statusLabel->setStyleSheet("QLabel { color: #6dbf6b; font-size: 16px; font-weight: 700; }");
        qobject_cast<QVBoxLayout *>(mainLayout)->insertWidget(2, statusLabel);
    }
}

void VotingScreen::clearVotingUI() {
    voteButtons.clear();
    voteCountLabels.clear();
    activePlayerIds.clear();
}
