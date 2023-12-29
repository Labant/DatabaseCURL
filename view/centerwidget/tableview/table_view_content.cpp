#include "table_view_content.h"
#include "qt_layout_include.h"
#include <QDebug>

Table_View_Content::Table_View_Content(QWidget* parent)
	:QTableView(parent)
{
	Init();
}

Table_View_Content::~Table_View_Content()
{
}

QString Table_View_Content::GetCurrentData()
{
	return current_str_;
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

void Table_View_Content::
	currentChanged(const QModelIndex& current, 
			const QModelIndex& previous)
{
	qDebug()<<"current.data:" << current.data();
	current_str_ = current.data().toString();
	//
	emit this->SignalTableViewClick(current.data().toString());

	//qDebug() <<"new:" << current.row() << current.data() << current.flags();
	//qDebug() <<"old:" << previous.row();
}
