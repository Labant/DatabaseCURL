#pragma once
#include <qobject.h>
#include "common.h"
#include "qt_mode_base.h"
#include <QAction>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <vector>
#include "structs.hpp"

class Db_Connect;

class Menu_Bar_Mode :
    public QObject,public Qt_Mode_Base
{
    Q_OBJECT
public:
    Menu_Bar_Mode(QObject* parent = nullptr);
    ~Menu_Bar_Mode();

    void OnOpenOrCloseDb();
    void ChangeMenuStat();
    void OnToolBarPositionChange(int);
protected:
	virtual void InitMembers();
	virtual void InitConnects();

private:
    void DealWithForClosedOfDb();
    void DealWithForOpeningOfDb();
    void DealWithForOpenedOfDb();

private:
    Db_Connect* db_connect_ptr_ = nullptr;

};

