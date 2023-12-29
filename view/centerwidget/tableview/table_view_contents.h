#pragma once
#include <qwidget.h>
#include "qt_layout_base.h"
#include "table_view_content.h"
#include <QGridLayout>

class Table_View_Contents :
    public QWidget,public Qt_Layout_Base
{
    Q_OBJECT
public:
    Table_View_Contents(QWidget* parent = nullptr);
    ~Table_View_Contents();
    void SetModels(QAbstractItemModel* model1, QAbstractItemModel* model2);
    void SetModel2(QAbstractItemModel* model2);
protected:
	virtual void InitMembers();
    virtual void InitLayout();

private:
    QGridLayout* gridlayout_table_widget_contents_ptr_ = nullptr;
	Table_View_Content* table_view_left_ptr_;
	Table_View_Content* table_view_right_ptr_;

};

