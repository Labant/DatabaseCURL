#include "controler.h"
#include "qt_mode_include.h"
#include "v_controler.h"

Controler::Controler()
{
	Init();
}

Controler::~Controler()
{
}

void Controler::InitMembers()
{
	menu_bar_mode_ptr_ = new Menu_Bar_Mode();
	COMMON->InsertQObjectPtr("menu_bar_mode_ptr_", menu_bar_mode_ptr_);

	operator_area_serach_imp_mode_ = new Operator_Area_Serach_Imp_Mode;
	COMMON->InsertQObjectPtr("operator_area_serach_imp_mode_", operator_area_serach_imp_mode_);

	
}

void Controler::InitConnects()
{

	//!menu bar 
	//首页区
	connect(qobject_cast<QAction*>(COMMON->Get("action_front_page_ptr_")), &QAction::triggered,
		qobject_cast<V_Controler*>(COMMON->Get("w")), &V_Controler::OnChangeToolBar2FrontPage);
	//操作区
	connect(qobject_cast<QAction*>(COMMON->Get("action_operator_ptr_")), &QAction::triggered,
		qobject_cast<V_Controler*>(COMMON->Get("w")), &V_Controler::OnChangeToolBar2Operator);

	//!tool bar
	//首页区
	//open db dialog
	connect(qobject_cast<Db_Connect*>(COMMON->Get("db_connect_ptr_")), &Db_Connect::FileNameFromDialog,
		qobject_cast<Menu_Bar*>(COMMON->Get("menu_bar_ptr_")), &Menu_Bar::OnFileNameFromDialog);
	//open and close db
	connect(qobject_cast<QAction*>(COMMON->Get("action_ptr_open_or_close_db_")), &QAction::triggered,
		qobject_cast<Menu_Bar_Mode*>(COMMON->Get("menu_bar_mode_ptr_")), &Menu_Bar_Mode::OnOpenOrCloseDb);


	//操作区
	//serach area
	connect(qobject_cast<QAction*>(COMMON->Get("action_serach_ptr_")), &QAction::triggered,
		qobject_cast<V_Controler*>(COMMON->Get("w")), [this] {
			STATE->center_widows_index_state_info.store(State_Machine::SerachWindow);
			qobject_cast<V_Controler*>(COMMON->Get("w"))->OnSetCurrentWindow();
		});
	//ComBox state change
	connect(qobject_cast<QComboBox*>(COMMON->Get("combo_box_operator_area_serach_imp_")), &QComboBox::currentTextChanged,
		qobject_cast<Db_Connect*>(COMMON->Get("db_connect_ptr_")) , &Db_Connect::OnCurrentTextChanged);


	//insert area
	connect(qobject_cast<QAction*>(COMMON->Get("action_insert_ptr_")), &QAction::triggered,
		qobject_cast<V_Controler*>(COMMON->Get("w")), [this] {
			STATE->center_widows_index_state_info.store(State_Machine::InsertWindow);
			qobject_cast<V_Controler*>(COMMON->Get("w"))->OnSetCurrentWindow();
		});
	//delete area
	connect(qobject_cast<QAction*>(COMMON->Get("action_delete_ptr_")), &QAction::triggered,
		qobject_cast<V_Controler*>(COMMON->Get("w")), [this] {
			STATE->center_widows_index_state_info.store(State_Machine::DeleteWindow);
			qobject_cast<V_Controler*>(COMMON->Get("w"))->OnSetCurrentWindow();
		});
	//compare area
	connect(qobject_cast<QAction*>(COMMON->Get("action_compare_ptr_")), &QAction::triggered,
		qobject_cast<V_Controler*>(COMMON->Get("w")), [this] {
			STATE->center_widows_index_state_info.store(State_Machine::CompareWindow);
			qobject_cast<V_Controler*>(COMMON->Get("w"))->OnSetCurrentWindow();
		});






}
