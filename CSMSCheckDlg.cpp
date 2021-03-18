// CSMSCheckDlg.cpp: 구현 파일
//

#include "pch.h"
#include "MySQLSample.h"
#include "CSMSCheckDlg.h"
#include "afxdialogex.h"


// CSMSCheckDlg 대화 상자

IMPLEMENT_DYNAMIC(CSMSCheckDlg, CDialogEx)

CSMSCheckDlg::CSMSCheckDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SMS_DIALOG, pParent)
{

}

CSMSCheckDlg::~CSMSCheckDlg()
{
}

void CSMSCheckDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSMSCheckDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BtnDBConnect, &CSMSCheckDlg::OnBnClickedBtndbconnect)
	ON_BN_CLICKED(IDC_BtnInsert, &CSMSCheckDlg::OnBnClickedBtninsert)
END_MESSAGE_MAP()


// CSMSCheckDlg 메시지 처리기


void CSMSCheckDlg::OnBnClickedBtndbconnect()
{
	CString strMsg;
	ReadDBInfo();
	stDBInfo dbinfo = GetDBInfo();
	BOOL bRet =  m_DB.ConnectDB(dbinfo.dbip, dbinfo.dbuser, dbinfo.dbpwd, dbinfo.dbname, dbinfo.dbport);
	if (bRet) {
		MessageDisplay("DB Open Success");
	}
	else {
		MessageDisplay("DB Open Fail");
	}
}
void CSMSCheckDlg::ReadDBInfo()
{
	char path[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH, path);

	CString fn = _T("");
	fn.Format(_T("%s%s"), path, _T("\\config.ini"));

	GetPrivateProfileString(_T("Database"), _T("addr"), _T("localhost"), m_DBInfo.dbip, MAX_STRING, fn);
	m_DBInfo.dbport = GetPrivateProfileInt(_T("Database"), _T("port"), 3306, fn);
	GetPrivateProfileString(_T("Database"), _T("dbname"), _T("NMS"), m_DBInfo.dbname, MAX_STRING, fn);
	GetPrivateProfileString(_T("Database"), _T("id"), _T("root"), m_DBInfo.dbuser, MAX_STRING, fn);
	GetPrivateProfileString(_T("Database"), _T("pwd"), _T("root"), m_DBInfo.dbpwd, MAX_STRING, fn);



}
stDBInfo CSMSCheckDlg::GetDBInfo()
{
	return m_DBInfo;
}

