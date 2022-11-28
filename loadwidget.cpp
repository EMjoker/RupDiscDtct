#include "loadwidget.h"
#include "ui_loadwidget.h"
#include <QFileDialog>
#include <QDir>
#include <QDebug>

LoadWidget::LoadWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadWidget),
    src(new std::string)
{
    ui->setupUi(this);
    connect(ui->fileBtn, &QPushButton::clicked, this, &LoadWidget::loadFile);
    connect(ui->modeBtn, &QPushButton::clicked, this, &LoadWidget::shift2Vdo);
}

LoadWidget::~LoadWidget()
{
    delete ui;
}

void LoadWidget::loadFile(){
    QString dir = QFileDialog::getOpenFileName(this,
                                               "Image to Load",
                                               QDir::homePath(),
                                               "Images(*.png *.jpg *.jpeg)");
    *src = dir.toStdString();
    if(src->empty()){
        qDebug() << "Image Load Failed.";
    }
    else{
        ui->lineEdit->setText(dir);
        emit imageLoadReady();
    }
}

std::string* LoadWidget::getSrcDir(){
    return src;
}
