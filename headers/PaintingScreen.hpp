#ifndef PAINTINGSCREEN_HPP
#define PAINTINGSCREEN_HPP

#include <QWidget>
#include <QPixmap>
#include <QLabel>

#include "Canvas.hpp"

class NetworkManager;

class PaintingScreen : public QWidget {

    Q_OBJECT // Макрос, без которого не работают сигналы

public:
    PaintingScreen(QWidget* parent = nullptr);
    virtual ~PaintingScreen();

    void newCanvas();
    void setThemeLabel(const QString &theme);
    //QPixmap getCanvasPixmap() const;

public slots:
    //void onGameStateChanged(int state);
    //void onStartVoting(const QList<int> &playerIds);

private:
    Canvas *canvas;
    QLabel *themeLabel;

signals:
    void exitLobbyClicked();
    //void readyForVoting();
};

#endif