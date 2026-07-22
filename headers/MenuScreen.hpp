#ifndef MENUSCREEN_HPP
#define MENUSCREEN_HPP

#include <QWidget>

class MenuScreen : public QWidget {

    Q_OBJECT // Макрос, без которого не работают сигналы

public:
    MenuScreen(QWidget* parent = nullptr);
    virtual ~MenuScreen();

signals:
    void createLobbyClicked();
    void connectLobbyClicked();
    void exitBtnClicked();
};

#endif