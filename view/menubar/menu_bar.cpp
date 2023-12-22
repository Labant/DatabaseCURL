#include "menu_bar.h"

Menu_Bar::Menu_Bar()
{
	Init();
}

Menu_Bar::~Menu_Bar()
{
}

void Menu_Bar::InitMembers()
{

	action_front_page_ptr_ = new QAction(QString::fromLocal8Bit("首页"));
	COMMON->InsertQObjectPtr("action_front_page_ptr_", action_front_page_ptr_);
	action_front_page_ptr_->setObjectName("action_front_page_ptr_");


	action_operator_ptr_ = new QAction(QString::fromLocal8Bit("操作"));
	COMMON->InsertQObjectPtr("action_operator_ptr_", action_operator_ptr_);
	action_operator_ptr_->setObjectName("action_operator_ptr_");
		
}

void Menu_Bar::InitLayout()
{
	this->addAction(action_front_page_ptr_);
	this->addAction(action_operator_ptr_);
}
void Menu_Bar::OnFileNameFromDialog()
{
	if (STATE->bool_is_clearn_db_connect_name.load())
	{
		file_path_str_.clear();
		STATE->bool_is_clearn_db_connect_name.store(!STATE->bool_is_clearn_db_connect_name);
		file_path_str_ = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("打开数据库"), 
			QDir::currentPath() + "/db", "DataBase File (*.db)");

	}
	
}
