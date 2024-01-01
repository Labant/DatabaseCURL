#pragma once
#include <qwidget.h>
#include <QStatusBar>

class Status_Bar :
    public QStatusBar
{
    Q_OBJECT
public:
    Status_Bar(QWidget* parent = nullptr);
    ~Status_Bar();
};

