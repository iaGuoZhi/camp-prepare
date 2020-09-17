#include "mainwindow.h"
#include<QFileDialog>
#include<QDebug>
#include <cctype>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this->setWindowTitle("函数调用关系分析");
    this->setFixedSize(FUNC_ANALYSIS_WINDOW_WIDTH, FUNC_ANALYSIS_WINDOW_HEIGHT);

    selectButton = new QPushButton("选择文件",this);
    analysisButton = new QPushButton("分析", this);

    srcText = new QTextEdit(this);
    resText = new QTextEdit(this);

    selectButton->setGeometry(100, 20, 100, 30);
    analysisButton->setGeometry(400,20, 100, 30);

    srcText->setGeometry(50, 150, 250, 600);
    resText->setGeometry(350, 150, 250, 600);

    this->connect(selectButton, &QPushButton::clicked, this, &MainWindow::openFile);
    this->connect(analysisButton, &QPushButton::clicked, this, &MainWindow::analysisFile);

}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName(
            this,
            tr("open a file."),
            "./",
            tr("All files(*.*)"));
   qDebug()<<fileName;

   std::ifstream istr(fileName.toStdString());
   if (istr.fail()) {
       throw new std::runtime_error("");
   }
   std::string line;
   while (getline(istr, line)) {
       this->fileContent.push_back(line);
       this->srcText->append(QString::fromStdString(line));
   }
   istr.close();
}

void MainWindow::analysisFile(){
    std::string curFunc;

    for(int i=0;i<int(fileContent.size());++i){
        std::string s= fileContent[i];
        int j=0;
        while(s[j]==' ')
            j++;
        if(s.substr(j,4)=="func"){
            j+=4;
            while(s[j]==' ')
                j++;
            int end=j;
            while(s[end]!=' ')
                end++;
            std::string funcName= s.substr(j,end-j);
            curFunc=funcName;
            this->table[funcName]=std::vector<std::string>{};
            continue;
        }
        if(s.substr(j,4)=="call"){
            j+=4;
            while(s[j]==' ')
                j++;
            int end=j;
            while(s[end]!=' ')
                end++;
            std::string callName= s.substr(j,end-j);
            this->table[curFunc].push_back(callName);
        }
    }

    search("main", 0);
}

void MainWindow::search(std::string func, int depth){
    std::string display="";
    for(int i=0;i<depth;++i)
        display.append("|   ");
    display.append(func);

    this->resText->append(QString::fromStdString(display));
    for(int i=0;i<int(this->table[func].size());++i){
        search(table[func][i], depth+1);
    }
}

MainWindow::~MainWindow()
{

}

