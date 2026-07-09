#include <QPainter>

#include "Canvas.hpp"

Canvas::Canvas(QWidget *parent) : QWidget(parent) {
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
        
        update();
    }
}

void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        QPainter painter(&pixmap);
        painter.setRenderHint(QPainter::Antialiasing);
        painter.setPen(QPen(penColor, penWidth, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
        
        painter.drawLine(lastPos, event->pos());
        
        lastPos = event->pos();
        update();
    }
}

void Canvas::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        lastPos = QPoint();
    }
}