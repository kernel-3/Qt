#include"stdafx.h"
#include"Theme.h"
#include"GlobalData.h"
#include"../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../include/mfctoolkit/tool/MtSingleton.h"
#include"../../../../include/mfctoolkit/graphic/MtImage.h"

/**
 * name: ~Theme
 * brief: 析构函数。
 * param: --
 * return: --
 */
Theme::~Theme(void){
}

/**
 * name: instance
 * breif: 获取系统中唯一的主题类实例对象。
 * param: --
 * return: 返回系统中唯一的主题类实例对象。
 */
Theme *Theme::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: get_theme_path
 * brief: 获取主题路径。
 * param: 
 * return: 返回主题路径。
 */
const CString &Theme::get_theme_path() const{
	return(_theme_path);
}

/**
 * name: load_images
 * breif: 加载主题所需要的图片。
 * param: --
 * return: --
 */
void Theme::load_images(){
	for(unsigned int image_no=1;image_no<=NUMBER_OF_IMAGES;++image_no){
		//1.根据当前图片编号，生成图片名称。
		CString image_name(_T(""));
		image_name.Format(_T("%d.png"),image_no);
		//2.根据图片名称创建指向图片的智能指针，并且判断创建是否成功。
		PtrToImage image(new MtImage(GlobalData::instance()->get_master_directory()+
			get_theme_path()+image_name));
		//3.如果当前图片创建成功，则将其放入图片容器中。
		if((static_cast<bool>(image))&&(image->is_valid())){
			_image_map[image_no]=image;
		}
	}
}

/**
 * name: unload_images
 * breif: 卸载主题所需要的图片。。
 * param: --
 * return: --
 */
void Theme::unload_images(){
	_image_map.clear();
}

/**
 * name: get_image
 * brief: 获取指定图片。
 * param: image_no - 图片编号。
 * return: 如果获取指定图片成功，返回指向图片的智能指针，
 *         否则返回空指针。
 */
Theme::PtrToImage Theme::get_image(const unsigned int image_no) const{
	//1.根据图片编号在指定的容器中查找相应的图片。
	ImageMap::const_iterator image=_image_map.find(image_no);
	//2.如果图片未能找到，则直接返回空指针。
	if(_image_map.end()==image){
		return(PtrToImage());
	}
	//3.如果图片成功找到，则直接返回指定的图片。
	else{
		return(image->second);
	}
}

/**
 * name: get_string
 * brief: 从系统资源中获取指定的字符串。
 * param: string_id - 字符串ID。
 * return: 如果字符串获取成功返回相应的字符串，否则返回空字符串。
 */
CString Theme::get_string(const unsigned int string_id) const{
	//1.声明当前操作所需变量。
	TCHAR string[_MAX_PATH];
	memset(string,0,_MAX_PATH*sizeof(TCHAR));
	//2.获取当前资源中存储的指定字符串，并且判断获取是否成功。
	const int execute_result=LoadString(0,string_id,string,_MAX_PATH);
	if(execute_result<=0){
		return(_T(""));
	}
	//3.返回当前指定的字符串。
	return(string);
}

/**
 * name: Theme
 * brief: 构造函数。
 * param: --
 * return: --
 */
Theme::Theme(void)
	:_theme_path(_T("theme\\blue_white\\"))
	,_image_map(){
}