
// MySQLSampleDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MySQLSample.h"
#include "MySQLSampleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMySQLSampleDlg 대화 상자



CMySQLSampleDlg::CMySQLSampleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MYSQLSAMPLE_DIALOG, pParent)
{

	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	ZeroMemory(&m_DBInfo, sizeof(m_DBInfo));
}

void CMySQLSampleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMySQLSampleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BtnQuery, &CMySQLSampleDlg::OnBnClickedBtnquery)
	ON_BN_CLICKED(IDC_BtnInsert, &CMySQLSampleDlg::OnBnClickedBtninsert)
	ON_BN_CLICKED(IDC_BtnDBClose, &CMySQLSampleDlg::OnBnClickedBtndbclose)
	ON_BN_CLICKED(IDC_BtnDBConnect, &CMySQLSampleDlg::OnBnClickedBtndbconnect)
	ON_BN_CLICKED(IDC_BtnUpdate, &CMySQLSampleDlg::OnBnClickedBtnupdate)
	ON_BN_CLICKED(IDC_BtnDelete, &CMySQLSampleDlg::OnBnClickedBtndelete)
END_MESSAGE_MAP()


// CMySQLSampleDlg 메시지 처리기

BOOL CMySQLSampleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CMySQLSampleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.
#include "CMyDB.h"

void CMySQLSampleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMySQLSampleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMySQLSampleDlg::ReadDBInfo()
{
	char path[MAX_PATH];
	::GetCurrentDirectory(MAX_PATH, path);

	CString fn = _T("");
	fn.Format(_T("%s%s"), path, _T("\\config.ini"));

	GetPrivateProfileString(_T("Database"), _T("addr"), _T("localhost"), m_DBInfo.dbip, MAX_STRING, fn);
	m_DBInfo.dbport = GetPrivateProfileInt(_T("Database"), _T("port"), 3306, fn);
	GetPrivateProfileString(_T("Database"), _T("dbname"), _T("ALPR"), m_DBInfo.dbname, MAX_STRING, fn);
	GetPrivateProfileString(_T("Database"), _T("id"), _T("root"), m_DBInfo.dbuser, MAX_STRING, fn);
	GetPrivateProfileString(_T("Database"), _T("pwd"), _T("root"), m_DBInfo.dbpwd, MAX_STRING, fn);

}
void CMySQLSampleDlg::OnBnClickedBtndbconnect()
{
	CString strMsg;
	ReadDBInfo();

	BOOL bRet = m_DB.ConnectDB(m_DBInfo.dbip, m_DBInfo.dbuser, m_DBInfo.dbpwd, m_DBInfo.dbname, m_DBInfo.dbport);
	if (bRet) {
		MessageDisplay("DB Open Success");
	}
	else {
		MessageDisplay("DB Open Fail");
	}

}
void CMySQLSampleDlg::MessageDisplay(CString szMsg)
{

	CStatic* pWnd = (CStatic*)GetDlgItem(IDC_LBL_RESULT);
	pWnd->SetWindowText(szMsg);
	
}
void CMySQLSampleDlg::OnBnClickedBtnquery()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.

	CString strQuery;
	CString szRow;
	strQuery.Format("Select * From tbl_car");
	int cnt = m_DB.SelectQuery(strQuery);
	CListBox* pList =(CListBox *)GetDlgItem(IDC_LIST1);
	pList->ResetContent();
	if (cnt > 0)
	{
		MYSQL_ROW row = 0;
		while ((row = m_DB.GetNextRow()) != NULL)
		{
			szRow.Format("%s,%s,%s,%s, %s\n", row[0], row[1], row[2], row[3], row[4]);
			TRACE(szRow);
			pList->AddString(szRow);

		}

	}

}
#define LONG_STRING				20
#define MAX_STRING				50
#define SHORT_STRING			10
#define LONG_STRING				20

typedef struct {
	char platenumber[LONG_STRING];
	char type[LONG_STRING];
	char manufacturer[LONG_STRING];
	char color[LONG_STRING];
	char owner[LONG_STRING];
	char phone[LONG_STRING];
	char addr_dong[SHORT_STRING];
	char addr_ho[SHORT_STRING];
	char regdate[LONG_STRING];
	char expdate[LONG_STRING];
	char reason[MAX_STRING];
	BYTE bwv; //1:black,2:white,4:visit
	BYTE alarm; //1:on,2:off
	BYTE allow_enter; //1:disallowed 2:allowed
} stCarInfo;

