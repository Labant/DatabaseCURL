#include "table_content_and_operator_widget.h"
#include "qt_layout_include.h"
#include "table_view_content_insert.h"
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
		local_category.store(category);
		bool_is_add_operator_area_ = false;
		table_view_ptr_ = new Table_View_Content;
		break;
	case State_Machine::SerachCategory:
		local_category.store(category);
		operator_aera_ptr_ = new Operator_Area_Serach_Imp;
		COMMON->InsertQObjectPtr("operator_aera_ptr_of_serach", operator_aera_ptr_);
		table_view_ptr_ = new Table_View_Content;
		break;
	case State_Machine::InsertCategory:
		local_category.store(category);
		table_view_enteny_ptr_ = new Table_View_Content;
		COMMON->InsertQObjectPtr("table_view_enteny_ptr_", table_view_enteny_ptr_);
		dou_table_view_ptr_ = new Table_View_Content_Insert();
		COMMON->InsertQObjectPtr("dou_table_view_ptr_", dou_table_view_ptr_);
		operator_aera_ptr_ = new Operator_Area_Insert_Imp;
		COMMON->InsertQObjectPtr("operator_aera_ptr_of_insert", operator_aera_ptr_);
		break;
	case State_Machine::DeleteCategory:
		local_category.store(category);
		table_view_ptr_ = new Table_View_Content;
		operator_aera_ptr_ = new Operator_Area_Delete_Imp;
		COMMON->InsertQObjectPtr("operator_aera_ptr_of_delete", operator_aera_ptr_);
		break;
	case State_Machine::CompareCategory:
		local_category.store(category);
		table_view_ptr_ = new Table_View_Content;
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

void Table_Content_And_Operator_Widget::SetTableModeEntery(QSqlQueryModel* model)
{
	table_view_enteny_ptr_->setModel(model);
	////set show
	//table_view_enteny_ptr_->setColumnHidden(0, true);
	//table_view_enteny_ptr_->setColumnHidden(1, true);
	////qDebug() << table_view_enteny_ptr_->isColumnHidden(0);
}

void Table_Content_And_Operator_Widget::SetTableMode(QSqlQueryModel* m1, QSqlQueryModel* m2)
{
	dou_table_view_ptr_->SetModels(m1,m2);
}

void Table_Content_And_Operator_Widget::OnSetOperatorImp()
{
}

void Table_Content_And_Operator_Widget::InitMembers()
{
	gridlayout_center_ptr_ = new QGridLayout;


}

void Table_Content_And_Operator_Widget::InitLayout()
{
	this->setLayout(gridlayout_center_ptr_);

	//layout setting
	switch (local_category.load())
	{
	case State_Machine::OpenAndCloseCategory:
		gridlayout_center_ptr_->addWidget(table_view_ptr_, 0, 0, 1, 1); 
		break;
	case State_Machine::SerachCategory:
		gridlayout_center_ptr_->addWidget(table_view_ptr_, 0, 0, 1, 1);  
		break;
	case State_Machine::InsertCategory:
		gridlayout_center_ptr_->addWidget(table_view_enteny_ptr_,0,0,1,1);
		gridlayout_center_ptr_->addWidget(dou_table_view_ptr_, 0, 1, 1, 1);
		break;
	case State_Machine::DeleteCategory:
		gridlayout_center_ptr_->addWidget(table_view_ptr_, 0, 0, 1, 1); 
		break;
	case State_Machine::CompareCategory:
		gridlayout_center_ptr_->addWidget(table_view_ptr_, 0, 0, 1, 1);
		break;
	default:
		break;
	}

	//layout control stretch setting
	switch (local_category.load())
	{
	case State_Machine::InsertCategory:
		gridlayout_center_ptr_->setColumnStretch(0, 1);
		gridlayout_center_ptr_->setColumnStretch(1, 4);
		gridlayout_center_ptr_->setColumnStretch(2, 1);
		if (bool_is_add_operator_area_)
		{
			gridlayout_center_ptr_->addWidget(operator_aera_ptr_, 0, 2, 1, 1);  //operator area widget
		}
		break;
	default:
		gridlayout_center_ptr_->setColumnStretch(0, 4);
		if (bool_is_add_operator_area_)
		{
			gridlayout_center_ptr_->setColumnStretch(1, 2);
		}
		if (bool_is_add_operator_area_)
		{
			gridlayout_center_ptr_->addWidget(operator_aera_ptr_, 0, 1, 1, 1);  //operator area widget
		}
		break;
	}


}
