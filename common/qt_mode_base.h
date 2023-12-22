#pragma once
class Qt_Mode_Base
{
public:
	Qt_Mode_Base();
	virtual ~Qt_Mode_Base();

protected:
	virtual void Init();
	virtual void InitMembers() = 0;
	virtual void InitConnects() = 0;
};

