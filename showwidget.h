#ifndef SHOWWIDGET_H
#define SHOWWIDGET_H

#include <QWidget>
#include <opencv.hpp>

namespace Ui {
class ShowWidget;
}

class ShowWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ShowWidget(QWidget *parent = nullptr);
    ~ShowWidget();
    void receiver(cv::Mat*, cv::Mat*);

private:
    Ui::ShowWidget *ui;

};

#endif // SHOWWIDGET_H
