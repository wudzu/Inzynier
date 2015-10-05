
// GUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "GUI.h"
#include "GUIDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString metoda, zmienna, trivest, tnormalny, m, r, plaintext, seed, finalna, krok, testy, zera, tablica, tryb;
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGUIDlg dialog




CGUIDlg::CGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CGUIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_RADIO1, &CGUIDlg::OnBnClickedRadio1)
	ON_BN_CLICKED(IDC_RADIO2, &CGUIDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO3, &CGUIDlg::OnBnClickedRadio3)
	ON_BN_CLICKED(IDC_RADIO4, &CGUIDlg::OnBnClickedRadio4)
	ON_BN_CLICKED(IDC_RADIO5, &CGUIDlg::OnBnClickedRadio5)
	ON_BN_CLICKED(IDC_RADIO6, &CGUIDlg::OnBnClickedRadio6)
	ON_BN_CLICKED(IDC_RADIO7, &CGUIDlg::OnBnClickedRadio7)
	ON_BN_CLICKED(IDC_RADIO8, &CGUIDlg::OnBnClickedRadio8)
	ON_BN_CLICKED(IDC_RADIO9, &CGUIDlg::OnBnClickedRadio9)
	ON_BN_CLICKED(IDC_RADIO10, &CGUIDlg::OnBnClickedRadio10)
	ON_EN_CHANGE(IDC_EDIT1, &CGUIDlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CGUIDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CGUIDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CGUIDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CGUIDlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &CGUIDlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, &CGUIDlg::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, &CGUIDlg::OnEnChangeEdit8)
	ON_EN_CHANGE(IDC_EDIT9, &CGUIDlg::OnEnChangeEdit9)
	ON_BN_CLICKED(IDOK, &CGUIDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT10, &CGUIDlg::OnEnChangeEdit10)
	ON_BN_CLICKED(IDC_RADIO11, &CGUIDlg::OnBnClickedRadio11)
	ON_BN_CLICKED(IDC_RADIO12, &CGUIDlg::OnBnClickedRadio12)
	ON_BN_CLICKED(IDC_RADIO13, &CGUIDlg::OnBnClickedRadio13)
	ON_BN_CLICKED(IDC_RADIO14, &CGUIDlg::OnBnClickedRadio14)
	ON_BN_CLICKED(IDC_BUTTON1, &CGUIDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDCANCEL, &CGUIDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CGUIDlg message handlers

BOOL CGUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CGUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CGUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CGUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CGUIDlg::OnBnClickedRadio1()
{
	((CButton*) GetDlgItem(IDC_RADIO11))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO12))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO11))->SetCheck(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO12))->SetCheck(FALSE);
	((CButton*) GetDlgItem(IDC_EDIT10))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_EDIT10))->SetWindowText(0);
	((CButton*) GetDlgItem(IDC_RADIO7))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_RADIO8))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO8))->SetCheck(FALSE);	
	((CButton*) GetDlgItem(IDC_RADIO10))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_EDIT2))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_EDIT2))->SetWindowText(0);
	((CButton*) GetDlgItem(IDC_EDIT4))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_EDIT1))->EnableWindow(TRUE);
}


void CGUIDlg::OnBnClickedRadio2()
{
	((CButton*) GetDlgItem(IDC_RADIO11))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO12))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO11))->SetCheck(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO12))->SetCheck(FALSE);
	((CButton*) GetDlgItem(IDC_EDIT10))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_EDIT10))->SetWindowText(0);
	((CButton*) GetDlgItem(IDC_RADIO7))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO7))->SetCheck(FALSE);	
	((CButton*) GetDlgItem(IDC_RADIO8))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_RADIO10))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_EDIT2))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_EDIT1))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_EDIT1))->SetWindowText(0);
	((CButton*) GetDlgItem(IDC_EDIT4))->EnableWindow(TRUE);
}


