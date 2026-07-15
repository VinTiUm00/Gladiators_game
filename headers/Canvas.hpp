#ifndef CANVAS_HPP
#define CANVAS_HPP

#include <QWidget>
#include <QPixmap>
#include <QMouseEvent>
#include <QColor>

class NetworkManager;

struct DrawingEvent;

class Canvas : public QWidget {

    Q_OBJECT // Макрос, без которого не работают сигналы

public:
    explicit Canvas(QWidget *parent = nullptr);
    virtual ~Canvas();

    void clearCanvas();
    void setNetworkManager(NetworkManager *netMgr) { networkManager = netMgr; }
    void drawRemoteEvent(const DrawingEvent &event);

public slots:
    void setPenColor(const QColor &color);
    void setPenWidth(int width);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void drawingEventToSend(const DrawingEvent &event);

private:
    QPixmap pixmap;
    QColor penColor;
    int penWidth;
    QPoint lastPos;
    NetworkManager *networkManager;
};

#endif