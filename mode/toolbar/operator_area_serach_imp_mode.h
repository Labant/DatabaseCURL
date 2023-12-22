#pragma once
#include <qobject.h>
#include "qt_mode_base.h"

class Operator_Area_Serach_Imp_Mode :
    public QObject,public Qt_Mode_Base
{
    Q_OBJECT
public:
    Operator_Area_Serach_Imp_Mode();
    ~Operator_Area_Serach_Imp_Mode();

    void OnGetAllTableName2ComBox();
protected:
	virtual void InitMembers();
	virtual void InitConnects();

};

