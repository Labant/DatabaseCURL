#pragma once
#include <qobject.h>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QSqlRecord>
#include <map>

class Edit_Query_Model :
    public QSqlQueryModel
{
    Q_OBJECT
public:
    Edit_Query_Model();
    ~Edit_Query_Model();

	virtual QVariant data(const QModelIndex& index,
		int role = Qt::DisplayRole) const override;
    virtual bool setData(const QModelIndex& index,
        const QVariant& value, int role = Qt::EditRole) override;
    Qt::ItemFlags flags(const QModelIndex& index) const override;
    void SetConfig(const QSqlQuery& query, QString str_);
    int GetKeyIdOfShortNameString(QString);
private:
    QList<QVariant> variant_list_;
    QString cow_name_;
    QSqlQuery sqlquery_;
    std::map<QString, int> map_;
};

