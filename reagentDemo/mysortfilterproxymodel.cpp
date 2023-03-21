
//MySortFilterProxyModel::MySortFilterProxyModel(QObject *parent)
//    : QSortFilterProxyModel(parent)
//{
//}
//
//bool MySortFilterProxyModel::lessThan(const QModelIndex& source_left, const QModelIndex& source_right) const
//{
//	if (!source_left.isValid() || !source_right.isValid())
//		return false;
//
//	if ((source_left.column() == 1) && (source_right.column() ==1))
//	{
//		QVariant leftData = sourceModel()->data(source_left);
//		QVariant rightData = sourceModel()->data(source_right);
//
//		if (leftData.canConvert<QString>() && rightData.canConvert<QString>())
//		{
//			return rightData.toInt() > leftData.toInt();
//		}
//	}
//
//	return QSortFilterProxyModel::lessThan(source_left, source_right);
//}
