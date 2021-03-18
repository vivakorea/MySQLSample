#pragma once

#include "CMyDB.h"
// CSMSCheckDlg 대화 상자
#include "sms_define.h"
class CSMSCheckDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSMSCheckDlg)

	stDBInfo m_DBInfo;
	CMyDB  m_DB;
	void ReadDBInfo();
	stDBInfo GetDBInfo();

	stSMSInfo  m_smsInfo;

public:
	CSMSCheckDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CSMSCheckDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SMS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtndbconnect();
	afx_msg

	void OnBnClickedBtninsert();
	void MessageDisplay(CString szMsg);
	BOOL MakeSMSInfo(stSMSInfo& smsInfo);
	char* GetCurrentTimeString();
	CString GetDlgContentString(int id);
	void InsertSQL_small();
	void InsertSQL_Large();
	virtual BOOL OnInitDialog();
};
