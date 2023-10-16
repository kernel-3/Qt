#include"stdafx.h"
#include"MtImage.h"
#include"../tool/MtCharacterSet.h"
#include"MtBitmap.h"

/**
 * name: MtImage
 * brief: 构造函数，负责对类中图片进行初始化赋值。
 * param: image_path - 图片的完整路径。
 *        is_color_correction_forbidden - 是否禁止对图片颜色进行校正。
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
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtImage::~MtImage(void){
}

/**
 * name: is_valid
 * brief: 判断当前图片是否有效。
 * param: --
 * return: 如果当前图片有效返回TRUE，否则返回FALSE。
 */
BOOL MtImage::is_valid() const{
	return(_is_valid);
}

/**
 * name: get_width
 * brief: 获取当前图片宽度。
 * param: --
 * return: 返回当前图片宽度。
 */
int MtImage::get_width(){
	return(static_cast<int>(_image.GetWidth()));
}

/**
 * name: get_height
 * brief: 获取当前图片高度。
 * param: --
 * return: 返回当前图片高度。
 */
int MtImage::get_height(){
	return(static_cast<int>(_image.GetHeight()));
}

/**
 * name: create_graphics
 * brief: 为当前图片创建一个绘图器。
 * param: --
 * return: 返回新创建的绘图器。
 */
MtImage::PtrToGraphics MtImage::create_graphics(){
	return(PtrToGraphics(new Gdiplus::Graphics(&_image)));
}

