#ifndef RUPDISCDTCT_H
#define RUPDISCDTCT_H

#include <QWidget>
#include <opencv.hpp>
#include <loadwidget.h>
#include <loadwidgetv.h>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class RupDiscDtct; }
QT_END_NAMESPACE

class RupDiscDtct : public QWidget
{
    Q_OBJECT

public:
    RupDiscDtct(QWidget *parent = nullptr);
    ~RupDiscDtct();

private:
    Ui::RupDiscDtct *ui;
    cv::Mat* lineDetect(cv::Mat*);
    cv::Mat* circleDetect(cv::Mat*);
    void shift2VdoWgt(LoadWidget*, LoadWidgetV*, QVBoxLayout*);
    void shift2PicWgt(LoadWidgetV*, LoadWidget*, QVBoxLayout*);

private slots:

signals:
    void cameraCheck();
    void srcProcessed(cv::Mat*, cv::Mat*);

};
#endif // RUPDISCDTCT_H
