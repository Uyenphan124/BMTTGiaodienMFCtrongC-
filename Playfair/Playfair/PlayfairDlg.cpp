// PlayfairDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Playfair.h"
#include "PlayfairDlg.h"
#include "afxdialogex.h"
#include <string> // Include the <string> header file
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
    CAboutDlg();

    // Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_ABOUTBOX };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

    // Implementation
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

// CPlayfairDlg dialog

CPlayfairDlg::CPlayfairDlg(CWnd* pParent /*=nullptr*/)
    : CDialogEx(IDD_PLAYFAIR_DIALOG, pParent)
    , Banma(_T(""))
    , Khoa(_T(""))
{
    m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPlayfairDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Text(pDX, IDC_Cipher, Banma);
    DDX_Text(pDX, IDC_Key, Khoa);
    DDX_Control(pDX, IDC_Result, ketqua);
    DDX_Control(pDX, IDC_EDIT4, MATRAN11);
    DDX_Control(pDX, IDC_EDIT5, MATRAN12);
    DDX_Control(pDX, IDC_EDIT6, MATRAN13);
    DDX_Control(pDX, IDC_EDIT7, MATRAN14);
    DDX_Control(pDX, IDC_EDIT8, MATRAN15);
    DDX_Control(pDX, IDC_EDIT9, MATRAN21);
    DDX_Control(pDX, IDC_EDIT10, MATRAN22);
    DDX_Control(pDX, IDC_EDIT11, MATRAN23);
    DDX_Control(pDX, IDC_EDIT12, MATRAN24);
    DDX_Control(pDX, IDC_EDIT13, MATRAN25);
    DDX_Control(pDX, IDC_EDIT14, MATRAN31);
    DDX_Control(pDX, IDC_EDIT15, MATRAN32);
    DDX_Control(pDX, IDC_EDIT16, MATRAN33);
    DDX_Control(pDX, IDC_EDIT17, MATRAN34);
    DDX_Control(pDX, IDC_EDIT18, MATRAN35);
    DDX_Control(pDX, IDC_EDIT19, MATRAN41);
    DDX_Control(pDX, IDC_EDIT20, MATRAN42);
    DDX_Control(pDX, IDC_EDIT21, MATRAN43);
    DDX_Control(pDX, IDC_EDIT22, MATRAN44);
    DDX_Control(pDX, IDC_EDIT23, MATRAN45);
    DDX_Control(pDX, IDC_EDIT24, MATRAN51);
    DDX_Control(pDX, IDC_EDIT25, MATRAN52);
    DDX_Control(pDX, IDC_EDIT26, MATRAN53);
    DDX_Control(pDX, IDC_EDIT27, MATRAN54);
    DDX_Control(pDX, IDC_EDIT28, MATRAN55);
}

