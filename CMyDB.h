#pragma once

#include "mysql.h"
#pragma comment(lib,"libmariadb.lib")

#define MAX_STRING  50
typedef struct {
	int displaycount;
	char dbip[MAX_STRING];
	int dbport;
	char dbname[MAX_STRING];
	char dbuser[MAX_STRING];
	char dbpwd[MAX_STRING];
	int expire; // days after
} stDBInfo;


class CMyDB
{
private:
	MYSQL m_Database;
	MYSQL_RES* m_DB_Result;
	
public:
	CMyDB();
	~CMyDB();
	

	BOOL ConnectDB(CString addr, CString id, CString pwd, CString name, int port);
	void CloseDB();
	int SelectQuery(CString strQuery);
	int InsertQuery(CString strQuery);
	int UpdateQuery(CString strQuery);
	int DeleteQuery(CString strQuery);
	MYSQL_ROW GetNextRow();

};

