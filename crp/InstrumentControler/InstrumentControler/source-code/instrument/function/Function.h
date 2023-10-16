#pragma once

/**
 * name: Function
 * breif: ����ʵ���࣬�����豸ȫ������ʵ����Ļ��ࡣ
 * author: yameng_he
 * date: 2016-03-15.
 */
class Function{
//construction & destruction
public:
	Function(void);
	virtual ~Function(void);
//overrides
public:
	virtual int start()=0;
	virtual void stop()=0;
//restriction
private:
	Function(const Function &);
	Function &operator=(const Function &);
};