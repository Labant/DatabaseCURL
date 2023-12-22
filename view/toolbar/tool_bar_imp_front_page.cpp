#include "tool_bar_imp_front_page.h"
#include "common.h"

Tool_Bar_Imp_Front_Page::Tool_Bar_Imp_Front_Page()
{
	Init();
}

Tool_Bar_Imp_Front_Page::~Tool_Bar_Imp_Front_Page()
{
}

void Tool_Bar_Imp_Front_Page::InitMembers()
{
	action_ptr_open_or_close_db_ = new QAction(QStringLiteral("打开数据库"));
	COMMON->InsertQObjectPtr("action_ptr_open_or_close_db_", action_ptr_open_or_close_db_);
}

void Tool_Bar_Imp_Front_Page::InitLayout()
{
	this->addAction(action_ptr_open_or_close_db_);
}
