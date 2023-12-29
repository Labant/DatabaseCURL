#include "operator_area_insert_imp.h"
#include <QDebug>

Operator_Area_Insert_Imp::Operator_Area_Insert_Imp()
{
	Init();
}

Operator_Area_Insert_Imp::~Operator_Area_Insert_Imp()
{
}

void Operator_Area_Insert_Imp::InitMembers()
{
	opera_area_insert_combox_ptr_ = new QComboBox;
	COMMON->InsertQObjectPtr("opera_area_insert_combox_ptr_", opera_area_insert_combox_ptr_);
	for (int i = 0; i < 3; ++i)
	{
		opera_area_insert_btn_ptrs_[i] = new QPushButton();
	}
	opera_area_insert_btn_ptrs_[0]->setText(QStringLiteral("上移"));
	COMMON->InsertQObjectPtr("opera_area_insert_btn_ptrs_[0]", opera_area_insert_btn_ptrs_[0]);
	opera_area_insert_btn_ptrs_[1]->setText(QStringLiteral("下移"));
	COMMON->InsertQObjectPtr("opera_area_insert_btn_ptrs_[1]", opera_area_insert_btn_ptrs_[1]);
	opera_area_insert_btn_ptrs_[2]->setText(QStringLiteral("确认"));
	COMMON->InsertQObjectPtr("opera_area_insert_btn_ptrs_[2]", opera_area_insert_btn_ptrs_[2]);
}

void Operator_Area_Insert_Imp::InitLayout()
{
	this->setTitle(QStringLiteral("插入操作区"));
	opera_area_insert_combox_ptr_->setFixedHeight(30);
	grid_layout_operator_area_ptr->addWidget(opera_area_insert_combox_ptr_,0,0,1,1);
	for (int i = 1; i < 4; ++i)
	{
		grid_layout_operator_area_ptr->addWidget(opera_area_insert_btn_ptrs_[i-1], i, 0, 1, 1);
	}
}
