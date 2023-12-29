#pragma once
#include <qlabel.h>
#include <QMouseEvent>

class Label_Control_Remove :
    public QLabel
{
	Q_OBJECT
public:
	Label_Control_Remove(QWidget* parent = nullptr);
	~Label_Control_Remove();

signals:
	void SignalRemoveClicked();
protected:
	void Init();
	void InitMembers();
	void InitLayout();

	virtual void
		mousePressEvent(QMouseEvent* ev) override;

private:
	QImage image_icon_left_;
};

