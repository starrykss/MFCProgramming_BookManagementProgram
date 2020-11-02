
// MFC_MidtermDlg.h: 헤더 파일
//

#pragma once


// CMFCMidtermDlg 대화 상자
class CMFCMidtermDlg : public CDialog
{
// 생성입니다.
public:
	CMFCMidtermDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFC_MIDTERM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


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
	CString m_strBookName;
	CString m_strBookWriter;
	afx_msg void OnRadioLibbook();
	afx_msg void OnRadioMagazine();
	afx_msg void OnRadioMajbook();
	int m_intBookType;   // 책의 종류 (교양서적, 전공서적, 잡지)
	afx_msg void OnClickedButtonEnroll();
	CListBox m_listBookList;
	afx_msg void OnClickedCheckForeignbook();
	bool m_bForeignBook;
	CListBox m_listSelected;
	afx_msg void OnSelchangeListBooklist();
	CComboBox m_comboBorrow;
	afx_msg void OnClickedButtonBorrow();
//	afx_msg void OnClickedButtonReturn();
	CComboBox m_comboReturn;
	afx_msg void OnClickedButtonReturn();
};
