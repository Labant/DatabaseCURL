#pragma once

#include <QMenuBar> 
#include "qt_layout_include.h"
#include "qt_layout_base.h"
#include "common.h"
#include <QMenu>

class Menu_Bar :
    public QMenuBar,public Qt_Layout_Base
{
	Q_OBJECT
public:
    Menu_Bar();
    ~Menu_Bar();

public:
	void OnFileNameFromDialog();

protected:
	virtual void InitMembers();
	virtual void InitLayout();

public:

	QString file_path_str_;

private:

	QAction* action_front_page_ptr_ = nullptr;
	QAction* action_operator_ptr_ = nullptr;

};

