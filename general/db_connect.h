#pragma once
#include <qobject.h>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QDir>
#include "common.h"
#include "qt_mode_base.h"
#include <QSqlTableModel> 

class Db_Connect :
    public QObject,public Qt_Mode_Base
{
    Q_OBJECT
public:
    Db_Connect();
    ~Db_Connect();
   
    QSqlDatabase& OpenDB();
    void OnOpenDb();
    void OnCloseDb();
    QList<QVariant>& OnGetDbAllTableName();
    void OnCurrentTextChanged(QString);
protected:
	void OpenDbPath();
    QSqlDatabase& OpenDb();

protected:
	virtual void InitMembers() override;
	virtual void InitConnects() override;

signals:
    void FileNameFromDialog();

private:

    QSqlDatabase sql_database_;
    QSqlQueryModel* sql_model_query_ptr_ = nullptr;
    QSqlQueryModel* sql_model_query_of_serach_ptr_ = nullptr;

    QSqlTableModel* sql_table_model = nullptr;

	QList<QVariant> table_name_ls;

};

