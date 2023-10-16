#pragma once

#include<map>
#include<memory>

class MtLock;
template<typename _Tp,typename _Lock>
class MtSingleton;
class MtImage;

/**
 * name: Theme
 * brief: 主题类，负责管理UI中所有字体以及图片，
 *        为UI提供不同风格的主题。
 * author: yameng_he
 * date: 2014-12-04
 */
class Theme{
//define
public:
	enum{NUMBER_OF_IMAGES=40,};
	typedef std::shared_ptr<MtImage> PtrToImage;
	typedef std::map<unsigned int,PtrToImage> ImageMap;
	typedef MtSingleton<Theme,MtLock> Singleton_Instance;
	friend class Singleton_Instance;
//destruction
public:
	~Theme(void);
//static interface
public:
	static Theme *instance();
//interface
public:
	const CString &get_theme_path() const;
	void load_images();
	void unload_images();
	PtrToImage get_image(const unsigned int image_no) const;
	CString get_string(const unsigned int string_id) const;
//construction
private:
	Theme(void);
//restrict
private:
	Theme(const Theme &);
	Theme &operator=(const Theme &);
//variables
private:
	CString _theme_path;
	ImageMap _image_map;
};