void CMySQLSampleDlg::OnBnClickedBtninsert()
{
	CString val_0 = "서울34너4444";
	CString val_1 = "승용차";
	CString val_2 = "현대";
	CString val_3 = "빨강";
	CString val_4 = "길동무";
	CString strSQL;
	stCarInfo stCarInfo;
	/*strSQL.Format("INSERT INTO tbl_car (plateNumber,type,manufacturer,color,owner) \
				VALUES (\'%s\',\'%s\',\'%s\',\'%s\',\'%s\');",
				val_0, val_1, val_2, val_3, val_4);*/
	strcpy(stCarInfo.platenumber, "서울34너4444");
	strcpy(stCarInfo.type,"1");
	strcpy(stCarInfo.manufacturer,"1");
	strcpy(stCarInfo.color,"1");
	strcpy(stCarInfo.owner,"1");
	strcpy(stCarInfo.phone, "1");
	strcpy(stCarInfo.addr_dong,"1");
	strcpy(stCarInfo.addr_ho, "1");
	strcpy(stCarInfo.regdate,"2021-03-16 12:36:00");
	strcpy(stCarInfo.expdate, "2022-03-16 12:36:00");
	strcpy(stCarInfo.reason, "1");
	stCarInfo.bwv = 1;
	stCarInfo.alarm = 1;
	stCarInfo.allow_enter = 1;
	strSQL.Format("INSERT INTO tbl_car( \
			plateNumber,type,manufacturer,color,owner,phone,addr_dong,addr_ho,regDate,expDate,reg_reason,bwv,remote_alarm,allow_enter) \
			VALUES(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',%d,%d,%d);",
		stCarInfo.platenumber,
		stCarInfo.type,
		stCarInfo.manufacturer,
		stCarInfo.color,
		stCarInfo.owner,
		stCarInfo.phone,
		stCarInfo.addr_dong,
		stCarInfo.addr_ho,
		stCarInfo.regdate,
		stCarInfo.expdate,
		stCarInfo.reason,
		stCarInfo.bwv,
		stCarInfo.alarm,
		stCarInfo.allow_enter);
	
    if (m_DB.InsertQuery(strSQL)==false)
	{ 
		MessageDisplay("Insert Fail");
	}
	else {
		MessageDisplay("Insert Success");
	}
}


void CMySQLSampleDlg::OnBnClickedBtnupdate()
{
	stCarInfo stCarInfo;
	CString strSQL;
	CString v1 = "2";
	strcpy(stCarInfo.platenumber, "서울34너4444");
	strcpy(stCarInfo.type,v1);
	strcpy(stCarInfo.manufacturer,v1);
	strcpy(stCarInfo.color,v1);
	strcpy(stCarInfo.owner,v1);
	strcpy(stCarInfo.phone, v1);
	strcpy(stCarInfo.addr_dong,v1);
	strcpy(stCarInfo.addr_ho, v1);
	strcpy(stCarInfo.regdate,"2021-03-16 12:36:00");
	strcpy(stCarInfo.expdate, "2022-03-16 12:36:00");
	strcpy(stCarInfo.reason, v1);
	stCarInfo.bwv = 1;
	stCarInfo.alarm = 1;
	stCarInfo.allow_enter = 1;
	strSQL.Format("UPDATE tbl_car SET  \
					plateNumber=\'%s\', \
					type=\'%s\', \
					manufacturer=\'%s\', \
					color=\'%s\', \
					owner=\'%s\', \
					phone=\'%s\', \
					addr_dong=\'%s\', \
					addr_ho=\'%s\', \
					regDate=\'%s\', \
					expDate=\'%s\', \
					reg_reason=\'%s\', \
					bwv=%d, \
					remote_alarm=%d, \
					allow_enter=%d \
					WHERE plateNumber=\'%s\';",
					stCarInfo.platenumber,
					stCarInfo.type,
					stCarInfo.manufacturer,
					stCarInfo.color,
					stCarInfo.owner,
					stCarInfo.phone,
					stCarInfo.addr_dong,
					stCarInfo.addr_ho,
					stCarInfo.regdate,
					stCarInfo.expdate,
					stCarInfo.reason,
					stCarInfo.bwv,
					stCarInfo.alarm,
					stCarInfo.allow_enter,
					stCarInfo.platenumber);

					if (m_DB.InsertQuery(strSQL) > 0)
					{
						MessageDisplay("Insert Fail");
					}
					else {
						MessageDisplay("Insert Success");
					}
}
void CMySQLSampleDlg::OnBnClickedBtndelete()
{
	stCarInfo stCarInfo;
	CString strSQL;
	CString v1 = "2";
	strcpy(stCarInfo.platenumber, "서울34너4444");
	strSQL.Format("DELETE FROM tbl_car WHERE plateNumber = \'%s\';", stCarInfo.platenumber);
	
	if (m_DB.DeleteQuery(strSQL)==0)
	{
		MessageDisplay("Insert Fail");
	}
	else {
		MessageDisplay("Insert Success");
	}

}
void CMySQLSampleDlg::OnBnClickedBtndbclose()
{
	
	m_DB.CloseDB();
	MessageDisplay("DB Close");

}
