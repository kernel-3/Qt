#ifndef REAGENT_H
#define REAGENT_H

#include <QWidget>
#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QMessageBox>
#include <QStandardItemModel>
#include <QSortFilterProxyModel>


#include "reagentdiskscanningdialog.h"
#include "sortheaderview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ReagentDialog; }
QT_END_NAMESPACE

class ReagentDialog : public QWidget
{
    Q_OBJECT

public:
    ReagentDialog(QWidget *parent = nullptr);
    ~ReagentDialog();
public slots:
    void slotManualRegistration();
    void slotDeleteReagentInfo();
    void slotReagentDiskScanning();
    void slotReagentDiskRoation();
  
    void slotVerifyBarCodeWhetherLegal();
    
    void slotOnReagentStatusSelectTableClicked(const QModelIndex& index);

private:
    void initReagentInfoUI();
    void initReagentStatusUI();
    void initReagentStatusUISelect();
    void initReagentStatusUIDisaply();
    void initSlotAndSingal();

private:
    Ui::ReagentDialog *ui;
    QStandardItemModel* reagentStastusModel;
};
#endif // REAGENT_H


class MySortFilterProxyModel : public QSortFilterProxyModel
{
public:
	explicit MySortFilterProxyModel(QObject* parent = nullptr);
protected:
	bool lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const override;
};
