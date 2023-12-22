#include "operator_area_serach_imp.h"
#include "qt_layout_include.h"
#include <QDebug>

Operator_Area_Serach_Imp::Operator_Area_Serach_Imp()
{
	Init();
}

Operator_Area_Serach_Imp::~Operator_Area_Serach_Imp()
{
}

void Operator_Area_Serach_Imp::UpDateComBoxList(QStringList& data)
{
	combo_box_operator_area_serach_imp_->clear();
	combo_box_operator_area_serach_imp_->addItems(data);
}

void Operator_Area_Serach_Imp::InitMembers()
{
	combo_box_operator_area_serach_imp_ = new QComboBox();
	COMMON->InsertQObjectPtr("combo_box_operator_area_serach_imp_", combo_box_operator_area_serach_imp_);

}

void Operator_Area_Serach_Imp::InitLayout()
{
	this->setTitle(QStringLiteral("²éÑ¯²Ù×÷Çø"));
	//combo_box_operator_area_serach_imp_->setMinimumHeight(combo_box_operator_area_serach_imp_->height() * 1.3f);
	//qDebug() <<"height:" << combo_box_operator_area_serach_imp_->height();
	this->grid_layout_operator_area_ptr->addWidget(combo_box_operator_area_serach_imp_, 0, 0, 1, 1);
}
