#pragma once
#include <qobject.h>
#include "common.h"
#include "qt_layout_include.h"
#include "qt_mode_base.h"

class Menu_Bar_Mode;
class Operator_Area_Serach_Imp_Mode;

class Controler :
    public QObject,public Qt_Mode_Base
{
    Q_OBJECT
public:
    Controler();
    ~Controler();

protected:
	virtual void InitMembers() override;
	virtual void InitConnects() override;

private:
    Menu_Bar_Mode* menu_bar_mode_ptr_ = nullptr;
    Operator_Area_Serach_Imp_Mode* operator_area_serach_imp_mode_;

};

