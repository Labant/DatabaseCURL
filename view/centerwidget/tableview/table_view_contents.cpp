#include "table_view_contents.h"
#include "qt_layout_include.h"

Table_View_Contents::Table_View_Contents(QWidget* parent)
	:QWidget(parent)
{
	Init();
}

Table_View_Contents::~Table_View_Contents()
{
}

void Table_View_Contents::SetModels(QAbstractItemModel* model1, QAbstractItemModel* model2)
{
	table_view_left_ptr_->setModel(model1);
	table_view_right_ptr_->setModel(model2);
}

void Table_View_Contents::SetModel2(QAbstractItemModel* model2)
{
	table_view_right_ptr_->setModel(model2);
}

void Table_View_Contents::InitMembers()
{
	gridlayout_table_widget_contents_ptr_ = new QGridLayout;
	table_view_left_ptr_ = new Table_View_Content(this);
	COMMON->InsertQObjectPtr("table_view_left_ptr_", table_view_left_ptr_);
	table_view_right_ptr_ = new Table_View_Content(this);
	COMMON->InsertQObjectPtr("table_view_right_ptr_", table_view_right_ptr_);
}

void Table_View_Contents::InitLayout()
{
	this->setLayout(gridlayout_table_widget_contents_ptr_);
	gridlayout_table_widget_contents_ptr_->addWidget(table_view_left_ptr_, 0, 0, 1, 1);
	gridlayout_table_widget_contents_ptr_->addWidget(table_view_right_ptr_, 0, 1, 1, 1);
}
