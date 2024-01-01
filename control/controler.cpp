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
	//tip widget
	connect(qobject_cast<Db_Connect*>(COMMON->Get("db_connect_ptr_")), &Db_Connect::ErrorInfo,
		qobject_cast<V_Controler*>(COMMON->Get("w")), &V_Controler::OnShowInfos);

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
	//show current window
	connect(qobject_cast<QAction*>(COMMON->Get("action_insert_ptr_")), &QAction::triggered,
		qobject_cast<V_Controler*>(COMMON->Get("w")), [this] {
			STATE->center_widows_index_state_info.store(State_Machine::InsertWindow);
			qobject_cast<V_Controler*>(COMMON->Get("w"))->OnSetCurrentWindow();
		});
	//the combox of insert area set value 
	connect(qobject_cast<QAction*>(COMMON->Get("action_insert_ptr_")), &QAction::triggered,
		qobject_cast<Db_Connect*>(COMMON->Get("db_connect_ptr_")),&Db_Connect::OnCurrentTextChangedOfInsert);
	//ComBox state change
	connect(qobject_cast<QComboBox*>(COMMON->Get("opera_area_insert_combox_ptr_")), &QComboBox::currentTextChanged,
		qobject_cast<Db_Connect*>(COMMON->Get("db_connect_ptr_")), &Db_Connect::OnCurrentTextChangedOfComboxOfInsert);
	//Table_View_Content_Insert place get data for two table
	connect(qobject_cast<Table_View_Content_Insert*>(COMMON->Get("dou_table_view_ptr_")), &Table_View_Content_Insert::GetTableViewContentsModels,
		qobject_cast<Db_Connect*>(COMMON->Get("db_connect_ptr_")), &Db_Connect::OnGetTableViewContentsModels);
	//AreaId of table is clicked
	connect(qobject_cast<Table_View_Content*>(COMMON->Get("table_view_enteny_ptr_")), &Table_View_Content::SignalTableViewClick,
		qobject_cast<Table_View_Content_Insert*>(COMMON->Get("dou_table_view_ptr_")), &Table_View_Content_Insert::OnSignalTableViewClick);
	//left view of dou tables is clicked
	connect(qobject_cast<Table_View_Content*>(COMMON->Get("table_view_left_ptr_")), &Table_View_Content::SignalTableViewClick,
		qobject_cast<Db_Connect*>(COMMON->Get("db_connect_ptr_")), &Db_Connect::OnLeftTableClicked);
	//up move
	connect(qobject_cast<QPushButton*>(COMMON->Get("opera_area_insert_btn_ptrs_[0]")), &QPushButton::clicked,
		qobject_cast<Db_Connect*>(COMMON->Get("db_connect_ptr_")), &Db_Connect::OnUpMoveBtnClicked);
	//down move
	connect(qobject_cast<QPushButton*>(COMMON->Get("opera_area_insert_btn_ptrs_[1]")), &QPushButton::clicked,
		qobject_cast<Db_Connect*>(COMMON->Get("db_connect_ptr_")), &Db_Connect::OnDownMoveBtnClicked);
	//sure btn
	connect(qobject_cast<QPushButton*>(COMMON->Get("opera_area_insert_btn_ptrs_[2]")), &QPushButton::clicked,
		qobject_cast<Db_Connect*>(COMMON->Get("db_connect_ptr_")), &Db_Connect::OnSureBtnClicked);
	//addition lable mouse press event
	connect(qobject_cast<Label_Control_Addi*>(COMMON->Get("label_control_addi_ptr_")), &Label_Control_Addi::SignalAddiClicked,
		qobject_cast<Db_Connect*>(COMMON->Get("db_connect_ptr_")), &Db_Connect::OnSignalAddiClicked);
	//remove lable mouse press event
	connect(qobject_cast<Label_Control_Remove*>(COMMON->Get("label_control_rm_ptr_")), &Label_Control_Remove::SignalRemoveClicked,
		qobject_cast<Db_Connect*>(COMMON->Get("db_connect_ptr_")), &Db_Connect::OnSignalRmClicked);


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

	//status bar info of tip show
	connect(qobject_cast<Db_Connect*>(COMMON->Get("db_connect_ptr_")), &Db_Connect::ShowStatusBarInfo,
		qobject_cast<V_Controler*>(COMMON->Get("w")), &V_Controler::OnShowStatusBarInfo);

}
