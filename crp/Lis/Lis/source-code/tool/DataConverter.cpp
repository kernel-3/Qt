#include"stdafx.h"
#include"DataConverter.h"

/**
 * name: is_number
 * brief: �ж�ָ�������д洢�������Ƿ�Ϊ���֡�
 * param: content - ָ�������ݡ�
 * return: ���ָ���������д洢������Ϊ�����򷵻�TRUE�����򷵻�FALSE��
 */
BOOL DataConverter::is_number(const String &content){
	return(is_unsigned_int(content));
}

/**
 * name: is_unsigned_int
 * brief: �ж�ָ�������д洢�������Ƿ�Ϊ�޷����������ݡ�
 * param: content - ָ�������ݡ�
 * return: ���ָ��������Ϊ�޷����������ݷ���TRUE�����򷵻�FALSE��
 */
BOOL DataConverter::is_unsigned_int(const String &content){
	//1.�����ǰ���ݵ��ַ���Ϊ�գ���ֱ�ӷ���FALSE��
	if(content.IsEmpty()){
		return(FALSE);
	}
	//2.���㵱ǰ�ַ������ȡ�
	const unsigned int content_size=content.GetLength();
	//3.�����ַ������ж��ַ������Ƿ�ȫ��Ϊ���֡�
	for(unsigned int index=0;index!=content_size;++index){
		if((Text('0')>content[index])||(Text('9')<content[index])){
			return(FALSE);
		}
	}
	//4.�������е���ֱ�ӷ���TRUE��
	return(TRUE);
}

/**
 * name: to_string
 * breif: ��ָ�����޷�����������ת�����ַ�����
 * param: content - ָ�����޷����������ݡ�
 * return: ����ת���ɵ��ַ�����
 */
String DataConverter::to_string(const unsigned int content){
	String string_content(Text(""));
	string_content.Format(Text("%ld"),content);
	return(string_content);
}

/**
 * name: to_unsigned_int
 * brief: ��ָ��������ת��Ϊ�޷����������ݡ�
 * param: content - ָ�����ݡ�
 * return: �������ִ�гɹ�����ת������޷����������ݣ����򷵻��㡣
 */
unsigned int DataConverter::to_unsigned_int(const String &content){
	//1.�����ǰָ�������д洢�����ݲ������޷����������ݡ�
	if(!is_unsigned_int(content)){
		return(0);
	}
	//2.�����ǰָ�������д洢���������޷����������ݡ�
	else{
		return(Atoi(content));
	}
}