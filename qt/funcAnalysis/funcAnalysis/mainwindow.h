#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QWidget>
#include <QTextEdit>
#include<QPushButton>
#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
    QPushButton *selectButton;
    QPushButton *analysisButton;
    QTextEdit *srcText;
    QTextEdit *resText;

    std::map<std::string, std::vector<std::string>> table;
    std::vector<std::string> fileContent;

void search(std::string func, int depth);

   public slots:
    void openFile();
    void analysisFile();



public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    static const int FUNC_ANALYSIS_WINDOW_WIDTH = 650;
    static const int FUNC_ANALYSIS_WINDOW_HEIGHT = 800;
};
#endif // MAINWINDOW_H