/**
 * name: paste_to_bitmap
 * brief: 将当前图片黏贴到指定位图上。
 * param: bitmap - 指向目标位图。
 *        dest_x - 目标区域的左上角x坐标。
 *        dest_y - 目标区域的左上角y坐标。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
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
 * brief: 将当前图片黏贴到指定位图上。
 * param: bitmap - 指向目标位图。
 *        dest_x - 目标区域的左上角x坐标。
 *        dest_y - 目标区域的左上角y坐标。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
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
 * brief: 将当前图片黏贴到指定位图上。
 * param: bitmap - 指向目标位图。
 *        dest_x - 目标区域的左上角x坐标。
 *        dest_y - 目标区域的左上角y坐标。
 *        src_x - 源黏贴区域左上角x坐标。
 *        src_y - 源黏贴区域左上角y坐标。
 *	      src_width - 源黏贴区域宽度。
 *        src_height - 源黏贴区域高度。
 *        src_unit - 源黏贴区域所采用的度量单位（默认为像素）。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
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
 * brief: 将当前图片黏贴到指定位图上。
 * param: bitmap - 指向目标位图。
 *        dest_x - 目标区域的左上角x坐标。
 *        dest_y - 目标区域的左上角y坐标。
 *        src_x - 源黏贴区域左上角x坐标。
 *        src_y - 源黏贴区域左上角y坐标。
 *	      src_width - 源黏贴区域宽度。
 *        src_height - 源黏贴区域高度。
 *        src_unit - 源黏贴区域所采用的度量单位（默认为像素）。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
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
 * brief: 将当前图片黏贴到指定位图上。
 * param: bitmap - 指向目标位图。
 *        dest_x - 目标区域的左上角x坐标。
 *        dest_y - 目标区域的左上角y坐标。
 *        dest_width - 目标区域宽度。
 *        dest_height - 目标区域高度。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
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
 * brief: 将当前图片黏贴到指定位图上。
 * param: bitmap - 指向目标位图。
 *        dest_x - 目标区域的左上角x坐标。
 *        dest_y - 目标区域的左上角y坐标。
 *        dest_width - 目标区域宽度。
 *        dest_height - 目标区域高度。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
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
 * brief: 将当前图片黏贴到指定位图上。
 * param: bitmap - 指向目标位图。
 *        dest_x - 目标区域的左上角x坐标。
 *        dest_y - 目标区域的左上角y坐标。
 *	      dest_width - 目标区域的宽度。
 *		  dest_height - 目标区域的高度。
 *        src_x - 源黏贴区域左上角x坐标。
 *        src_y - 源黏贴区域左上角y坐标。
 *	      src_width - 源黏贴区域宽度。
 *        src_height - 源黏贴区域高度。
 *        src_unit - 源黏贴区域所采用的度量单位（默认为像素）。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
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
 * brief: 将当前图片黏贴到指定位图上。
 * param: bitmap - 指向目标位图。
 *        dest_x - 目标区域的左上角x坐标。
 *        dest_y - 目标区域的左上角y坐标。
 *	      dest_width - 目标区域的宽度。
 *		  dest_height - 目标区域的高度。
 *        src_x - 源黏贴区域左上角x坐标。
 *        src_y - 源黏贴区域左上角y坐标。
 *	      src_width - 源黏贴区域宽度。
 *        src_height - 源黏贴区域高度。
 *        src_unit - 源黏贴区域所采用的度量单位（默认为像素）。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
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
 * brief: 将当前图片黏贴到指定位图上。
 * param: bitmap - 指向目标位图。
 *        dest_x - 目标区域的左上角x坐标。
 *        dest_y - 目标区域的左上角y坐标。
 *        dest_width - 目标区域宽度。
 *        dest_height - 目标区域高度。
 *        src_l_stretch - 源图片左侧拉伸系数。
 *        src_t_stretch - 源图片顶部拉伸系数。
 *        src_r_stretch - 源图片右侧拉伸系数。
 *        src_b_stretch - 源图片底部拉伸系数。
 *        src_unit - 源图片度量单位。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
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
 * brief: 将当前图片黏贴到指定位图上。
 * param: bitmap - 指向目标位图。
 *        dest_x - 目标区域的左上角x坐标。
 *        dest_y - 目标区域的左上角y坐标。
 *        dest_width - 目标区域宽度。
 *        dest_height - 目标区域高度。
 *        src_l_stretch - 源图片左侧拉伸系数。
 *        src_t_stretch - 源图片顶部拉伸系数。
 *        src_r_stretch - 源图片右侧拉伸系数。
 *        src_b_stretch - 源图片底部拉伸系数。
 *        src_unit - 源图片度量单位。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
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
 * brief: 将当前图片黏贴到指定位图上。
 * param: bitmap - 指向目标位图。
 *        dest_x - 目标区域的左上角x坐标。
 *        dest_y - 目标区域的左上角y坐标。
 *        dest_width - 目标区域宽度。
 *        dest_height - 目标区域高度。
 *        src_x - 源黏贴区域左上角x坐标。
 *        src_y - 源黏贴区域左上角y坐标。
 *	      src_width - 源黏贴区域宽度。
 *        src_height - 源黏贴区域高度。
 *        src_l_stretch - 源图片左侧拉伸系数。
 *        src_t_stretch - 源图片顶部拉伸系数。
 *        src_r_stretch - 源图片右侧拉伸系数。
 *        src_b_stretch - 源图片底部拉伸系数。
 *        src_unit - 源图片度量单位。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
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
 * brief: 将当前图片黏贴到指定位图上。
 * param: bitmap - 指向目标位图。
 *        dest_x - 目标区域的左上角x坐标。
 *        dest_y - 目标区域的左上角y坐标。
 *        dest_width - 目标区域宽度。
 *        dest_height - 目标区域高度。
 *        src_x - 源黏贴区域左上角x坐标。
 *        src_y - 源黏贴区域左上角y坐标。
 *	      src_width - 源黏贴区域宽度。
 *        src_height - 源黏贴区域高度。
 *        src_l_stretch - 源图片左侧拉伸系数。
 *        src_t_stretch - 源图片顶部拉伸系数。
 *        src_r_stretch - 源图片右侧拉伸系数。
 *        src_b_stretch - 源图片底部拉伸系数。
 *        src_unit - 源图片度量单位。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
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