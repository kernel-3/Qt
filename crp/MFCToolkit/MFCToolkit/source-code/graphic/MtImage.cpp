#include"stdafx.h"
#include"MtImage.h"
#include"../tool/MtCharacterSet.h"
#include"MtBitmap.h"

/**
 * name: MtImage
 * brief: ���캯�������������ͼƬ���г�ʼ����ֵ��
 * param: image_path - ͼƬ������·����
 *        is_color_correction_forbidden - �Ƿ��ֹ��ͼƬ��ɫ����У����
 * return: --
 */
MtImage::MtImage(const CString &image_path,const BOOL is_color_correction_forbidden/*=FALSE*/)
	:_is_valid(FALSE)
	,_image(MtCharacterSet::to_unicode(image_path),is_color_correction_forbidden){
	if(Gdiplus::Ok==_image.GetLastStatus()){
		_is_valid=TRUE;
	}
}

/**
 * name: ~MtImage
 * brief: ����������
 * param: --
 * return: --
 */
MtImage::~MtImage(void){
}

/**
 * name: is_valid
 * brief: �жϵ�ǰͼƬ�Ƿ���Ч��
 * param: --
 * return: �����ǰͼƬ��Ч����TRUE�����򷵻�FALSE��
 */
BOOL MtImage::is_valid() const{
	return(_is_valid);
}

/**
 * name: get_width
 * brief: ��ȡ��ǰͼƬ��ȡ�
 * param: --
 * return: ���ص�ǰͼƬ��ȡ�
 */
int MtImage::get_width(){
	return(static_cast<int>(_image.GetWidth()));
}

/**
 * name: get_height
 * brief: ��ȡ��ǰͼƬ�߶ȡ�
 * param: --
 * return: ���ص�ǰͼƬ�߶ȡ�
 */
int MtImage::get_height(){
	return(static_cast<int>(_image.GetHeight()));
}

/**
 * name: create_graphics
 * brief: Ϊ��ǰͼƬ����һ����ͼ����
 * param: --
 * return: �����´����Ļ�ͼ����
 */
MtImage::PtrToGraphics MtImage::create_graphics(){
	return(PtrToGraphics(new Gdiplus::Graphics(&_image)));
}

/**
 * name: paste_to_bitmap
 * brief: ����ǰͼƬ�����ָ��λͼ�ϡ�
 * param: bitmap - ָ��Ŀ��λͼ��
 *        dest_x - Ŀ����������Ͻ�x���ꡣ
 *        dest_y - Ŀ����������Ͻ�y���ꡣ
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImage::paste_to_bitmap(MtBitmap *bitmap,const int dest_x,const int dest_y){
	if(0==bitmap){
		return(-1);
	}
	MtBitmap::PtrToGraphics graphics=bitmap->create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,dest_x,dest_y)){
		return(-4);
	}
	return(0);
}

/**
 * name: paste_to_bitmap
 * brief: ����ǰͼƬ�����ָ��λͼ�ϡ�
 * param: bitmap - ָ��Ŀ��λͼ��
 *        dest_x - Ŀ����������Ͻ�x���ꡣ
 *        dest_y - Ŀ����������Ͻ�y���ꡣ
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImage::paste_to_bitmap(MtBitmap *bitmap,const float dest_x,const float dest_y){
	if(0==bitmap){
		return(-1);
	}
	MtBitmap::PtrToGraphics graphics=bitmap->create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,dest_x,dest_y)){
		return(-4);
	}
	return(0);
}

/**
 * name: paste_to_bitmap
 * brief: ����ǰͼƬ�����ָ��λͼ�ϡ�
 * param: bitmap - ָ��Ŀ��λͼ��
 *        dest_x - Ŀ����������Ͻ�x���ꡣ
 *        dest_y - Ŀ����������Ͻ�y���ꡣ
 *        src_x - Դ����������Ͻ�x���ꡣ
 *        src_y - Դ����������Ͻ�y���ꡣ
 *	      src_width - Դ��������ȡ�
 *        src_height - Դ�������߶ȡ�
 *        src_unit - Դ������������õĶ�����λ��Ĭ��Ϊ���أ���
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImage::paste_to_bitmap(MtBitmap *bitmap,const int dest_x,const int dest_y,
	const int src_x,const int src_y,const int src_width,const int src_height,
	const Gdiplus::Unit src_unit/*=Gdiplus::UnitPixel*/){
	if(0==bitmap){
		return(-1);
	}
	MtBitmap::PtrToGraphics graphics=bitmap->create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,dest_x,dest_y,
		src_x,src_y,src_width,src_height,src_unit)){
		return(-4);
	}
	return(0);
}

