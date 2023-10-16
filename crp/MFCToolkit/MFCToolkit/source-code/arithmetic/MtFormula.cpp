#include"stdafx.h"
#include"MtFormula.h"
#include<assert.h>

/**
 * name: MtFormula
 * breif: ���캯����
 * param: x - ָ�����ϵ�x���顣
 *        y - ָ�����ϵ�y���顣
 *        size - �����x��y����ߴ硣
 *        min_size - �����x��y������С�ߴ硣
 * return: --
 */
MtFormula::MtFormula(const double *x,const double *y,
	const unsigned int size,const unsigned int minimum_size)
	:_x(x)
	,_y(y)
	,_size(size)
	,_minimum_size(minimum_size){
}

/**
 * name: ~MtFormula
 * brief: �����������������������ͷš�
 * param: --
 * return: --
 */
MtFormula::~MtFormula(void){
}

/**
 * name: get_x
 * brief: ��ȡ��ʽ��ָ���±��xֵ��
 * param: index - �±�ֵ��
 * return: ����ָ���±��xֵ��
 */
double MtFormula::get_x(const unsigned int index) const{
	//1.�˴����Ե�ǰ��ʽ�����������״̬��
	assert(MtFormula::is_can_fitted());
	//2.�˴����Բ������ݵ������Ϸ���
	assert(index<_size);
	//3.���ص�ǰָ���±��Ũ��ֵ��
	return(_x[index]);
}

/**
 * name: get_y
 * brief: ��ȡ��ʽ��ָ���±��yֵ����
 * param: index - �±�ֵ��
 * return: ����ָ���±��yֵ��
 */
double MtFormula::get_y(const unsigned int index) const{
	//1.�˴����Ե�ǰ��ʽ�����������״̬��
	assert(MtFormula::is_can_fitted());
	//2.�˴����Բ������ݵ������Ϸ���
	assert(index<_size);
	//3.���ص�ǰָ���±�������ֵ��
	return(_y[index]);
}

/**
 * name: get_average_x
 * brief: ��ȡx��ƽ��ֵ��
 * param: --
 * return: ����x��ƽ��ֵ��
 */
double MtFormula::get_average_x() const{
	//1.�˴����Ե�ǰ��ʽ�����������״̬��
	assert(MtFormula::is_can_fitted());
	//2.���㵱ǰ��ʽ��x��ƽ��ֵ��
	//2-1.������ǰ�������������
	double average_x=0.0;
	//2-2.������ʽ��x���飬�ۼ�x�ĺ͡�
	for(unsigned int index=0;index!=_size;++index){
		average_x+=_x[index];
	}
	//2-3.����x��ƽ��ֵ��
	average_x=average_x/static_cast<double>(_size);
	//3.�������е��ˣ�ֱ�ӷ���x��ƽ��ֵ��
	return(average_x);
}

/**
 * name: get_average_y
 * brief: ��ȡy��ƽ��ֵ��
 * param: --
 * return: ����y��ƽ��ֵ��
 */
double MtFormula::get_average_y() const{
	//1.�˴����Ե�ǰ��ʽ�����������״̬��
	assert(MtFormula::is_can_fitted());
	//2.���㵱ǰ��ʽ��y��ƽ��ֵ��
	//2-1.������ǰ�������������
	double average_y=0.0;
	//2-2.������ʽ��y���飬�ۼ�y�ĺ͡�
	for(unsigned int index=0;index!=_size;++index){
		average_y+=_y[index];
	}
	//2-3.����y��ƽ��ֵ��
	average_y=average_y/static_cast<double>(_size);
	//3.�������е��ˣ�ֱ�ӷ���ƽ������ȡ�
	return(average_y);
}

/**
 * name: get_size
 * brief: ��ȡ��ǰ��ʽ��δ֪������ĸ�����
 * param: --
 * return: ���ص�ǰ��ʽ��δ֪������ĸ�����
 */
unsigned int MtFormula::get_size() const{
	//1.�����ǰ��ʽ��δ���������������ֱ�ӷ����㡣
	if(!MtFormula::is_can_fitted()){
		return(0);
	}
	//2.���ص�ǰǰ��ʽ��δ֪������ĸ�����
	else{
		return(_size);
	}
}

/**
 * name: get_maximum_x_index
 * brief: ��ȡ��ǰ��ʽ�У����x���±�ֵ��
 * param: --
 * return: ���ص�ǰ��ʽ�����x���±�ֵ��
 */
