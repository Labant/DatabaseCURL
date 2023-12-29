#pragma once
#include <qwidget.h>
#include <QObject>
#include <QGridLayout>
#include "qt_layout_base.h"
#include <QSqlQueryModel>
#include "state_machine.h"

class QGridLayout;
class Operator_Aera;
class Table_View_Content;
class Operator_Area_Serach_Imp;
class Operator_Area_Insert_Imp;
class Operator_Area_Delete_Imp;
class Operator_Area_Compare_Imp;
class Table_Content_And_Operator_Widget;
class Table_View_Content_Insert;

class Table_Content_And_Operator_Widget :
    public QWidget,public Qt_Layout_Base
{
    Q_OBJECT
public:
    Table_Content_And_Operator_Widget();
    Table_Content_And_Operator_Widget(Table_View_Content* table_view__ = nullptr, 
        State_Machine::OperatorAreaCategory category = State_Machine::OpenAndCloseCategory);
    virtual ~Table_Content_And_Operator_Widget();

    void SetTableMode(QSqlQueryModel*);
    void SetTableModeEntery(QSqlQueryModel*);
    void SetTableMode(QSqlQueryModel* m1, QSqlQueryModel* m2);
    void OnSetOperatorImp();
protected:
	virtual void InitMembers();
	virtual void InitLayout();

protected:
    QGridLayout* gridlayout_center_ptr_ = nullptr;

    Table_View_Content* table_view_ptr_ = nullptr;  //default
    Table_View_Content_Insert* dou_table_view_ptr_ = nullptr;  //insert table 

    Operator_Aera* operator_aera_ptr_ = nullptr;
    Operator_Area_Serach_Imp* operator_area_serach_imp_ = nullptr;

    Table_View_Content* table_view_enteny_ptr_ = nullptr;
private:
    bool bool_is_add_operator_area_ = true;
   std::atomic< State_Machine::OperatorAreaCategory> local_category = State_Machine::OpenAndCloseCategory;
};

