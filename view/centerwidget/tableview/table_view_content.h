#pragma once
#include <qobject.h>
#include <QTableView>
#include "qt_layout_base.h"
#include <QPair>

class QHeaderView;
class Table_View_Content :
    public QTableView,public Qt_Layout_Base
{
    Q_OBJECT
public:
    Table_View_Content(QWidget* parent = nullptr);
    ~Table_View_Content();
    QString GetCurrentData();
signals:
    void SignalTableViewClick(QString str_data_);
protected:
	virtual void InitMembers();
	virtual void InitLayout();
    void currentChanged(const QModelIndex& current, const QModelIndex& previous) override;


private:
    QHeaderView* header_view_of_table_view = nullptr;
    QPair<int, int> pari_infos_of_row_click_;
    QString current_str_;
};