/**
 * name: paste_to_bitmap
 * brief: ����ǰͼƬ�����ָ��λͼ�ϡ�
 * param: bitmap - ָ��Ŀ��λͼ��
 *        dest_x - Ŀ����������Ͻ�x���ꡣ
 *        dest_y - Ŀ����������Ͻ�y���ꡣ
 *        src_x - Դ����������Ͻ�x���ꡣ
 *        src_y - Դ����������Ͻ�y���ꡣ
 *	      src_width - Դ��������ȡ�
 *        src_height - Դ�������߶ȡ�
 *        src_unit - Դ������������õĶ�����λ��Ĭ��Ϊ���أ���
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImage::paste_to_bitmap(MtBitmap *bitmap,const float dest_x,const float dest_y,
	const float src_x,const float src_y,const float src_width,const float src_height,
	const Gdiplus::Unit src_unit/*=Gdiplus::UnitPixel*/){
	if(0==bitmap){
		return(-1);
	}
	MtBitmap::PtrToGraphics graphics=bitmap->create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,dest_x,dest_y,
		src_x,src_y,src_width,src_height,src_unit)){
		return(-4);
	}
	return(0);
}

/**
 * name: paste_to_bitmap
 * brief: ����ǰͼƬ�����ָ��λͼ�ϡ�
 * param: bitmap - ָ��Ŀ��λͼ��
 *        dest_x - Ŀ����������Ͻ�x���ꡣ
 *        dest_y - Ŀ����������Ͻ�y���ꡣ
 *        dest_width - Ŀ�������ȡ�
 *        dest_height - Ŀ������߶ȡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImage::paste_to_bitmap(MtBitmap *bitmap,const int dest_x,
	const int dest_y,const int dest_width,const int dest_height){
	if(0==bitmap){
		return(-1);
	}
	MtBitmap::PtrToGraphics graphics=bitmap->create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	if(Gdiplus::Ok!=graphics->DrawImage(
		&_image,dest_x,dest_y,dest_width,dest_height)){
		return(-4);
	}
	return(0);
}

/**
 * name: paste_to_bitmap
 * brief: ����ǰͼƬ�����ָ��λͼ�ϡ�
 * param: bitmap - ָ��Ŀ��λͼ��
 *        dest_x - Ŀ����������Ͻ�x���ꡣ
 *        dest_y - Ŀ����������Ͻ�y���ꡣ
 *        dest_width - Ŀ�������ȡ�
 *        dest_height - Ŀ������߶ȡ�
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImage::paste_to_bitmap(MtBitmap *bitmap,const float dest_x,
	const float dest_y,const float dest_width,const float dest_height){
	if(0==bitmap){
		return(-1);
	}
	MtBitmap::PtrToGraphics graphics=bitmap->create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	if(Gdiplus::Ok!=graphics->DrawImage(
		&_image,dest_x,dest_y,dest_width,dest_height)){
		return(-4);
	}
	return(0);
}

/**
 * name: paste_to_bitmap
 * brief: ����ǰͼƬ�����ָ��λͼ�ϡ�
 * param: bitmap - ָ��Ŀ��λͼ��
 *        dest_x - Ŀ����������Ͻ�x���ꡣ
 *        dest_y - Ŀ����������Ͻ�y���ꡣ
 *	      dest_width - Ŀ������Ŀ�ȡ�
 *		  dest_height - Ŀ������ĸ߶ȡ�
 *        src_x - Դ����������Ͻ�x���ꡣ
 *        src_y - Դ����������Ͻ�y���ꡣ
 *	      src_width - Դ��������ȡ�
 *        src_height - Դ�������߶ȡ�
 *        src_unit - Դ������������õĶ�����λ��Ĭ��Ϊ���أ���
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImage::paste_to_bitmap(MtBitmap *bitmap,const int dest_x,const int dest_y,
	const int dest_width,const int dest_height,const int src_x,const int src_y,
	const int src_width,const int src_height,const Gdiplus::Unit src_unit/*=Gdiplus::UnitPixel*/){
	if(0==bitmap){
		return(-1);
	}
	MtBitmap::PtrToGraphics graphics=bitmap->create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	Gdiplus::ImageAttributes image_attributes;
	if(Gdiplus::Ok!=image_attributes.SetWrapMode(Gdiplus::WrapModeTile)){
		return(-4);
	}
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::Rect(dest_x,dest_y,
		dest_width,dest_height),src_x,src_y,src_width,src_height,src_unit,
		&image_attributes)){
		return(-5);
	}
	return(0);
}

