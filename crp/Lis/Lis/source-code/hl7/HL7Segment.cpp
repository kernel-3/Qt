#include"stdafx.h"
#include"HL7Segment.h"
#include<algorithm>

//初始化全局变量。
const Char HL7Segment::END_CHARACTER=0x0D;
const Char HL7Segment::FIELD_SEPARATOR=Text('|');
const Char HL7Segment::GROUP_SEPARATOR=Text('^');

/**
 * name: HL7Segment
 * brief: 构造函数。
 * param: name - “段”名。
 *        field_amount - “段”中包含“域”的数量。
 * return: --
 */
HL7Segment::HL7Segment(const String &name,const unsigned int field_amount)
	:_name(name)
	,_field_amount(field_amount){
}

/**
 * name: ~HL7Segment
 * brief: 析构函数。
 * param: --
 * return: --
 */
HL7Segment::~HL7Segment(void){
}

/**
 * name: get_name
 * brief: 获取当前“段”的名称。
 * param: --
 * return: 返回当前“段”的名称。
 */
const String &HL7Segment::get_name() const{
	return(_name);
}

/**
 * name: get_field_amount
 * brief: 获取当前“段”中“域”的数量。
 * param: --
 * return: 返回当前“段”中“域”的数量。
 */
unsigned int HL7Segment::get_field_amount() const{
	return(_field_amount);
}

/**
 * name: from_hl7
 * brief: 根据指定的HL7“段”语句，生成“段”类中的相关数据。
 * param: hl7 - HL7“段”字符串。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int HL7Segment::from_hl7(const String &hl7){
	//1.判断当前“段”字符串是否为空，如果为空直接返回错误。
	const int size=hl7.GetLength();
	if(size<=0){
		return(-1);
	}
	//2.如果当前“段”字符串没有终止字符，则直接返回错误。
	if(END_CHARACTER!=hl7[size-1]){
		return(-2);
	}
	//3.如果当前“段”中域的个数不合法，则直接返回错误。
	if(static_cast<int>(_field_amount)!=std::count(
		static_cast<const Char *>(hl7),static_cast<
		const Char *>(hl7)+size,FIELD_SEPARATOR)){
		return(-3);
	}
	//4.遍历“段”字符串，提取段中各“域”内容进行翻译。
	//4-1.声明当前操作所需变量。
	int start_index=0;//记录当前遍历“段”字符串的起始位置。
	int end_index=0;//记录当前遍历“段”字符串的结束位置。
	//4-2.遍历“段”字符串，提取“段”中“域”的内容。
	for(unsigned int index=1;index<=_field_amount;++index){
		//4-2-1.计算当前“域”的结束位。
		end_index=hl7.Find(FIELD_SEPARATOR,start_index);
		//4-2-2.如果计算“域”的结束位失败，则直接返回错误。
		if((end_index<0)||(end_index<start_index)){
			return(-4);
		}
		//4-2-3.提取当前“域”中的内容。
		const String field_content=hl7.Mid(start_index,
			end_index-start_index);
		//4-2-4.重新计算起始位置。
		start_index=end_index+1;
		//4-2-5.将内容设置到当前“域”中，并且判断设置是否成功。
		if(set_field(index,field_content)<0){
			return(-5);
		}
	}
	//5.程序运行到此成功返回。
	return(0);
}

/**
 * name: to_hl7
 * brief: 将当前“段”转化成HL7字符串。
 * param: --
 * return: 返回转化后的HL7字符串。
 */
String HL7Segment::to_hl7() const{
	//1.声明当前操作所需变量。
	String hl7_statement(Text(""));
	//2.遍历“段”的“域”，利用“域”内容生成HL7字符串。
	//2-1.连接“段”中“域”的内容，并且用“域”分隔符隔开。
	for(unsigned int index=1;index<=_field_amount;++index){
		//2-1-1.声明当前操作所需变量。
		String content(Text(""));
		//2-1-2.获取当前“域”的内容。
		if(get_field(index,content)<0){
			return(Text(""));
		}
		//2-1-3.连接形成HL7字符串。
		hl7_statement+=content;//添加“域”的内容。
		hl7_statement+=FIELD_SEPARATOR;//添加“域”分隔符。
	}
	//2-2.添加“段”的结束字符。
	hl7_statement+=END_CHARACTER;
	//3.程序运行到此返回HL7字符串。
	return(hl7_statement);
}

