#pragma once
#include <qobject.h>
#include <QTableView>
#include "qt_layout_base.h"

class QHeaderView;
class Table_View_Content :
    public QTableView,public Qt_Layout_Base
{
    Q_OBJECT
public:
    Table_View_Content();
    ~Table_View_Content();

protected:
	virtual void InitMembers();
	virtual void InitLayout();

private:
    QHeaderView* header_view_of_table_view = nullptr;
};

