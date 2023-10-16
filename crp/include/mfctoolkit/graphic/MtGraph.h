#pragma once

#include"../Symbol"

class MtBitmap;

/**
 * name: MtGraph
 * breif: ͼ���࣬��ϵͳ�����пɻ���ͼ�εĻ��࣬
 *        �����ǳ����ࡣ
 * author: yameng_he
 * date: 2015-10-28
 */
class MFC_TOOLKIT_API MtGraph{
//construction & destruction
public:
	MtGraph(void);
	virtual ~MtGraph(void);
//overrides
public:
	virtual int draw(const HDC dest_dc,
		MtBitmap &dest_bitmap,const CRect &dest_area)=0;
};

