#pragma once

class Database;
class MtADORecordset;

/**
 * name: StandardApplication
 * brief: 标准申请参数类，负责描述一个项目中包含标准相关的申请参数。
 * author: yameng_he
 * date: 2015-07-13
 */
class StandardApplication{
//construction & destruction
public:
	StandardApplication(void);
	~StandardApplication(void);
//interface
public:
	void set_calibrator_code_1(const int calibrator_code);
	int get_calibrator_code_1() const;
	void set_calibrator_code_2(const int calibrator_code);
	int get_calibrator_code_2() const;
	void set_calibrator_code_3(const int calibrator_code);
	int get_calibrator_code_3() const;
	void set_calibrator_code_4(const int calibrator_code);
	int get_calibrator_code_4() const;
	void set_calibrator_code_5(const int calibrator_code);
	int get_calibrator_code_5() const;
	void set_calibrator_code_6(const int calibrator_code);
	int get_calibrator_code_6() const;
	void set_sample_volume_1(const double sample_volume);
	double get_sample_volume_1() const;
	void set_diluted_sample_volume_1(const double diluted_sample_volume);
	double get_diluted_sample_volume_1() const;
	void set_diluent_volume_1(const double diluent_volume);
	double get_diluent_volume_1() const;
	void set_sample_volume_2(const double sample_volume);
	double get_sample_volume_2() const;
	void set_diluted_sample_volume_2(const double diluted_sample_volume);
	double get_diluted_sample_volume_2() const;
	void set_diluent_volume_2(const double diluent_volume);
	double get_diluent_volume_2() const;
	void set_sample_volume_3(const double sample_volume);
	double get_sample_volume_3() const;
	void set_diluted_sample_volume_3(const double diluted_sample_volume);
	double get_diluted_sample_volume_3() const;
	void set_diluent_volume_3(const double diluent_volume);
	double get_diluent_volume_3() const;
	void set_sample_volume_4(const double sample_volume);
	double get_sample_volume_4() const;
	void set_diluted_sample_volume_4(const double diluted_sample_volume);
	double get_diluted_sample_volume_4() const;
	void set_diluent_volume_4(const double diluent_volume);
	double get_diluent_volume_4() const;
	void set_sample_volume_5(const double sample_volume);
	double get_sample_volume_5() const;
	void set_diluted_sample_volume_5(const double diluted_sample_volume);
	double get_diluted_sample_volume_5() const;
	void set_diluent_volume_5(const double diluent_volume);
	double get_diluent_volume_5() const;
	void set_sample_volume_6(const double sample_volume);
	double get_sample_volume_6() const;
	void set_diluted_sample_volume_6(const double diluted_sample_volume);
	double get_diluted_sample_volume_6() const;
	void set_diluent_volume_6(const double diluent_volume);
	double get_diluent_volume_6() const;
	int is_valid(CString *error_message=0) const;
	void reset_default_value();
	int commit(const int item_id,const int method,Database &database) const;
	int update(MtADORecordset &record);
//variables
private:
	int _calibrator_code_1;
	int _calibrator_code_2;
	int _calibrator_code_3;
	int _calibrator_code_4;
	int _calibrator_code_5;
	int _calibrator_code_6;
	double _sample_volume_1;
	double _diluted_sample_volume_1;
	double _diluent_volume_1;
	double _sample_volume_2;
	double _diluted_sample_volume_2;
	double _diluent_volume_2;
	double _sample_volume_3;
	double _diluted_sample_volume_3;
	double _diluent_volume_3;
	double _sample_volume_4;
	double _diluted_sample_volume_4;
	double _diluent_volume_4;
	double _sample_volume_5;
	double _diluted_sample_volume_5;
	double _diluent_volume_5;
	double _sample_volume_6;
	double _diluted_sample_volume_6;
	double _diluent_volume_6;
};