unsigned int MtFormula::get_maximum_x_index() const{
	//1.�˴����Ե�ǰ��ʽ�����������״̬��
	assert(MtFormula::is_can_fitted());
	//2.���㵱ǰ��ʽ�����x���±�ֵ��
	//2-1.������ǰ�������������
	double max_x=0.0;
	unsigned int index=0;
	//2-2.����x�洢���飬�������x���±�ֵ��
	for(unsigned int i=0;i!=_size;++i){
		if(0==i){
			max_x=_x[i];
			index=i;
		}else if(_x[i]>max_x){
			max_x=_x[i];
			index=i;
		}
	}
	//3.���ؼ�����±�ֵ��
	return(index);
}

/**
 * name: get_minimum_x_index
 * brief: ��ȡ��ǰ��ʽ����Сx���±�ֵ��
 * param: --
 * return: ���ص�ǰ��ʽ����Сx���±�ֵ��
 */
unsigned int MtFormula::get_minimum_x_index() const{
	//1.�˴����Ե�ǰ��ʽ�����������״̬��
	assert(MtFormula::is_can_fitted());
	//2.���㵱ǰ��ʽ����Сx���±�ֵ��
	//2-1.������ǰ�������������
	double min_x=0.0;
	unsigned int index=0;
	//2-2.����x�洢���飬������x���±�ֵ��
	for(unsigned int i=0;i!=_size;++i){
		if(0==i){
			min_x=_x[i];
			index=i;
		}else if(_x[i]<min_x){
			min_x=_x[i];
			index=i;
		}
	}
	//3.���ؼ�����±�ֵ��
	return(index);
}

/**
 * name: get_maximum_y_index
 * brief: ��ȡ��ǰ��ʽ�����y���±ꡣ
 * param: --
 * return: ���ص�ǰ��ʽ�����y���±�ֵ��
 */
unsigned int MtFormula::get_maximum_y_index() const{
	//1.�˴����Ե�ǰ��ʽ�����������״̬��
	assert(MtFormula::is_can_fitted());
	//2.���㵱ǰ��ʽ�����y���±ꡣ
	//2-1.������ǰ�������������
	double max_y=0.0;
	unsigned int index=0;
	//2-2.����y�Ĵ洢���飬�������y���±�ֵ��
	for(unsigned int i=0;i!=_size;++i){
		if(0==i){
			max_y=_y[i];
			index=i;
		}else if(_y[i]>max_y){
			max_y=_y[i];
			index=i;
		}
	}
	//3.���ؼ�����±�ֵ��
	return(index);
}

/**
 * name: get_minimum_y_index
 * brief: ��ȡ��ǰ��ʽ����Сy���±�ֵ��
 * param: --
 * return: ���ص�ǰ��ʽ����Сy���±�ֵ��
 */
unsigned int MtFormula::get_minimum_y_index() const{
	//1.�˴����Ե�ǰ��ʽ�����������״̬��
	assert(MtFormula::is_can_fitted());
	//2.���㵱ǰ��ʽ����Сy���±ꡣ
	//2-1.������ǰ�������������
	double min_y=0.0;
	unsigned int index=0;
	//2-2.����y�Ĵ洢���飬������Сy���±�ֵ��
	for(unsigned int i=0;i!=_size;++i){
		if(0==i){
			min_y=_y[i];
			index=i;
		}else if(_y[i]<min_y){
			min_y=_y[i];
			index=i;
		}
	}
	//3.���ؼ�����±�ֵ��
	return(index);
}

/**
 * name: get_maximum_x
 * brief: ��ȡ��ǰ��ʽ������xֵ��
 * param: --
 * return: ���ع�ʽ������xֵ��
 */
double MtFormula::get_maximum_x() const{
	return(get_x(get_maximum_x_index()));
}

/**
 * name: get_minimum_x
 * brief: ��ȡ��ǰ��ʽ����С��xֵ��
 * param: --
 * return: ���ص�ǰ��ʽ����С��xֵ��
 */
double MtFormula::get_minimum_x() const{
	return(get_x(get_minimum_x_index()));
}

/**
 * name: get_maximum_y
 * brief: ��ȡ��ǰ��ʽ������yֵ��
 * param: --
 * return: ���ص�ǰ��ʽ������yֵ��
 */
double MtFormula::get_maximum_y() const{
	return(get_y(get_maximum_y_index()));
}

/**
 * name: get_minimum_y
 * brief: ��ȡ��ǰ��ʽ����С��yֵ��
 * param: --
 * return: ���ص�ǰ��ʽ����С��yֵ��
 */
double MtFormula::get_minimum_y() const{
	return(get_y(get_minimum_y_index()));
}

/**
 * name: is_can_fitted
 * breif: �жϵ�ǰ��ʽ�Ƿ���Ա���ϡ�
 * param: --
 * return: �����ǰ��ʽ�ɱ���Ϸ���TRUE�����򷵻�FALSE��
 */
BOOL MtFormula::is_can_fitted() const{
	return (_size>=_minimum_size
		)&&(_minimum_size>0);
}