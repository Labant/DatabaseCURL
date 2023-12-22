#include "center_widget.h"
#include "qt_layout_include.h"
#include "table_content_and_operator_widget.h"

Center_Widget::Center_Widget()
{
	Init();
}

Center_Widget::~Center_Widget()
{
}

void Center_Widget::InitMembers()
{
	open_or_close_center_widget_ptr_ = new Table_Content_And_Operator_Widget(0,State_Machine::OpenAndCloseCategory);
	COMMON->InsertQObjectPtr("open_or_close_center_widget_ptr_", open_or_close_center_widget_ptr_);
	serach_center_widget_ptr_ = new Table_Content_And_Operator_Widget(0, State_Machine::SerachCategory);
	COMMON->InsertQObjectPtr("serach_center_widget_ptr_", serach_center_widget_ptr_);
	insert_center_widget_ptr_ = new Table_Content_And_Operator_Widget(0, State_Machine::InsertCategory);
	COMMON->InsertQObjectPtr("insert_center_widget_ptr_", insert_center_widget_ptr_);
	delete_center_widget_ptr_ = new Table_Content_And_Operator_Widget(0, State_Machine::DeleteCategory);
	COMMON->InsertQObjectPtr("delete_center_widget_ptr_", delete_center_widget_ptr_);
	compare_center_widget_ptr_ = new Table_Content_And_Operator_Widget(0, State_Machine::CompareCategory);
	COMMON->InsertQObjectPtr("compare_center_widget_ptr_", compare_center_widget_ptr_);
}

void Center_Widget::InitLayout()
{
	this->addWidget(open_or_close_center_widget_ptr_);
	this->addWidget(serach_center_widget_ptr_);
	this->addWidget(insert_center_widget_ptr_);
	this->addWidget(delete_center_widget_ptr_);
	this->addWidget(compare_center_widget_ptr_);

}
