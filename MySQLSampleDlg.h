
// MySQLSampleDlg.h: 헤더 파일
//

#pragma once

#include "CMyDB.h"
// CMySQLSampleDlg 대화 상자
class CMySQLSampleDlg : public CDialogEx
{
// 생성입니다.
public:
	CMySQLSampleDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MYSQLSAMPLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.

private:

	void ReadDBInfo();
	stDBInfo m_DBInfo;
	CMyDB  m_DB;

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg	void OnBnClickedBtnquery();
	
	afx_msg void OnBnClickedBtninsert();
	afx_msg void OnBnClickedBtndbclose();
	afx_msg void OnBnClickedBtndbconnect();



public:
	afx_msg void OnBnClickedBtnupdate();
	afx_msg void OnBnClickedBtndelete();


	void MessageDisplay(CString szMsg);
};
