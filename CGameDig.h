#pragma once
#include"global.h"
#include"CGameControl.h"

// CGameDig 对话框
class CGameDig : public CDialogEx{
	DECLARE_DYNAMIC(CGameDig)
public:
	CGameDig(int Basic,CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CGameDig();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	DECLARE_MESSAGE_MAP()
public:
	void InitBackground();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
protected:
	CDC m_dcMem;
	CDC m_dcElement;
	CDC m_dcMask;
	CDC m_dcBG;
	CDC m_dcPause;	//暂停图片
	
	CPoint m_ptGameTop;	
	CSize m_sizeElem;
	CRect m_rtGameRect;
	CGameControl m_gameControl;
	bool m_bFirstPoint;
	bool m_bePlaying;
	bool m_bPause;
	int basicRelex;
	void InitElement();
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	void UpdateMap();
	void UpdateWindow();
	void DrawTipFrame(int nRow, int nCol);
	void DrawTopLine(Vertex avPath[MAX_NUM],int nVexNum);
	afx_msg void OnClickedBtnStart();
	afx_msg void OnBnClickedBtnPrompt();
	afx_msg void OnBnClickedBtnStop();
	afx_msg void OnBnClickedBtnRestart();
	CProgressCtrl m_GameProgress;
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void JudgeWin();
	afx_msg void OnBnClickedBtnHelp();
};
