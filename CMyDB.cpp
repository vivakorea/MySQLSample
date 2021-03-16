#include "pch.h"
#include "CMyDB.h"



CMyDB::CMyDB()
{
	m_DB_Result = 0;
	mysql_init(&m_Database);

}

CMyDB::~CMyDB()
{
}

BOOL CMyDB::ConnectDB(CString addr, CString id, CString pwd, CString name, int port)
{
	if (mysql_real_connect(&m_Database, addr, id, pwd, name, port, NULL, 0))
		return TRUE;
	return FALSE;
}

void CMyDB::CloseDB()
{
	if (m_DB_Result)
		mysql_free_result(m_DB_Result);
	mysql_close(&m_Database);
}

int CMyDB::SelectQuery(CString strQuery)
{
	if (mysql_query(&m_Database, CStringA(strQuery)))
	{
		return 0;
	}
	if (m_DB_Result)
		mysql_free_result(m_DB_Result);
	if ((m_DB_Result = mysql_store_result(&m_Database)) == NULL){
		return 0;
	}
	return static_cast<int>(m_DB_Result->row_count);
}

int CMyDB::InsertQuery(CString strQuery)
{
	int ret = mysql_query(&m_Database, strQuery);
	mysql_commit(&m_Database);
	return (ret==0)? true:false;
}

int CMyDB::UpdateQuery(CString strQuery)
{
	int ret = mysql_query(&m_Database, strQuery);
	mysql_commit(&m_Database);
	return (ret == 0) ? true : false;
}

int CMyDB::DeleteQuery(CString strQuery)
{
	int ret = mysql_query(&m_Database, strQuery);
	mysql_commit(&m_Database);
	return (ret == 0) ? true : false;
}

MYSQL_ROW CMyDB::GetNextRow()
{
	return mysql_fetch_row(m_DB_Result);
}
