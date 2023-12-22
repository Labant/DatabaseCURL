#include "v_controler.h"  //View
#include "controler.h"  //Mode
#include <QtWidgets/QApplication>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QDebug>
#include "common.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

	//QFile c;
	//qDebug() << QDir::currentPath();
	//c.setFileName(QDir::currentPath() + "/main.css");
	//if (!c.open(QIODevice::ReadOnly))
	//{
	//	qDebug() << "css file not opened!";
	//}
	//QTextStream filetext(&c);
	//QString stylesheet = filetext.readAll();
	//a.setStyleSheet(stylesheet);
	//c.close();

	//QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

	//QString tt = QString::fromLocal8Bit("E:\\01_\\04_Code\\数据库增删改查操作\\db\\pa_ann_sqlit3_jlct3.db");
	//qDebug() << tt;
	//db.setDatabaseName(tt);
	//if (db.open())
	//{
	//	QSqlQuery query;

	//	query.prepare("SELECT * FROM TTextContent");
	//	query.exec();
	//	QSqlRecord record = query.record();
	//	qDebug() << record.fieldName(0) << record.fieldName(1) << record.fieldName(2);

	//	for (;query.next();)
	//	{
	//		db_data data;
	//		data.keyId = query.value("keyId").toInt();
	//		data.StringContent = query.value("StringContent").toString();
	//		data.ShortName = query.value("ShortName").toString();

	//		vec_data.emplace_back(data);
	//	}
	//}
	//if (!vec_data.empty())
	//{
	//	for (int i = 0; i < vec_data.size(); ++i)
	//	{
	//		qDebug() << vec_data[i].keyId << " :"  \
	//			<< vec_data[i].StringContent << " :" \
	//			<< vec_data[i].ShortName;
	//	}
	//}

	V_Controler w;  //View
	COMMON->InsertQObjectPtr("w", &w);

	Controler Contorl;  //Mode、MV
	
	w.show();
    return a.exec();
}
