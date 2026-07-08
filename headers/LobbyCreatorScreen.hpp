#ifndef LOBBYCREATORSCREEN_HPP
#define LOBBYCREATORSCREEN_HPP

#include <QWidget>

class LobbyCreatorScreen : public QWidget {

    Q_OBJECT // Макрос, без которого не работают сигналы

public:
    LobbyCreatorScreen(QWidget* parent = nullptr);
    virtual ~LobbyCreatorScreen();

signals:
    void createGameClicked();
    void backToMenuClicked();
};

#endif