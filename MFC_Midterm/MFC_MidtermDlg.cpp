
// MFC_MidtermDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "MFC_Midterm.h"
#include "MFC_MidtermDlg.h"
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


// CMFCMidtermDlg 대화 상자



CMFCMidtermDlg::CMFCMidtermDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MFC_MIDTERM_DIALOG, pParent)
	, m_strBookName(_T(""))
	, m_strBookWriter(_T(""))
	, m_intBookType(1)   // 초기화
	, m_bForeignBook(false)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCMidtermDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_BNAME, m_strBookName);
	DDX_Text(pDX, IDC_EDIT_BWRITER, m_strBookWriter);
	DDX_Control(pDX, IDC_LIST_BOOKLIST, m_listBookList);
	DDX_Control(pDX, IDC_LIST_SELECT, m_listSelected);
	DDX_Control(pDX, IDC_COMBO_BORROW, m_comboBorrow);
	DDX_Control(pDX, IDC_COMBO_RETURN, m_comboReturn);
}

BEGIN_MESSAGE_MAP(CMFCMidtermDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(IDC_RADIO_LIBBOOK, &CMFCMidtermDlg::OnRadioLibbook)
	ON_COMMAND(IDC_RADIO_MAGAZINE, &CMFCMidtermDlg::OnRadioMagazine)
	ON_COMMAND(IDC_RADIO_MAJBOOK, &CMFCMidtermDlg::OnRadioMajbook)
	ON_BN_CLICKED(IDC_BUTTON_ENROLL, &CMFCMidtermDlg::OnClickedButtonEnroll)
	ON_BN_CLICKED(IDC_CHECK_FOREIGNBOOK, &CMFCMidtermDlg::OnClickedCheckForeignbook)
	ON_LBN_SELCHANGE(IDC_LIST_BOOKLIST, &CMFCMidtermDlg::OnSelchangeListBooklist)
	ON_BN_CLICKED(IDC_BUTTON_BORROW, &CMFCMidtermDlg::OnClickedButtonBorrow)
//	ON_BN_CLICKED(IDC_BUTTON_RETURN, &CMFCMidtermDlg::OnClickedButtonReturn)
ON_BN_CLICKED(IDC_BUTTON_RETURN, &CMFCMidtermDlg::OnClickedButtonReturn)
END_MESSAGE_MAP()


// CMFCMidtermDlg 메시지 처리기

BOOL CMFCMidtermDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

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

void CMFCMidtermDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CMFCMidtermDlg::OnPaint()
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
		CDialog::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CMFCMidtermDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMFCMidtermDlg::OnRadioLibbook()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_intBookType = 1;
}

void CMFCMidtermDlg::OnRadioMajbook()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_intBookType = 2;
}

void CMFCMidtermDlg::OnRadioMagazine()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	m_intBookType = 3;
	
}


void CMFCMidtermDlg::OnClickedButtonEnroll()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (AfxMessageBox(_T("등록 하시겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES) 
	{
		// 도서 대출 성공
		AfxMessageBox(_T("등록 되었습니다."));
		CString strBookType;
		CString strBookCountry = (m_bForeignBook) ?  _T("해외") : _T("국내");
		CString strList;

		if (m_intBookType == 1)
		{
			strBookType = "교양";
		}
		else if (m_intBookType == 2)
		{
			strBookType = "전공";
		}
		else 
		{
			strBookType = "잡지";
		}

		strList.Format(_T("%s, %s, %s, %s"), m_strBookName, m_strBookWriter, strBookType, strBookCountry);
		m_listBookList.AddString(strList);        // 리스트 박스에 내용 추가
		m_comboBorrow.AddString(strList);   // 콤보 박스에 내용 추가


		m_strBookName.Empty();
		m_strBookWriter.Empty();
	}
	else
	{
		AfxMessageBox(_T("등록이 취소 되었습니다."));
		m_strBookName.Empty();
		m_strBookWriter.Empty();

	}
	UpdateData(FALSE);
}


void CMFCMidtermDlg::OnClickedCheckForeignbook()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (m_bForeignBook)
	{
		m_bForeignBook = false;
	}
	else
	{
		m_bForeignBook = true;
	}
}


void CMFCMidtermDlg::OnSelchangeListBooklist()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	// 리스트에서 선택한 내용을 다른 리스트에 나타나게 설정
	UpdateData(TRUE);
	m_listSelected.ResetContent();      // 기존에 있던 리스트 박스의 내용을 삭제

	int index = m_listBookList.GetCurSel();
	CString str;
	m_listBookList.GetText(index, str);

	m_listSelected.AddString(str);
	UpdateData(FALSE);
}


void CMFCMidtermDlg::OnClickedButtonBorrow()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (AfxMessageBox(_T("대출 하시겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		// 도서 대출 성공
		AfxMessageBox(_T("대출 되었습니다."));

		int index = m_comboBorrow.GetCurSel();
		if (index != CB_ERR)  // 콤보 박스에서 무언가를 선택할 경우
		{
			CString strBorrow;
			m_comboBorrow.GetLBText(index, strBorrow);  // 현재 콤보 박스에서 선택된 내용을 strBorrow에 넣기
			m_comboBorrow.DeleteString(index);				   // 항목 지우기
			m_comboReturn.AddString(strBorrow);             // 반납 콤보 박스에 strBorrow의 내용 넣기
		}
	}
	else
	{
		AfxMessageBox(_T("대출이 취소 되었습니다."));
	}
	UpdateData(FALSE);
}

void CMFCMidtermDlg::OnClickedButtonReturn()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	UpdateData(TRUE);

	if (AfxMessageBox(_T("반납 하시겠습니까?"), MB_YESNO | MB_ICONQUESTION) == IDYES)
	{
		// 도서 반납 성공
		AfxMessageBox(_T("반납 되었습니다."));

		int index = m_comboReturn.GetCurSel();
		if (index != CB_ERR)  // 콤보 박스에서 무언가를 선택할 경우
		{
			CString strRent;
			m_comboReturn.GetLBText(index, strRent);    // 현재 콤보 박스에서 선택된 내용을 strRent에 넣기
			m_comboReturn.DeleteString(index);			    // 항목 지우기
			m_comboBorrow.AddString(strRent);             // 대출 콤보 박스에 strRent의 내용 넣기
		}
	}
	else
	{
		AfxMessageBox(_T("반납이 취소 되었습니다."));
	}
	UpdateData(FALSE);
}