/**
 * name: paste_to_bitmap
 * brief: ����ǰͼƬ�����ָ��λͼ�ϡ�
 * param: bitmap - ָ��Ŀ��λͼ��
 *        dest_x - Ŀ����������Ͻ�x���ꡣ
 *        dest_y - Ŀ����������Ͻ�y���ꡣ
 *	      dest_width - Ŀ������Ŀ�ȡ�
 *		  dest_height - Ŀ������ĸ߶ȡ�
 *        src_x - Դ����������Ͻ�x���ꡣ
 *        src_y - Դ����������Ͻ�y���ꡣ
 *	      src_width - Դ��������ȡ�
 *        src_height - Դ�������߶ȡ�
 *        src_unit - Դ������������õĶ�����λ��Ĭ��Ϊ���أ���
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImage::paste_to_bitmap(MtBitmap *bitmap,const float dest_x,const float dest_y,
	const float dest_width,const float dest_height,const float src_x,const float src_y,
	const float src_width,const float src_height,const Gdiplus::Unit src_unit/*=Gdiplus::UnitPixel*/){
	if(0==bitmap){
		return(-1);
	}
	MtBitmap::PtrToGraphics graphics=bitmap->create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	Gdiplus::ImageAttributes image_attributes;
	if(Gdiplus::Ok!=image_attributes.SetWrapMode(Gdiplus::WrapModeTile)){
		return(-4);
	}
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::RectF(dest_x,dest_y,
		dest_width,dest_height),src_x,src_y,src_width,src_height,src_unit,
		&image_attributes)){
		return(-5);
	}
	return(0);
}

