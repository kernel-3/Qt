#pragma once

/**
 * name: WM_UPDATE_DATA_FOR_CONTROLS
 * breif: 更新控件数据。
 * param: WPARAM - 无意义。
 *        LPARAM - 无意义。
 * author: yameng_he
 * date: 2015-06-17
 */
#define WM_UPDATE_DATA_FOR_CONTROLS WM_USER+101

/**
 * name: WM_ITEM_OR_PROFILE_BUTTON_CLICKED
 * breif: 项目或组合按钮点击消息。
 * param: WPARAM - 1 项目键 2 组合键。
 *        LPARAM - 点击的按钮序号。
 * author: yameng_he
 * date: 2015-06-16
 */
#define WM_ITEM_OR_PROFILE_BUTTON_CLICKED WM_USER+1001

/**
 * name: WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID
 * brief: 通过项目标识更新控件数据。
 * param: WPARAM - 模块标识（高8位）、样本类型标识（中8位）、项目标识（低16位）。
 *        LPARAM - 无意义。
 * author: yameng_he
 * date: 2015-06-24
 */
#define WM_UPDATE_DATA_FOR_CONTROLS_BY_MODULE_ID_AND_SPECIMEN_TYPE_ID_AND_ITEM_ID WM_USER+1002

/**
 * name: WM_COMMIT_DATA_OF_CONTROLS
 * brief: 提交控件中的数据到数据库中。
 * param: WPARAM - 无意义。
 *        LPARAM - 无意义。
 * author: yameng_he
 * date: 2015-07-01
 */
#define WM_COMMIT_DATA_OF_CONTROLS WM_USER+1003

/**
 * name: get_combo_box_index_by_item_data
 * brief: 根据下拉框的项目数据，获取对应的索引。
 * param: item_data - 指定的项目数据。
 *        combo_box - 指定的下拉框引用。
 * return: 如果成功找到下拉框索引，则返回找到的索引，否则返回值小于零。
 */
template<typename _Tp>
int get_combo_box_index_by_item_data(const _Tp item_data,const CComboBox &combo_box){
	//1.遍历下拉框，比对每一项的数据，并且判断比对是否成功。
	for(int index=0;index!=combo_box.GetCount();++index){
		if(item_data==static_cast<_Tp>(combo_box.GetItemData(index))){
			return(index);
		}
	}
	//2.程序运行到此失败返回。
	return(-1);
}