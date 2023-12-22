#include "table_view_content.h"
#include "qt_layout_include.h"

Table_View_Content::Table_View_Content()
{
	Init();
}

Table_View_Content::~Table_View_Content()
{
}

void Table_View_Content::InitMembers()
{
	header_view_of_table_view = new QHeaderView(Qt::Horizontal, 0);
}

void Table_View_Content::InitLayout()
{

	header_view_of_table_view->setStretchLastSection(true);
	this->setHorizontalHeader(header_view_of_table_view);
}