char* CSMSCheckDlg::GetCurrentTimeString()
{
	char szBuff[100];
	SYSTEMTIME tm;
	GetLocalTime(&tm);
	sprintf_s(szBuff,100, "%04d-%d-%d %d:%d:%d", tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);
	return szBuff;
}
CString CSMSCheckDlg::GetDlgContentString(int id)
{
	CString str;
	CWnd* pWnd = (CWnd*)GetDlgItem(id);
	pWnd->GetWindowText(str);
	return str;
}
void CSMSCheckDlg::InsertSQL_small()
{
	CString strSQL;
	stSMSInfo  smsInfo;
	ZeroMemory(&smsInfo, sizeof(smsInfo));
	strcpy_s(smsInfo.REQ_TIME, LONG_STRING, GetCurrentTimeString());
	strcpy_s(smsInfo.SND_NUM, NUMBER_MAX, GetDlgContentString(IDC_EDIT_SND_NUM));
	strcpy_s(smsInfo.RECV_NUM, NUMBER_MAX, GetDlgContentString(IDC_EDIT_RECV_NUM));
	strcpy_s(smsInfo.SEND_MSG, MSG_MAX, GetDlgContentString(IDC_EDIT_MSG));
	strcpy_s(smsInfo.GROUP_ID, 4, "");
	smsInfo.SMS_TYPE = '1';
	memset(smsInfo.RESERVED_TIME, 0, sizeof(smsInfo.RESERVED_TIME));
	smsInfo.PRIORITY = '2';
	smsInfo.STATUS = '0';
	smsInfo.TRY_COUNT = 0;
	
	strSQL.Format("INSERT INTO WAIT_SMS(\
							REQ_TIME,SND_NUM,\
		                    RECV_NUM,SEND_MSG,\
                            GROUP_ID,SMS_TYPE,\
							PRIORITY, STATUS,\
		                    TRY_COUNT) \
			                VALUES(\'%s\',\'%s\',\
		                           \'%s\',\'%s\',\
                                   \'%s\',\'%c\',\
                                   \'%c\',\'%c\',\
                    	             %d);",
						smsInfo.REQ_TIME,smsInfo.SND_NUM,
						smsInfo.RECV_NUM,smsInfo.SEND_MSG,
			    		smsInfo.GROUP_ID,smsInfo.SMS_TYPE,
						smsInfo.PRIORITY,smsInfo.STATUS,
						smsInfo.TRY_COUNT);  //16

	if (m_DB.InsertQuery(strSQL) == false)
	{
		MessageDisplay("Insert Fail");
	}
	else {
		MessageDisplay("Insert Success");
	}
}
void CSMSCheckDlg::InsertSQL_Large()
{
	CString strSQL;
	stSMSInfo  smsInfo;
	ZeroMemory(&smsInfo, sizeof(smsInfo));
	strcpy_s(smsInfo.REQ_TIME, LONG_STRING, GetCurrentTimeString());
	strcpy_s(smsInfo.SND_NUM, NUMBER_MAX, GetDlgContentString(IDC_EDIT_SND_NUM));
	strcpy_s(smsInfo.RECV_NUM, NUMBER_MAX, GetDlgContentString(IDC_EDIT_RECV_NUM));
	strcpy_s(smsInfo.SEND_MSG, MSG_MAX, GetDlgContentString(IDC_EDIT_MSG));
	strcpy_s(smsInfo.GROUP_ID, 4, "");
	smsInfo.SMS_TYPE = '1';
	memset(smsInfo.RESERVED_TIME, 0, sizeof(smsInfo.RESERVED_TIME));
	smsInfo.PRIORITY = '2';
	strcpy_s(smsInfo.URL, 80, "");
	smsInfo.STATUS = '0';
	smsInfo.TRY_COUNT = 0;
	strcpy_s(smsInfo.REQ_USER, 50, "");
	memset(smsInfo.END_DATE, 0, sizeof(smsInfo.END_DATE));
	strcpy_s(smsInfo.reserved1, 30, "");
	strcpy_s(smsInfo.reserved2, 30, "");
	strcpy_s(smsInfo.reserved3, 30, "");


	strSQL.Format("INSERT INTO WAIT_SMS(\
			REQ_TIME, SND_NUM,RECV_NUM,SEND_MSG,GROUP_ID,SMS_TYPE,PRIORITY,RESERVED_TIME,\
		    URL,STATUS,TRY_COUNT,REG_USER,END_DATE,RESERVED1,RESERVED2,RESERVED3) \
			VALUES(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%c\',\'%c\',\'%s\',\
		           \'%s\',\'%c\',%d,    \'%s\',\'%s\',\'%s\',\'%s\',\'%s\');",
		smsInfo.REQ_TIME,
		smsInfo.SND_NUM,
		smsInfo.RECV_NUM,
		smsInfo.SEND_MSG,
		smsInfo.GROUP_ID,
		smsInfo.SMS_TYPE,
		smsInfo.PRIORITY,
		smsInfo.RESERVED_TIME,
		smsInfo.URL,        // 9
		smsInfo.STATUS,
		smsInfo.TRY_COUNT,
		smsInfo.REQ_USER,
		smsInfo.END_DATE,
		smsInfo.reserved1,
		smsInfo.reserved2,
		smsInfo.reserved3);  //16

	if (m_DB.InsertQuery(strSQL) == false)
	{
		MessageDisplay("Insert Fail");
	}
	else {
		MessageDisplay("Insert Success");
	}
}
void CSMSCheckDlg::OnBnClickedBtninsert()
{

	InsertSQL_small();

}

void CSMSCheckDlg::MessageDisplay(CString szMsg)
{
	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_LBL_RESULT);
	pWnd->SetWindowText(szMsg);

}

BOOL CSMSCheckDlg::MakeSMSInfo(stSMSInfo& smsInfo)
{
	// TODO: 여기에 구현 코드 추가.
	return 0;
}


BOOL CSMSCheckDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	
	SetDlgItemText(IDC_EDIT_SND_NUM, "01089461439");
	SetDlgItemText(IDC_EDIT_RECV_NUM, "01081696651");
	SetDlgItemText(IDC_EDIT_MSG, "NVR SMS Alarm Message");
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
