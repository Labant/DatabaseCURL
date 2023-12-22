#pragma once
#include <qobject.h>
#include <QStackedWidget>
#include "qt_layout_base.h"

class Table_Content_And_Operator_Widget;

class Center_Widget :
    public QStackedWidget,public Qt_Layout_Base
{
    Q_OBJECT
public:
    Center_Widget();
    ~Center_Widget();
protected:
	virtual void InitMembers();
	virtual void InitLayout();

    //4 widget in center widget,eg,�ر����ݿ�/�����ݿ⡢ ��ѯ�����롢ɾ�����Աȣ�δʵ�֣�
    Table_Content_And_Operator_Widget* open_or_close_center_widget_ptr_ = nullptr;
    Table_Content_And_Operator_Widget* serach_center_widget_ptr_ = nullptr;
    Table_Content_And_Operator_Widget* insert_center_widget_ptr_ = nullptr;
    Table_Content_And_Operator_Widget* delete_center_widget_ptr_ = nullptr;
    Table_Content_And_Operator_Widget* compare_center_widget_ptr_ = nullptr;


};