void CGUIDlg::OnBnClickedRadio3()
{
	((CButton*) GetDlgItem(IDC_RADIO11))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_RADIO12))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_EDIT10))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_EDIT10))->SetWindowText(0);
	((CButton*) GetDlgItem(IDC_RADIO7))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_RADIO8))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO8))->SetCheck(FALSE);	
	((CButton*) GetDlgItem(IDC_RADIO1))->SetCheck(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO10))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO10))->SetCheck(FALSE);	
	((CButton*) GetDlgItem(IDC_EDIT2))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_EDIT2))->SetWindowText(0);
	((CButton*) GetDlgItem(IDC_EDIT4))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_EDIT4))->SetWindowText(0);
	((CButton*) GetDlgItem(IDC_EDIT1))->EnableWindow(TRUE);
}


void CGUIDlg::OnBnClickedRadio4()
{
	((CButton*) GetDlgItem(IDC_RADIO11))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO12))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO11))->SetCheck(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO12))->SetCheck(FALSE);
	((CButton*) GetDlgItem(IDC_EDIT10))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_EDIT10))->SetWindowText(0);
	((CButton*) GetDlgItem(IDC_RADIO7))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_RADIO8))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO8))->SetCheck(FALSE);	
	((CButton*) GetDlgItem(IDC_RADIO10))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_EDIT2))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_EDIT2))->SetWindowText(0);
	((CButton*) GetDlgItem(IDC_EDIT4))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_EDIT1))->EnableWindow(TRUE);
}


void CGUIDlg::OnBnClickedRadio5()
{
	((CButton*) GetDlgItem(IDC_RADIO11))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO12))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO11))->SetCheck(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO12))->SetCheck(FALSE);
	((CButton*) GetDlgItem(IDC_EDIT10))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_RADIO7))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO7))->SetCheck(FALSE);	
	((CButton*) GetDlgItem(IDC_RADIO8))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_RADIO10))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_EDIT2))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_EDIT1))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_EDIT1))->SetWindowText(0);
	((CButton*) GetDlgItem(IDC_EDIT4))->EnableWindow(TRUE);
}


void CGUIDlg::OnBnClickedRadio6()
{
	((CButton*) GetDlgItem(IDC_RADIO11))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_RADIO12))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_EDIT10))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_EDIT10))->SetWindowText(0);
	((CButton*) GetDlgItem(IDC_RADIO7))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_RADIO8))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO8))->SetCheck(FALSE);	
	((CButton*) GetDlgItem(IDC_RADIO1))->SetCheck(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO10))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO10))->SetCheck(FALSE);	
	((CButton*) GetDlgItem(IDC_EDIT2))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_EDIT2))->SetWindowText(0);
	((CButton*) GetDlgItem(IDC_EDIT4))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_EDIT4))->SetWindowText(0);
	((CButton*) GetDlgItem(IDC_EDIT1))->EnableWindow(TRUE);
}


void CGUIDlg::OnBnClickedRadio7()
{
	// TODO: Add your control notification handler code here
}


void CGUIDlg::OnBnClickedRadio8()
{
	// TODO: Add your control notification handler code here
}


void CGUIDlg::OnBnClickedRadio9()
{
	// TODO: Add your control notification handler code here
}


void CGUIDlg::OnBnClickedRadio10()
{
	// TODO: Add your control notification handler code here
}


void CGUIDlg::OnBnClickedRadio11()
{
	// TODO: Add your control notification handler code here
}


void CGUIDlg::OnBnClickedRadio12()
{
	// TODO: Add your control notification handler code here
}


