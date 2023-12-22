#pragma once
#include <qobject.h>
#include "operator_aera.h"
#include "qt_layout_base.h"

class Operator_Area_Insert_Imp :
    public Operator_Aera
{
	Q_OBJECT
public:
	Operator_Area_Insert_Imp();
	~Operator_Area_Insert_Imp();

protected:
	virtual void InitMembers() override;
	virtual void InitLayout() override;
};

