#pragma once
#include <qobject.h>
//#include "qt_layout_include.h"
#include <QToolBar>
#include "qt_layout_base.h"

class Tool_Bar_Imp_Front_Page :
    public QToolBar,public Qt_Layout_Base
{
	Q_OBJECT
public:
	Tool_Bar_Imp_Front_Page();
	~Tool_Bar_Imp_Front_Page();

protected:
	virtual void InitMembers();
	virtual void InitLayout();

private:
	QAction* action_ptr_open_or_close_db_ = nullptr;
};

