#ifndef PAINTINGSCREEN_HPP
#define PAINTINGSCREEN_HPP

#include <QWidget>

#include "Canvas.hpp"

class PaintingScreen : public QWidget {

    Q_OBJECT // Макрос, без которого не работают сигналы

public:
    PaintingScreen(QWidget* parent = nullptr);
    virtual ~PaintingScreen();

private:
    Canvas *canvas;

signals:
    void exitLobbyClicked();
};

#endif