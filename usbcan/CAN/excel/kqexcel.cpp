#include "kqexcel.h"
#include "libxl.h"
#include <QDebug>
using namespace libxl;

#define q2wString(key) key.toStdWString().c_str()

KQExcel::KQExcel(const QString &srcPath)
{
    mBook = xlCreateXMLBook();  // use xlCreateXMLBook() for working with xlsx files
    const wchar_t *x = L"Halil Kural";
    const wchar_t *y = L"windows-2723210a07c4e90162b26966a8jcdboe";
    mBook->setKey(x, y);
    if (!srcPath.isEmpty())
    {
        bool loadReslult = mBook->load(q2wString(srcPath));
        qDebug() << "load excel " << loadReslult << "  -->  " << srcPath;
        Q_ASSERT(loadReslult);
    }
    else
    {
        mBook->addSheet(L"Sheet1");
    }
    mSheet = mBook->getSheet(0);
}

KQExcel::~KQExcel()
{
    mBook->release();
}

bool KQExcel::save(const QString &savePath)
{
    return mBook->save(q2wString(savePath));
}

/**
 * @brief tocell 向单元格中写入数据
 * @param col 单元格所在列，如果是合并的单元格，以合并单元格的第一列的列数为准
 * @param row 单元格所在行，如果是合并的单元格，以合并单元格的第一行的行数为准
 * @param value 要写入的数据
 */
void KQExcel::tocell(int row, int col, const QVariant &value)  //向单元格写入字符串 col row从1开始
{
    Q_ASSERT(col);
    Q_ASSERT(row);
    int irow=row-1;
    int icol=col-1;
    switch (value.type())
    {
    case QVariant::Bool:
        mSheet->writeBool(irow,icol,value.toBool());
        break;
    case QVariant::Int:
    case QVariant::UInt:
    case QVariant::LongLong:
    case QVariant::ULongLong:
        mSheet->writeNum(irow,icol,value.toInt());
        break;
    case QVariant::Double:
        mSheet->writeNum(irow,icol,value.toDouble());
        break;
    case QVariant::Char:
    case QVariant::String:
    case QVariant::ByteArray:
        mSheet->writeStr(irow,icol,q2wString(value.toString()));
        break;
    case QVariant::Date:
    case QVariant::Time:
    case QVariant::DateTime:
        mSheet->writeStr(irow,icol,q2wString(value.toString()));
        break;
    default:
        break;
    }
}


QString KQExcel::cell(int row, int col)
{
    Q_ASSERT(col);
    Q_ASSERT(row);
    int irow=row-1;
    int icol=col-1;

    QString value= QString::fromStdWString(mSheet->readStr(irow,icol));
    return value;
}

void KQExcel::gosheet(int page)  //跳转到指定sheet页  激活并选择，page从1开始
{
    Q_ASSERT(page);
    mSheet = mBook->getSheet(page - 1);
}


/**
 * @brief insertRow 插入行，新增的行从第row行开始，即插入在原第row行之上
 * @param row
 * @param count 要插入多少行，不填写的话默认只插入一行
 */
void KQExcel::insertRow(int row,int count)
{
    Q_ASSERT(count);
    int irow=row-1;
    mSheet->insertRow(irow,irow+count-1);
}

