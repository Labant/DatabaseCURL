#pragma once
#include <qobject.h>
#include "operator_aera.h"
#include "qt_layout_base.h"
#include "qt_layout_include.h"

class Operator_Area_Insert_Imp :
    public Operator_Aera
{
	Q_OBJECT
public:
	Operator_Area_Insert_Imp();
	~Operator_Area_Insert_Imp();

private:
	QComboBox* opera_area_insert_combox_ptr_ = nullptr;
	QPushButton* opera_area_insert_btn_ptrs_[3];

protected:
	virtual void InitMembers() override;
	virtual void InitLayout() override;
};

