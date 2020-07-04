
// LLKDlg.h: 头文件
//

#pragma once
// CLLKDlg 对话框
class CLLKDlg : public CDialogEx{
// 构造
public:
	CLLKDlg(CWnd* pParent = nullptr);	// 标准构造函数
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LLK_DIALOG };
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持
// 实现
protected:
	HICON m_hIcon;
	CDC m_dcMem;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	void InitBackground();		//初始化主界面背景图片
public:
	afx_msg void OnBnClickedBtnBasic();
	void UpdateWindow();
	afx_msg void OnBnClickedBtnSetting();
	afx_msg void OnBnClickedBtnRelax();
};
