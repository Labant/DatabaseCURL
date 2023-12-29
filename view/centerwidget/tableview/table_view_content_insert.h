#pragma once
#include <qwidget.h>
#include "qt_layout_base.h"
#include "qt_layout_include.h"
#include "table_view_contents.h"

class Operator_Icon_Domain;

class Table_View_Content_Insert :
    public QWidget,public Qt_Layout_Base
{
    Q_OBJECT
public:
    Table_View_Content_Insert(QWidget *parent = nullptr);
    ~Table_View_Content_Insert();
    void SetModels(QAbstractItemModel* model1, QAbstractItemModel* model2);
    void SetModel2(QAbstractItemModel* model2);

    void OnSignalTableViewClick(QString str_data_);
	void SetIconsOnCenter();

protected:
	virtual void InitMembers();
	virtual void InitLayout();

signals:
    void GetTableViewContentsModels(int category,QString content_);
private:
    QGridLayout* gridlayout_table_view_content_insert_ptr_ = nullptr;
    Table_View_Contents* table_view_contents_ptr_ = nullptr;
    Operator_Icon_Domain* operator_icon_domain_ptr_ = nullptr;


};

