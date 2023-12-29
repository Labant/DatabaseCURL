#pragma once

#include <QtWidgets/QMainWindow>
#include <QObject>
#include "qt_layout_base.h"
#include "qt_layout_include.h"
#include "common.h"
#include "menu_bar.h"
#include <QDebug>
#include <QHeaderView>
#include <QPainter>
#include <QMessageBox>

class Center_Widget;

class V_Controler : public QMainWindow,public Qt_Layout_Base
{
    Q_OBJECT

public:
    V_Controler(QWidget *parent = nullptr);
    ~V_Controler();

	void OnChangeToolBar2FrontPage();
	void OnChangeToolBar2Operator();
	void OnSetCurrentWindow(State_Machine::CenterWidgetIndexState = State_Machine::OpenAndCloseWindow);
	void OnShowInfos(QString);
protected:
	virtual void InitMembers();
	virtual void InitLayout();
	//void paintEvent(QPaintEvent* event);
public:

private:


    Menu_Bar* menu_bar_ptr_ = nullptr;
    Tool_Bar_Imp_Front_Page* tool_bar_front_page_ptr_ = nullptr;
    Tool_Bar_Imp_Operator* tool_bar_operator_ptr_ = nullptr;

	//center window
	Center_Widget* center_widget_ptr = nullptr;


};
