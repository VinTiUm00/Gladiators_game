#ifndef LOBBYCREATORSCREEN_HPP
#define LOBBYCREATORSCREEN_HPP

#include <QWidget>
#include <QStringList>
#include <QLabel>
#include <QPushButton>

class LobbyCreatorScreen : public QWidget {

    Q_OBJECT // Макрос, без которого не работают сигналы

public:
    LobbyCreatorScreen(QWidget* parent = nullptr);
    virtual ~LobbyCreatorScreen();

public:
    void setLobbyStatus(const QString &status);
    void setPlayers(const QStringList &players);
    void setStartEnabled(bool enabled);

signals:
    void createGameClicked();
    void backToMenuClicked();

private:
    QLabel *statusLabel;
    QLabel *playersLabel;
    QPushButton *createGameBtn;
};

#endif