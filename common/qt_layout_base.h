#pragma once
#include <QObject>

class Qt_Layout_Base
{
public:
	explicit Qt_Layout_Base();
	virtual ~Qt_Layout_Base();
protected:
	virtual void SetControler(QObject* view_ptr_);
	virtual void Init();
	virtual void InitMembers() = 0;
	virtual void InitLayout() = 0;
};

