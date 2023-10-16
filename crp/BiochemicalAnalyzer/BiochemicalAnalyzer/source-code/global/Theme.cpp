#include"stdafx.h"
#include"Theme.h"
#include"GlobalData.h"
#include"../../../../include/mfctoolkit/tool/MtLock.h"
#include"../../../../include/mfctoolkit/tool/MtSingleton.h"
#include"../../../../include/mfctoolkit/graphic/MtImage.h"

/**
 * name: ~Theme
 * brief: ����������
 * param: --
 * return: --
 */
Theme::~Theme(void){
}

/**
 * name: instance
 * breif: ��ȡϵͳ��Ψһ��������ʵ������
 * param: --
 * return: ����ϵͳ��Ψһ��������ʵ������
 */
Theme *Theme::instance(){
	return(Singleton_Instance::instance());
}

/**
 * name: get_theme_path
 * brief: ��ȡ����·����
 * param: 
 * return: ��������·����
 */
const CString &Theme::get_theme_path() const{
	return(_theme_path);
}

/**
 * name: load_images
 * breif: ������������Ҫ��ͼƬ��
 * param: --
 * return: --
 */
void Theme::load_images(){
	for(unsigned int image_no=1;image_no<=NUMBER_OF_IMAGES;++image_no){
		//1.���ݵ�ǰͼƬ��ţ�����ͼƬ���ơ�
		CString image_name(_T(""));
		image_name.Format(_T("%d.png"),image_no);
		//2.����ͼƬ���ƴ���ָ��ͼƬ������ָ�룬�����жϴ����Ƿ�ɹ���
		PtrToImage image(new MtImage(GlobalData::instance()->get_master_directory()+
			get_theme_path()+image_name));
		//3.�����ǰͼƬ�����ɹ����������ͼƬ�����С�
		if((static_cast<bool>(image))&&(image->is_valid())){
			_image_map[image_no]=image;
		}
	}
}

/**
 * name: unload_images
 * breif: ж����������Ҫ��ͼƬ����
 * param: --
 * return: --
 */
void Theme::unload_images(){
	_image_map.clear();
}

/**
 * name: get_image
 * brief: ��ȡָ��ͼƬ��
 * param: image_no - ͼƬ��š�
 * return: �����ȡָ��ͼƬ�ɹ�������ָ��ͼƬ������ָ�룬
 *         ���򷵻ؿ�ָ�롣
 */
Theme::PtrToImage Theme::get_image(const unsigned int image_no) const{
	//1.����ͼƬ�����ָ���������в�����Ӧ��ͼƬ��
	ImageMap::const_iterator image=_image_map.find(image_no);
	//2.���ͼƬδ���ҵ�����ֱ�ӷ��ؿ�ָ�롣
	if(_image_map.end()==image){
		return(PtrToImage());
	}
	//3.���ͼƬ�ɹ��ҵ�����ֱ�ӷ���ָ����ͼƬ��
	else{
		return(image->second);
	}
}

/**
 * name: get_string
 * brief: ��ϵͳ��Դ�л�ȡָ�����ַ�����
 * param: string_id - �ַ���ID��
 * return: ����ַ�����ȡ�ɹ�������Ӧ���ַ��������򷵻ؿ��ַ�����
 */
CString Theme::get_string(const unsigned int string_id) const{
	//1.������ǰ�������������
	TCHAR string[_MAX_PATH];
	memset(string,0,_MAX_PATH*sizeof(TCHAR));
	//2.��ȡ��ǰ��Դ�д洢��ָ���ַ����������жϻ�ȡ�Ƿ�ɹ���
	const int execute_result=LoadString(0,string_id,string,_MAX_PATH);
	if(execute_result<=0){
		return(_T(""));
	}
	//3.���ص�ǰָ�����ַ�����
	return(string);
}

/**
 * name: Theme
 * brief: ���캯����
 * param: --
 * return: --
 */
Theme::Theme(void)
	:_theme_path(_T("theme\\blue_white\\"))
	,_image_map(){
}