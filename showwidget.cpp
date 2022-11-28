#include "showwidget.h"
#include "ui_showwidget.h"
#include <opencv.hpp>

ShowWidget::ShowWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ShowWidget)
{
    ui->setupUi(this);
    ui->labelSrc->setScaledContents(true);
    ui->labelDst->setScaledContents(true);
}

ShowWidget::~ShowWidget()
{
    delete ui;
}

void ShowWidget::receiver(cv::Mat *passsrc, cv::Mat *passdst){
    QImage disImage1 = QImage((const unsigned char*)(passsrc->data),
                              passsrc->cols,passsrc->rows,
                              passsrc->cols * passsrc->channels(),
                              QImage::Format_RGB888);
    QImage disImage2 = QImage((const unsigned char*)(passdst->data),
                              passdst->cols,passdst->rows,
                              passdst->cols * passdst->channels(),
                              QImage::Format_RGB888);
    ui->labelSrc->setPixmap(QPixmap::fromImage(disImage1));
    ui->labelDst->setPixmap(QPixmap::fromImage(disImage2));
    passsrc->release(); passdst->release();
}