/**
 * name: extract_group_content_from_field_content
 * brief: 从一个指定“域”的内容中，提取“组”的内容。
 * param: field_content - 准备分析的“域”的内容。
 *        group_content - 返回的“组”的内容（它可以是一个数组指针）。
 *        group_content_amount - “组”内容的数量。
 * return: 如果函数执行成功返回值大于等于零，否则返回值小于零。
 */
int HL7Segment::extract_group_content_from_field_content(const String &field_content,
	String *group_content,const unsigned int group_content_amount) const{
	//1.判断当前传递参数是否合法。
	if((0==group_content)||(0==group_content_amount)){
		return(-1);
	}
	//2.计算当前“组”分割符的数量，并且判断分割符数量是否合法。
	//2-1.计算当前传递“域”内容的尺寸。
	const unsigned int field_content_size=field_content.GetLength();
	//2-2.计算当前“组”分割符数量。
	const unsigned int group_separator_amount=std::count(static_cast<const Char *>(
		field_content),static_cast<const Char *>(field_content)+field_content_size,
		GROUP_SEPARATOR);
	//2-3.如果当前“组”分割符数量不合法。
	if((group_content_amount-1)!=group_separator_amount){
		return(-2);
	}
	//3.遍历混合“域”的内容，从中提取“组”内容。
	//3-1.声明当前操作所需变量。
	int start_index=0;//记录当前遍历“域”内容的起始位置。
	int end_index=0;//记录当前遍历“域”内容的结束位置。
	//3-2.遍历“域”的内容，提取“域”中“组”的内容。
	for(unsigned int index=0;index<group_content_amount;++index){
		//3-2-1.查找当前“组”内容的结束位。
		end_index=field_content.Find(GROUP_SEPARATOR,start_index);
		//3-2-2.如果查找“组”内容的结束位失败，则认为当前“域”的内容中不含“组”分割符。
		if((end_index<0)||(end_index<start_index)){
			end_index=field_content_size;
		}
		//3-2-3.提取当前“域”中“组”的内容，并将内容返回。
		if(1==group_content_amount){
			*group_content=field_content.Mid(
				start_index,end_index-start_index);
		}else{
			group_content[index]=field_content.Mid(
				start_index,end_index-start_index);
		}
		//3-2-4.重新计算起始位置。
		start_index=end_index+1;
	}
	//4.程序运行到此，成功返回。
	return(0);
}

/**
 * name: set_field
 * brief: 设置当前“段”的指定域。
 * param: no - “域”的编号（注意：从1开始计数）。
 *        content - “域”的内容。
 * return: 如果“域”设置成功返回值大于零，如果忽略“域”的设置则返回零，
 *         如果“域”设置失败返回负数。
 */
int HL7Segment::set_field(const unsigned int no,const String &content){
	//1.如果当前“域”编号为1，则进行“域”的设置。
	if(1==no){
		//1-1.如果“域”设置成功。
		if(_name==content){
			return(1);
		}
		//1-2.如果“域”设置失败。
		else{
			return(-1);
		}
	}
	//2.如果当前“域”的编号大于1，则忽略当前设置操作。
	else if(no>1){
		return(0);
	}
	//3.如果当前“域”的编号为其它异常情况。
	else{
		return(-2);
	}
}

/**
 * name: get_field
 * brief: 获取“段”中指定“域”的内容。
 * param: no - “域”的编号（注意：从1开始计数）。
 *        content - 返回“域”的内容。
 * return: 如果“域”内容获取成功返回值大于零，如果忽略“域”
 *         内容的获取设置则返回零，如果“域”内容的获取失败
 *         返回负数。
 */
int HL7Segment::get_field(const unsigned int no,String &content) const{
	//1.如果当前“域”编号为1，则进行“域”内容的获取。
	if(1==no){
		//1-1.获取当前“域”的内容。
		content=_name;
		//1-2.程序运行到此成功返回。
		return(1);
	}
	//2.如果当前“域”的编号大于1，则忽略当前设置操作。
	else if(no>1){
		return(0);
	}
	//3.如果当前“域”的编号为其它异常情况。
	else{
		return(-2);
	}
}