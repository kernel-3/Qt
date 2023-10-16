#include"stdafx.h"
#include"MtRegionDivision.h"
#include<assert.h>

/**
 * name: MtRegionDivision
 * brief: ���캯����
 * param: region_width - �����ȡ�
 *        region_height - ����߶ȡ�
 *        region_rows - ����������
 *        region_cols - ����������
 * return: --
 */
MtRegionDivision::MtRegionDivision(const int region_width,const int region_height,
	const int region_rows,const int region_cols)
	:_region_width(region_width)
	,_region_height(region_height)
	,_region_rows(region_rows)
	,_region_cols(region_cols){
}

/**
 * name: ~MtRegionDivision
 * brief: ����������
 * param: --
 * return: --
 */
MtRegionDivision::~MtRegionDivision(void){
}

/**
 * name: is_valid
 * brief: �жϵ�ǰ�ü����Ƿ�Ϸ���
 * param: --
 * return: ����ü����Ϸ�����TRUE�����򷵻�FALSE��
 */
BOOL MtRegionDivision::is_valid() const{
	return(_region_width>0&&_region_height>0&&_region_rows>0&&_region_cols>0);
}

/**
 * name: get_child_region_rect
 * brief: ��ȡ������ߴ硣
 * param: index - ����Դ������
 * return: �����ȡ����Դ�ߴ�ʧ�ܣ��򷵻ؿյ�CRect���󣨵���
 *         CRect::IsRectEmpty�жϣ������򷵻�����Դ�ĳߴ硣
 * remark: ���ô˺���ǰ������ȷ��MtRegionDivisionʵ�������
 *		   ����ͨ�����ó�Ա����is_validȷ�ϣ���
 */
CRect MtRegionDivision::get_child_region_rect(const int index) const{
	//1.�����ǰ������Ų��Ϸ���ֱ�ӷ��ؿճߴ硣
	if((index<0)||(index>=(_region_rows*_region_cols))){
		return(CRect(0,0,0,0));
	}
	//2.���㵱ǰ������Ŀ�ȡ��߶ȡ�
	const int child_region_width=_region_width/_region_cols;
	const int child_region_height=_region_height/_region_rows;
	//3.���㵱ǰ��������кš��кš�
	int row_no=(index+1)/_region_cols;
	int col_no=(index+1)%_region_cols;
	if(0==col_no){
		row_no-=1;
		col_no=_region_cols-1;
	}else{
		col_no-=1;
	}
	//4.����������ĳߴ硣
	const int child_region_left=col_no*child_region_width;
	const int child_region_top=row_no*child_region_height;
	const int child_region_right=child_region_left+child_region_width;
	const int child_region_bottom=child_region_top+child_region_height;
	//5.����������ĳߴ硣
	return(CRect(child_region_left,child_region_top,child_region_right,child_region_bottom));
}

/**
 * name: get_child_region_amount
 * brief: ���㵱ǰ������ĺϼ�������
 * param: --
 * return: ���ص�ǰ������ĺϼ�������
 */
int MtRegionDivision::get_child_region_amount() const{
	int child_region_amount=_region_rows*_region_cols;
	if(child_region_amount<0){
		child_region_amount=0;
	}
	return(child_region_amount);
}