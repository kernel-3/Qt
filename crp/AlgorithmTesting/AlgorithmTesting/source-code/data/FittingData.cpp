#include"stdafx.h"
#include"FittingData.h"
#include<math.h>

/**
 * name: FittingData
 * breif: ���캯����
 * param: --
 * return: --
 */
FittingData::FittingData(void)
	:_x(0.0)
	,_y(0.0){
}

/**
 * name: FittingData
 * breif: ���캯����
 * param: x - ָ����xֵ��
 *        y - ָ����yֵ��
 * return: --
 */
FittingData::FittingData(const double x,const double y)
	:_x(x)
	,_y(y){
}

/**
 * name: ~FittingData
 * breif: ����������
 * param: --
 * return: --
 */
FittingData::~FittingData(void){
}

/**
 * name: set_x
 * breif: ����x��
 * param: x - ָ��x��ֵ��
 * return: --
 */
void FittingData::set_x(const double x){
	_x=x;
}

/**
 * name: get_x
 * breif: ��ȡx��
 * param: --
 * return: ����x��
 */
double FittingData::get_x() const{
	return(_x);
}

/**
 * name: set_y
 * breif: ����y��
 * param: y - ָ��y��ֵ��
 * return: --
 */
void FittingData::set_y(const double y){
	_y=y;
}

/**
 * name: get_y
 * breif: ��ȡy��
 * parma: --
 * return: ����y��
 */
double FittingData::get_y() const{
	return(_y);
}