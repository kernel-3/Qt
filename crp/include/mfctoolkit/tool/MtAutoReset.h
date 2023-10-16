#pragma once

/**
 * name: MtAutoReset
 * brief: �Զ������࣬�����ĳ�ֱ���ʵ��
 *        �������ڽ������Զ����ù��ܡ�
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
 * breif: ���캯����
 * param: val - ʵ���Զ����õı��������á�
 *        init_value - �����ĳ�ʼֵ��
 *        reset_value - ����������ֵ��
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
 * breif: ����������
 * param: --
 * return: --
 */
template<typename _Tp>
MtAutoReset<_Tp>::~MtAutoReset(){
	_value=_reset_value;
}