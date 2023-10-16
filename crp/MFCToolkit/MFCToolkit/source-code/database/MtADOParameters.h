#pragma once

#include"../Symbol"
#import "C:\Program Files (x86)\Common Files\System\ado\msado15.dll" \
	named_guids rename("EOF","adoEOF"),rename("BOF","adoBOF")

/**
 * name: MtADOParameters
 * brief:  对ADO中Parameters对象的封装，提供所有Parameters对象的方法实现。
 * author: yameng_he
 * date: 2014-09-02
 */
class MFC_TOOLKIT_API MtADOParameters{
//constructor & destructor
public:
	MtADOParameters(void);
	~MtADOParameters(void);
};