#pragma once

/**
 * name: MtAutoReset
 * brief: 自动重置类，负责对某种变量实现
 *        生命周期结束后自动重置功能。
 * author: yameng_he
 * date: 2015-06-26
 */
template<typename _Tp>
class MtAutoReset{
//construction & destruction
public:
	MtAutoReset(_Tp &value,const _Tp init_value,
		const _Tp reset_value);
	~MtAutoReset();
//variables
private:
	_Tp &_value;
	const _Tp _reset_value;
};

/**
 * name: MtAutoReset
 * breif: 构造函数。
 * param: val - 实现自动重置的变量的引用。
 *        init_value - 变量的初始值。
 *        reset_value - 变量的重置值。
 * return: --
 */
template<typename _Tp>
MtAutoReset<_Tp>::MtAutoReset(_Tp &value,
	const _Tp init_value,const _Tp reset_value)
	:_value(value)
	,_reset_value(reset_value){
	_value=init_value;
}

/**
 * name: ~MtAutoReset
 * breif: 析构函数。
 * param: --
 * return: --
 */
template<typename _Tp>
MtAutoReset<_Tp>::~MtAutoReset(){
	_value=_reset_value;
}