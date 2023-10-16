#include"stdafx.h"
#include"MtADORecordset.h"
#include"MtADOConnection.h"
#include<assert.h>

/**
 * name: MtADORecordset
 * brief: 构造函数。
 * param: --
 * return: --
 */
MtADORecordset::MtADORecordset(void)
	:_last_error_code(0)
	,_last_error_message(_T(""))
	,_recordset(0){
	create_instance();
}

/**
 * name: ~MtADORecordset
 * brief: 析构函数。
 * param: --
 * return: --
 */
MtADORecordset::~MtADORecordset(void){
	release_instance();
}

/**
 * name: set_absolute_page
 * brief: 指定当前记录所在的页。
 * param: page - 页号。
 * return: --
 * note: 设置或返回从 1 到 Recordset 对象 (PageCount) 所含页数的长整型值，或者返回以下常量。
 *       常量                   说明 
 *       ======================================================================================
 *       AdPosUnknown          Recordset 为空，当前位置未知，或者提供者不支持 AbsolutePage 属性。 
 *       AdPosBOF              当前记录指针位于 BOF（即 BOF 属性为 True）。 
 *       AdPosEOF              当前记录指针位于 EOF（即 EOF 属性为 True）。 
 *       ======================================================================================
 * remark: 使用 AbsolutePage 属性可识别当前记录所在的页码。使用 PageSize 属性可将 Recordset 
 *         对象逻辑划分为一系列的页，每页的记录数等于 PageSize（最后页除外，该页记录数较少）。提
 *         供者必须支持该属性的相应功能才能使用该属性。与 AbsolutePosition 属性一样，AbsolutePage 
 *         从 1 开始并在当前记录为 Recordset 中的第一个记录时等于 1。设置该属性可移动到特定页的第一个
 *         记录。从 PageCount 属性中可获得总页数。
 */
