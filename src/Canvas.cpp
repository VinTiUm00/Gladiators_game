#include <QPainter>

#include "Canvas.hpp"
#include "NetworkManager.hpp"

Canvas::Canvas(QWidget *parent) : QWidget(parent), networkManager(nullptr) {
    setFixedSize(600, 600);
    setMouseTracking(true); // Для отслеживания движения мыши
    
    // Создаем QPixmap с белым фоном
    pixmap = QPixmap(size());
    pixmap.fill(Qt::white);
    
    penColor = Qt::black;
    penWidth = 10;
    lastPos = QPoint();
}

Canvas::~Canvas() = default;

void Canvas::setPenColor(const QColor &color) {
    penColor = color;
}

void Canvas::setPenWidth(int width) {
    penWidth = width;
}

void Canvas::clearCanvas() {
    pixmap.fill(Qt::white);
    update();
}


void Canvas::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.drawPixmap(0, 0, pixmap);
}

void Canvas::resizeEvent(QResizeEvent *event) {
    QPixmap newPixmap(size());
    newPixmap.fill(Qt::white);
    
    QPainter painter(&newPixmap);
    painter.drawPixmap(0, 0, pixmap);
    
    pixmap = newPixmap;
    QWidget::resizeEvent(event);
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastPos = event->pos();

        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        
        painter.drawPoint(lastPos);
        
        if (networkManager) {
            DrawingEvent evt;
            evt.playerId = networkManager->getPlayerId();
            evt.from = lastPos;
            evt.to = lastPos;
            evt.color = penColor;
            evt.width = penWidth;
            networkManager->broadcastDrawingEvent(evt);
        }
        
        update();
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        
        painter.drawLine(lastPos, event->pos());
        
        if (networkManager) {
            DrawingEvent evt;
            evt.playerId = networkManager->getPlayerId();
            evt.from = lastPos;
            evt.to = event->pos();
            evt.color = penColor;
            evt.width = penWidth;
            networkManager->broadcastDrawingEvent(evt);
        }
        
        lastPos = event->pos();
        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastPos = QPoint();
    }
}

void Canvas::drawRemoteEvent(const DrawingEvent &event) {
    QPainter painter(&pixmap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(event.color, event.width, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    
    if (event.from == event.to) {
        painter.drawPoint(event.from);
    } else {
        painter.drawLine(event.from, event.to);
    }
    
    update();
}