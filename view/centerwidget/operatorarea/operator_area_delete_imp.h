#pragma once
#include <qobject.h>
#include "operator_aera.h"
#include "qt_layout_base.h"

class Operator_Area_Delete_Imp :
    public Operator_Aera //,public Qt_Layout_Base
{
    Q_OBJECT
public:
    Operator_Area_Delete_Imp();
    ~Operator_Area_Delete_Imp();

protected:
	virtual void InitMembers() override;
	virtual void InitLayout() override;
};