void CGUIDlg::OnBnClickedRadio13()
{
	((CButton*) GetDlgItem(IDC_RADIO1))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO2))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO3))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO4))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO5))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO6))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO7))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO8))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO9))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO10))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO11))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO12))->EnableWindow(FALSE);

	((CButton*) GetDlgItem(IDC_RADIO1))->SetCheck(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO2))->SetCheck(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO3))->SetCheck(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO4))->SetCheck(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO5))->SetCheck(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO6))->SetCheck(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO7))->SetCheck(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO8))->SetCheck(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO9))->SetCheck(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO10))->SetCheck(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO11))->SetCheck(FALSE);
	((CButton*) GetDlgItem(IDC_RADIO12))->SetCheck(FALSE);

	((CButton*) GetDlgItem(IDC_EDIT2))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_EDIT2))->SetWindowText(0);
	((CButton*) GetDlgItem(IDC_EDIT7))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_EDIT7))->SetWindowText(0);
	((CButton*) GetDlgItem(IDC_EDIT8))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_EDIT8))->SetWindowText(0);
	((CButton*) GetDlgItem(IDC_EDIT9))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_EDIT9))->SetWindowText(0);
	((CButton*) GetDlgItem(IDC_EDIT10))->EnableWindow(FALSE);
	((CButton*) GetDlgItem(IDC_EDIT10))->SetWindowText(0);
}


void CGUIDlg::OnBnClickedRadio14()
{
	((CButton*) GetDlgItem(IDC_RADIO1))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_RADIO2))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_RADIO3))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_RADIO4))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_RADIO5))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_RADIO6))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_RADIO7))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_RADIO8))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_RADIO9))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_RADIO10))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_RADIO11))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_RADIO12))->EnableWindow(TRUE);

	((CButton*) GetDlgItem(IDC_EDIT2))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_EDIT4))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_EDIT7))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_EDIT8))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_EDIT9))->EnableWindow(TRUE);
	((CButton*) GetDlgItem(IDC_EDIT10))->EnableWindow(TRUE);
}


void CGUIDlg::OnEnChangeEdit1()
{
	//if(IsDlgButtonChecked(IDC_RADIO2) != BST_CHECKED || IsDlgButtonChecked(IDC_RADIO4) != BST_CHECKED)
		GetDlgItemText(IDC_EDIT1,tnormalny);
}


void CGUIDlg::OnEnChangeEdit2()
{
	//if(IsDlgButtonChecked(IDC_RADIO2) == BST_CHECKED || IsDlgButtonChecked(IDC_RADIO4) == BST_CHECKED)
		GetDlgItemText(IDC_EDIT2,trivest);
}


void CGUIDlg::OnEnChangeEdit3()
{
		GetDlgItemText(IDC_EDIT3,m);
}


void CGUIDlg::OnEnChangeEdit4()
{
		GetDlgItemText(IDC_EDIT4,r);
}


void CGUIDlg::OnEnChangeEdit5()
{
		GetDlgItemText(IDC_EDIT5,plaintext);
}


void CGUIDlg::OnEnChangeEdit6()
{
		GetDlgItemText(IDC_EDIT6,seed);
}


void CGUIDlg::OnEnChangeEdit7()
{
		GetDlgItemText(IDC_EDIT7,finalna);
}


void CGUIDlg::OnEnChangeEdit8()
{
		GetDlgItemText(IDC_EDIT8,krok);
}


void CGUIDlg::OnEnChangeEdit9()
{
		GetDlgItemText(IDC_EDIT9,testy);
}

void CGUIDlg::OnEnChangeEdit10()
{
		GetDlgItemText(IDC_EDIT10,zera);
}

