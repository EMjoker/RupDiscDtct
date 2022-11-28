#ifndef LOADWIDGETV_H
#define LOADWIDGETV_H

#include <QWidget>

namespace Ui {
class LoadWidgetV;
}

class LoadWidgetV : public QWidget
{
    Q_OBJECT

public:
    explicit LoadWidgetV(QWidget *parent = nullptr);
    ~LoadWidgetV();

private:
    Ui::LoadWidgetV *ui;

signals:
    void cameraReady(int);
    void shift2Pic();

};

#endif // LOADWIDGETV_H
