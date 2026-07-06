#include "MainWindow.hpp"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);  // Инициализация приложения

    MainWindow window; // Инициализация главного окна
    window.setObjectName("mainWindow"); // Отображаемое имя
    window.setStyleSheet("MainWindow { background-color: #282C34; }"); // CSS для главного окна

    window.resize(600, 500); // Размер главного окна
    window.show(); // Показать главное окно
    window.raise();

    return app.exec();
}