void MtADORecordset::set_absolute_page(const ADODB::PositionEnum page){
	clear_last_error();
	try{
		_recordset->PutAbsolutePage(page);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: set_absolute_page
 * brief: 指定当前记录所在的页。
 * param: page - 页号。
 * return: 返回当前记录所在的页。
 * note: 设置或返回从 1 到 Recordset 对象 (PageCount) 所含页数的长整型值，或者返回以下常量。
 *       常量                   说明 
 *       ======================================================================================
 *       AdPosUnknown          Recordset 为空，当前位置未知，或者提供者不支持 AbsolutePage 属性。 
 *       AdPosBOF              当前记录指针位于 BOF（即 BOF 属性为 True）。 
 *       AdPosEOF              当前记录指针位于 EOF（即 EOF 属性为 True）。 
 *       ======================================================================================
 * remark: 使用 AbsolutePage 属性可识别当前记录所在的页码。使用 PageSize 属性可将 Recordset 
 *         对象逻辑划分为一系列的页，每页的记录数等于 PageSize（最后页除外，该页记录数较少）。提
 *         供者必须支持该属性的相应功能才能使用该属性。与 AbsolutePosition 属性一样，AbsolutePage 
 *         从 1 开始并在当前记录为 Recordset 中的第一个记录时等于 1。设置该属性可移动到特定页的第一个
 *         记录。从 PageCount 属性中可获得总页数。
 */
ADODB::PositionEnum MtADORecordset::get_absolute_page() const{
	clear_last_error();
	try{
		return(_recordset->GetAbsolutePage());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adPosUnknown);
	}
}

/**
 * name: set_absolute_position
 * brief: 设置当前记录的序号位置。
 * param: position - 位置序号。
 * return: --
 * note: 设置或返回从 1 到 Recordset 对象 (PageCount) 所含页数的长整型值，或者返回以下常量。
 *       常量                               说明 
 *       =============================================================================================
 *       AdPosUnknown                      Recordset 为空，当前位置未知，或者提供者不支持 AbsolutePage 属性。 
 *       AdPosBOF                          当前记录指针位于 BOF（即 BOF 属性为 True。） 
 *       adPosEOF                          当前记录指针位于 EOF（即 EOF 属性为 True。） 
 *       =============================================================================================
 * remark: 使用 AbsolutePosition 属性可根据其在 Recordset 中的序号位置移动到记录，或确定当前记录的序号位置。提供者
 *         必须支持该属性的相应功能才能使用该属性。同 AbsolutePage 属性一样，AbsolutePosition 从 1 开始，并在当前
 *         记录为 Recordset 中的第一个记录时等于 1。从 RecordCount 属性可获得 Recordset 对象的总记录数。设置 AbsolutePosition 
 *         属性时，即使该属性指向位于当前缓存中的记录，ADO 也将使用以指定的记录开始的新记录组重新加载缓存。CacheSize 
 *         属性决定该记录组的大小。
 *         注意: 不能将 AbsolutePosition 属性作为替代的记录编号使用。删除前面的记录时，给定记录的当前位置将发生改变。
 *         如果 Recordset 对象被重新查询或重新打开，则无法保证给定记录有相同的 AbsolutePosition。书签仍然是保持和返
 *         回给定位置的推荐方式，并且在所有类型的 Recordset 对象的定位时是唯一的方式。
 */
void MtADORecordset::set_absolute_position(const ADODB::PositionEnum position){
	clear_last_error();
	try{
		_recordset->PutAbsolutePosition(position);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_absolute_position
 * brief: 获取当前记录的序号位置。
 * param: --
 * return: 返回当前记录的序号位置。
 * note: 设置或返回从 1 到 Recordset 对象 (PageCount) 所含页数的长整型值，或者返回以下常量。
 *       常量                               说明 
 *       =============================================================================================
 *       AdPosUnknown                      Recordset 为空，当前位置未知，或者提供者不支持 AbsolutePage 属性。 
 *       AdPosBOF                          当前记录指针位于 BOF（即 BOF 属性为 True。） 
 *       adPosEOF                          当前记录指针位于 EOF（即 EOF 属性为 True。） 
 *       =============================================================================================
 * remark: 使用 AbsolutePosition 属性可根据其在 Recordset 中的序号位置移动到记录，或确定当前记录的序号位置。提供者
 *         必须支持该属性的相应功能才能使用该属性。同 AbsolutePage 属性一样，AbsolutePosition 从 1 开始，并在当前
 *         记录为 Recordset 中的第一个记录时等于 1。从 RecordCount 属性可获得 Recordset 对象的总记录数。设置 AbsolutePosition 
 *         属性时，即使该属性指向位于当前缓存中的记录，ADO 也将使用以指定的记录开始的新记录组重新加载缓存。CacheSize 
 *         属性决定该记录组的大小。
 *         注意: 不能将 AbsolutePosition 属性作为替代的记录编号使用。删除前面的记录时，给定记录的当前位置将发生改变。
 *         如果 Recordset 对象被重新查询或重新打开，则无法保证给定记录有相同的 AbsolutePosition。书签仍然是保持和返
 *         回给定位置的推荐方式，并且在所有类型的 Recordset 对象的定位时是唯一的方式。
 */
ADODB::PositionEnum MtADORecordset::get_absolute_position() const{
	clear_last_error();
	try{
		return(_recordset->GetAbsolutePosition());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adPosUnknown);
	}
}

/**
 * name: get_active_command
 * brief: 获取关联的 Recordset 对象的 Command 对象。
 * param: --
 * return: 返回关联的 Recordset 对象的 Command 对象。
 * remark: ActiveCommand 属性为只读。如果没有使用 Command 对象创建当前 
 *         Recordset，将返回 Null 对象引用。如果您只有结果 Recordset 对象，
 *         则可使用该属性查找关联的 Command 对象。
 */
ADODB::_CommandPtr MtADORecordset::get_active_command() const{
	clear_last_error();
	try{
		return(_recordset->GetActiveCommand());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: set_active_connection
 * breif: 设置指定的 Command 或 Recordset 对象当前所属的 Connection 对象。
 * param: connection - Connection 对象。
 * return: --
 * note: 使用 ActiveConnection 属性可确定在其上将执行指定 Command 对象或打开指定 
 *       Recordset 的 Connection 对象。
 * remark: 对于打开的 Recordset 对象或其 Source 属性被设置为有效 Command 对象的 Recordset 对象，
 *         ActiveConnection 属性为只读。否则，该属性为读/写。可以将该属性设置为有效的 Connection 对象，
 *         或设置为有效的连接字符串。这时，提供者可使用该定义创建新的 Connection 对象，并打开连接。另外，
 *         提供者可以将该属性设置为新的 Connection 对象，以便向您提供访问扩展错误信息的 Connection 对象或
 *         执行其他命令。如果使用 Open 方法的 ActiveConnection 参数打开 Recordset 对象，ActiveConnection 
 *         属性将继承该参数的值。如果将 Recordset 对象的 Source 属性设置为有效 Command 对象变量，Recordset 的 
 *         ActiveConnection 属性将继承 Command 对象的 ActiveConnection 属性的设置。
 *        【远程数据服务】 在客户端 (ADOR) Recordset 对象上使用时，只能将该属性设置为连接字符串或（Microsoft 
 *         Visual Basic 或 VBScript 中）Nothing。 
 */
void MtADORecordset::set_active_connection(ADODB::_ConnectionPtr connection){
	clear_last_error();
	try{
		_recordset->PutActiveConnection(_variant_t(connection));
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_active_connection
 * breif: 获取指定的 Command 或 Recordset 对象当前所属的 Connection 对象。
 * param: --
 * return: 返回指定的 Command 或 Recordset 对象当前所属的 Connection 对象。
 * note: 使用 ActiveConnection 属性可确定在其上将执行指定 Command 对象或打开指定 
 *       Recordset 的 Connection 对象。
 * remark: 对于打开的 Recordset 对象或其 Source 属性被设置为有效 Command 对象的 Recordset 对象，
 *         ActiveConnection 属性为只读。否则，该属性为读/写。可以将该属性设置为有效的 Connection 对象，
 *         或设置为有效的连接字符串。这时，提供者可使用该定义创建新的 Connection 对象，并打开连接。另外，
 *         提供者可以将该属性设置为新的 Connection 对象，以便向您提供访问扩展错误信息的 Connection 对象或
 *         执行其他命令。如果使用 Open 方法的 ActiveConnection 参数打开 Recordset 对象，ActiveConnection 
 *         属性将继承该参数的值。如果将 Recordset 对象的 Source 属性设置为有效 Command 对象变量，Recordset 的 
 *         ActiveConnection 属性将继承 Command 对象的 ActiveConnection 属性的设置。
 *        【远程数据服务】 在客户端 (ADOR) Recordset 对象上使用时，只能将该属性设置为连接字符串或（Microsoft 
 *         Visual Basic 或 VBScript 中）Nothing。 
 */
ADODB::_ConnectionPtr MtADORecordset::get_active_connection() const{
	clear_last_error();
	try{
		return(_recordset->GetActiveConnection());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: get_bof
 * breif: 获取当前记录位置是否位于Recordset对象的第一个记录之前。
 * param: --
 * return: 返回当前记录位置是否位于Recordset对象的第一个记录之前。
 * remark: 使用 BOF 和 EOF 属性可确定 Recordset 对象是否包含记录，或者从一个记录移动到另一个记录时是否超出
 *         Recordset 对象的限制。如果当前记录位于第一个记录之前，BOF 属性将返回 True (-1)，如果当前记录为
 *         第一个记录或位于其后则将返回 False (0)。如果当前记录位于 Recordset 对象的最后一个记录之后 EOF 
 *         属性将返回 True，而当前记录为 Recordset 对象的最后一个记录或位于其前，则将返回 False。如果 BOF 
 *         或 EOF 属性为 True，则没有当前记录。如果打开没有记录的 Recordset 对象，BOF 和 EOF 属性将设置为 
 *         True，而 Recordset 对象的 RecordCount 属性设置为零。打开至少包含一条记录的 Recordset 对象时，
 *         第一条记录为当前记录，而 BOF 和 EOF 属性为 False。如果删除 Recordset 对象中保留的最后记录，BOF 
 *         和 EOF 属性将保持 False，直到重新安排当前记录。
 */
BOOL MtADORecordset::get_bof() const{
	clear_last_error();
	try{
		if(0==_recordset->GetadoBOF()){
			return(FALSE);
		}else{
			return(TRUE);
		}
	}catch(const _com_error &error){
		record_last_error(error);
		return(FALSE);
	}
}

/**
 * name: get_eof
 * breif: 获取当前记录位置是否位于Recordset对象的最后一个记录之后。
 * param: --
 * return: 返回当前记录位置是否位于Recordset对象的最后一个记录之后。
 * remark: 使用 BOF 和 EOF 属性可确定 Recordset 对象是否包含记录，或者从一个记录移动到另一个记录时是否超出
 *         Recordset 对象的限制。如果当前记录位于第一个记录之前，BOF 属性将返回 True (-1)，如果当前记录为
 *         第一个记录或位于其后则将返回 False (0)。如果当前记录位于 Recordset 对象的最后一个记录之后 EOF 
 *         属性将返回 True，而当前记录为 Recordset 对象的最后一个记录或位于其前，则将返回 False。如果 BOF 
 *         或 EOF 属性为 True，则没有当前记录。如果打开没有记录的 Recordset 对象，BOF 和 EOF 属性将设置为 
 *         True，而 Recordset 对象的 RecordCount 属性设置为零。打开至少包含一条记录的 Recordset 对象时，
 *         第一条记录为当前记录，而 BOF 和 EOF 属性为 False。如果删除 Recordset 对象中保留的最后记录，BOF 
 *         和 EOF 属性将保持 False，直到重新安排当前记录。
 */
BOOL MtADORecordset::get_eof() const{
	clear_last_error();
	try{
		if(0==_recordset->GetadoEOF()){
			return(FALSE);
		}else{
			return(TRUE);
		}
	}catch(const _com_error &error){
		record_last_error(error);
		return(FALSE);
	}
}

/**
 * name: set_bookmark
 * breif: 设置唯一标识 Recordset 对象中当前记录的书签，或者将 Recordset 
 *        对象的当前记录设置为由有效书签所标识的记录。
 * param: bookmark - 书签。
 * return: --
 * remark: 使用 Bookmark 属性可保存当前记录的位置并随时返回到该记录。书签
 *         只能在支持书签功能的 Recordset 对象中使用。打开 Recordset 对象时，
 *         其每个记录都有唯一的书签。要保存当前记录的书签，请将 Bookmark 属性
 *         的值赋给一个变量。移动到其他记录后要快速返回到该记录，请将该 Recordset 
 *         对象的 Bookmark 属性设置为该变量的值。用户可能无法查看书签的值，也同样
 *         无法对书签直接进行比较（指向同一记录的两个书签的值可能不同）。如果使用 Clone 
 *         方法创建 Recordset 的一个副本，则原始的和复制的 Recordset 对象 Bookmark 
 *         属性设置相同并可以替换使用。但是，无法替换使用不同 Recordset 对象的书签，
 *         即使这些书签是通过同一数据源或命令创建的。
 *        【远程数据服务】 在客户端 (ADOR) Recordset 对象上使用时，Bookmark 属性始终有效。
 */
void MtADORecordset::set_bookmark(const _variant_t &bookmark){
	clear_last_error();
	try{
		_recordset->PutBookmark(bookmark);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_bookmark
 * breif: 获取唯一标识 Recordset 对象中当前记录的书签，或者将 Recordset 
 *        对象的当前记录设置为由有效书签所标识的记录。
 * param: --
 * return: 返回计算有效书签的变体型表达式。
 * remark: 使用 Bookmark 属性可保存当前记录的位置并随时返回到该记录。书签
 *         只能在支持书签功能的 Recordset 对象中使用。打开 Recordset 对象时，
 *         其每个记录都有唯一的书签。要保存当前记录的书签，请将 Bookmark 属性
 *         的值赋给一个变量。移动到其他记录后要快速返回到该记录，请将该 Recordset 
 *         对象的 Bookmark 属性设置为该变量的值。用户可能无法查看书签的值，也同样
 *         无法对书签直接进行比较（指向同一记录的两个书签的值可能不同）。如果使用 Clone 
 *         方法创建 Recordset 的一个副本，则原始的和复制的 Recordset 对象 Bookmark 
 *         属性设置相同并可以替换使用。但是，无法替换使用不同 Recordset 对象的书签，
 *         即使这些书签是通过同一数据源或命令创建的。
 *        【远程数据服务】 在客户端 (ADOR) Recordset 对象上使用时，Bookmark 属性始终有效。
 */
_variant_t MtADORecordset::get_bookmark() const{
	clear_last_error();
	try{
		return(_recordset->GetBookmark());
	}catch(const _com_error &error){
		record_last_error(error);
		return(_variant_t());
	}
}

/**
 * name: set_catch_size
 * brief: 设置缓存在本地内存中的 Recordset 对象的记录数。
 * param: size - 缓存尺寸
 * return: --
 * remark: 使用 CacheSize 属性可控制提供者在缓存中所保存的记录的数目，并可控制一次恢复到本地内存的记录数。
 *         例如，如果 CacheSize 为 10，首次打开 Recordset 对象后，提供者将前面 10 个记录调入本地内存。
 *         当在 Recordset 对象中移动时，提供者返回本地内存缓冲区中的数据；一旦移动超过缓存中最后的记录，
 *         提供者便将数据源中随后的 10 个记录恢复到缓存。可以在 Recordset 对象的存活期调整该属性的值，
 *         但是更改该值只影响随后从数据源调入缓存的记录数。只更改属性值将不会更改缓存中的当前内容。如果要
 *         检索的记录较 CacheSize 指定的少，提供者将返回其余的记录，不会产生错误。不允许将 CacheSize 设
 *         置为零，否则将返回错误。从缓存恢复的记录不反映其他用户对数据源同时所作的更改。如需强行对所有缓存
 *         数据进行更新，请使用 Resync 方法。
 */
void MtADORecordset::set_catch_size(const long size){
	clear_last_error();
	try{
		_recordset->PutCacheSize(size);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_catch_size
 * brief: 获取缓存在本地内存中的 Recordset 对象的记录数。
 * param: --
 * return: 返回缓存在本地内存中的 Recordset 对象的记录数。
 * remark: 使用 CacheSize 属性可控制提供者在缓存中所保存的记录的数目，并可控制一次恢复到本地内存的记录数。
 *         例如，如果 CacheSize 为 10，首次打开 Recordset 对象后，提供者将前面 10 个记录调入本地内存。
 *         当在 Recordset 对象中移动时，提供者返回本地内存缓冲区中的数据；一旦移动超过缓存中最后的记录，
 *         提供者便将数据源中随后的 10 个记录恢复到缓存。可以在 Recordset 对象的存活期调整该属性的值，
 *         但是更改该值只影响随后从数据源调入缓存的记录数。只更改属性值将不会更改缓存中的当前内容。如果要
 *         检索的记录较 CacheSize 指定的少，提供者将返回其余的记录，不会产生错误。不允许将 CacheSize 设
 *         置为零，否则将返回错误。从缓存恢复的记录不反映其他用户对数据源同时所作的更改。如需强行对所有缓存
 *         数据进行更新，请使用 Resync 方法。
 */
long MtADORecordset::get_catch_size() const{
	clear_last_error();
	try{
		return(_recordset->GetCacheSize());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: set_cursor_location
 * brief: 设置游标服务的位置。
 * param: location - 游标服务的位置。
 * return: --
 * note: 设置或返回可设置为以下某个常量的长整型值。
 *       常量                     说明 
 *       =============================================================================
 *       adUseNone               没有使用游标服务。（该常量已过时并且只为了向后兼容才出现）。 
 *       adUseClient             使用由本地游标库提供的客户端游标。本地游标服务通常允许使用的
 *                               许多功能可能是驱动程序提供的游标无法使用的，因此使用该设置对
 *                               于那些将要启用的功能是有好处的。AdUseClient 具有向后兼容性，
 *                               也支持同义的 adUseClientBatch。 
 *       adUseServer             默认值。使用数据提供者的或驱动程序提供的游标。这些游标有时非
 *                               常灵活，对于其他用户对数据源所作的更改具有额外的敏感性。但是，
 *                               Microsoft Client Cursor Provider（如已断开关联的记录集）
 *                               的某些功能无法由服务器端游标模拟，通过该设置将无法使用这些功能。 
 *       ==============================================================================
 * remark: 该属性允许在可用于提供者的各种游标库中进行选择。通常，可以选择使用客户端游标库或位于服务器上的某个游标库。
 *         该属性设置仅对属性已经设置后才建立的连接有影响。更改 CursorLocation 属性不会影响现有的连接。对于 Connection 
 *         或关闭的 Recordset 该属性为读/写，而对打开的 Recordset 该属性为只读。由 Execute 方法返回的游标继承该设置。
 *         Recordset 将自动从与之关联的连接中继承该设置。
 *        【远程数据服务】 当用于客户端 (ADOR) Recordset 或 Connection 对象时，只能将 CursorLocation 属性设置为 
 *         adUseClient。
 */
void MtADORecordset::set_cursor_location(const ADODB::CursorLocationEnum location){
	clear_last_error();
	try{
		_recordset->PutCursorLocation(location);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_cursor_location
 * brief: 获取游标服务的位置。
 * param: --
 * return: 返回游标服务的位置。
 * note: 设置或返回可设置为以下某个常量的长整型值。
 *       常量                     说明 
 *       =============================================================================
 *       adUseNone               没有使用游标服务。（该常量已过时并且只为了向后兼容才出现）。 
 *       adUseClient             使用由本地游标库提供的客户端游标。本地游标服务通常允许使用的
 *                               许多功能可能是驱动程序提供的游标无法使用的，因此使用该设置对
 *                               于那些将要启用的功能是有好处的。AdUseClient 具有向后兼容性，
 *                               也支持同义的 adUseClientBatch。 
 *       adUseServer             默认值。使用数据提供者的或驱动程序提供的游标。这些游标有时非
 *                               常灵活，对于其他用户对数据源所作的更改具有额外的敏感性。但是，
 *                               Microsoft Client Cursor Provider（如已断开关联的记录集）
 *                               的某些功能无法由服务器端游标模拟，通过该设置将无法使用这些功能。 
 *       ===============================================================================
 * remark: 该属性允许在可用于提供者的各种游标库中进行选择。通常，可以选择使用客户端游标库或位于服务器上的某个游标库。
 *         该属性设置仅对属性已经设置后才建立的连接有影响。更改 CursorLocation 属性不会影响现有的连接。对于 Connection 
 *         或关闭的 Recordset 该属性为读/写，而对打开的 Recordset 该属性为只读。由 Execute 方法返回的游标继承该设置。
 *         Recordset 将自动从与之关联的连接中继承该设置。
 *        【远程数据服务】 当用于客户端 (ADOR) Recordset 或 Connection 对象时，只能将 CursorLocation 属性设置为 
 *                       adUseClient。
 */
ADODB::CursorLocationEnum MtADORecordset::get_cursor_location() const{
	clear_last_error();
	try{
		return(_recordset->GetCursorLocation());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adUseNone);
	}
}

/**
 * name: set_cursor_type
 * brief: 设置在Recordset对象中使用的游标类型。
 * param: type - 游标类型。
 * return: --
 * note: 设置或返回以下某个CursorTypeEnum值。
 *       常量                         说明 
 *       =============================================================================================
 *       AdOpenForwardOnly           仅向前游标，默认值。除了只能在记录中向前滚动外，与静态游标相同。
 *                                   当只需要在记录集中单向移动时，使用它可提高性能。 
 *       AdOpenKeyset                键集游标。尽管从您的记录集不能访问其他用户删除的记录，但除无法
 *                                   查看其他用户添加的记录外，键集游标与动态游标相似。仍然可以看见
 *                                   其他用户更改的数据。 
 *       AdOpenDynamic               动态游标。可以看见其他用户所作的添加、更改和删除。允许在记录集中
 *                                   进行所有类型的移动，但不包括提供者不支持的书签操作。 
 *       AdOpenStatic                静态游标。可以用来查找数据或生成报告的记录集合的静态副本。另外，
 *                                   对其他用户所作的添加、更改或删除不可见。 
 *       ==============================================================================================
 * remark: 使用 CursorType 属性可指定打开 Recordset 对象时应该使用的游标类型。Recordset 关闭时 CursorType 属性为读/写，
 *         而 Recordset 打开时该属性为只读。如果将 CursorLocation 属性设置为 adUseClient 则只支持 adUseStatic 的设置。
 *         如果设置了不支持的值，不会导致错误，将使用最接近支持的 CursorType。如果提供者不支持所请求的游标类型，提供者可能会
 *         返回其他游标类型。打开 Recordset 对象时，将更改 CursorType 属性使之与实际使用的游标匹配。要验证返回游标的指定功能，
 *         请使用 Supports 方法。关闭 Recordset 后，CursorType 属性将恢复为最初的设置。
 *         下表说明每个游标类型所需的提供者功能（由 Supports 方法常量标识）。 
 *         ====================================================================================================
 *         对于该 CursorType 的某Recordset                 对于所有这些常量， Supports 方法必须返回 True 
 *         AdOpenForwardOnly                              无 
 *         AdOpenKeyset                                  AdBookmark、adHoldRecords、adMovePrevious、adResync 
 *         AdOpenDynamic                                 adMovePrevious 
 *         AdOpenStatic                                  adBookmark, adHoldRecords, adMovePrevious, adResync 
 *         ====================================================================================================
 *         注意: 尽管对于动态游标和仅向前游标 Supports(adUpdateBatch) 可能是真，但对于批处理更新应使用键集游标或静态游标。
 *              请将 LockType 属性设置为 adLockBatchOptimistic，然后将 CursorLocation 属性设置为 adUseClient 以启用
 *              批更新需要的 OLE DB 游标服务。
 *        【远程数据服务】 当用于客户端 (ADOR) Recordset 对象时，只能将 CursorType 属性设置为 adOpenStatic。
 */
void MtADORecordset::set_cursor_type(const ADODB::CursorTypeEnum type){
	clear_last_error();
	try{
		_recordset->PutCursorType(type);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_cursor_type
 * brief: 获取在Recordset对象中使用的游标类型。
 * param: --
 * return: 返回在Recordset对象中使用的游标类型。
 * note: 设置或返回以下某个CursorTypeEnum值。
 *       常量                         说明 
 *       =============================================================================================
 *       AdOpenForwardOnly           仅向前游标，默认值。除了只能在记录中向前滚动外，与静态游标相同。
 *                                   当只需要在记录集中单向移动时，使用它可提高性能。 
 *       AdOpenKeyset                键集游标。尽管从您的记录集不能访问其他用户删除的记录，但除无法
 *                                   查看其他用户添加的记录外，键集游标与动态游标相似。仍然可以看见
 *                                   其他用户更改的数据。 
 *       AdOpenDynamic               动态游标。可以看见其他用户所作的添加、更改和删除。允许在记录集中
 *                                   进行所有类型的移动，但不包括提供者不支持的书签操作。 
 *       AdOpenStatic                静态游标。可以用来查找数据或生成报告的记录集合的静态副本。另外，
 *                                   对其他用户所作的添加、更改或删除不可见。 
 *       ==============================================================================================
 * remark: 使用 CursorType 属性可指定打开 Recordset 对象时应该使用的游标类型。Recordset 关闭时 CursorType 属性为读/写，
 *         而 Recordset 打开时该属性为只读。如果将 CursorLocation 属性设置为 adUseClient 则只支持 adUseStatic 的设置。
 *         如果设置了不支持的值，不会导致错误，将使用最接近支持的 CursorType。如果提供者不支持所请求的游标类型，提供者可能会
 *         返回其他游标类型。打开 Recordset 对象时，将更改 CursorType 属性使之与实际使用的游标匹配。要验证返回游标的指定功能，
 *         请使用 Supports 方法。关闭 Recordset 后，CursorType 属性将恢复为最初的设置。
 *         下表说明每个游标类型所需的提供者功能（由 Supports 方法常量标识）。 
 *         ====================================================================================================
 *         对于该 CursorType 的某Recordset                 对于所有这些常量， Supports 方法必须返回 True 
 *         AdOpenForwardOnly                              无 
 *         AdOpenKeyset                                  AdBookmark、adHoldRecords、adMovePrevious、adResync 
 *         AdOpenDynamic                                 adMovePrevious 
 *         AdOpenStatic                                  adBookmark, adHoldRecords, adMovePrevious, adResync 
 *         ====================================================================================================
 *         注意: 尽管对于动态游标和仅向前游标 Supports(adUpdateBatch) 可能是真，但对于批处理更新应使用键集游标或静态游标。
 *              请将 LockType 属性设置为 adLockBatchOptimistic，然后将 CursorLocation 属性设置为 adUseClient 以启用
 *              批更新需要的 OLE DB 游标服务。
 *        【远程数据服务】 当用于客户端 (ADOR) Recordset 对象时，只能将 CursorType 属性设置为 adOpenStatic。
 */
ADODB::CursorTypeEnum MtADORecordset::get_cursor_type() const{
	clear_last_error();
	try{
		return(_recordset->GetCursorType());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adOpenForwardOnly);
	}
}

/**
 * name: set_data_member 
 * breif: 设置从 DataSource 属性所引用的对象中检索的数据成员的名称。
 * param: member - 成员名称。
 * return: --
 * remark: 该属性用于通过“数据环境”创建数据绑定控件。“数据环境”保存着数据集合（数据源），
 *         而数据集合包含将被表示为 Recordset 对象的已命名对象（数据成员）。DataMember 和 
 *         DataSource 属性必须连同使用。DataMember 属性决定将把 DataSource 属性所指定的
 *         哪个对象作为 Recordset 对象提取出来。设置该属性前必须关闭 Recordset 对象。如果
 *         在设置 DataSource 属性前没有设置 DataMember 属性，或者在 DataSource 属性中指
 *         定的对象不能识别 DataMember 名称，都将产生错误。详细信息，请参阅“Data Access SDK”
 *         的“Control Writer”部分内容。
 */
void MtADORecordset::set_data_member(const CString &member){
	clear_last_error();
	try{
		_recordset->PutDataMember(static_cast<_bstr_t>(member));
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_data_member 
 * breif: 获取从 DataSource 属性所引用的对象中检索的数据成员的名称。
 * param: --
 * return: 返回从 DataSource 属性所引用的对象中检索的数据成员的名称。
 * remark: 该属性用于通过“数据环境”创建数据绑定控件。“数据环境”保存着数据集合（数据源），
 *         而数据集合包含将被表示为 Recordset 对象的已命名对象（数据成员）。DataMember 和 
 *         DataSource 属性必须连同使用。DataMember 属性决定将把 DataSource 属性所指定的
 *         哪个对象作为 Recordset 对象提取出来。设置该属性前必须关闭 Recordset 对象。如果
 *         在设置 DataSource 属性前没有设置 DataMember 属性，或者在 DataSource 属性中指
 *         定的对象不能识别 DataMember 名称，都将产生错误。详细信息，请参阅“Data Access SDK”
 *         的“Control Writer”部分内容。
 */
CString MtADORecordset::get_data_member() const{
	clear_last_error();
	try{
		return(static_cast<LPCTSTR>(_recordset->GetDataMember()));
	}catch(const _com_error &error){
		record_last_error(error);
		return(_T(""));
	}
}

/**
 * name: get_data_source
 * brief: 指定所包含的数据将被表示为 Recordset 对象的对象。
 * param: --
 * return: 返回指定所包含的数据将被表示为 Recordset 对象的对象。
 * remark: 该属性用于通过“数据环境”创建数据绑定控件。“数据环境”保存着数据集合（数据源），
 *         而数据集合包含将被表示为Recordset对象的已命名对象（数据成员）。DataMember 和 
 *         DataSource 属性必须连同使用。所引用的对象必须执行 IDataSource 接口，并且必须
 *         包含 IRowset 接口。详细信息，请参阅“Data Access SDK”的“Control Writer”部分
 *         内容。
 */
IUnknownPtr MtADORecordset::get_data_source() const{
	clear_last_error();
	try{
		return(_recordset->GetDataSource());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: get_edit_mode
 * brief: 获取当前记录的编辑状态。
 * param: --
 * return: 返回当前记录的编辑状态。
 * note: 返回如下某个 EditModeEnum 值。
 *       常量                     说明 
 *       =============================================================================================
 *       AdEditNone              指示当前没有编辑操作。 
 *       AdEditInProgress        指示当前记录中的数据已被修改但未保存。 
 *       AdEditAdd               指示 AddNew 方法已被调用，且复制缓冲区中的当前记录是尚未保存到数据库中的新记录 。 
 *       AdEditDelete            指示当前记录已被删除。 
 *       =============================================================================================
 * remark: ADO 维护与当前记录关联的编辑缓冲区。该属性指示是否对该缓冲进行了更改，或是否已创建了新的记录。使用 EditMode 
 *         属性可确定当前记录的编辑状态。如果编辑进程被中断，可以对挂起的更改进行测试，并确定是否需要使用 Update 方法或 
 *         CancelUpdate 方法。有关不同编辑条件下 EditMode 属性的详细说明，请参考 AddNew 方法。
 */
ADODB::EditModeEnum MtADORecordset::get_edit_mode() const{
	clear_last_error();
	try{
		return(_recordset->GetEditMode());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adEditNone);
	}
}

/**
 * name: set_filter
 * brief: 为 Recordset 中的数据指定筛选条件。
 * param: filter - 指定的筛选条件。
 * return: --
 * note: 设置或返回变体型值，该值包含以下某项内容： 
 *       条件字符串 — 由一个或多个用 AND 或 OR 操作符连接的子句组成的字符串。
 *       书签数组 — 指向 Recordset 对象中记录的唯一书签值数组。
 *       以下某个 FilterGroupEnum 值。常数 说明 
 *       AdFilterNone 删除当前筛选条件并恢复查看的所有记录。 
 *       AdFilterPendingRecords 允许只查看已更改且尚未发送到服务器的记录。只能应用于批更新模式。 
 *       AdFilterAffectedRecords 允许只查看上一次 Delete、Resync、UpdateBatch 或 CancelBatch 调用所影响的记录。 
 *       AdFilterFetchedRecords 允许查看当前缓冲区中的记录，即上一次从数据库中检索记录的调用结果。 
 *       AdFilterConflictingRecords 允许查看在上一次批更新中失败的记录。 
 * remark: 使用 Filter 属性可选择性地屏蔽 Recordset 对象中的记录，已筛选的 Recordset 将成为当前游标。这将影响基于当
 *         前游标返回值的其他属性，如 AbsolutePosition、AbsolutePage、RecordCount 和 PageCount，因为将 Filter 属性
 *         设置为特定值可将当前记录移动到满足新值的第一个记录。条件字符串由 FieldName-Operator-Value 格式（如“LastName = 
 *         'Smith'”）的子句组成。可以创建用单独的 AND（如“LastName = 'Smith' AND FirstName = 'John'”）或 OR（如“LastName = 
 *         'Smith' OR LastName = 'Jones'”）子句连接而成的混合子句。对于条件字符串请遵循以下规则： FieldName 必须为 Recordset 中
 *         的有效字段名。如果字段名包含空格，必须用方括号将字段名括起来。Operator 必须使用的操作符为：<、>、<=、>=、<>、= 或 LIKE。
 *         Value 是用于与字段值（如 'Smith'、#8/24/95#、12.345 或 $50.00）进行比较的值。字符串使用单引号而日期使用井号 (#)，对于数字，
 *         可以使用小数点、货币符号和科学记数法。如果 Operator 为 LIKE，Value 则可使用通配符。只允许使用星号 (*) 和百分号 (%) 通配符，
 *         而且必须为字符串的尾字符。Value 不可为 Null。AND 和 OR 在级别上没有先后之分。可使用括号将子句分组。但不能象以下示例那样先将由 
 *         OR 联接的子句分组，然后将该组用 and 联接到其他子句。(LastName = 'Smith' OR LastName = 'Jones') AND FirstName = 'John'
 *         与之相反，可以构造如下形式的筛选：(LastName = 'Smith' AND FirstName = 'John') OR (LastName = 'Jones' AND FirstName = 
 *         'John')在 LIKE 子句中，可在样式的开头和结尾使用通配符（如 LastName Like '*mit*'），或者只在结尾使用通配符（如，LastName Like 
 *         'Smit*'） 。 通过仅允许查看（例如）上次调用 UpdateBatch 方法时受到影响的记录，筛选常量使得在批更新模式时所发生的单个记录冲突更易
 *         于解决。设置 Filter 属性本身可能会因与基本数据发生冲突（如某记录已被其他用户删除）而失败。在此情况下，提供者将返回对 Errors 集合的
 *         警告但不停止程序执行。只有在所有需要的记录上发生冲突时才产生运行时错误。使用 Status 属性可定位发生冲突的记录。将 Filter 属性设置为
 *         零长度字符串 ("") 与使用 adFilterNone 常量具有同样效果。一旦设置 Filter 属性，当前记录位置将移动到 Recordset 中已筛选记录子集中
 *         的第一个记录。类似地，清除 Filter 属性后，当前记录位置将移动到 Recordset 的第一个记录。有关可与 Filter 属性一起使用创建数组的书签
 *         值的解释，请参考 Bookmark 属性。
 */
void MtADORecordset::set_filter(const _variant_t &filter){
	clear_last_error();
	try{
		_recordset->PutFilter(filter);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_filter
 * brief: 获取 Recordset 中的数据指定筛选条件。
 * param: filter - 指定的筛选条件。
 * return: 返回 Recordset 中的数据指定筛选条件。
 * note: 设置或返回变体型值，该值包含以下某项内容： 
 *       条件字符串 — 由一个或多个用 AND 或 OR 操作符连接的子句组成的字符串。
 *       书签数组 — 指向 Recordset 对象中记录的唯一书签值数组。
 *       以下某个 FilterGroupEnum 值。常数 说明 
 *       AdFilterNone 删除当前筛选条件并恢复查看的所有记录。 
 *       AdFilterPendingRecords 允许只查看已更改且尚未发送到服务器的记录。只能应用于批更新模式。 
 *       AdFilterAffectedRecords 允许只查看上一次 Delete、Resync、UpdateBatch 或 CancelBatch 调用所影响的记录。 
 *       AdFilterFetchedRecords 允许查看当前缓冲区中的记录，即上一次从数据库中检索记录的调用结果。 
 *       AdFilterConflictingRecords 允许查看在上一次批更新中失败的记录。 
 * remark: 使用 Filter 属性可选择性地屏蔽 Recordset 对象中的记录，已筛选的 Recordset 将成为当前游标。这将影响基于当
 *         前游标返回值的其他属性，如 AbsolutePosition、AbsolutePage、RecordCount 和 PageCount，因为将 Filter 属性
 *         设置为特定值可将当前记录移动到满足新值的第一个记录。条件字符串由 FieldName-Operator-Value 格式（如“LastName = 
 *         'Smith'”）的子句组成。可以创建用单独的 AND（如“LastName = 'Smith' AND FirstName = 'John'”）或 OR（如“LastName = 
 *         'Smith' OR LastName = 'Jones'”）子句连接而成的混合子句。对于条件字符串请遵循以下规则： FieldName 必须为 Recordset 中
 *         的有效字段名。如果字段名包含空格，必须用方括号将字段名括起来。Operator 必须使用的操作符为：<、>、<=、>=、<>、= 或 LIKE。
 *         Value 是用于与字段值（如 'Smith'、#8/24/95#、12.345 或 $50.00）进行比较的值。字符串使用单引号而日期使用井号 (#)，对于数字，
 *         可以使用小数点、货币符号和科学记数法。如果 Operator 为 LIKE，Value 则可使用通配符。只允许使用星号 (*) 和百分号 (%) 通配符，
 *         而且必须为字符串的尾字符。Value 不可为 Null。AND 和 OR 在级别上没有先后之分。可使用括号将子句分组。但不能象以下示例那样先将由 
 *         OR 联接的子句分组，然后将该组用 and 联接到其他子句。(LastName = 'Smith' OR LastName = 'Jones') AND FirstName = 'John'
 *         与之相反，可以构造如下形式的筛选：(LastName = 'Smith' AND FirstName = 'John') OR (LastName = 'Jones' AND FirstName = 
 *         'John')在 LIKE 子句中，可在样式的开头和结尾使用通配符（如 LastName Like '*mit*'），或者只在结尾使用通配符（如，LastName Like 
 *         'Smit*'） 。 通过仅允许查看（例如）上次调用 UpdateBatch 方法时受到影响的记录，筛选常量使得在批更新模式时所发生的单个记录冲突更易
 *         于解决。设置 Filter 属性本身可能会因与基本数据发生冲突（如某记录已被其他用户删除）而失败。在此情况下，提供者将返回对 Errors 集合的
 *         警告但不停止程序执行。只有在所有需要的记录上发生冲突时才产生运行时错误。使用 Status 属性可定位发生冲突的记录。将 Filter 属性设置为
 *         零长度字符串 ("") 与使用 adFilterNone 常量具有同样效果。一旦设置 Filter 属性，当前记录位置将移动到 Recordset 中已筛选记录子集中
 *         的第一个记录。类似地，清除 Filter 属性后，当前记录位置将移动到 Recordset 的第一个记录。有关可与 Filter 属性一起使用创建数组的书签
 *         值的解释，请参考 Bookmark 属性。
 */
_variant_t MtADORecordset::get_filter() const{
	clear_last_error();
	try{
		return(_recordset->GetFilter());
	}catch(const _com_error &error){
		record_last_error(error);
		return(vtMissing);
	}
}

/**
 * name: set_lock_type
 * brief: 设置编辑过程中对记录使用的锁定类型。
 * param: type - 锁定类型。
 * return: --
 * note: 设置或返回以下某个 LockTypeEnum 的值。
 *       常量                          说明
 *       ===============================================================================================================
 *       adLockReadOnly               默认值，只读。无法更改数据。 
 *       adLockPessimistic            保守式记录锁定（逐条）。提供者执行必要的操作确保成功编辑记录，
 *                                    通常采用编辑时立即锁定数据源的记录的方式。 
 *       adLockOptimistic             开放式记录锁定（逐条）。提供者使用开放式锁定，只在调用 Update 方法时锁定记录。 
 *       adLockBatchOptimistic        开放式批更新。用于与立即更新模式相反的批更新模式。 
 *       ===============================================================================================================
 * remark: 打开 Recordset 前设置 LockType 属性可指定打开时提供者应该使用的锁定类型。读取该属性可返回在打开的 Recordset 
 *         对象上正在使用的锁定类型。Recordset 关闭时 LockType 属性为读/写，打开时该属性为只读。提供者可能不支持所有的锁
 *         定类型。如果某提供者不支持所需的 LockType 设置，则将替换为其他类型的锁定。要确定 Recordset 对象可用的实际锁定
 *         功能，请通过 adUpdate 和 adUpdateBatch 使用 Supports 方法。如果 CursorLocation 属性被设置为 adUseClient，
 *         将不支持 adLockPessimistic 设置。设置不支持的值不会产生错误，因为此时将使用支持的最接近的 LockType 的值。
 */
void MtADORecordset::set_lock_type(const ADODB::LockTypeEnum type){
	clear_last_error();
	try{
		_recordset->PutLockType(type);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_lock_type
 * brief: 获取编辑过程中对记录使用的锁定类型。
 * param: --
 * return: 获取编辑过程中对记录使用的锁定类型。
 * note: 设置或返回以下某个 LockTypeEnum 的值。
 *       常量                          说明
 *       ===============================================================================================================
 *       adLockReadOnly               默认值，只读。无法更改数据。 
 *       adLockPessimistic            保守式记录锁定（逐条）。提供者执行必要的操作确保成功编辑记录，
 *                                    通常采用编辑时立即锁定数据源的记录的方式。 
 *       adLockOptimistic             开放式记录锁定（逐条）。提供者使用开放式锁定，只在调用 Update 方法时锁定记录。 
 *       adLockBatchOptimistic        开放式批更新。用于与立即更新模式相反的批更新模式。 
 *       ===============================================================================================================
 * remark: 打开 Recordset 前设置 LockType 属性可指定打开时提供者应该使用的锁定类型。读取该属性可返回在打开的 Recordset 
 *         对象上正在使用的锁定类型。Recordset 关闭时 LockType 属性为读/写，打开时该属性为只读。提供者可能不支持所有的锁
 *         定类型。如果某提供者不支持所需的 LockType 设置，则将替换为其他类型的锁定。要确定 Recordset 对象可用的实际锁定
 *         功能，请通过 adUpdate 和 adUpdateBatch 使用 Supports 方法。如果 CursorLocation 属性被设置为 adUseClient，
 *         将不支持 adLockPessimistic 设置。设置不支持的值不会产生错误，因为此时将使用支持的最接近的 LockType 的值。
 */
ADODB::LockTypeEnum MtADORecordset::get_lock_type() const{
	clear_last_error();
	try{
		return(_recordset->GetLockType());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adLockReadOnly);
	}
}

/**
 * name: set_marshal_options
 * brief: 设置要被调度返回服务器的记录。
 * param: options - 要被调度返回服务器的记录。
 * return: 返回要被调度返回服务器的记录。
 * note: 设置或返回以下某常量的长整型值。
 *       常量                       说明 
 *       =================================================================
 *       AdMarshalAll              默认值。表明所有行将返回到服务器。 
 *       AdMarshalModifiedOnly     表明只有已修改的行返回到服务器。
 *       =================================================================
 * remark: 当使用客户端 (ADOR) Recordset 时，已在客户端被修改的记录将通过称作“调度”的技术写回中间层或 Web 服务器。
 *         调度是指越过线程或进程边界包装和发送接口方法参数的过程。当已修改的远程数据通过调度被更新回中间层或 Web 服务器时，
 *         设置 MarshalOptions 属性可以提高性能。
 *        【远程数据服务】 该属性只能在客户端 (ADOR) Recordset 上使用。
 */
void MtADORecordset::set_marshal_options(const ADODB::MarshalOptionsEnum options){
	clear_last_error();
	try{
		_recordset->PutMarshalOptions(options);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_marshal_options
 * brief: 获取要被调度返回服务器的记录。
 * param: --
 * return: 返回要被调度返回服务器的记录。
 * note: 设置或返回以下某常量的长整型值。
 *       常量                       说明 
 *       =================================================================
 *       AdMarshalAll              默认值。表明所有行将返回到服务器。 
 *       AdMarshalModifiedOnly     表明只有已修改的行返回到服务器。
 *       =================================================================
 * remark: 当使用客户端 (ADOR) Recordset 时，已在客户端被修改的记录将通过称作“调度”的技术写回中间层或 Web 服务器。
 *         调度是指越过线程或进程边界包装和发送接口方法参数的过程。当已修改的远程数据通过调度被更新回中间层或 Web 服务器时，
 *         设置 MarshalOptions 属性可以提高性能。
 *        【远程数据服务】 该属性只能在客户端 (ADOR) Recordset 上使用。
 */
ADODB::MarshalOptionsEnum MtADORecordset::get_marshal_options() const{
	clear_last_error();
	try{
		return(_recordset->GetMarshalOptions());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adMarshalAll);
	}
}

/**
 * name: set_max_records
 * brief: 设置通过查询返回 Recordset 的记录的最大数目。
 * param: records - 最大记录数。
 * return: --
 * note: 设置或返回长整型值。默认值为零（没有限制）。
 * remark: 使用 MaxRecords 属性可对提供者从数据源返回的记录数加以限制。
 *         该属性的默认设置为零，表明提供者返回所有所需的记录。Recordset 关闭时，
 *         MaxRecords 属性为读/写，打开时为只读。
 */
void MtADORecordset::set_max_records(const long records){
	clear_last_error();
	try{
		_recordset->PutMaxRecords(records);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_max_records
 * brief: 获取通过查询返回 Recordset 的记录的最大数目。
 * param: --
 * return: 返回通过查询返回 Recordset 的记录的最大数目。
 * note: 设置或返回长整型值。默认值为零（没有限制）。
 * remark: 使用 MaxRecords 属性可对提供者从数据源返回的记录数加以限制。
 *         该属性的默认设置为零，表明提供者返回所有所需的记录。Recordset 关闭时，
 *         MaxRecords 属性为读/写，打开时为只读。
 */
long MtADORecordset::get_max_records() const{
	clear_last_error();
	try{
		return(_recordset->GetMaxRecords());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: get_page_count
 * brief: 获取 Recordset 对象包含的数据页数。
 * param: --
 * return: 返回 Recordset 对象包含的数据页数。
 * note: 返回长整型值。
 * remark: 使用 PageCount 属性可确定 Recordset 对象中数据的页数。
 *         “页”是大小等于 PageSize 属性设置的记录组。即使最后页不完整，
 *         由于记录数比 PageSize 值少，该页也会作为 PageCount 值中的附加页进行计数。
 *         如果 Recordset 对象不支持该属性，该值为-1 以表明 PageCount 无法确定。有
 *         关页的功能的详细信息，请参阅 PageSize 和 AbsolutePage 属性。
 */
long MtADORecordset::get_page_count() const{
	clear_last_error();
	try{
		return(_recordset->GetPageCount());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: set_page_size
 * brief: 设置 Recordset 中一页所包含的记录数。
 * param: size - 一页所包含的记录数。
 * return: --
 * note: 设置或返回长整型值，该值指示某页上的记录数。默认值为 10。
 * remark: 使用 PageSize 属性可确定组成逻辑数据页的记录数。建立
 *         页的大小允许使用 AbsolutePage 属性移动到特定页的第一个记录。
 *         在您希望允许用户对数据进行分页时，该属性在 Web-服务器方案中非常有用，
 *         可用来在某一时刻查看一定数量的记录。随时可以设置该属性，其值将用来计
 *         算特定页第一个记录的位置。
 */
void MtADORecordset::set_page_size(const long size){
	clear_last_error();
	try{
		_recordset->PutPageSize(size);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_page_size
 * brief: 获取 Recordset 中一页所包含的记录数。
 * param: --
 * return: 返回 Recordset 中一页所包含的记录数。
 * note: 设置或返回长整型值，该值指示某页上的记录数。默认值为 10。
 * remark: 使用 PageSize 属性可确定组成逻辑数据页的记录数。建立
 *         页的大小允许使用 AbsolutePage 属性移动到特定页的第一个记录。
 *         在您希望允许用户对数据进行分页时，该属性在 Web-服务器方案中非常有用，
 *         可用来在某一时刻查看一定数量的记录。随时可以设置该属性，其值将用来计
 *         算特定页第一个记录的位置。
 */
long MtADORecordset::get_page_size() const{
	clear_last_error();
	try{
		return(_recordset->GetPageSize());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: get_record_count
 * brief: 获取 Recordset 对象中记录的当前数目。
 * param: --
 * return: 返回 Recordset 对象中记录的当前数目。
 * note: 返回长整型值。
 * remark: 使用 RecordCount 属性可确定 Recordset 对象中记录的数目。ADO 无法确定记录数时，
 *         或者如果提供者或游标类型不支持 RecordCount，则该属性返回 –1。读已关闭的 Recordset 上的 RecordCount 属性将产生错误。
 *         如果 Recordset 对象支持近似定位或书签（即 Supports (adApproxPosition) 或 Supports (adBookmark) 各自返回 True），
 *         不管是否完全填充该值，该值将为 Recordset 中记录的精确数目。如果 Recordset 对象不支持近似定位，该属性可能由于必须对所有
 *         记录进行检索和计数以返回精确 RecordCount 值而严重消耗资源。Recordset 对象的游标类型会影响是否能够确定记录的数目。对仅
 *         向前游标，RecordCount 属性将返回 -1，对静态或键集游标返回实际计数，对动态游标取决于数据源返回 -1 或实际计数。
 */
long MtADORecordset::get_record_count() const{
	clear_last_error();
	try{
		return(_recordset->GetRecordCount());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: set_sort
 * brief: 指定一个或多个 Recordset 以之排序的字段名，并指定按升序还是降序对字段进行排序。
 * param: sort - 排序字符串。
 * return: --
 * note: 设置或返回以之排序的用逗号分隔的字段名字符串，其中的每个名称是 Recordset 中的 Field。
 *       可以选择后跟空格和用于指定字段排序顺序的关键字 ASC 或 DESC。 
 * remark: 实际上数据并没有重新排列，只是简单地按排序的顺序进行访问。如果 CursorLocation 属性被设置为 
 *         adUseClient，并且索引尚不存在，则将为 Sort 属性中指定的每个字段创建临时索引。将 Sort 属性
 *         设置为空字符串将使行重置为原始顺序，并删除临时索引。现存索引将不被删除。由于与关键字 ASC 和 
 *         DESC 发生冲突，字段无法命名为“ASC”或“DESC”。请通过在返回 Recordset 的查询中使用 AS 关键字，
 *         来给使用发生名称冲突的字段设置别名。
 */
void MtADORecordset::set_sort(const CString &sort){
	clear_last_error();
	try{
		_recordset->PutSort(static_cast<LPCTSTR>(sort));
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_sort
 * brief: 获取一个或多个 Recordset 以之排序的字段名，并指定按升序还是降序对字段进行排序。
 * param: --
 * return: 返回一个或多个 Recordset 以之排序的字段名，并指定按升序还是降序对字段进行排序。
 * note: 设置或返回以之排序的用逗号分隔的字段名字符串，其中的每个名称是 Recordset 中的 Field。
 *       可以选择后跟空格和用于指定字段排序顺序的关键字 ASC 或 DESC。 
 * remark: 实际上数据并没有重新排列，只是简单地按排序的顺序进行访问。如果 CursorLocation 属性被设置为 
 *         adUseClient，并且索引尚不存在，则将为 Sort 属性中指定的每个字段创建临时索引。将 Sort 属性
 *         设置为空字符串将使行重置为原始顺序，并删除临时索引。现存索引将不被删除。由于与关键字 ASC 和 
 *         DESC 发生冲突，字段无法命名为“ASC”或“DESC”。请通过在返回 Recordset 的查询中使用 AS 关键字，
 *         来给使用发生名称冲突的字段设置别名。
 */
CString MtADORecordset::get_sort() const{
	clear_last_error();
	try{
		return(static_cast<LPCTSTR>(_recordset->GetSort()));
	}catch(const _com_error &error){
		record_last_error(error);
		return(_T(""));
	}
}

/**
 * name: set_source
 * brief: 指示 Recordset 对象中数据的来源（Command 对象、SQL 语句、表的名称或存储过程）。
 * param: source - 数据的来源。
 * return: --
 * note: 设置字符串值或 Command 对象引用。仅返回字符串值。
 * remark: 使用 Source 属性指定 Recordset 对象的数据源，该 Recordset 对象使用下列项之一：
 *         Command 对象变量、SQL 语句、存储过程或表的名称。Source 属性对于关闭的 Recordset 
 *         是可读/写的，对于打开的 Recordset 是只读的。如果设置 Source 属性为 Command 对象，
 *         Recordset 对象的 ActiveConnection 属性将继承指定 Command 对象的 ActiveConnection 
 *         属性的值。但是，读取 Source 属性将不返回 Command 对象，而是将 Command 对象的 CommandText 
 *         属性返回到设置 Source 属性的地方。如果 Source 属性是一个 SQL 语句、存储过程或表的名称，
 *         则可以通过调用 Open 方法传递相应的 Options 参数来优化性能。
 */
void MtADORecordset::set_source(const CString &source){
	clear_last_error();
	try{
		_recordset->PutSource(static_cast<LPCTSTR>(source));
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_source
 * brief: 获取 Recordset 对象中数据的来源（Command 对象、SQL 语句、表的名称或存储过程）。
 * param: --
 * return: 返回 Recordset 对象中数据的来源（Command 对象、SQL 语句、表的名称或存储过程）。
 * note: 设置字符串值或 Command 对象引用。仅返回字符串值。
 * remark: 使用 Source 属性指定 Recordset 对象的数据源，该 Recordset 对象使用下列项之一：
 *         Command 对象变量、SQL 语句、存储过程或表的名称。Source 属性对于关闭的 Recordset 
 *         是可读/写的，对于打开的 Recordset 是只读的。如果设置 Source 属性为 Command 对象，
 *         Recordset 对象的 ActiveConnection 属性将继承指定 Command 对象的 ActiveConnection 
 *         属性的值。但是，读取 Source 属性将不返回 Command 对象，而是将 Command 对象的 CommandText 
 *         属性返回到设置 Source 属性的地方。如果 Source 属性是一个 SQL 语句、存储过程或表的名称，
 *         则可以通过调用 Open 方法传递相应的 Options 参数来优化性能。
 */
_variant_t MtADORecordset::get_source() const{
	clear_last_error();
	try{
		return(_recordset->GetSource());
	}catch(const _com_error &error){
		record_last_error(error);
		return(vtMissing);
	}
}

/**
 * name: get_state
 * brief: 获取当前 Recordset 对象状态。
 * param: --
 * return: 返回当前 Recordset 对象状态。
 * note: 对所有可应用对象，说明其对象状态是打开或是关闭。对执行异步方法的 Recordset 对象，
 *       说明当前的对象状态是连接、执行或是获取。
 *       返回下列常量之一的长整型值。
 *       常量                                    说明 
 *       ========================================================================================
 *       AdStateClosed                          默认，指示对象是关闭的。 
 *       AdStateOpen                            指示对象是打开的。 
 *       AdStateConnecting                      指示 Recordset 对象正在连接。 
 *       AdStateExecuting                       指示 Recordset 对象正在执行命令。 
 *       AdStateFetching                        指示 Recordset 对象的行正在被读取。 
 *       ========================================================================================
 * remark: 可以随时使用 State 属性确定指定对象的当前状态。该属性是只读的。Recordset 对象的 State 属性可以是组合值。
 *         例如，如果正在执行语句，该属性将是 adStateOpen 和 adStateExecuting 的组合值。
 */
long MtADORecordset::get_state() const{
	clear_last_error();
	try{
		return(_recordset->GetState());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adStateClosed);
	}
}

/**
 * name: get_status
 * brief: 获取有关批更新或其他大量操作的当前记录的状态。
 * param: --
 * return: 返回有关批更新或其他大量操作的当前记录的状态。
 * note: 返回下列一个或多个 RecordStatusEnum 值之和。
 *       常量                                说明 
 *       ===============================================================================================
 *       AdRecOK                            成功地更新记录。 
 *       AdRecNew                           记录是新建的。 
 *       AdRecModified                      记录被修改。 
 *       AdRecDeleted                       记录被删除。 
 *       AdRecUnmodified                    记录没有修改。 
 *       AdRecInvalid                       由于书签无效，记录没有保存。 
 *       AdRecMultipleChanges               由于影响多个记录，因此记录未被保存。 
 *       AdRecPendingChanges                由于记录引用挂起的插入，因此未被保存。 
 *       AdRecCanceled                      由于操作被取消，未保存记录。 
 *       AdRecCantRelease                   由于现有记录锁定，没有保存新记录。 
 *       AdRecConcurrencyViolation          由于开放式并发在使用中，记录未被保存。 
 *       AdRecIntegrityViolation            由于用户违反完整性约束，记录未被保存。 
 *       AdRecMaxChangesExceeded            由于存在过多挂起更改，记录未被保存。 
 *       AdRecObjectOpen                    由于与打开的储存对象冲突，记录未被保存。 
 *       AdRecOutOfMemory                   由于计算机内存不足，记录未被保存。 
 *       AdRecPermissionDenied              由于用户没有足够的权限，记录未被保存。 
 *       AdRecSchemaViolation               由于记录违反基本数据库的结构，因此未被保存。 
 *       AdRecDBDeleted                     记录已经从数据源中删除。 
 *       =================================================================================================
 *remark: 使用 Status 属性查看在批更新中被修改的记录有哪些更改被挂起。也可使用 Status 属性查看大量操作时失败记录的状态。
 *        例如，调用 Recordset 对象的 Resync、UpdateBatch 或 CancelBatch 方法，或者设置 Recordset 对象的 Filter 
 *        属性为书签数组。使用该属性，可检查指定记录为何失败并将问题解决。
 */
long MtADORecordset::get_status() const{
	clear_last_error();
	try{
		return(_recordset->GetStatus());
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adRecOK);
	}
}

/**
 * name: set_stay_in_sync
 * brief: 在分级 Recordset 对象中指示当父行位置更改时，对基本子记录（即“子集”）的引用是否会更改。
 * param： is_stay_in_sync - 是否更改。
 * return: --
 * note: 设置或返回布尔型值。如果设置为 True，则父 Recordset 对象更改行位置时子集将更新；如果设置为 False，
 *       则子集将继续引用先前子集的数据而不管父 Recordset 对象是否更改行位置。
 * remark: 该属性应用于分级记录集，例如由 MSDataShape 提供者支持的记录集，而且必须在父 Recordset 上设置才能检索子 
 *         Recordset。此属性简化分级记录集的定位。
 */
void MtADORecordset::set_stay_in_sync(const BOOL is_stay_in_sync){
	clear_last_error();
	try{
		const short stay_in_sync=((TRUE==is_stay_in_sync)?-1:0);
		_recordset->PutStayInSync(stay_in_sync);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_stay_in_sync
 * brief: 获取在分级 Recordset 对象中指示当父行位置更改时，对基本子记录（即“子集”）的引用是否会更改。
 * param： --
 * return: 返回在分级 Recordset 对象中指示当父行位置更改时，对基本子记录（即“子集”）的引用是否会更改。
 * note: 设置或返回布尔型值。如果设置为 True，则父 Recordset 对象更改行位置时子集将更新；如果设置为 False，
 *       则子集将继续引用先前子集的数据而不管父 Recordset 对象是否更改行位置。
 * remark: 该属性应用于分级记录集，例如由 MSDataShape 提供者支持的记录集，而且必须在父 Recordset 上设置才能检索子 
 *         Recordset。此属性简化分级记录集的定位。
 */
BOOL MtADORecordset::get_stay_in_sync() const{
	clear_last_error();
	try{
		if(-1==_recordset->GetStayInSync()){
			return(TRUE);
		}else{
			return(FALSE);
		}
	}catch(const _com_error &error){
		record_last_error(error);
		return(FALSE);
	}
}

/**
 * name: get_fileds
 * brief: 获取当前记录集中的字段信息。
 * param: --
 * return: 返回当前记录集中的字段信息。
 */
ADODB::FieldsPtr MtADORecordset::get_fileds() const{
	clear_last_error();
	try{
		return(_recordset->GetFields());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: get_properties
 * brief: 获取当前记录集属性信息。
 * param: --
 * return: 返回当前记录集属性信息。
 */
ADODB::PropertiesPtr MtADORecordset::get_properties() const{
	clear_last_error();
	try{
		return(_recordset->GetProperties());
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: add_new
 * brief: 创建可更新 Recordset 对象的新记录。
 * param: field_list -  可选。新记录中字段的单个名称、一组名称或序号位置。
 *        values - 可选。新记录中字段的单个或一组值。如果 Fields 是数组，
 *                 那么 Values 也必须是有相同成员数的数组，否则将发生错误。
 *                 字段名称的次序必须与每个数组中的字段值的次序相匹配。
 * return: 返回函数执行是否成功（可以使用SUCCEEDED宏或FAILED宏来判断）。
 * remark: 使用 AddNew 方法创建和初始化新记录。通过 adAddNew 使用 Supports 方法可验证是否能够将记录添加到当前的 Recordset 对象。
 *         在调用 AddNew 方法后，新记录将成为当前记录，并在调用 Update 方法后继续保持为当前记录。如果 Recordset 对象不支持书签，
 *         当移动到其他记录时将无法对新记录进行访问。是否需要调用 Requery 方法访问新记录则取决于所使用的游标类型。如果在编辑当前记录
 *         或添加新记录时调用 AddNew，ADO 将调用 Update 方法保存任何更改并创建新记录。AddNew 方法的行为取决于 Recordset 对象的更
 *         新模式以及是否传送 Fields 和 Values 参数。在立即更新模式（调用 Update 方法时提供者会立即将更改写入基本数据源）下，调用不
 *         带参数的 AddNew 方法可将 EditMode 属性设置为 adEditAdd。提供者将任何字段值的更改缓存在本地。调用 Update 方法可将新记录
 *         传递到数据库并将 EditMode 属性重置为 adEditNone。如果传送了 Fields 和 Values 参数，ADO 则立即将新记录传递到数据库（无
 *         须调用 Update），且 EditMode 属性值没有改变 (adEditNone)。在批更新模式（提供者缓存多个更改并只在调用 UpdateBatch 时将
 *         其写入基本数据源）下，调用不带参数的 AddNew 方法可将 EditMode 属性设置为 adEditAdd。提供者将任何字段值的更改缓存在本地。
 *         调用 Update 方法可将新的记录添加到当前记录集并将 EditMode 属性重置为 adEditNone，但在调用 UpdateBatch 方法之前提供者
 *         不将更改传递到基本数据库。如果传送 Fields 和 Values 参数，ADO 则将新记录发送给提供者以便缓存；需要调用 UpdateBatch 方法将
 *         新记录传递到基本数据库。
 *         如果 Unique Table 动态属性被设置，并且 Recordset 是对多个表执行 JOIN 操作的结果，那么，AddNew 方法只能将字段插入到由 
 *         Unique Table 属性所命名的表中。
 */
HRESULT MtADORecordset::add_new(const _variant_t &field_list/*=vtMissing*/,const _variant_t &values/*=vtMissing*/){
	clear_last_error();
	try{
		return(_recordset->AddNew(field_list,values));
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: cancel
 * brief: 取消执行挂起的异步 Execute 或 Open 方法的调用。
 * param: --
 * return: 返回函数执行是否成功（可以使用SUCCEEDED宏或FAILED宏来判断）。
 * remark: 使用 Cancel 方法终止执行异步 Execute 或 Open 方法调用（即通过 adAsyncConnect、adAsyncExecute
 *         或 adAsyncFetch 选项调用该方法）。如果在试图终止的方法中没有使用 adAsyncExecute，则 Cancel 将返
 *         回运行时错误。
 *         下表显示在特定类型对象上使用 Cancel 方法时将终止的任务。
 *         如果对象为                                       将终止对该方法的上一次异步调用 
 *         =======================================================================================
 *         Command                                         Execute 
 *         Connection                                      Execute 或 Open 
 *         Recordset                                       Open 
 *         =======================================================================================
 */
HRESULT MtADORecordset::cancel(){
	clear_last_error();
	try{
		return(_recordset->Cancel());
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: cancel_bantch
 * brief: 取消挂起的批更新。
 * param: affect_records - 可选的 AffectEnum 值，决定 CancelBatch 方法所影响记录的数目，可为下列常量之一：
 *        常量                                         说明 
 *        =========================================================================================================
 *        AdAffectCurrent                             仅取消当前记录的挂起更新。 
 *        AdAffectGroup                               对满足当前 Filter 属性设置的记录取消挂起更新。使用该选项时，
 *                                                    必须将 Filter 属性设置为合法的预定义常量之一。 
 *        AdAffectAll                                 默认值。取消 Recordset 对象中所有记录的挂起更新，包括由当前 Filter 
 *                                                    属性设置所隐藏的任何记录。 
 *        =========================================================================================================
 * return: 返回函数执行是否成功（可以使用SUCCEEDED宏或FAILED宏来判断）。
 * remark: 使用 CancelBatch 方法可取消批更新模式下记录集中所有挂起的更新。如果记录集处于立即更新模式，调用不带 adAffectCurrent 的 
 *         CancelBatch 将产生错误。如果调用 CancelBatch 时正在编辑当前记录或添加新记录，则 ADO 首先调用 CancelUpdate 方法取消所
 *         有已被缓存的修改，然后取消记录集中挂起的所有更改。有可能在 CancelBatch 调用后，特别是在添加新记录时无法确定当前记录。为此，
 *         在 CancelBatch 调用后将当前记录位置设置为记录集中的已知位置是明智的。例如可调用 MoveFirst 方法。如果由于与基本数据冲突（
 *         如记录已被其他用户删除）而导致取消挂起更新失败，则提供者将向 Errors 集合返回警告，但不终止程序的执行。只有当所有请求的记录都
 *         发生冲突时才发生运行时错误。使用 Filter 属性 (adFilterAffectedRecords) 和 Status 属性可以对冲突记录进行定位。
 */
HRESULT MtADORecordset::cancel_bantch(const ADODB::AffectEnum affect_records/*=ADODB::adAffectAll*/){
	clear_last_error();
	try{
		return(_recordset->CancelBatch(affect_records));
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: cancel_update
 * breif: 取消在调用 Update 方法前对当前记录或新记录所作的任何更改。
 * param: --
 * return: 返回函数执行是否成功（可以使用SUCCEEDED宏或FAILED宏来判断）。
 * remark: 使用 CancelUpdate 方法可取消对当前记录所作的任何更改或放弃新添加的记录。在调用 Update 方法后将
 *         无法撤消对当前记录或新记录所做的更改，除非更改是可以用 RollbackTrans 方法回卷的事务的一部分，或者
 *         是可以用 CancelBatch 方法取消的批更新的一部分。如果在调用 CancelUpdate 方法时添加新记录，则调用 
 *         AddNew 之前的当前记录将再次成为当前记录。如果尚未更改当前记录或添加新记录，调用 CancelUpdate 方法
 *         将产生错误。
 */
HRESULT MtADORecordset::cancel_update(){
	clear_last_error();
	try{
		return(_recordset->CancelUpdate());
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: clone
 * brief: 创建与现有 Recordset 对象相同的复制 Recordset 对象。可选择指定该副本为只读。
 * param: type - 可选，LockTypeEnum 值，指定原始 Recordset 的锁定类型或只读 Recordset。
 *               常量                           说明 
 *               ======================================================================
 *               AdLockUnspecified              默认值。使用与原始类型相同的锁定类型创建副本。 
 *               AdLockReadOnly                 副本创建为只读。 
 *               ======================================================================
 * return: 返回 Recordset 对象引用。
 * remark: 使用 Clone 方法可创建多个 Recordset 对象副本，这对于希望在给定的记录组中保留多个当前记录十分有用。
 *         使用 Clone 方法比使用与初始定义相同的定义创建和打开新 Recordset 对象要有效得多。新创建副本的当前
 *         记录将设置为首记录。无论游标类型如何，对某个 Recordset 对象所作的修改在其所有副本中都是可见的。不过
 *         一旦在原始 Recordset 上执行了 Requery，副本将不再与原始 Recordset 同步。关闭原始 Recordset 时
 *         并不关闭它的副本，而关闭某个副本也将不关闭原始 Recordset 或任何其他副本。用户只允许复制支持书签的 
 *         Recordset 对象。书签值是可交换的，也就是说，来自一个 Recordset 对象的书签引用可引用其任何副本中的
 *         相同记录。
 */
ADODB::_RecordsetPtr MtADORecordset::clone(const ADODB::LockTypeEnum type){
	clear_last_error();
	try{
		return(_recordset->Clone(type));
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: close
 * brief: 关闭打开的对象及任何相关对象。
 * param: --
 * return: 返回函数执行是否成功（可以使用SUCCEEDED宏或FAILED宏来判断）。
 * remark: 使用 Close 方法可关闭 Connection 对象或 Recordset 对象以便释放所有关联的系统资源。
 *         关闭对象并非将它从内存中删除，可以更改它的属性设置并且在此后再次打开。要将对象从内存中
 *         完全删除，可将对象变量设置为 Nothing。
 *         Connection
 *         使用 Close 方法关闭 Connection 对象的同时，也将关闭与连接相关联的任何活动 Recordset 对象。
 *         与正在关闭的 Connection 对象相关联的 Command 对象将被持久保留，但不再与 Connection 对象关联，
 *         即它的 ActiveConnection 属性将被设置为 Nothing，同时，Command 对象的 Parameters 集合将清除
 *         任何提供者定义的参数。可以随后调用 Open 方法重新建立与相同数据源或其他数据源的连接，关闭 Connection 
 *         对象后，调用任何需要打开与对数据源连接的方法都将产生错误。当连接上有打开的 Recordset 对象时，关闭 
 *         Connection 对象将回卷所有 Recordset 对象的挂起更改。在事务进行过程中显式关闭 Connection 对象（
 *         调用 Close 方法）将产生错误。如果在事务进行过程中 Connection 对象超出范围，那么 ADO 将自动回卷事务。
 *         Recordset
 *         使用 Close 方法关闭 Recordset 对象的同时，将释放关联的数据和可能已经通过该特定 Recordset 对象对数据进行
 *         的独立访问。随后可调用 Open 方法重新打开具有相同属性或已修改属性的 Recordset。在 Recordset 对象关闭后，调
 *         用任何需要活动游标的方法将产生错误。如果正在立即更新模式下进行编辑，调用 Close 方法将产生错误，应首先调用 
 *         Update 或 CancelUpdate 方法。如果在批更新期间关闭 Recordset 对象，则自上次 UpdateBatch 调用以来所做的
 *         修改将全部丢失。如果使用 Clone 方法创建已打开的 Recordset 对象的副本，关闭原始 Recordset 或其副本将不影响
 *         任何其他副本。
 */
HRESULT MtADORecordset::close(){
	clear_last_error();
	try{
		return(_recordset->Close());
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: compare_bookmarks
 * brief: 比较两个书签并返回它们相差值的说明。
 * param: bookmark_left - 书签1。
 *        bookmark_right - 书签2。
 * return: 返回的值指示书签所代表的两个记录的相对行位置。可返回下列值。
 *         常量                                说明 
 *         ======================================================================
 *         AdCompareLessThan                   第一个书签在第二个之前。 
 *         AdCompareEqual                      书签相同。 
 *         AdCompareGreaterThan                第一个书签在第二个之后。 
 *         AdCompareNotEqual                   书签不相同而且未排序。 
 *         AdCompareNotComparable              无法比较书签。 
 *         ======================================================================
 * remark: 书签必须应用于相同的 Recordset 对象，或者是 Recordset 对象及其  clone。无法可靠地比
 *         较来自不同 Recordset 对象的书签，即使它们的创建来源及创建所使用的命令相同。同时，对于其
 *         基本提供者不支持比较的 Recordset 对象，也无法比较书签。书签唯一标识 Recordset 对象中的行。
 *         使用当前行的 Bookmark 属性可以获得它的书签。无效或形式错误的书签将引发错误。
 */
ADODB::CompareEnum MtADORecordset::compare_bookmarks(
	const _variant_t &bookmark_left,const _variant_t &bookmark_right){
	clear_last_error();
	try{
		return(_recordset->CompareBookmarks(bookmark_left,bookmark_right));
	}catch(const _com_error &error){
		record_last_error(error);
		return(ADODB::adCompareNotComparable);
	}
}

/**
 * name: deletes
 * brief: 删除当前记录或记录组。
 * param: affect_records - AffectEnum 值，确定 Delete 方法所影响的记录数目，该值可以是下列常量之一。
 *                         常量                               说明
 *                         ===============================================================================
 *                         AdAffectCurrent                    默认。仅删除当前记录。 
 *                         AdAffectGroup                      删除满足当前 Filter 属性设置的记录。要使用该选项，
 *                                                            必须将 Filter 属性设置为有效的预定义常量之一。 
 *                         adAffectAll                        删除所有记录。 
 *                         adAffectAllChapters                删除所有子集记录。 
 *                         ===============================================================================
 * return: 返回函数执行是否成功（可以使用SUCCEEDED宏或FAILED宏来判断）。
 * remark: 使用 Delete 方法可将 Recordset 对象中的当前记录或一组记录标记为删除。如果 Recordset 对象不允许删除记录将引发错误。
 *         使用立即更新模式将在数据库中进行立即删除，否则记录将标记为从缓存删除，实际的删除将在调用 UpdateBatch 方法时进行。（
 *         使用 Filter 属性可查看已删除的记录）。从已删除的记录中检索字段值将引发错误。删除当前记录后，在移动到其他记录之前已删除
 *         的记录将保持为当前记录。一旦离开已删除记录，则无法再次访问它。如果在事务中嵌套删除，可用 RollbackTrans 方法恢复已删除的记录。
 *         如果处于批更新模式，则可用 CancelBatch 方法取消一个或一组挂起删除。如果因与基本数据冲突而导致删除记录失败（如记录已被其他用户
 *         删除），则提供者向 Errors 集合返回警告但不终止程序执行，只有在所有提出请求的记录上发生冲突时才会产生运行时错误。
 *         如果 Unique Table 动态属性被设置，并且 Recordset 是对多个表执行 JOIN 操作的结果，那么，Delete 方法将仅删除 Unique Table 
 *         属性所命名的表中的行。
 */
HRESULT MtADORecordset::deletes(const ADODB::AffectEnum affect_records/*=ADODB::adAffectCurrent*/){
	clear_last_error();
	try{
		return(_recordset->Delete(affect_records));
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: find
 * brief: 搜索 Recordset 中满足指定标准的记录。如果满足标准，则记录集位置设置在找到的记录上，否则位置将设置在记录集的末尾。
 * param: criteria - 字符串，包含指定用于搜索的列名、比较操作符和值的语句。
 *        skip_rows - 可选，长整型值，其默认值为零，它指定当前行或 start 书签的位移以开始搜索。
 *        search_direction - 可选的 SearchDirectionEnum 值，指定搜索应从当前行还是下一个有效行开始。其值可为 adSearchForward 或 
 *                           adSearchBackward。搜索是在记录集的开始还是末尾结束由 searchDirection 值决定。
 *        start - 可选，变体型书签，用作搜索的开始位置。
 * return: 返回函数执行是否成功（可以使用SUCCEEDED宏或FAILED宏来判断）。
 * remark: criteria 中的“比较操作符”可以是“>”（大于）、“<”（小于）、“=”（等于）、“>=”（大于或等于）、“<=”（小于或等于）、“<>”（不等于）或
 *         “like”（模式匹配）。 criteria 中的值可以是字符串、浮点数或者日期。字符串值以单引号分界（如“state = 'WA'”）。日期值以“#”（数字
 *         记号）分界（如“start_date > #7/22/97#”）。如“比较操作符”为“like”，则字符串“值”可以包含“*”（某字符可出现一次或多次）或者“_”（
 *         某字符只出现一次）。（如“state like M_*”与 Maine 和 Massachusetts 匹配。）。
 */
HRESULT MtADORecordset::find(const CString &criteria,const long skip_rows,
	const ADODB::SearchDirectionEnum search_direction,const _variant_t &start/*=vtMissing*/){
	clear_last_error();
	try{
		return(_recordset->Find(
			static_cast<LPCTSTR>(criteria),skip_rows,search_direction,start));
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: get_rows
 * brief: 将 Recordset 对象的多个记录恢复到数组中。
 * param: rows - 可选，长整型表达式，指定要检索记录数。默认值为 adGetRowsRest (-1)。
 *        start - 可选，字符串或长整型，计算得到在 GetRows 操作开始处的记录的书签。也可使用下列 BookmarkEnum 值。
 *                常量                                  说明 
 *                ====================================================================================
 *                AdBookmarkCurrent                     从当前记录开始。 
 *                AdBookmarkFirst                       从首记录开始。 
 *                AdBookmarkLast                        从尾记录开始。 
 *                ====================================================================================
 *        fields - 可选，变体型，代表单个字段名、顺序位置、字段名数组或顺序位置号。ADO 仅返回这些字段中的数据。
 * return: 返回二维数组。
 * remark: 使用 GetRows 方法可将记录从 Recordset 复制到二维数组中。第一个下标标识字段，第二个则标识记录号。当 GetRows 
 *         方法返回数据时数组变量将自动调整到正确大小。如果不指定 Rows 参数的值，GetRows 方法将自动检索 Recordset 对象
 *         中的所有记录。如果请求的记录比可用记录多，则 GetRows 仅返回可用记录数。如果 Recordset 对象支持书签，则可以通
 *         过传送该记录的 Bookmark 属性值，来指定 GetRows 方法将从哪个记录开始检索数据。如要限制 GetRows 调用返回的字段，
 *         则可以在 Fields 参数中传送单个字段名/编号或者字段名/编号数组。在调用 GetRows 后，下一个未读取的记录成为当前记录，
 *         或者如果没有更多的记录，则 EOF 属性设置为 True。
 */
_variant_t MtADORecordset::get_rows(
	const long rows,const _variant_t start/*=vtMissing*/,const _variant_t &fields/*=vtMissing*/){
	clear_last_error();
	try{
		return(_recordset->GetRows(rows,start,fields));
	}catch(const _com_error &error){
		record_last_error(error);
		return(vtMissing);
	}
}

/**
 * name: move
 * brief: 移动 Recordset 对象中当前记录的位置。
 * param: records - 带符号长整型表达式，指定当前记录位置移动的记录数。
 *        start - 可选，字符串或变体型，用于计算书签。也可为下列 BookmarkEnum 值之一：
 *                常量                              说明 
 *                ===================================================================
 *                AdBookmarkCurrent                 默认。从当前记录开始。 
 *                AdBookmarkFirst                   从首记录开始。 
 *                AdBookmarkLast                    从尾记录开始。 
 *                ===================================================================
 * return: 返回函数执行是否成功（可以使用SUCCEEDED宏或FAILED宏来判断）。
 * remark: 所有 Recordset 对象都支持 Move 方法。如果 NumRecords 参数大于零，则当前记录位置将向前移动（向记录集的末尾）。
 *         如果 NumRecords 小于零，则当前记录位置向后移动（向记录集的开始）。如果 Move 调用将当前记录位置移动到首记录之前，
 *         则 ADO 将当前记录放置在记录集（BOF 为 True）的首记录之前。在 BOF 属性已经为 True 时试图向后移动将产生错误。如
 *         果 Move 调用将当前记录位置移动到尾记录之后，则 ADO 将当前记录放置在记录集（EOF 为 True）的尾记录之后。在 EOF 
 *         属性已经为 True 时试图向前移动将产生错误。从空的 Recordset 对象调用 Move 方法将产生错误。如果传送 Start 参数，
 *         则移动相对于该书签的记录（假定 Recordset 对象支持书签）。如果没有指定，则移动相对于当前记录。如果使用 CacheSize 
 *         属性在本地缓存来自提供者的记录，则在传送将当前记录位置移动到当前缓存的记录组之外的 NumRecords 参数时， ADO 将不得
 *         不从目标记录开始检索新的记录组。CacheSize 属性决定新检索记录组的大小，而目标记录是检索到的第一个记录。如果 Recordset 
 *         对象是仅向前的，则用户仍然可以传送小于零的 NumRecords 参数（只要目标在已缓存记录的当前集合中）。如果 Move 调用将当前
 *         记录位置移动到第一个已缓存记录的前一个记录，将产生错误。因此可使用记录缓存，它在支持仅向前滚动的提供者上支持完全滚动。由于
 *         缓存的记录将加载到内存，因此应避免不必要地缓存过多记录。即使仅向前 Recordset 对象支持这种方式的向后移动，在任何仅向前的 
 *         Recordset 对象上调用 MovePrevious 方法仍将产生错误。
 */
HRESULT MtADORecordset::move(const long records,const ADODB::BookmarkEnum start/*=ADODB::adBookmarkCurrent*/){
	clear_last_error();
	try{
		return(_recordset->Move(records,start));
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: move_first
 * brief: 在指定 Recordset 对象中移动到第一个记录并使该记录成为当前记录。
 * param: --
 * return: 返回函数执行是否成功（可以使用SUCCEEDED宏或FAILED宏来判断）。
 * remark: 使用 MoveFirst 方法将当前记录位置移动到 Recordset 中的第一个记录。
 *         使用 MoveLast 方法将当前记录位置移动到 Recordset 中的最后一个记录。Recordset 对象必须支持书签或向后光标移动；
 *         否则调用该方法将产生错误。
 *         使用 MoveNext 方法将当前记录向前移动一个记录（向 Recordset 的底部）。如果最后一个记录是当前记录并且调用 MoveNext 方法，
 *         则 ADO 将当前记录设置到 Recordset （EOF 为 True）的尾记录之后。当 EOF 属性已经为 True 时试图向前移动将产生错误。
 *         使用 MovePrevious 方法将当前记录位置向后移动一个记录（向记录集的顶部）。Recordset 对象必须支持书签或向后游标移动；
 *         否则方法调用将产生错误。如果首记录是当前记录并且调用 MovePrevious 方法，则 ADO 将当前记录设置在 Recordset （BOF 为 True）的
 *         首记录之前。而 BOF 属性为 True 时向后移动将产生错误。如果 Recordset 对象不支持书签或向后游标移动，则 MovePrevious 方法将产生
 *         错误。
 *         如果记录集是仅向前的，但是用户希望支持向前和向后滚动，则可以使用 CacheSize 属性创建记录缓存，通过 Move 方法支持向后游标移动。
 *         由于缓存记录是加载到内存中的，所以应避免不必要地缓存太多记录。可以调用仅向前 Recordset 对象的 MoveFirst 方法；这样做可使提
 *         供者重新执行生成 Recordset 对象的命令。
 */
HRESULT MtADORecordset::move_first(){
	clear_last_error();
	try{
		return(_recordset->MoveFirst());
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: move_last
 * brief: 在指定 Recordset 对象中移动到最后一个记录并使该记录成为当前记录。
 * param: --
 * return: 返回函数执行是否成功（可以使用SUCCEEDED宏或FAILED宏来判断）。
 * remark: 使用 MoveFirst 方法将当前记录位置移动到 Recordset 中的第一个记录。
 *         使用 MoveLast 方法将当前记录位置移动到 Recordset 中的最后一个记录。Recordset 对象必须支持书签或向后光标移动；
 *         否则调用该方法将产生错误。
 *         使用 MoveNext 方法将当前记录向前移动一个记录（向 Recordset 的底部）。如果最后一个记录是当前记录并且调用 MoveNext 方法，
 *         则 ADO 将当前记录设置到 Recordset （EOF 为 True）的尾记录之后。当 EOF 属性已经为 True 时试图向前移动将产生错误。
 *         使用 MovePrevious 方法将当前记录位置向后移动一个记录（向记录集的顶部）。Recordset 对象必须支持书签或向后游标移动；
 *         否则方法调用将产生错误。如果首记录是当前记录并且调用 MovePrevious 方法，则 ADO 将当前记录设置在 Recordset （BOF 为 True）的
 *         首记录之前。而 BOF 属性为 True 时向后移动将产生错误。如果 Recordset 对象不支持书签或向后游标移动，则 MovePrevious 方法将产生
 *         错误。
 *         如果记录集是仅向前的，但是用户希望支持向前和向后滚动，则可以使用 CacheSize 属性创建记录缓存，通过 Move 方法支持向后游标移动。
 *         由于缓存记录是加载到内存中的，所以应避免不必要地缓存太多记录。可以调用仅向前 Recordset 对象的 MoveFirst 方法；这样做可使提
 *         供者重新执行生成 Recordset 对象的命令。
 */
HRESULT MtADORecordset::move_last(){
	clear_last_error();
	try{
		return(_recordset->MoveLast());
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: move_next
 * brief: 在指定 Recordset 对象中移动到下一个记录并使该记录成为当前记录。
 * param: --
 * return: 返回函数执行是否成功（可以使用SUCCEEDED宏或FAILED宏来判断）。
 * remark: 使用 MoveFirst 方法将当前记录位置移动到 Recordset 中的第一个记录。
 *         使用 MoveLast 方法将当前记录位置移动到 Recordset 中的最后一个记录。Recordset 对象必须支持书签或向后光标移动；
 *         否则调用该方法将产生错误。
 *         使用 MoveNext 方法将当前记录向前移动一个记录（向 Recordset 的底部）。如果最后一个记录是当前记录并且调用 MoveNext 方法，
 *         则 ADO 将当前记录设置到 Recordset （EOF 为 True）的尾记录之后。当 EOF 属性已经为 True 时试图向前移动将产生错误。
 *         使用 MovePrevious 方法将当前记录位置向后移动一个记录（向记录集的顶部）。Recordset 对象必须支持书签或向后游标移动；
 *         否则方法调用将产生错误。如果首记录是当前记录并且调用 MovePrevious 方法，则 ADO 将当前记录设置在 Recordset （BOF 为 True）的
 *         首记录之前。而 BOF 属性为 True 时向后移动将产生错误。如果 Recordset 对象不支持书签或向后游标移动，则 MovePrevious 方法将产生
 *         错误。
 *         如果记录集是仅向前的，但是用户希望支持向前和向后滚动，则可以使用 CacheSize 属性创建记录缓存，通过 Move 方法支持向后游标移动。
 *         由于缓存记录是加载到内存中的，所以应避免不必要地缓存太多记录。可以调用仅向前 Recordset 对象的 MoveFirst 方法；这样做可使提
 *         供者重新执行生成 Recordset 对象的命令。
 */
HRESULT MtADORecordset::move_next(){
	clear_last_error();
	try{
		return(_recordset->MoveNext());
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: move_previous
 * brief: 在指定 Recordset 对象中移动到前一个记录并使该记录成为当前记录。
 * param: --
 * return: 返回函数执行是否成功（可以使用SUCCEEDED宏或FAILED宏来判断）。
 * remark: 使用 MoveFirst 方法将当前记录位置移动到 Recordset 中的第一个记录。
 *         使用 MoveLast 方法将当前记录位置移动到 Recordset 中的最后一个记录。Recordset 对象必须支持书签或向后光标移动；
 *         否则调用该方法将产生错误。
 *         使用 MoveNext 方法将当前记录向前移动一个记录（向 Recordset 的底部）。如果最后一个记录是当前记录并且调用 MoveNext 方法，
 *         则 ADO 将当前记录设置到 Recordset （EOF 为 True）的尾记录之后。当 EOF 属性已经为 True 时试图向前移动将产生错误。
 *         使用 MovePrevious 方法将当前记录位置向后移动一个记录（向记录集的顶部）。Recordset 对象必须支持书签或向后游标移动；
 *         否则方法调用将产生错误。如果首记录是当前记录并且调用 MovePrevious 方法，则 ADO 将当前记录设置在 Recordset （BOF 为 True）的
 *         首记录之前。而 BOF 属性为 True 时向后移动将产生错误。如果 Recordset 对象不支持书签或向后游标移动，则 MovePrevious 方法将产生
 *         错误。
 *         如果记录集是仅向前的，但是用户希望支持向前和向后滚动，则可以使用 CacheSize 属性创建记录缓存，通过 Move 方法支持向后游标移动。
 *         由于缓存记录是加载到内存中的，所以应避免不必要地缓存太多记录。可以调用仅向前 Recordset 对象的 MoveFirst 方法；这样做可使提
 *         供者重新执行生成 Recordset 对象的命令。
 */
HRESULT MtADORecordset::move_previous(){
	clear_last_error();
	try{
		return(_recordset->MovePrevious());
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: next_record
 * brief: 清除当前 Recordset 对象并通过提前执行命令序列返回下一个记录集。
 * param: affect_records - 可选，长整型变量，提供者向其返回当前操作所影响的记录数目。
 *                         注意： 该参数仅返回受操作影响的记录的数目；它不会从用于生成
 *                         Recordset 的选择语句返回记录的计数。
 * return: 返回 Recordset 对象。在语法模型中，recordset1 和 recordset2 可以是相同的 Recordset 对象，或者可以使用不同的对象。
 * remark: 使用 NextRecordset 方法返回复合命令语句中下一条命令的结果，或者是返回多个结果的已存储过程结果。如果使用 Command 的 
 *         Execute 方法或者 Recordset 的 Open 方法打开基于复合命令语句（例如“SELECT * FROM table1;SELECT * FROM table2”）的 
 *         Recordset 对象，则 ADO 仅执行第一条命令并将结果返回到“记录集”。要访问语句中后续命令的结果，请调用 NextRecordset 方法。
 *         只要有其他的结果，并且包含复合语句的 Recordset 未被跨进程边界调度，则 NextRecordset 方法将继续返回 Recordset 对象。
 *         如果行返回命令没有返回记录，则返回的 Recordset 对象将为空；在确认 BOF 和 EOF 都为 True 的情况下可验证这种情况。如果非按行
 *         返回命令成功执行，则返回的 Recordset 对象将关闭，通过测试 Recordset 的 State 属性可以测试这种情况。如果没有其他的结果，“
 *         记录集”将设置为 Nothing。
 *        【远程数据服务】 NextRecordset 方法对客户端的 Recordset 对象不可用。如果在立即更新模式下进行编辑，调用 NextRecordset 方法
 *         将产生错误。应首先调用 Update 或 CancelUpdate 方法。如果需要通过填写 Parameters 集合或者通过使用原有的 Open 或 Execute 
 *         调用传送数组为复合语句中的多个命令传送参数，则参数在集合或数组中的次序必须与它们在命令序列中各自命令的次序相同。在读取输出参数值
 *         之前必须读取所有结果。在调用 NextRecordset 方法时，ADO 仅执行语句中的下一条命令。如果在单步执行整个命令语句之前显式关闭 Recordset
 *         对象，则 ADO 不执行其余的命令。
 */
ADODB::_RecordsetPtr MtADORecordset::next_record(VARIANT *affect_records){
	clear_last_error();
	try{
		return(_recordset->NextRecordset(affect_records));
	}catch(const _com_error &error){
		record_last_error(error);
		return(0);
	}
}

/**
 * name: open
 * brief: 打开游标。
 * param: source - 可选，变体型，计算 Command 对象的变量名、SQL 语句、表名、存储过程调用或持久 Recordset 文件名。
 *        active_connection - 可选。变体型，计算有效 Connection 对象变量名；或字符串，包含 ConnectionString 参数。
 *        cursor_type - 可选，CursorTypeEnum 值，确定提供者打开 Recordset 时应该使用的游标类型。可为下列常量之一（
 *                      参阅 CursorType 属性可获得这些设置的定义）。
 *                      常量                                          说明 
 *                      ====================================================================================
 *                      AdOpenForwardOnly                            （默认值）打开仅向前类型游标。 
 *                      AdOpenKeyset                                  打开键集类型游标。 
 *                      AdOpenDynamic                                 打开动态类型游标。 
 *                      AdOpenStatic                                  打开静态类型游标。 
 *                      ====================================================================================
 *        lock_type - 可选。确定提供者打开 Recordset 时应该使用的锁定（并发）类型的 LockTypeEnum 值，可为下列常量之一（
 *                    参见 LockType 属性可获得详细信息）。
 *                    常量                                            说明 
 *                    =================================================================================================
 *                    AdLockReadOnly                                （默认值）只读 — 不能改变数据。 
 *                    AdLockPessimistic                             保守式锁定（逐个） — 提供者完成确保成功编辑记录所需的工作，
 *                                                                  通常通过在编辑时立即锁定数据源的记录。 
 *                    AdLockOptimistic                              开放式锁定（逐个） — 提供者使用开放式锁定，只在调用Update 
 *                                                                  方法时才锁定记录。 
 *                    AdLockBatchOptimistic                         开放式批更新—用于批更新模式（与立即更新模式相对）。 
 *                    ==================================================================================================
 *        options - 可选，长整型值，用于指示提供者如何计算 Source 参数（如果它代表的不是 Command 对象），或从以前保存 Recordset 的文件
 *                  中恢复 Recordset。可为下列常量之一（参见 CommandType 属性可获得该列表中前五个常量的详细说明）。
 *                  常量                                         说明
 *                  =======================================================================================================
 *                  adCmdText                                   指示提供者应该将 Source 作为命令的文本定义来计算。 
 *                  adCmdTable                                  指示 ADO 生成 SQL 查询以便从在 Source 中命名的表中返回所有行。 
 *                  adCmdTableDirect                            指示提供者更改从在 Source 中命名的表中返回所有行。 
 *                  adCmdStoredProc                             指示提供者应该将 Source 视为存储过程。 
 *                  adCmdUnknown                                指示 Source 参数中的命令类型为未知。 
 *                  adCmdFile                                   指示应从在 Source 中命名的文件中恢复保留（保存的）Recordset。 
 *                  adAsyncExecute                              指示应异步执行 Source。 
 *                  adAsyncFetch                                指示在提取 Initial Fetch Size 属性中指定的初始数量后，应该异步
 *                                                              提取所有剩余的行。如果所需的行尚未提取，主要的线程将被堵塞直到行重新
 *                                                              可用。 
 *                  adAsyncFetchNonBlocking                     指示主要线程在提取期间从未堵塞。如果所请求的行尚未提取，当前行自动移
 *                                                              到文件末尾。
 *                  ========================================================================================================
 * return: 返回函数执行是否成功（可以使用SUCCEEDED宏或FAILED宏来判断）。
 * remark: 使用 Recordset 对象的 Open 方法可打开代表基本表、查询结果或者以前保存的 Recordset 中记录的游标。使用可选的 Source 参数指定使用
 *         下列内容之一的数据源：Command 对象变量、SQL 语句、存储过程、表名或完整的文件路径名。
 *         如果 Source 是文件路径名，它可以是完整路径（“c:\dir\file.rst”）、相对路径（“..\file.rst”）或 URL（“http://files/file.rst”）。
 *         ActiveConnection 参数对应于 ActiveConnection 属性，并指定在哪个连接中打开 Recordset 对象。如果传送该参数的连接定义，则 ADO 使
 *         用指定的参数打开新连接。可以在打开 Recordset 之后更改该属性的值以便将更新发送到其他提供者。或者可以将该属性设置为 Nothing（在 
 *         Microsoft Visual Basic 中）以便将 Recordset 与所有提供者断开。对于直接对应于 Recordset 对象属性的参数（Source、CursorType 和 
 *         LockType），参数和属性的关系如下： 在 Recordset 对象打开之前属性是读/写。除非在执行 Open 方法时传送相应的参数，否则将使用属性设置。
 *         如果传送参数，则它将覆盖相应的属性设置，并且用参数值更新属性设置。在打开 Recordset 对象后，这些属性将变为只读。 注意: 对于其 Source 
 *         属性被设置为有效 Command 对象的 Recordset 对象，即使 Recordset 对象没有打开，ActiveConnection 属性也是只读的。如果在 Source 
 *         参数中传送 Command 对象并且同时传递 ActiveConnection 参数，那么将产生错误。Command 对象的 ActiveConnection 属性必须已经设置为
 *         有效的 Connection 对象或者连接字符串。如果在 Source 参数中传送的不是 Command 对象，那么可以使用 Options 参数优化对 Source 参数
 *         的计算。如果没有定义 Options 则性能将会降低，原因是 ADO 必须调用提供者以确定参数是否为 SQL 语句、存储过程或表名。如果已确定所用的 
 *         Source 类型，则可以设置 Options 参数以指示 ADO 直接跳到相关的代码。如果 Options 参数不匹配 Source 类型，将产生错误。如果不存在与
 *         Recordset 关联的连接，Options 参数的默认值将为 adCmdFile。这是持久 Recordset 对象的典型情况。如果数据源没有返回记录，那么提供者将
 *         BOF 和 EOF 属性同时设置为 True，并且不定义当前记录位置。如果游标类型允许，仍然可以将新数据添加到该空 Recordset 对象。在打开的 
 *         Recordset 对象上完成操作时，可使用 Close 方法释放任何相关的系统资源。关闭对象并非将它从内存中删除，可以更改它的属性设置并且在以后使
 *         用 Open 方法再次将其打开。要将对象从内存中完全删除，可将对象变量设置为 Nothing。在设置 ActiveConnection 属性之前调用不带操作数的 
 *         Open，可通过将字段追加到 Recordset Fields 集合创建 Recordset 的实例。如果已经将 CursorLocation 属性设置为 adUseClient，就可以
 *         采用两种途径之一异步检索行。建议使用的方法是将 Options 设置为 adAsyncFetch。或者，可以使用在 Properties 集合中的“异步行集合处理”
 *         动态属性，但如果未将 Options 参数设置为 adAsyncFetch，则可能丢失相关的被检索事件。
 *         注意: 在 MSRemote 提供者中的背景提取仅能通过 Open 方法的 Options 参数得到支持。
 */
HRESULT MtADORecordset::open(const _variant_t &source,const _variant_t &active_connection,
	const ADODB::CursorTypeEnum cursor_type,ADODB::LockTypeEnum lock_type,const long options){
	clear_last_error();
	try{
		return(_recordset->Open(source,active_connection,cursor_type,lock_type,options));
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: requery
 * brief: 通过重新执行对象所基于的查询，更新 Recordset 对象中的数据。
 * param: options - 可选。指示影响该操作选项的位屏蔽。如果该参数设置为 adAsyncExecute，
 *                  则该操作将异步执行并在它结束时产生 RecordsetChangeComplete 事件。
 * return: 返回函数执行是否成功（可以使用SUCCEEDED宏或FAILED宏来判断）。
 * remark: 通过重新发出原始命令并再次检索数据，可使用 Requery 方法刷新来自数据源的 Recordset 对象的全部内容。
 *         调用该方法等于相继调用 Close 和 Open 方法。如果正在编辑当前记录或者添加新记录将产生错误。在 Recordset 
 *         对象打开期间，定义游标性质（CursorType、LockType、MaxRecords 等）的属性为只读，因此 Requery 方法只能
 *         刷新当前游标。要更改某个游标属性并查看结果，必须使用 Close 方法使属性再次成为读/写。然后可以更改属性设置并
 *         且调用 Open 方法重新打开游标。
 */
HRESULT MtADORecordset::requery(const long options){
	clear_last_error();
	try{
		return(_recordset->Requery(options));
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: resync
 * brief: 从基本数据库刷新当前 Recordset 对象中的数据。
 * param: affect_records - 可选，AffectEnum 值，决定 Resync 方法所影响的记录数目，可以为下列常量之一。
 *                         常量                                        说明 
 *                         ==================================================================================
 *                         AdAffectCurrent                             只刷新当前记录。 
 *                         AdAffectGroup                               刷新满足当前 Filter 属性设置的记录。
 *                                                                     只有将 Filter 属性设置为有效预定义常
 *                                                                     量之一才能使用该选项。 
 *                         AdAffectAll                                 默认值。刷新 Recordset 对象中的所有记录，
 *                                                                     包括由于当前 Filter 属性设置而隐藏的记录。 
 *                         adAffectAllChapters                         刷新所有子集记录。 
 *                         ==================================================================================
 *        resync_values - 可选，ResyncEnum 值。指定是否覆盖基本值。可为下列常量之一。
 *                        常量                                          说明 
 *                        ====================================================================================
 *                        AdResyncAllValues                            默认值。覆盖数据，取消挂起的更新。 
 *                        AdResyncUnderlyingValues                     不覆盖数据，不取消挂起的更新。 
 *                        ====================================================================================
 * return: 返回函数执行是否成功（可以使用SUCCEEDED宏或FAILED宏来判断）。
 * remark: 使用 Resync 方法将当前 Recordset 中的记录与基本的数据库重新同步。这在使用静态或仅向前的游标但希望看到基本数据库中的改动
 *         时十分有用。如果将 CursorLocation 属性设置为 adUseClient，则 Resync 仅对非只读的 Recordset 对象可用。与 Requery 方
 *         法不同，Resync 方法不重新执行 Recordset 对象的基本的命令，基本的数据库中的新记录将不可见。如果由于与基本的数据冲突（如其
 *         他用户已将记录删除）而使重新同步的尝试失败，则提供者将警告返回到 Errors 集合并且产生运行时错误。使用 Filter 属性 (
 *         adFilterConflictingRecords) 和 Status 属性可以找到发生冲突的记录。
 *        【远程数据服务】Resync 方法在客户端 Recordset 上无效。
 *         如果设置了 Unique Table 和 Resync Command 动态属性，并且 Recordset 是对多个表执行 JOIN 操作的结果，那么，Resync 方法
 *         将仅对 Unique Table 属性中命名的表执行在 Resync Command 属性中所给定的操作。
 */
HRESULT MtADORecordset::resync(const ADODB::AffectEnum affect_records,const ADODB::ResyncEnum resync_values){
	clear_last_error();
	try{
		return(_recordset->Resync(affect_records,resync_values));
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: save
 * brief: 将 Recordset 保存（持久）在文件中。
 * param: file_name - 可选。文件的完整路径名，用于保存 Recordset。
 *        persist_format - 可选。PersistFormatEnum 值，指定保存 Recordset 所使用的格式。可以是如下的某个常量：
 *                         常量                                         说明
 *                         ===========================================================================================
 *                         adPersistADTG                              （默认）使用专用的“Advanced Data Tablegram”格式保存。 
 *                         adPersistXML                                使用 XML 格式保存。 
 *                         ===========================================================================================
 * return: 返回函数执行是否成功（可以使用SUCCEEDED宏或FAILED宏来判断）。
 * remark: 只能对打开的 Recordset 调用 Save 方法。随后使用 Open 方法可由 FileName 恢复 Recordset。
 *         如果 Filter 属性影响 Recordset，将只保存经过筛选的行。如果 Recordset 是分级结构的，那么将保存当前子 Recordset 和
 *         它的子 Recordset，但不保存上一级 Recordset。在第一次保存 Recordset 时指定 FileName。如果随后调用 Save 时，应忽略
 *         FileName，否则将产生运行时错误。如果随后使用新的 FileName 调用 Save，那么 Recordset 将保存到新的文件中，但新文件和
 *         原始文件都是打开的。Save 不关闭 Recordset 或 FileName，从而可以继续使用 Recordset 并保存最新的更改。在 Recordset 
 *         关闭之前 FileName 将保持打开，在这段时间其它应用程序可以读取但不能写入 FileName。出于安全的原因，对由 Microsoft Internet
 *         Explorer 执行的脚本，Save 方法仅允许使用低的和自定义的安全设置。有关安全问题的详细解释，请参阅 在 
 *         http://www.microsoft.com/data/techmat.htm 上的白皮书标题“Security Issues in the Microsoft Internet Explorer”。
 *         如果正在进行异步 Recordset 获取、执行或更新操作时调用 Save 方法，则 Save 将进入等待状态，直到异步操作完成。
 *         在 Save 方法完成后，当前行位置将成为 Recordset 的首行。要得到最佳结果，应使用 Save 将 CursorLocation 属性设置为 adUseClient。
 *         如果您的提供者不支持用于保存 Recordset 对象的所需功能，则客户端游标将提供该功能。
 */ 
HRESULT MtADORecordset::save(const CString &file_name,const ADODB::PersistFormatEnum persist_format){
	clear_last_error();
	try{
		return(_recordset->Save(
			static_cast<_bstr_t>(static_cast<LPCTSTR>(file_name)),persist_format));
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: supports
 * brief: 确定指定的 Recordset 对象是否支持特定类型的功能。
 * param: options - 长整型表达式，包括一个或多个下列 CursorOptionEnum 值。
 *                  常量                                    说明 
 *                  =====================================================================================================
 *                  adAddNew                                可使用 AddNew 方法添加新记录。 
 *                  adApproxPosition                        可读取并设置 AbsolutePosition 和 AbsolutePage 的属性。 
 *                  adBookmark                              可使用 Bookmark 属性获得对特定记录的访问。 
 *                  adDelete                                可以使用 Delete 方法删除记录。 
 *                  AdHoldRecords                           可以检索多个记录或者更改下一个检索位置而不必提交所有挂起的更改。 
 *                  AdMovePrevious                          可使用 MoveFirst 和 MovePrevious 方法，以及 Move 或 GetRows 
 *                                                          方法将当前记录位置向后移动而不必使用书签。 
 *                  AdResync                                通过 Resync 方法，使用在基本的数据库中可见的数据更新游标。 
 *                  AdUpdate                                可使用 Update 方法修改现有的数据。 
 *                  AdUpdateBatch                           可以使用批更新（UpdateBatch 和 CancelBatch 方法）将更改组传输给提供者。 
 *                  AdIndex                                 可以使用 Index 属性命名索引。 
 *                  AdSeek                                  可以使用 Seek 方法定位 Recordset 中的行。 
 *                  =======================================================================================================
 * return: 返回指定的 Recordset 对象是否支持特定类型的功能。
 * remark: 使用 Supports 方法确定 Recordset 对象所支持的功能类型。如果 Recordset 对象支持其相应常量在 CursorOptions 中的功能，
 *         那么 Supports 方法返回 True。否则返回 False。
 *         注意: 尽管 Supports 方法可对给定的功能返回 True，但它不能保证提供者可以使功能在所有环境下均有效。Supports 方法只返回提供者
 *         是否支持指定的功能（假定符合某些条件）。例如，Supports 方法可能指示 Recordset 对象支持更新（即使游标基于多个表的合并），但并
 *         且某些列仍然无法更新。
 */
BOOL MtADORecordset::supports(const ADODB::CursorOptionEnum options){
	clear_last_error();
	try{
		if(-1==_recordset->Supports(options)){
			return(TRUE);
		}else{
			return(FALSE);
		}
	}catch(const _com_error &error){
		record_last_error(error);
		return(FALSE);
	}
}

/**
 * name: update
 * brief: 保存对 Recordset 对象的当前记录所做的所有更改。
 * param: fields - 可选。变体型，代表单个名称；或变体型数组，代表需要修改的字段（一个或多个）名称及序号位置。 
 *        values - 可选。变体型，代表单个值；或变体型数组，代表新记录中字段（单个或多个）值。
 * return: 返回函数执行是否成功（可以使用SUCCEEDED宏或FAILED宏来判断）。
 * remark: 使用 Update 方法保存自调用 AddNew 方法或更改现有记录中任何字段值以来所作的所有更改。Recordset 对象必须支持更新。
 *         要设置字段值，请进行下列某项操作： 为 Field 对象的 Value 属性赋值，并调用 Update 方法。在 Update 调用中传送字段
 *         名和值作为参数。在 Update 调用中传送字段名数组和值数组。 在使用字段和值的数组时，两个数组中必须有相等数量的元素，同
 *         时字段名的次序必须匹配字段值的次序。字段和值的数量及次序不匹配将产生错误。如果 Recordset 对象支持批更新，那么可以在
 *         调用 UpdateBatch 方法之前将一个或多个记录的多个改动缓存在本地。如果在调用 UpdateBatch 对象时正在编辑当前记录或者
 *         添加新的记录，那么 ADO 将自动调用 Update 方法以便在将批更改传送到提供者之前保存挂起的更改。如果在调用 Update 方法
 *         之前移动出正在添加或编辑的记录，那么 ADO 将自动调用 Update 以便保存更改。如果希望取消对当前记录所做的任何更改或者放
 *         弃新添加的记录，则必须调用 CancelUpdate 方法。在调用 Update 方法后当前记录仍为当前记录。如果设置了 Unique Table 
 *         动态属性，并且 Recordset 是对多个表执行 JOIN 操作的结果，那么，Update 方法将无法更新多个表的任何主要关键字。此外，
 *         Update 只能更新在 Unique Table 属性中指定的表中的字段。
 */
HRESULT MtADORecordset::update(
	const _variant_t &fields/*=vtMissing*/,const _variant_t &values/*=vtMissing*/){
	clear_last_error();
	try{
		return(_recordset->Update(fields,values));
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: update_batch
 * brief: 将所有挂起的批更新写入磁盘。
 * param: affect_records - 可选，AffectEnum 值。决定 UpdateBatch 方法所影响的记录数目。可以为如下常量之一。
 *                         常量                                  说明 
 *                         ============================================================================================
 *                         adAffectCurrent                      只写入当前记录的挂起更改。 
 *                         adAffectGroup                        写入满足当前 Filter 属性设置的记录所发生的挂起更改。
 *                                                              必须将 Filter 属性设置为某个有效的预定义常量才能使用该选项。 
 *                         adAffectAll                          （默认值）。写入 Recordset 对象中所有记录的挂起更改，包括由
 *                                                              于当前 Filter 属性设置而隐藏的任何记录。 
 *                         adAffectAllChapters                  写入所有子集的挂起更改。 
 *                         ============================================================================================
 * return: 返回函数执行是否成功（可以使用SUCCEEDED宏或FAILED宏来判断）。
 * remark: 按批更新模式修改 Recordset 对象时，使用 UpdateBatch 方法可将 Recordset 对象中的所有更改传递到基本数据库。如果 Recordset 对象
 *         支持批更新，那么可以将一个或多个记录的多重更改缓存在本地，然后再调用 UpdateBatch 方法。如果在调用 UpdateBatch 方法时正在编辑当前
 *         记录或者添加新的记录，那么在将批更新传送到提供者之前，ADO 将自动调用 Update 方法保存对当前记录的所有挂起更改。
 *         注意： 只能对键集或静态游标使用批更新。
 *         如果由于与基本的数据冲突而导致对所有或任意记录的传送更改失败（如其他用户已将记录删除），那么提供者将把警告返回给 Errors 集合，并发生
 *         运行时错误。使用 Filter 属性 (adFilterAffectedRecords) 和 Status 属性可以找到发生冲突的记录。要取消所有挂起的批更新，请使用 
 *         CancelBatch 方法。如果设置了 Unique Table 和 Update Resync 动态属性，并且 Recordset 是对多个表执行 JOIN 操作的结果，那么，
 *         取决于 Update Resync 属性，执行 UpdateBatch 方法会隐性导致 Resync 方法。
 */
HRESULT MtADORecordset::update_batch(const ADODB::AffectEnum affect_records){
	clear_last_error();
	try{
		return(_recordset->UpdateBatch(affect_records));
	}catch(const _com_error &error){
		record_last_error(error);
		return(-1);
	}
}

/**
 * name: put_collect
 * brief: 设置记录集中指定记录的域值。
 * param: index - 域编号。
 *        value - 域值。
 * return: --
 */
void MtADORecordset::put_collect(const _variant_t &index,const _variant_t &value){
	clear_last_error();
	try{
		_recordset->PutCollect(index,value);
	}catch(const _com_error &error){
		record_last_error(error);
	}
}

/**
 * name: get_collect
 * brief: 获取记录集中指定记录的域值。
 * param: index - 域编号。
 * return: 返回域值。
 */
_variant_t MtADORecordset::get_collect(const _variant_t &index){
	clear_last_error();
	try{
		return(_recordset->GetCollect(index));
	}catch(const _com_error &error){
		record_last_error(error);
		return(vtMissing);
	}
}

/**
 * name: is_null_value_in_collect
 * brief: 判断当前记录集中指定域是否为空。
 * param: index - 域编号。
 * return: 返回当前记录集中指定域是否为空。
 */
BOOL MtADORecordset::is_null_value_in_collect(const _variant_t &index){
	//1.获取指定域中的值,并且判断获取是否成功。
	const _variant_t value=get_collect(index);
	if(0!=get_last_error_code()){
		return(FALSE);
	}
	//2.判断值是否为空，并且返回结果。
	if(VT_NULL==value.vt){
		return(TRUE);
	}else{
		return(FALSE);
	}
}

/**
 * name: get_last_error_code
 * brief: 获取最近的错误编码。
 * param: --
 * return: 返回最近的错误编码。
 */
long MtADORecordset::get_last_error_code() const{
	return(_last_error_code);
}

/**
 * name: get_last_error_message
 * brief: 获取最近的错误消息。
 * param: --
 * return: 返回最近的错误消息。
 */
CString MtADORecordset::get_last_error_message() const{
	return(_last_error_message);
}

/**
 * name: create_instance
 * brief: 创建实例。
 * param: --
 * return: --
 */
void MtADORecordset::create_instance(){
	const HRESULT result=
		_recordset.CreateInstance(_T("ADODB.Recordset"));
	assert((SUCCEEDED(result))&&(0!=_recordset));
}

/**
 * name: release_instance
 * brief: 释放实例。
 * param: --
 * return: --
 */
void MtADORecordset::release_instance(){
	if(0!=_recordset){
		const long state=get_state();
		assert(0==get_last_error_code());
		if(ADODB::adStateOpen==state){
			close();
			assert(0==get_last_error_code());
		}
		_recordset.Release();
		_recordset=0;
	}
}

/**
 * name: clear_last_error
 * brief: 清除最近错误信息。
 * param: --
 * return: --
 */
void MtADORecordset::clear_last_error() const{
	_last_error_code=0;
	_last_error_message=_T("");
}

/**
 * name: record_last_error
 * brief: 记录最近错误信息。
 * param: error - 最近错误信息。
 * return: --
 */
void MtADORecordset::record_last_error(const _com_error &error) const{
	_last_error_code=error.Error();
	_last_error_message=error.ErrorMessage();
}