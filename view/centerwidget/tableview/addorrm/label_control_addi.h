#pragma once
#include <qlabel.h>
#include "qt_layout_base.h"
#include <QImage>
#include <QMouseEvent>

class Label_Control_Addi :
    public QLabel//,public Qt_Layout_Base
{
    Q_OBJECT
public:
	Label_Control_Addi(QWidget* parent = nullptr);
	~Label_Control_Addi();

protected:
	void Init();
	void InitMembers();
	void InitLayout();

	virtual void
		mousePressEvent(QMouseEvent* ev) override;
signals:
	void SignalAddiClicked();

private:
	QImage image_icon_right_;
};

