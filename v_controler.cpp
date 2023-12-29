#include "v_controler.h"
#include "center_widget.h"
#include <QDebug>

V_Controler::V_Controler(QWidget *parent): QMainWindow(parent)
{
	Init();
}

V_Controler::~V_Controler()
{
}

void V_Controler::OnChangeToolBar2FrontPage()
{
	if (STATE->tool_bar_state_info == State_Machine::FrontPage)
	{
		return;
	}
	else
	{		
		STATE->tool_bar_state_info.store(State_Machine::FrontPage);
		this->removeToolBar(tool_bar_operator_ptr_);
		this->addToolBar((Qt::ToolBarArea)STATE->tool_bar_position_state_info.load(), tool_bar_front_page_ptr_);
		tool_bar_front_page_ptr_->show();
		center_widget_ptr->setCurrentIndex(State_Machine::OpenAndCloseWindow);
	}

}

void V_Controler::OnChangeToolBar2Operator()
{
	if (STATE->tool_bar_state_info == State_Machine::Operator)
	{
		return;
	}
	else
	{
		STATE->tool_bar_state_info.store(State_Machine::Operator);

		this->removeToolBar(tool_bar_front_page_ptr_);
		this->addToolBar((Qt::ToolBarArea)STATE->tool_bar_position_state_info.load(), tool_bar_operator_ptr_);
		tool_bar_operator_ptr_->show();
		center_widget_ptr->setCurrentIndex(State_Machine::SerachWindow);
	}
}

void V_Controler::OnSetCurrentWindow(State_Machine::CenterWidgetIndexState state)
{
	center_widget_ptr->setCurrentIndex(STATE->center_widows_index_state_info.load());
	qDebug() << __FUNCDNAME__ << STATE->center_widows_index_state_info.load();


}

void V_Controler::OnShowInfos(QString show_info_)
{
	QMessageBox::information(this, QStringLiteral("¾¯¸æ"), QStringLiteral("show_info_"));
}


void V_Controler::InitMembers()
{
	//gridlayout_center_ptr_ = new QGridLayout;

	center_widget_ptr = new Center_Widget;
	COMMON->InsertQObjectPtr("center_widget_ptr", center_widget_ptr);

	menu_bar_ptr_ = new Menu_Bar;
	COMMON->InsertQObjectPtr("menu_bar_ptr_", menu_bar_ptr_);
	tool_bar_front_page_ptr_ = new Tool_Bar_Imp_Front_Page();
	COMMON->InsertQObjectPtr("tool_bar_front_page_ptr_", tool_bar_front_page_ptr_);

	tool_bar_operator_ptr_ = new Tool_Bar_Imp_Operator();
	COMMON->InsertQObjectPtr("tool_bar_operator_ptr_", tool_bar_operator_ptr_);

}

void V_Controler::InitLayout()
{
	setMinimumSize(1200, 600);

	this->setMenuBar(menu_bar_ptr_);
	this->addToolBar(Qt::TopToolBarArea, tool_bar_front_page_ptr_);

	this->setCentralWidget(center_widget_ptr);
	center_widget_ptr->hide();
	center_widget_ptr->setCurrentIndex(STATE->center_widows_index_state_info);


	QFile a;
	a.setFileName(QDir::currentPath() + "/main.css");
	if (!a.open(QIODevice::ReadOnly))
	{
		qDebug() << "css file not opened!";
	}
	QTextStream filetext(&a);
	QString stylesheet = filetext.readAll();

	this->setStyleSheet(stylesheet);
	a.close();

	//this->update();
}

//void V_Controler::paintEvent(QPaintEvent*)
//{
//	QStyleOption opt;
//	opt.init(this);
//	QPainter p(this);
//	style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
//}

//void V_Controler::paintEvent(QPaintEvent* event)
//{
//	this->update();
//}