/**
 * name: paste_to_bitmap_ex
 * brief: ����ǰͼƬ�����ָ��λͼ�ϡ�
 * param: bitmap - ָ��Ŀ��λͼ��
 *        dest_x - Ŀ����������Ͻ�x���ꡣ
 *        dest_y - Ŀ����������Ͻ�y���ꡣ
 *        dest_width - Ŀ�������ȡ�
 *        dest_height - Ŀ������߶ȡ�
 *        src_l_stretch - ԴͼƬ�������ϵ����
 *        src_t_stretch - ԴͼƬ��������ϵ����
 *        src_r_stretch - ԴͼƬ�Ҳ�����ϵ����
 *        src_b_stretch - ԴͼƬ�ײ�����ϵ����
 *        src_unit - ԴͼƬ������λ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImage::paste_to_bitmap_ex(MtBitmap *bitmap,const int dest_x,const int dest_y,
	const int dest_width,const int dest_height,const int src_l_stretch,
	const int src_t_stretch,const int src_r_stretch,const int src_b_stretch,
	const Gdiplus::Unit src_unit/*=Gdiplus::UnitPixel*/){
	if(0==bitmap){
		return(-1);
	}
	MtBitmap::PtrToGraphics graphics=bitmap->create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	Gdiplus::ImageAttributes image_attributes;
	if(Gdiplus::Ok!=image_attributes.SetWrapMode(Gdiplus::WrapModeTile)){
		return(-4);
	}
	//top-left area.
	int src_left=0;
	int src_top=0;
	int src_right=src_left+src_l_stretch;
	int src_bottom=src_top+src_t_stretch;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::Rect(dest_x,dest_y,
		src_right-src_left,src_bottom-src_top),src_left,src_top,src_right-src_left,
		src_bottom-src_top,src_unit,&image_attributes)){
		return(-5);
	}
	//top-middle area.
	src_left=src_right;
	src_right=get_width()-src_r_stretch;
	int dest_left=dest_x+src_l_stretch;
	int dest_top=dest_y;
	int dest_right=dest_x+dest_width-src_r_stretch;
	int dest_bottom=dest_top+src_t_stretch;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::Rect(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-6);
	}
	//top-right area. 
	src_left=src_right;
	src_right=get_width();
	dest_left=dest_right;
	dest_right=dest_x+dest_width;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::Rect(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-7);
	}
	//middle-left area.
	src_left=0;
	src_top=src_t_stretch;
	src_right=src_left+src_l_stretch;
	src_bottom=get_height()-src_b_stretch;
	dest_left=dest_x;
	dest_top=dest_y+src_t_stretch;
	dest_right=dest_x+src_l_stretch;
	dest_bottom=dest_y+dest_height-src_b_stretch;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::Rect(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-8);
	}
	//middle-middle area.
	src_left=src_right;
	src_right=get_width()-src_r_stretch;
	dest_left=dest_right;
	dest_right=dest_x+dest_width-src_r_stretch;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::Rect(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-9);
	}
	//middle-right area.
	src_left=src_right;
	src_right=get_width();
	dest_left=dest_right;
	dest_right=dest_x+dest_width;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::Rect(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-10);
	}
	//bottom-left area.
	src_left=0;
	src_top=get_height()-src_b_stretch;
	src_right=src_left+src_l_stretch;
	src_bottom=get_height();
	dest_left=dest_x;
	dest_top=dest_y+dest_height-src_b_stretch;
	dest_right=dest_left+src_l_stretch;
	dest_bottom=dest_y+dest_height;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::Rect(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-11);
	}
	//bottom-middle area.
	src_left=src_right;
	src_right=get_width()-src_r_stretch;
	dest_left=dest_right;
	dest_right=dest_x+dest_width-src_r_stretch;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::Rect(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-12);
	}
	//bottom-right area.
	src_left=src_right;
	src_right=get_width();
	dest_left=dest_right;
	dest_right=dest_x+dest_width;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::Rect(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-13);
	}
	//return.
	return(0);
}

