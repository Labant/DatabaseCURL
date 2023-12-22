#include "Menu_Bar_Mode.h"
#include "qt_mode_include.h"
#include <QDebug>


Menu_Bar_Mode::Menu_Bar_Mode(QObject* parent)
{
	Init();
}

Menu_Bar_Mode::~Menu_Bar_Mode()
{
}

void Menu_Bar_Mode::OnOpenOrCloseDb()
{

	switch (STATE->db_state_info)
	{
	case 0:  //closed -> open
		DealWithForClosedOfDb();
		break;
	case 1:
		DealWithForOpeningOfDb();
		break;
	case 2: //opened -> close
		DealWithForOpenedOfDb();
		break;
	default:
		break;
	}

	ChangeMenuStat();




	//STATE->state_db_is_should_open = !STATE->state_db_is_should_open;
}

void Menu_Bar_Mode::ChangeMenuStat()
{
	if (0 == qobject_cast<QAction*>(COMMON->Get("action_ptr_open_or_close_db_"))->iconText().compare(QString::fromLocal8Bit("打开数据库"), Qt::CaseSensitive))
	{
		qobject_cast<QAction*>(COMMON->Get("action_ptr_open_or_close_db_"))->setText(QString::fromLocal8Bit("关闭数据库"));
		//STATE->state_db_is_should_open.store(true);
	}
	else
	{
		qobject_cast<QAction*>(COMMON->Get("action_ptr_open_or_close_db_"))->setText(QString::fromLocal8Bit("打开数据库"));
		//STATE->state_db_is_should_open.store(false);
	};
}

void Menu_Bar_Mode::OnToolBarPositionChange(int state)
{
	STATE->tool_bar_position_state_info.store(state);
}

void Menu_Bar_Mode::InitMembers()
{
	db_connect_ptr_ = new Db_Connect;
	COMMON->InsertQObjectPtr("db_connect_ptr_", db_connect_ptr_);

}

void Menu_Bar_Mode::InitConnects()
{
}

void Menu_Bar_Mode::DealWithForClosedOfDb()
{
	db_connect_ptr_->OnOpenDb();
	qobject_cast<QWidget*>(COMMON->Get("center_widget_ptr"))->show();
	qobject_cast<Operator_Area_Serach_Imp_Mode*>(COMMON->Get("operator_area_serach_imp_mode_"))->OnGetAllTableName2ComBox();
}

void Menu_Bar_Mode::DealWithForOpeningOfDb()
{

}

void Menu_Bar_Mode::DealWithForOpenedOfDb()
{
	//qobject_cast<QTableView*>(COMMON->Get("table_view_ptr_"))->hide();
	qobject_cast<QWidget*>(COMMON->Get("center_widget_ptr"))->hide();
	db_connect_ptr_->OnCloseDb();
}
