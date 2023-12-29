#pragma once
#include <qframe.h>
#include "label_control_addi.h"
#include "label_control_remove.h"
#include <QGridLayout>

class Operator_Icon_Domain :
    public QFrame
{
    Q_OBJECT
public:
    Operator_Icon_Domain(QWidget* parent = nullptr);
    ~Operator_Icon_Domain();

protected:
	void Init();
	void InitMembers();
	void InitLayout();

private:
    QGridLayout* gridlayout_operator_icon_domain_ptr_ = nullptr;
    Label_Control_Addi* label_control_addi_ptr_ = nullptr;
    Label_Control_Remove* label_control_rm_ptr_ = nullptr;

};

