#pragma once
#include <QObject>
#include <atomic>

#define  STATE State_Machine::GetIntance()

class State_Machine
{
private:
	State_Machine(QObject* parent = nullptr);
	~State_Machine();

public:
	static State_Machine*  GetIntance();
	
private:
	static State_Machine* intance_;

public:
	//Db connect state
	enum DbState {
		Closed = 0,
		Opening,
		Opened
	};

	//Db
	std::atomic<bool> state_db_is_should_open = true;
	std::atomic<bool> bool_is_clearn_db_connect_name = false;
	std::atomic<DbState> db_state_info = DbState::Closed;

	//tool bar state
	enum ToolBarState
	{
		FrontPage = 0,
		Operator
	};
	std::atomic<ToolBarState> tool_bar_state_info = ToolBarState::FrontPage;
	//tool bar position state
	std::atomic<int> tool_bar_position_state_info = Qt::TopToolBarArea;

	//center widget index state
	enum CenterWidgetIndexState
	{
		OpenAndCloseWindow = 0,
		SerachWindow,
		InsertWindow,
		DeleteWindow,
		CompareWindow
	};
	std::atomic<CenterWidgetIndexState> center_widows_index_state_info = CenterWidgetIndexState::OpenAndCloseWindow;

	//operator area category
	enum OperatorAreaCategory
	{
		OpenAndCloseCategory = CenterWidgetIndexState::OpenAndCloseWindow,
		SerachCategory = CenterWidgetIndexState::SerachWindow,
		InsertCategory = CenterWidgetIndexState::InsertWindow,
		DeleteCategory = CenterWidgetIndexState::DeleteWindow,
		CompareCategory = CenterWidgetIndexState::CompareWindow
	};

	//Table view category
	enum TableViewCategory
	{
		AudioCategory = 0,
		TextCategory,
	};
	std::atomic<TableViewCategory> table_category_state_info_of_insert_window = TableViewCategory::AudioCategory;

public:
class Destory
	{
	public:
		Destory() {};
		~Destory() {
			if (intance_ != nullptr)
			{
				delete intance_;
				intance_ = nullptr;
			}
		};
	};

};