BEGIN_MESSAGE_MAP(CPlayfairDlg, CDialogEx)
    ON_WM_SYSCOMMAND()
    ON_WM_PAINT()
    ON_WM_QUERYDRAGICON()
    ON_BN_CLICKED(IDC_BUTTON1, &CPlayfairDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

// CPlayfairDlg message handlers

BOOL CPlayfairDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();
    std::string key(CT2A(Khoa.GetBuffer()));
    std::string playfairMatrix = BuildPlayfairMatrix(key);
    UpdateMatrixUI(playfairMatrix);

    // Add "About..." menu item to system menu.

    // IDM_ABOUTBOX must be in the system command range.
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

    // Set the icon for this dialog.  The framework does this automatically
    //  when the application's main window is not a dialog
    SetIcon(m_hIcon, TRUE);         // Set big icon
    SetIcon(m_hIcon, FALSE);        // Set small icon

    // TODO: Add extra initialization here

    return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPlayfairDlg::OnSysCommand(UINT nID, LPARAM lParam)
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
void CPlayfairDlg::UpdateMatrixUI(const std::string& matrix)
{
    CEdit* editControls[] = {
        &MATRAN11, &MATRAN12, &MATRAN13, &MATRAN14, &MATRAN15,
        &MATRAN21, &MATRAN22, &MATRAN23, &MATRAN24, &MATRAN25,
        &MATRAN31, &MATRAN32, &MATRAN33, &MATRAN34, &MATRAN35,
        &MATRAN41, &MATRAN42, &MATRAN43, &MATRAN44, &MATRAN45,
        &MATRAN51, &MATRAN52, &MATRAN53, &MATRAN54, &MATRAN55
    };

    int charIndex = 0;
    for (CEdit* editControl : editControls) {
        std::string text = std::string(1, matrix[charIndex]);
        CString cstrText(text.c_str());
        editControl->SetWindowText(cstrText);
        charIndex++;
    }
}



std::string CPlayfairDlg::BuildPlayfairMatrix(const std::string& key)
{
    std::string matrix = key;
    std::string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";

    // Remove J and duplicates from the key
    std::string::iterator end_pos = std::remove(matrix.begin(), matrix.end(), 'J');
    matrix.erase(end_pos, matrix.end());
    matrix.erase(std::unique(matrix.begin(), matrix.end()), matrix.end());

    // Append the remaining alphabet characters to the key
    for (char c : alphabet) {
        if (c != 'J' && matrix.find(c) == std::string::npos) {
            matrix += c;
        }
    }

    // Append 'X' if the matrix size is less than 25
    while (matrix.size() < 25) {
        matrix += 'X';
    }

    return matrix.substr(0, 25); // Return only the first 25 characters
}
// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPlayfairDlg::OnPaint()
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
HCURSOR CPlayfairDlg::OnQueryDragIcon()
{
    return static_cast<HCURSOR>(m_hIcon);
}

// Decrypts the ciphertext using the Playfair decryption algorithm
std::string CPlayfairDlg::DECRYPTION(const std::string& Ciphertext, const std::string& k)
{
    std::string result = "";
    std::string Alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    std::string new_k = "";
    for (char c : k) {
        // Create a string by iterating through each character in the key "k"; Remove non-alphabetic characters, "J", and duplicates
        if (isalpha(c) && c != 'J' && new_k.find(toupper(c)) == std::string::npos) {
            new_k += toupper(c);
        }
    }
    // Build the 5x5 matrix
    for (char c : Alphabet) {
        if (c != 'J' && new_k.find(c) == std::string::npos) {
            new_k += c;
        }
    }
    // Add missing characters from 'a' to 'z' to the new key
    for (char c = 'A'; c <= 'Z'; ++c) {
        if (c != 'J' && new_k.find(c) == std::string::npos) {
            new_k += c;
        }
    }

    // Add missing character to the Playfair matrix
    new_k += 'X';

    char playfair[5][5];
    int key = 0;
    for (int i = 0; i < 5; i++) {
        // Traverse each pair of characters; Perform Playfair decryption
        for (int j = 0; j < 5; j++) {
            playfair[i][j] = new_k[key];
            key++;
        }
    }
    for (size_t i = 0; i < Ciphertext.length(); i += 2) {
        char a = Ciphertext[i];
        char b = Ciphertext[i + 1];
        int row1, col1, row2, col2;
        for (int j = 0; j < 5; j++) {
            if (a == 'J') {
                a = 'I';
            }
            if (b == 'J') {
                b = 'I';
            }
            if (playfair[j][0] == a || playfair[j][1] == a || playfair[j][2] == a || playfair[j][3] == a || playfair[j][4] == a) {
                row1 = j;
                col1 = static_cast<int>(std::find(std::begin(playfair[j]), std::end(playfair[j]), a) - std::begin(playfair[j]));

            }
            if (playfair[j][0] == b || playfair[j][1] == b || playfair[j][2] == b || playfair[j][3] == b || playfair[j][4] == b) {
                row2 = j;
                col2 = static_cast<int>(std::find(std::begin(playfair[j]), std::end(playfair[j]), b) - std::begin(playfair[j]));

            }
        }
        if (row1 == row2) {
            col1 = (col1 + 4) % 5;
            col2 = (col2 + 4) % 5;
        }
        else if (col1 == col2) {
            row1 = (row1 + 4) % 5;
            row2 = (row2 + 4) % 5;
        }
        else {
            std::swap(col1, col2);
        }
        result += playfair[row1][col1];
        result += playfair[row2][col2];
    }
    return result;
}

void CPlayfairDlg::OnBnClickedButton1()
{
    UpdateData(TRUE); // Update data from controls

    std::string ciphertext(CT2A(Banma.GetBuffer())); // Convert CString to std::string
    std::string key(CT2A(Khoa.GetBuffer())); // Convert CString to std::string

    Banma.ReleaseBuffer(); // Release buffer after use
    Khoa.ReleaseBuffer(); // Release buffer after use

    // Build Playfair matrix
    std::string playfairMatrix = BuildPlayfairMatrix(key);

    // Update Playfair matrix UI
    UpdateMatrixUI(playfairMatrix);

    CString result(DECRYPTION(ciphertext, key).c_str()); // Decrypt ciphertext
    ketqua.SetWindowText(result); // Show decrypted text
}
