#ifndef LOBBYCONNECTIONSCREEN_HPP
#define LOBBYCONNECTIONSCREEN_HPP

#include <QWidget>
#include <QString>

class LobbyConnectionScreen : public QWidget {

    Q_OBJECT // Макрос, без которого не работают сигналы

public:
    LobbyConnectionScreen(QWidget* parent = nullptr);
    virtual ~LobbyConnectionScreen();

signals:
    void connectToGame(QString ip);
    void backClicked();
};

#endif