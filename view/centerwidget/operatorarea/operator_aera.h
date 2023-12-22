#pragma once
#include <qobject.h>
#include <QGroupBox>
#include "qt_layout_base.h"
#include <QGridLayout>

class Operator_Aera :
    public QGroupBox,public Qt_Layout_Base
{
    Q_OBJECT
public:
    Operator_Aera();
    ~Operator_Aera();

protected:
	virtual void InitMembers();
	virtual void InitLayout();

public:
    QGridLayout* grid_layout_operator_area_ptr = nullptr;
};

