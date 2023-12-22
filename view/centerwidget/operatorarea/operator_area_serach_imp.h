#pragma once
#include <qobject.h>
#include "operator_aera.h"
#include "qt_layout_base.h"

class QComboBox;

class Operator_Area_Serach_Imp :
    public Operator_Aera //,public Qt_Layout_Base
{
    Q_OBJECT
public:
    Operator_Area_Serach_Imp();
    ~Operator_Area_Serach_Imp();
    void UpDateComBoxList(QStringList& data);

protected:
	virtual void InitMembers() override;
	virtual void InitLayout() override;

signals:
    void GetAllTableName2ComBox();
private:
    QComboBox* combo_box_operator_area_serach_imp_ = nullptr;
};

