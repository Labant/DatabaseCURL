#pragma once
#include <qobject.h>
//#include "qt_layout_include.h"
#include <QToolBar>
#include "qt_layout_base.h"

class Tool_Bar_Imp_Operator :
    public QToolBar,public Qt_Layout_Base
{
    Q_OBJECT
public:
	Tool_Bar_Imp_Operator();
	~Tool_Bar_Imp_Operator();

protected:
	virtual void InitMembers();
	virtual void InitLayout();

private:
	QAction* action_serach_ptr_ = nullptr;
	QAction* action_insert_ptr_ = nullptr;
	QAction* action_delete_ptr_ = nullptr;
	QAction* action_compare_ptr_ = nullptr;


};

