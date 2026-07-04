#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <vector>

class MainWindow : public QWidget {

    Q_OBJECT // Макрос, без которого не работают сигналы

public:
    MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();

public slots:
    void OpenDifficultMenu();
    void OpenScoreTable();
    void closeWindow();
    void hideWindow();
    void showWindow();

    void saveScore(int Score); // сохранение счета в файл

private: // какие видимые элементы будут
    QLabel* lblMaxScore;
    QPushButton* btnPlay;
    QPushButton* btnScoreTable;
    QPushButton* btnExit;

    // счет
    std::vector<int> scoreList;
    int maxScore = 0; // вынесен для удобства обновления счета в главном меню
};

#endif