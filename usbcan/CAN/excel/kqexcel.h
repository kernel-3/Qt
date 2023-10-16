#ifndef KQEXCEL_H
#define KQEXCEL_H
#include <QObject>


#include "libxl.h"

namespace libxl {
class IBook;
class ISheet;
}
/**
 * @author lrs
 * @brief The KQExcel class
 * @note 为保持与KQRWExcel保持一致，本辅助类中所有行列页数均以1开始
 * @note 如果过Book与sheet操作其他更多功能，注意三方库中 Book，Sheet 所有行列页数均以0开始
 * @note 写此类主要目地为 实现对表格 插入、 删除 行列的功能
 */
class  KQExcel
{
public:
    /**
     * @brief KQExcel 创建一个excel表格，在save()后保存为savePath
     * @param savePath 保存路径，最好写绝对路径，一般相对路径是相对于程序所在目录的路径
     * @param srcPath 模板路径，如为空则会新建一个只有一个“Sheet1”的表格
     * @param srcPath 模板路径，如不为空，会加载模板表的数据到新建的表中。
     */
    KQExcel(const QString &srcPath=QString());
    ~KQExcel();
public:
    /**
     * @brief tocell 向单元格中写入数据
     * @param col 单元格所在列，如果是合并的单元格，以合并单元格的第一列的列数为准
     * @param row 单元格所在行，如果是合并的单元格，以合并单元格的第一行的行数为准
     * @param value 要写入的数据
     */
    void tocell(int row,int col ,const QVariant &value);  //向单元格写入字符串 col row从1开始
    QString cell(int row,int col);
    void gosheet(int page);     //跳转到指定sheet页  激活并选择，page从1开始

    /**
     * @brief insertRow 插入行，新增的行从第row行开始，即插入在原第row行之上
     * @param row
     * @param count 要插入多少行，不填写的话默认只插入一行
     */
    void insertRow(int row,int count=1);

    //通过Book与sheet操作其他更多功能
    libxl::Book *book(){return mBook;}
    libxl::Sheet *currentSheet(){return mSheet;}

    bool save(const QString &savePath);

private:
    libxl::Book *mBook;
    libxl::Sheet *mSheet;
};


#endif // KQEXCEL_H
