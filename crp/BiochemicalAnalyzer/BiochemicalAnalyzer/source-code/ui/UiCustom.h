#pragma once

/**
 * name: WM_UPDATE_DATA_FOR_CONTROLS
 * breif: ���¿ؼ����ݡ�
 * param: WPARAM - �����塣
 *        LPARAM - �����塣
 * author: yameng_he
 * date: 2015-06-17
 */
#define WM_UPDATE_DATA_FOR_CONTROLS WM_USER+101

/**
 * name: WM_ITEM_OR_PROFILE_BUTTON_CLICKED
 * breif: ��Ŀ����ϰ�ť�����Ϣ��
 * param: WPARAM - 1 ��Ŀ�� 2 ��ϼ���
 *        LPARAM - ����İ�ť��š�
 * author: yameng_he
 * date: 2015-06-16
 */
#define WM_ITEM_OR_PROFILE_BUTTON_CLICKED WM_USER+1001

/**
 * name: WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID
 * brief: ͨ����Ŀ��ʶ���¿ؼ����ݡ�
 * param: WPARAM - ģ���ʶ����8λ�����������ͱ�ʶ����8λ������Ŀ��ʶ����16λ����
 *        LPARAM - �����塣
 * author: yameng_he
 * date: 2015-06-24
 */
#define WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID WM_USER+1002

/**
 * name: WM_COMMIT_DATA_OF_CONTROLS
 * brief: �ύ�ؼ��е����ݵ����ݿ��С�
 * param: WPARAM - �����塣
 *        LPARAM - �����塣
 * author: yameng_he
 * date: 2015-07-01
 */
#define WM_COMMIT_DATA_OF_CONTROLS WM_USER+1003

/**
 * name: get_combo_box_index_by_item_data
 * brief: �������������Ŀ���ݣ���ȡ��Ӧ��������
 * param: item_data - ָ������Ŀ���ݡ�
 *        combo_box - ָ�������������á�
 * return: ����ɹ��ҵ��������������򷵻��ҵ������������򷵻�ֵС���㡣
 */
template<typename _Tp>
int get_combo_box_index_by_item_data(const _Tp item_data,const CComboBox &combo_box){
	//1.���������򣬱ȶ�ÿһ������ݣ������жϱȶ��Ƿ�ɹ���
	for(int index=0;index!=combo_box.GetCount();++index){
		if(item_data==static_cast<_Tp>(combo_box.GetItemData(index))){
			return(index);
		}
	}
	//2.�������е���ʧ�ܷ��ء�
	return(-1);
}