#include "operator_icon_domain.h"
#include "common.h"
Operator_Icon_Domain::Operator_Icon_Domain(QWidget* parent)
	:QFrame(parent)
{
	Init();
}

Operator_Icon_Domain::~Operator_Icon_Domain()
{
}

void Operator_Icon_Domain::Init()
{
	InitMembers();
	InitLayout();
}

void Operator_Icon_Domain::InitMembers()
{
	gridlayout_operator_icon_domain_ptr_ = new QGridLayout;
	label_control_addi_ptr_ = new Label_Control_Addi(this);
	COMMON->InsertQObjectPtr("label_control_addi_ptr_", label_control_addi_ptr_);
	label_control_rm_ptr_ = new Label_Control_Remove(this);
	COMMON->InsertQObjectPtr("label_control_rm_ptr_", label_control_rm_ptr_);
	//label_control_addi_ptr_->setObjectName("label_control_addi_ptr_");
	//label_control_rm_ptr_->setObjectName("label_control_rm_ptr_");
	//label_control_addi_ptr_->setStyleSheet("#label_control_addi_ptr_{background-color:pink;}");
	//label_control_rm_ptr_->setStyleSheet("#label_control_rm_ptr_{background-color:lightblue;}");
}

void Operator_Icon_Domain::InitLayout()
{
	this->setFrameShape(QFrame::Box);
	//this->setFixedSize(300, 100);
	this->setLayout(gridlayout_operator_icon_domain_ptr_);
	gridlayout_operator_icon_domain_ptr_->addWidget(label_control_rm_ptr_,0,0,1,1);
	gridlayout_operator_icon_domain_ptr_->addWidget(label_control_addi_ptr_,2,0,1,1);
}
