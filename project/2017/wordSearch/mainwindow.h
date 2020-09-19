#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QWidget>
#include <QTextEdit>
#include<QPushButton>
#include<QLabel>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    std::vector<std::string> fileContent;
    std::string searchPatternString;

    QLabel *selectLabel;
    QLabel *searchLabel;
    QLabel *resLabel;
    QPushButton *selectButton;
    QTextEdit *patternText;
    QPushButton *searchButton;
    QTextEdit *resultText;

public slots:
    void openFile();
    void searchPattern();
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static const int WORD_SEARCH_WINDOW_WIDTH = 600;
    static const int WORD_SEARCH_WINDOW_HEIGHT = 800;
};
#endif // MAINWINDOW_H