void CGUIDlg::OnBnClickedOk()
{
	if(IsDlgButtonChecked(IDC_RADIO1) == BST_CHECKED)
		metoda="1";
	else if(IsDlgButtonChecked(IDC_RADIO2) == BST_CHECKED)
		metoda="2";
	else if(IsDlgButtonChecked(IDC_RADIO3) == BST_CHECKED)
		metoda="3";
	else if(IsDlgButtonChecked(IDC_RADIO4) == BST_CHECKED)
		metoda="4";
	else if(IsDlgButtonChecked(IDC_RADIO5) == BST_CHECKED)
		metoda="5";
	else if(IsDlgButtonChecked(IDC_RADIO6) == BST_CHECKED)
		metoda="6";
	else
		metoda="1";

	if(IsDlgButtonChecked(IDC_RADIO7) == BST_CHECKED || IsDlgButtonChecked(IDC_RADIO8) == BST_CHECKED )
		zmienna="0";
	else if(IsDlgButtonChecked(IDC_RADIO9) == BST_CHECKED)
		zmienna="1";
	else if(IsDlgButtonChecked(IDC_RADIO10) == BST_CHECKED)
		zmienna="2";
	else
		zmienna="0";

	if(IsDlgButtonChecked(IDC_RADIO11) == BST_CHECKED)
		tablica="1";
	else if(IsDlgButtonChecked(IDC_RADIO12) == BST_CHECKED)
		tablica="0";
	else
		tablica="0";

	if(IsDlgButtonChecked(IDC_RADIO13) == BST_CHECKED)
		tryb="0";
	else if(IsDlgButtonChecked(IDC_RADIO14) == BST_CHECKED)
		tryb="1";
	else
		tryb="1";

	if(trivest.IsEmpty() && tnormalny.IsEmpty())
		trivest="1"; tnormalny="1";	
	if(m.IsEmpty())
		m="1";
	if(r.IsEmpty())
		r="1";
	if(plaintext.IsEmpty())
		plaintext="1";
	if(seed.IsEmpty())
		seed="1";
	if(finalna.IsEmpty())
		finalna="100";
	if(krok.IsEmpty())
		krok="1";
	if(testy.IsEmpty())
		testy="1";
	if(zera.IsEmpty())
		zera="1";

	CStdioFile plik;
	if(plik.Open(_T("temp.txt"), CFile::modeCreate|CFile::modeWrite))
	{	
		plik.WriteString(_T("Poczatek: 0\n"));
		plik.WriteString(_T("Tryb: "));
		plik.WriteString(tryb);
		plik.WriteString(_T("\n"));
		plik.WriteString(_T("Metoda: "));
		plik.WriteString(metoda);
		plik.WriteString(_T("\n"));
		plik.WriteString(_T("Zmienna: "));
		plik.WriteString(zmienna);
		plik.WriteString(_T("\n"));
		plik.WriteString(_T("t: "));
		if(trivest.IsEmpty())
			plik.WriteString(tnormalny);
		else
			plik.WriteString(trivest);
		plik.WriteString(_T("\n"));
		plik.WriteString(_T("m: "));
		plik.WriteString(m);
		plik.WriteString(_T("\n"));
		plik.WriteString(_T("r: "));
		plik.WriteString(r);
		plik.WriteString(_T("\n"));
		plik.WriteString(_T("Plaintext: "));
		plik.WriteString(plaintext);
		plik.WriteString(_T("\n"));
		plik.WriteString(_T("Seed: "));
		plik.WriteString(seed);
		plik.WriteString(_T("\n"));
		plik.WriteString(_T("Finalna: "));
		plik.WriteString(finalna);
		plik.WriteString(_T("\n"));
		plik.WriteString(_T("Krok: "));
		plik.WriteString(krok);
		plik.WriteString(_T("\n"));
		plik.WriteString(_T("Testy: "));
		plik.WriteString(testy);
		plik.WriteString(_T("\n"));
		plik.WriteString(_T("Zera: "));
		plik.WriteString(zera);
		plik.WriteString(_T("\n"));
		plik.WriteString(_T("Tablica: "));
		plik.WriteString(tablica);
		plik.WriteString(_T("\n"));
		plik.WriteString(_T("Wykonano: 0\n"));
	}

	ShellExecute(0,NULL,_T("krypto.exe"), NULL, NULL, SW_SHOWNORMAL);
	CDialogEx::OnOK();
}


void CGUIDlg::OnBnClickedButton1()
{
	ShellExecute(0,NULL,_T("krypto.exe"), NULL, NULL, SW_SHOWNORMAL);
	CDialogEx::OnOK();
}


void CGUIDlg::OnBnClickedCancel()
{
	CDialogEx::OnCancel();
}
