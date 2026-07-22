#ifndef LOBBYCONNECTIONSCREEN_HPP
#define LOBBYCONNECTIONSCREEN_HPP

#include <QWidget>
#include <QString>

class ConnectionScreen : public QWidget {

    Q_OBJECT // Макрос, без которого не работают сигналы

public:
    ConnectionScreen(QWidget* parent = nullptr);
    virtual ~ConnectionScreen();

signals:
    void connectToGame(QString ip, QString lastNickname);
    void backClicked();
};

#endif