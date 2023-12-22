#include "table_content_and_operator_widget.h"
#include "qt_layout_include.h"
#include <QDebug>

Table_Content_And_Operator_Widget::Table_Content_And_Operator_Widget()
{
	Init();
}

Table_Content_And_Operator_Widget::Table_Content_And_Operator_Widget(Table_View_Content* table_view__, 
	State_Machine::OperatorAreaCategory category)
{
	switch (category)
	{
	case State_Machine::OpenAndCloseCategory:
		//operator_aera_ptr_ = new Operator_Area_Serach_Imp;
		bool_is_add_operator_area_ = false;
		break;
	case State_Machine::SerachCategory:
		operator_aera_ptr_ = new Operator_Area_Serach_Imp;
		COMMON->InsertQObjectPtr("operator_aera_ptr_of_serach", operator_aera_ptr_);
		break;
	case State_Machine::InsertCategory:
		operator_aera_ptr_ = new Operator_Area_Insert_Imp;
		COMMON->InsertQObjectPtr("operator_aera_ptr_of_insert", operator_aera_ptr_);
		break;
	case State_Machine::DeleteCategory:
		operator_aera_ptr_ = new Operator_Area_Delete_Imp;
		COMMON->InsertQObjectPtr("operator_aera_ptr_of_delete", operator_aera_ptr_);
		break;
	case State_Machine::CompareCategory:
		operator_aera_ptr_ = new Operator_Area_Compare_Imp;
		COMMON->InsertQObjectPtr("operator_aera_ptr_of_compare", operator_aera_ptr_);
		break;
	default:
		break;
	}
	
	Init();
}

Table_Content_And_Operator_Widget::~Table_Content_And_Operator_Widget()
{
}

void Table_Content_And_Operator_Widget::SetTableMode(QSqlQueryModel* model)
{
	table_view_ptr_->setModel(model);
}

void Table_Content_And_Operator_Widget::OnSetOperatorImp()
{
	//operator_aera_ptr_ = operator_area_serach_imp_;
	//gridlayout_center_ptr_->removeWidget(operator_aera_ptr_);
	//gridlayout_center_ptr_->removeWidget(table_view_ptr_);
 

}

void Table_Content_And_Operator_Widget::InitMembers()
{
	gridlayout_center_ptr_ = new QGridLayout;

	table_view_ptr_ = new Table_View_Content;
	COMMON->InsertQObjectPtr("table_view_ptr_", table_view_ptr_);

}

void Table_Content_And_Operator_Widget::InitLayout()
{
	this->setLayout(gridlayout_center_ptr_);


	gridlayout_center_ptr_->addWidget(table_view_ptr_, 0, 0, 1, 1);  //table view widget
	if (bool_is_add_operator_area_)
	{
		gridlayout_center_ptr_->addWidget(operator_aera_ptr_, 0, 1, 1, 1);  //operator area widget
	}

	gridlayout_center_ptr_->setColumnStretch(0, 4);
	if (bool_is_add_operator_area_)
	{
		gridlayout_center_ptr_->setColumnStretch(1, 2);
	}
}
