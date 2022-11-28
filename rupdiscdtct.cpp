#include "rupdiscdtct.h"
#include "ui_rupdiscdtct.h"
#include <QtWidgets/QVBoxLayout>

RupDiscDtct::RupDiscDtct(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::RupDiscDtct)
{
    ui->setupUi(this);
    LoadWidgetV* lLoadV = new LoadWidgetV(ui->lTab);
    lLoadV->setObjectName(QString::fromUtf8("lLoadV"));
    lLoadV->setMaximumSize(QSize(16777215, 30));
    lLoadV->hide();
    lLoadV->setEnabled(false);
    LoadWidgetV* cLoadV = new LoadWidgetV;
    cLoadV->setObjectName(QString::fromUtf8("cLoadV"));
    cLoadV->setMaximumSize(QSize(16777215, 30));
    cLoadV->hide();
    cLoadV->setEnabled(false);
    connect(ui->lLoad, &LoadWidget::imageLoadReady, this, [=](){
        cv::Mat *lineSrc = new cv::Mat(cv::imread(*ui->lLoad->getSrcDir()));
        cv::Mat *lineDst = lineDetect(lineSrc);
        ui->lShow->receiver(lineSrc, lineDst);
    });
    connect(ui->cLoad, &LoadWidget::imageLoadReady, this, [=](){
        cv::Mat *circleSrc = new cv::Mat(cv::imread(*ui->cLoad->getSrcDir()));
        cv::Mat *circleDst = circleDetect(circleSrc);
        ui->cShow->receiver(circleSrc, circleDst);
    });
    connect(ui->lLoad, &LoadWidget::shift2Vdo, this, [=](){
        shift2VdoWgt(ui->lLoad, lLoadV, ui->verticalLayout);
    });
    connect(ui->cLoad, &LoadWidget::shift2Vdo, this, [=](){
        shift2VdoWgt(ui->cLoad, cLoadV, ui->verticalLayout_2);
    });
    connect(lLoadV, &LoadWidgetV::shift2Pic, this, [=](){
        shift2PicWgt(lLoadV, ui->lLoad, ui->verticalLayout);
    });
    connect(cLoadV, &LoadWidgetV::shift2Pic, this, [=](){
        shift2PicWgt(cLoadV, ui->cLoad, ui->verticalLayout_2);
    });
}

RupDiscDtct::~RupDiscDtct()
{
    delete ui;
}

cv::Mat* RupDiscDtct::lineDetect(cv::Mat* lineSrc){
    cv::Mat *src_gray = new cv::Mat;
    cv::Mat *dst = new cv::Mat;
    lineSrc->copyTo(*dst);
    cv::Canny(*lineSrc, *src_gray, 50, 200);
    cv::cvtColor(*src_gray, *dst, cv::COLOR_GRAY2BGR);
    std::vector<cv::Vec4f> plines;
    cv::HoughLinesP(*src_gray, plines, 1, CV_PI / 180.0,
                    80, //阈值：霍夫空间重合次数， 超过判定为直线
                    50, //最小直线长度（像素）
                    10); //散点粘连成线的最小距离
    delete src_gray;
    for(size_t i = 0; i < plines.size(); ++i){
        cv::Vec4f hline = plines[i];
        cv::line(*dst, cv::Point(hline[0], hline[1]), cv::Point(hline[2], hline[3]), cv::Scalar(0, 0, 255), 1, cv::LINE_AA);
        cv::putText(*dst,
                    std::to_string(plines.size() / 2),
                    cv::Point(dst->cols / 4, dst->rows / 5),
                    cv::FONT_HERSHEY_PLAIN,
                    2,
                    cv::Scalar(255, 255, 255),
                    1, cv::LINE_AA);
    }
    return dst;
}

cv::Mat* RupDiscDtct::circleDetect(cv::Mat* circleSrc){
    cv::Mat *moutput = new cv::Mat;
    cv::medianBlur(*circleSrc, *moutput, 3);
    cv::cvtColor(*moutput, *moutput, cv::COLOR_BGR2GRAY);
    std::vector<cv::Vec3f> pcircles;
    cv::HoughCircles(*moutput, pcircles, cv::HOUGH_GRADIENT, 1,
                     0.05 * std::min(circleSrc->cols, circleSrc->rows), //判定为两圆的最小圆心距
                     150, //Canny算法中的高阈值
                     89, //霍夫变换后，重叠次数超过此阈值即判定为圆
                     0.15 * std::min(circleSrc->cols, circleSrc->rows), //最小半径
                     0.5 * std::max(circleSrc->cols, circleSrc->rows)); //最大半径
    delete moutput;
    cv::Mat* dst = new cv::Mat;
    circleSrc->copyTo(*dst);
    for(size_t  i = 0; i < pcircles.size(); ++i){
        cv::Vec3f cc = pcircles[i];
        cv::circle(*dst, cv::Point(cc[0], cc[1]), cc[2], cv::Scalar(0, 0, 255), 2, cv::LINE_AA);
        cv::circle(*dst, cv::Point(cc[0], cc[1]), 2, cv::Scalar(100, 0, 100), 2, cv::LINE_AA);
        cv::putText(*dst,
                    "("+std::to_string((int)cc[0])+","+std::to_string((int)cc[1])+")",
                cv::Point(cc[0], cc[1]),
                cv::FONT_HERSHEY_DUPLEX,
                0.5,
                cv::Scalar(0, 0, 0),
                1, cv::LINE_AA);
    }
    return dst;
}

void RupDiscDtct::shift2VdoWgt(LoadWidget* pic_widget, LoadWidgetV* vdo_widget, QVBoxLayout* verticalLayout){
    verticalLayout->replaceWidget(pic_widget,vdo_widget);
    pic_widget->hide();
    pic_widget->setEnabled(false);
    vdo_widget->show();
    vdo_widget->setEnabled(true);
}

void RupDiscDtct::shift2PicWgt(LoadWidgetV* vdo_widget, LoadWidget* pic_widget, QVBoxLayout* verticalLayout){
    verticalLayout->replaceWidget(vdo_widget, pic_widget);
    vdo_widget->hide();
    vdo_widget->setEnabled(false);
    pic_widget->show();
    pic_widget->setEnabled(true);
}
