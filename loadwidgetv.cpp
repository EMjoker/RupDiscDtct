#include "loadwidgetv.h"
#include "ui_loadwidgetv.h"

LoadWidgetV::LoadWidgetV(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadWidgetV)
{
    ui->setupUi(this);
    connect(ui->modeBtn, &QPushButton::clicked, this, &LoadWidgetV::shift2Pic);
}

LoadWidgetV::~LoadWidgetV()
{
    delete ui;
}
