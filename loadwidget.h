#ifndef LOADWIDGET_H
#define LOADWIDGET_H

#include <QWidget>
#include <loadwidgetv.h>
#include <QtWidgets/QVBoxLayout>

#include <string>

namespace Ui {
class LoadWidget;
}

class LoadWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LoadWidget(QWidget *parent = nullptr);
    ~LoadWidget();
    std::string* getSrcDir();

private:
    Ui::LoadWidget *ui;
    std::string* src;

signals:
    void imageLoadReady();
    void shift2Vdo();

private slots:
    void loadFile();
};

#endif // LOADWIDGET_H