/**
 * name: paste_to_bitmap_ex
 * brief: ����ǰͼƬ�����ָ��λͼ�ϡ�
 * param: bitmap - ָ��Ŀ��λͼ��
 *        dest_x - Ŀ����������Ͻ�x���ꡣ
 *        dest_y - Ŀ����������Ͻ�y���ꡣ
 *        dest_width - Ŀ�������ȡ�
 *        dest_height - Ŀ������߶ȡ�
 *        src_l_stretch - ԴͼƬ�������ϵ����
 *        src_t_stretch - ԴͼƬ��������ϵ����
 *        src_r_stretch - ԴͼƬ�Ҳ�����ϵ����
 *        src_b_stretch - ԴͼƬ�ײ�����ϵ����
 *        src_unit - ԴͼƬ������λ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImage::paste_to_bitmap_ex(MtBitmap *bitmap,const float dest_x,const float dest_y,
	const float dest_width,const float dest_height,const float src_l_stretch,
	const float src_t_stretch,const float src_r_stretch,const float src_b_stretch,
	const Gdiplus::Unit src_unit/*=Gdiplus::UnitPixel*/){
	if(0==bitmap){
		return(-1);
	}
	MtBitmap::PtrToGraphics graphics=bitmap->create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	Gdiplus::ImageAttributes image_attributes;
	if(Gdiplus::Ok!=image_attributes.SetWrapMode(Gdiplus::WrapModeTile)){
		return(-4);
	}
	//top-left area.
	float src_left=0;
	float src_top=0;
	float src_right=src_left+src_l_stretch;
	float src_bottom=src_top+src_t_stretch;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::RectF(dest_x,dest_y,
		src_right-src_left,src_bottom-src_top),src_left,src_top,src_right-src_left,
		src_bottom-src_top,src_unit,&image_attributes)){
		return(-5);
	}
	//top-middle area.
	src_left=src_right;
	src_right=get_width()-src_r_stretch;
	float dest_left=dest_x+src_l_stretch;
	float dest_top=dest_y;
	float dest_right=dest_x+dest_width-src_r_stretch;
	float dest_bottom=dest_top+src_t_stretch;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::RectF(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-6);
	}
	//top-right area. 
	src_left=src_right;
	src_right=static_cast<float>(get_width());
	dest_left=dest_right;
	dest_right=dest_x+dest_width;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::RectF(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-7);
	}
	//middle-left area.
	src_left=0;
	src_top=src_t_stretch;
	src_right=src_left+src_l_stretch;
	src_bottom=get_height()-src_b_stretch;
	dest_left=dest_x;
	dest_top=dest_y+src_t_stretch;
	dest_right=dest_x+src_l_stretch;
	dest_bottom=dest_y+dest_height-src_b_stretch;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::RectF(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-8);
	}
	//middle-middle area.
	src_left=src_right;
	src_right=get_width()-src_r_stretch;
	dest_left=dest_right;
	dest_right=dest_x+dest_width-src_r_stretch;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::RectF(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-9);
	}
	//middle-right area.
	src_left=src_right;
	src_right=static_cast<float>(get_width());
	dest_left=dest_right;
	dest_right=dest_x+dest_width;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::RectF(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-10);
	}
	//bottom-left area.
	src_left=0;
	src_top=get_height()-src_b_stretch;
	src_right=src_left+src_l_stretch;
	src_bottom=static_cast<float>(get_height());
	dest_left=dest_x;
	dest_top=dest_y+dest_height-src_b_stretch;
	dest_right=dest_left+src_l_stretch;
	dest_bottom=dest_y+dest_height;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::RectF(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-11);
	}
	//bottom-middle area.
	src_left=src_right;
	src_right=get_width()-src_r_stretch;
	dest_left=dest_right;
	dest_right=dest_x+dest_width-src_r_stretch;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::RectF(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-12);
	}
	//bottom-right area.
	src_left=src_right;
	src_right=static_cast<float>(get_width());
	dest_left=dest_right;
	dest_right=dest_x+dest_width;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::RectF(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-13);
	}
	//return.
	return(0);
}

