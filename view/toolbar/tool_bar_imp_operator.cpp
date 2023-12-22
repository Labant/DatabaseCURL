#include "tool_bar_imp_operator.h"
#include "common.h"

Tool_Bar_Imp_Operator::Tool_Bar_Imp_Operator()
{
	Init();
}

Tool_Bar_Imp_Operator::~Tool_Bar_Imp_Operator()
{
}

void Tool_Bar_Imp_Operator::InitMembers()
{
	action_serach_ptr_ = new QAction(QStringLiteral("��ѯ"));
	COMMON->InsertQObjectPtr("action_serach_ptr_", action_serach_ptr_);
	action_insert_ptr_ = new QAction(QStringLiteral("����"));
	COMMON->InsertQObjectPtr("action_insert_ptr_", action_insert_ptr_);
	action_delete_ptr_ = new QAction(QStringLiteral("ɾ��"));
	COMMON->InsertQObjectPtr("action_delete_ptr_", action_delete_ptr_);
	action_compare_ptr_ = new QAction(QStringLiteral("�Ա�"));
	COMMON->InsertQObjectPtr("action_compare_ptr_", action_compare_ptr_);
}

void Tool_Bar_Imp_Operator::InitLayout()
{
	this->addAction(action_serach_ptr_);
	this->addAction(action_insert_ptr_);
	this->addAction(action_delete_ptr_);
	this->addAction(action_compare_ptr_);
}
