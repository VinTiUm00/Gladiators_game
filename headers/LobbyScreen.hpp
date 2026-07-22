#ifndef LOBBYCREATORSCREEN_HPP
#define LOBBYCREATORSCREEN_HPP

#include <QWidget>
#include <QStringList>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>

class LobbyScreen : public QWidget {

    Q_OBJECT // Макрос, без которого не работают сигналы

public:
    LobbyScreen(QWidget* parent = nullptr);
    virtual ~LobbyScreen();

public:
    void setLobbyStatus(const QString &status);
    void setStartEnabled(bool enabled);
    void setIpLabel(QString ip);
    void clearPlayersList();
    void setHostRole(bool isHost);

public slots:
    void addPlayerToList(const int &playerId, const QString &playerName);
    void checkStartConditions(int numberPlayers);

signals:
    void createGameClicked();
    void backToMenuClicked();

private:
    QLabel *statusLabel;
    QLabel *ipLabel;
    QPushButton *createGameBtn;
    QListWidget *playersList; // Список игроков (виджет)
};

#endif