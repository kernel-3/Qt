#pragma once

class MtADORecordset;

/**
 * name: AnalysisMethod
 * breif: 分析方法类，负责描述一个分析方法，并提供与分析
 *        方法相关的全部接口。
 * author: yameng_he
 * date: 2015-11-30
 */
class AnalysisMethod{
//construction & destruction
public:
	AnalysisMethod(void);
	~AnalysisMethod(void);
//interface
public:
	void set_id(const int id);
	int get_id() const;
	void set_name(const CString &name);
	CString get_name() const;
	void set_alias(const CString &alias);
	CString get_alias() const;
	void set_expression(const CString &expression);
	CString get_expression() const;
	int is_valid() const;
	int update(MtADORecordset &recordset);
//variables
private:
	int _id;
	CString _name;
	CString _alias;
	CString _expression;
};