/**
 * name: paste_to_bitmap_ex
 * brief: ����ǰͼƬ�����ָ��λͼ�ϡ�
 * param: bitmap - ָ��Ŀ��λͼ��
 *        dest_x - Ŀ����������Ͻ�x���ꡣ
 *        dest_y - Ŀ����������Ͻ�y���ꡣ
 *        dest_width - Ŀ�������ȡ�
 *        dest_height - Ŀ������߶ȡ�
 *        src_x - Դ����������Ͻ�x���ꡣ
 *        src_y - Դ����������Ͻ�y���ꡣ
 *	      src_width - Դ��������ȡ�
 *        src_height - Դ�������߶ȡ�
 *        src_l_stretch - ԴͼƬ�������ϵ����
 *        src_t_stretch - ԴͼƬ��������ϵ����
 *        src_r_stretch - ԴͼƬ�Ҳ�����ϵ����
 *        src_b_stretch - ԴͼƬ�ײ�����ϵ����
 *        src_unit - ԴͼƬ������λ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImage::paste_to_bitmap_ex(MtBitmap *bitmap,const int dest_x,const int dest_y,
	const int dest_width,const int dest_height,const int src_x,const int src_y,
	const int src_width,const int src_height,const int src_l_stretch,const int src_t_stretch,
	const int src_r_stretch,const int src_b_stretch,const Gdiplus::Unit src_unit/*=Gdiplus::UnitPixel*/){
	if(0==bitmap){
		return(-1);
	}
	MtBitmap::PtrToGraphics graphics=bitmap->create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	Gdiplus::ImageAttributes image_attributes;
	if(Gdiplus::Ok!=image_attributes.SetWrapMode(Gdiplus::WrapModeTile)){
		return(-4);
	}
	//top-left area.
	int src_left=src_x;
	int src_top=src_y;
	int src_right=src_left+src_l_stretch;
	int src_bottom=src_top+src_t_stretch;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::Rect(dest_x,dest_y,
		src_right-src_left,src_bottom-src_top),src_left,src_top,src_right-src_left,
		src_bottom-src_top,src_unit,&image_attributes)){
		return(-5);
	}
	//top-middle area.
	src_left=src_right;
	src_right=src_x+src_width-src_r_stretch;
	int dest_left=dest_x+src_l_stretch;
	int dest_top=dest_y;
	int dest_right=dest_x+dest_width-src_r_stretch;
	int dest_bottom=dest_top+src_t_stretch;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::Rect(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-6);
	}
	//top-right area.
	src_left=src_right;
	src_right=src_x+src_width;
	dest_left=dest_right;
	dest_right=dest_x+dest_width;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::Rect(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-7);
	}
	//middle-left area.
	src_left=src_x;
	src_top=src_y+src_t_stretch;
	src_right=src_left+src_l_stretch;
	src_bottom=src_y+src_height-src_b_stretch;
	dest_left=dest_x;
	dest_top=dest_y+src_t_stretch;
	dest_right=dest_x+src_l_stretch;
	dest_bottom=dest_y+dest_height-src_b_stretch;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::Rect(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-8);
	}
	//middle-middle area.
	src_left=src_right;
	src_right=src_x+src_width-src_r_stretch;
	dest_left=dest_right;
	dest_right=dest_x+dest_width-src_r_stretch;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::Rect(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-9);
	}
	//middle-right area.
	src_left=src_right;
	src_right=src_x+src_width;
	dest_left=dest_right;
	dest_right=dest_x+dest_width;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::Rect(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-10);
	}
	//bottom-left area.
	src_left=src_x;
	src_top=src_y+src_height-src_b_stretch;
	src_right=src_left+src_l_stretch;
	src_bottom=src_y+src_height;
	dest_left=dest_x;
	dest_top=dest_y+dest_height-src_b_stretch;
	dest_right=dest_left+src_l_stretch;
	dest_bottom=dest_y+dest_height;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::Rect(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-11);
	}
	//bottom-middle area.
	src_left=src_right;
	src_right=src_x+src_width-src_r_stretch;
	dest_left=dest_right;
	dest_right=dest_x+dest_width-src_r_stretch;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::Rect(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-12);
	}
	//bottom-right area.
	src_left=src_right;
	src_right=src_x+src_width;
	dest_left=dest_right;
	dest_right=dest_x+dest_width;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::Rect(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-13);
	}
	//return.
	return(0);
}

/**
 * name: paste_to_bitmap_ex
 * brief: ����ǰͼƬ�����ָ��λͼ�ϡ�
 * param: bitmap - ָ��Ŀ��λͼ��
 *        dest_x - Ŀ����������Ͻ�x���ꡣ
 *        dest_y - Ŀ����������Ͻ�y���ꡣ
 *        dest_width - Ŀ�������ȡ�
 *        dest_height - Ŀ������߶ȡ�
 *        src_x - Դ����������Ͻ�x���ꡣ
 *        src_y - Դ����������Ͻ�y���ꡣ
 *	      src_width - Դ��������ȡ�
 *        src_height - Դ�������߶ȡ�
 *        src_l_stretch - ԴͼƬ�������ϵ����
 *        src_t_stretch - ԴͼƬ��������ϵ����
 *        src_r_stretch - ԴͼƬ�Ҳ�����ϵ����
 *        src_b_stretch - ԴͼƬ�ײ�����ϵ����
 *        src_unit - ԴͼƬ������λ��
 * return: �������ִ�гɹ�����ֵ���ڵ����㣬���򷵻�ֵС���㡣
 */
