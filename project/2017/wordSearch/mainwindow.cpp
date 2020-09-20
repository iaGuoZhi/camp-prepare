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
    this->setWindowTitle("全文搜索系统");
    this->setFixedSize(this->WORD_SEARCH_WINDOW_WIDTH, this->WORD_SEARCH_WINDOW_HEIGHT);

    selectLabel=new QLabel("选择文件",this);
    selectButton = new QPushButton("浏览",this);
    searchLabel=new QLabel("输入搜索选项",this);
    searchButton = new QPushButton("确定", this);
    resLabel = new QLabel("搜索结果",this);

    patternText = new QTextEdit(this);
    resultText = new QTextEdit(this);

    selectLabel->setGeometry(50, 20, 200, 20);
    selectButton->setGeometry(300, 20, 40,20);
    searchLabel->setGeometry(20, 60, 100, 20);
    patternText->setGeometry(150, 50, 300,30);
    searchButton->setGeometry(500, 50, 40, 20);
    resLabel->setGeometry(50,80,100,20);
    resultText->setGeometry(50,110,500,600);

    this->connect(selectButton, &QPushButton::clicked, this, &MainWindow::openFile);
    this->connect(searchButton, &QPushButton::clicked, this, &MainWindow::searchPattern);
}

std::vector<std::vector<std::pair<std::string,bool>>> MainWindow::parseKeyWords(std::string pattern, int &index){
    int len=pattern.size();
    if(index>=len)
        return std::vector<std::vector<std::pair<std::string,bool>>>{};

    bool needed=true;
    std::string token;
    char op='&';
    for(; index<len;index++){
        if(pattern[index]==' ')
            continue;
        if(pattern[index]=='!')
        {
            needed=false;
            continue;
        }
        if(index<len-1&&pattern[index]=='&'&&pattern[index+1]=='&'){

        }
    }

}
void MainWindow::searchPattern(){
    this->searchPatternString = this->patternText->toPlainText().toStdString();
    qDebug()<<QString::fromStdString(this->searchPatternString);


}

void MainWindow::openFile(){
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
   }

   qDebug()<<fileContent.size();
   istr.close();
}

MainWindow::~MainWindow()
{
}

