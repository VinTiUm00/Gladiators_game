#include <QApplication>
#include <QFile>

#include "MainWindow.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);  // Инициализация приложения

    /* // Проверка наличия .json файла
    QFile testFile(":/Titles.json");
    if (testFile.exists()) {
        qDebug() << "OK";
    } else {
        qDebug() << "NO";
    }
    */

    MainWindow window; // Инициализация главного окна
    window.setObjectName("mainWindow"); // Отображаемое имя
    window.setStyleSheet("MainWindow { background-color: #282C34; }"); // CSS для главного окна

    window.resize(600, 500); // Размер главного окна
    window.show(); // Показать главное окно
    window.raise();

    return app.exec();
}