int MtImage::paste_to_bitmap_ex(MtBitmap *bitmap,const float dest_x,const float dest_y,
	const float dest_width,const float dest_height,const float src_x,const float src_y,
	const float src_width,const float src_height,const float src_l_stretch,const float src_t_stretch,
	const float src_r_stretch,const float src_b_stretch,const Gdiplus::Unit src_unit/*=Gdiplus::UnitPixel*/){
	if(0==bitmap){
		return(-1);
	}
	MtBitmap::PtrToGraphics graphics=bitmap->create_graphics();
	if(!static_cast<bool>(graphics)){
		return(-2);
	}
	if(Gdiplus::Ok!=graphics->GetLastStatus()){
		return(-3);
	}
	Gdiplus::ImageAttributes image_attributes;
	if(Gdiplus::Ok!=image_attributes.SetWrapMode(Gdiplus::WrapModeTile)){
		return(-4);
	}
	//top-left area.
	float src_left=src_x;
	float src_top=src_y;
	float src_right=src_left+src_l_stretch;
	float src_bottom=src_top+src_t_stretch;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::RectF(dest_x,
		dest_y,src_right-src_left,src_bottom-src_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-5);
	}
	//top-middle area.
	src_left=src_right;
	src_right=src_x+src_width-src_r_stretch;
	float dest_left=dest_x+src_l_stretch;
	float dest_top=dest_y;
	float dest_right=dest_x+dest_width-src_r_stretch;
	float dest_bottom=dest_top+src_t_stretch;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::RectF(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-6);
	}
	//top-right area.
	src_left=src_right;
	src_right=src_x+src_width;
	dest_left=dest_right;
	dest_right=dest_x+dest_width;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::RectF(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-7);
	}
	//middle-left area.
	src_left=src_x;
	src_top=src_y+src_t_stretch;
	src_right=src_left+src_l_stretch;
	src_bottom=src_y+src_height-src_b_stretch;
	dest_left=dest_x;
	dest_top=dest_y+src_t_stretch;
	dest_right=dest_x+src_l_stretch;
	dest_bottom=dest_y+dest_height-src_b_stretch;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::RectF(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-8);
	}
	//middle-middle area.
	src_left=src_right;
	src_right=src_x+src_width-src_r_stretch;
	dest_left=dest_right;
	dest_right=dest_x+dest_width-src_r_stretch;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::RectF(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-9);
	}
	//middle-right area.
	src_left=src_right;
	src_right=src_x+src_width;
	dest_left=dest_right;
	dest_right=dest_x+dest_width;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::RectF(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-10);
	}
	//bottom-left area.
	src_left=src_x;
	src_top=src_y+src_height-src_b_stretch;
	src_right=src_left+src_l_stretch;
	src_bottom=src_y+src_height;
	dest_left=dest_x;
	dest_top=dest_y+dest_height-src_b_stretch;
	dest_right=dest_left+src_l_stretch;
	dest_bottom=dest_y+dest_height;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::RectF(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-11);
	}
	//bottom-middle area.
	src_left=src_right;
	src_right=src_x+src_width-src_r_stretch;
	dest_left=dest_right;
	dest_right=dest_x+dest_width-src_r_stretch;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::RectF(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-12);
	}
	//bottom-right area.
	src_left=src_right;
	src_right=src_x+src_width;
	dest_left=dest_right;
	dest_right=dest_x+dest_width;
	if(Gdiplus::Ok!=graphics->DrawImage(&_image,Gdiplus::RectF(dest_left,
		dest_top,dest_right-dest_left,dest_bottom-dest_top),src_left,src_top,
		src_right-src_left,src_bottom-src_top,src_unit,&image_attributes)){
		return(-13);
	}
	//return.
	return(0);
}