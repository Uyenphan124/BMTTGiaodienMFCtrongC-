#pragma once


// CPlayfairDlg dialog
class CPlayfairDlg : public CDialogEx
{
    // Construction
public:
    CPlayfairDlg(CWnd* pParent = nullptr);    // standard constructor

    // Dialog Data
#ifdef AFX_DESIGN_TIME
    enum { IDD = IDD_PLAYFAIR_DIALOG };
#endif

protected:
    virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support


    // Implementation
protected:
    HICON m_hIcon;

    // Generated message map functions
    virtual BOOL OnInitDialog();
    afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
    afx_msg void OnPaint();
    afx_msg HCURSOR OnQueryDragIcon();
    DECLARE_MESSAGE_MAP()
private:
    CString Banma;
    CString Khoa;
public:
    afx_msg void OnBnClickedButton1();

    // Decrypts the ciphertext using the Playfair decryption algorithm
    std::string DECRYPTION(const std::string& Ciphertext, const std::string& k);
    CStatic ketqua;
    CEdit MATRAN11;
    CEdit MATRAN12;
    CEdit MATRAN13;
    CEdit MATRAN14;
    CEdit MATRAN15;
    CEdit MATRAN21;
    CEdit MATRAN22;
    CEdit MATRAN23;
    CEdit MATRAN24;
    CEdit MATRAN25;
    CEdit MATRAN31;
    CEdit MATRAN32;
    CEdit MATRAN33;
    CEdit MATRAN34;
    CEdit MATRAN35;
    CEdit MATRAN41;
    CEdit MATRAN42;
    CEdit MATRAN43;
    CEdit MATRAN44;
    CEdit MATRAN45;
    CEdit MATRAN51;
    CEdit MATRAN52;
    CEdit MATRAN53;
    CEdit MATRAN54;
    CEdit MATRAN55;

    // Update the UI with the Playfair matrix
    void UpdateMatrixUI(const std::string& matrix);
    // Build the Playfair matrix based on the key
    std::string BuildPlayfairMatrix(const std::string& key);
};
