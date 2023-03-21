#ifndef REAGENTDISKSCANNINGDIALOG_H
#define REAGENTDISKSCANNINGDIALOG_H

#include <QDialog>
#include <QCheckBox>
#include <QVector>

namespace Ui {
class ReagentDiskScanningDialog;
}

class ReagentDiskScanningDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ReagentDiskScanningDialog(QWidget *parent = nullptr);
    ~ReagentDiskScanningDialog();
public slots:
    void slotSelectAll();
    void slotScan();
    void slotExit();
private:
    void initUI();
    void initSlotAndSignal();

private:
    Ui::ReagentDiskScanningDialog *ui;
    QVector<QCheckBox*> checkBoxVec;//ºóÆÚ¸ÄMap
};

#endif // REAGENTDISKSCANNINGDIALOG_H