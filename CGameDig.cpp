// CGameDig.cpp: 实现文件
//
#include "pch.h"
#include "LLK.h"
#include"global.h"
#include "CGameDig.h"
#include "afxdialogex.h"
#include"CGameLogic.h"
#include"CHelpDialog.h"

// CGameDig 对话框
IMPLEMENT_DYNAMIC(CGameDig, CDialogEx)
CGameDig::CGameDig(int Basic,CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent){
	this->m_ptGameTop.x = MAP_LITF;
	this->m_ptGameTop.y = MAP_TOP;
	this->m_sizeElem.cx = PIC_WIDTH;
	this->m_sizeElem.cy = PIC_HIGHT;
	this->m_rtGameRect.top = this->m_ptGameTop.y;
	this->m_rtGameRect.left = this->m_ptGameTop.x;
	this->m_rtGameRect.right = this->m_rtGameRect.left + this->m_sizeElem.cx * MAX_COL;
	this->m_rtGameRect.bottom = this->m_rtGameRect.top + this->m_sizeElem.cy * MAX_ROW;

	this->m_bFirstPoint = true;
	this->m_bePlaying = false;
	this->m_bPause = false;
	this->basicRelex = Basic;

}

CGameDig::~CGameDig(){
}
void CGameDig::DoDataExchange(CDataExchange* pDX){
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_TIME, m_GameProgress);
}

BEGIN_MESSAGE_MAP(CGameDig, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDig::OnClickedBtnStart)
	ON_WM_LBUTTONUP()
	ON_BN_CLICKED(IDC_BTN_PROMPT, &CGameDig::OnBnClickedBtnPrompt)
	ON_BN_CLICKED(IDC_BTN_STOP, &CGameDig::OnBnClickedBtnStop)
	ON_BN_CLICKED(IDC_BTN_RESTART, &CGameDig::OnBnClickedBtnRestart)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_HELP, &CGameDig::OnBnClickedBtnHelp)
END_MESSAGE_MAP()

// CGameDig 消息处理程序
//加载背景图片
void CGameDig::InitBackground(){
	CClientDC dc(this);
	HANDLE bmp = ::LoadImage(NULL, _T("Theme\\Picture\\001.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频内容兼容的dc
	this->m_dcBG.CreateCompatibleDC(&dc);
	//将位图资源选入dc
	this->m_dcBG.SelectObject(bmp);
	//初始化内存
	this->m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	this->m_dcMem.SelectObject(bmpMem);
	//绘制图片到内存DC
	this->m_dcMem.BitBlt(0, 0, 800, 600, &this->m_dcBG, 0, 0, SRCCOPY);
}

BOOL CGameDig::OnInitDialog(){
	CDialogEx::OnInitDialog();
	this->InitBackground();
	this->InitElement();
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CGameDig::OnPaint(){
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0,0,800,600,&this->m_dcMem,0,0,SRCCOPY);
	this->UpdateWindow();
}



//加载元素图片
void CGameDig::InitElement(){
	CClientDC dc(this);
	//加载图标
	HANDLE bmp = ::LoadImage(NULL, _T("Theme\\Picture\\element_2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	this->m_dcElement.CreateCompatibleDC(&dc);
	this->m_dcElement.SelectObject(bmp);
	//加载掩码
	HANDLE bmpMask = ::LoadImage(NULL, _T("Theme\\Picture\\element_2_mask.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	this->m_dcMask.CreateCompatibleDC(&dc);
	this->m_dcMask.SelectObject(bmpMask);
	//加载涨停图片
	HANDLE bmpPause = ::LoadImage(NULL, _T("Theme\\Picture\\element_3_pause.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	this->m_dcPause.CreateCompatibleDC(&dc);
	this->m_dcPause.SelectObject(bmpPause);

}

//开始游戏按钮响应
void CGameDig::OnClickedBtnStart(){
	//初始化游戏地图
	this->m_gameControl.startGame();
	//开始按钮禁用
	this->m_bePlaying = true;
	this->GetDlgItem(IDC_BTN_START)->EnableWindow(false);
	//设置进度条
	this->m_GameProgress.SetRange(0, 60 * 5);	//范围
	this->m_GameProgress.SetStep(-1);			//变化步长
	this->m_GameProgress.SetPos(60 * 5);		//初始位置
	//启动定时器
	if (this->basicRelex == BASIC) {
		this->SetTimer(PLAY_TIME_ID,1000,NULL);
	}
	//更新界面
	this->UpdateMap();
	//更新窗口
	InvalidateRect(this->m_rtGameRect,FALSE);
}

//更新棋盘
void CGameDig::UpdateMap(){
	int nTop = this->m_ptGameTop.y;
	int nLeft = this->m_ptGameTop.x;
	int nElemW = this->m_sizeElem.cx;
	int nElemH = this->m_sizeElem.cy;
	this->m_dcMem.BitBlt(0, 0, 800, 600, &this->m_dcBG, 0, 0, SRCCOPY);

	this->m_dcMem.BitBlt(this->m_rtGameRect.left, this->m_rtGameRect.top, 
		this->m_rtGameRect.Width(), this->m_rtGameRect.Height(),
		&this->m_dcBG, this->m_rtGameRect.left, this->m_rtGameRect.top, SRCCOPY);
	for (int i = 0; i < MAX_ROW ; i++) {
		for (int j = 0; j < MAX_COL; j++) {
			int ninfo = m_gameControl.getElement(i, j);
			this->m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &this->m_dcMask, 0, ninfo * nElemH, SRCPAINT);
			this->m_dcMem.BitBlt(nLeft + j * nElemW, nTop + i * nElemH, nElemW, nElemH, &this->m_dcElement, 0, ninfo * nElemH, SRCAND);
		}
	}
	InvalidateRect(this->m_rtGameRect, FALSE);
}

//设置窗口大小
void CGameDig::UpdateWindow(){
	//获得窗口大小
	CRect rtWin;
	CRect rtClient;
	this->GetWindowRect(rtWin);
	this->GetClientRect(rtClient);
	//获得标题栏和外边框大小
	int nSpanWidth = rtWin.Width() - rtClient.Width();
	int nSpanHeigth = rtWin.Height() - rtClient.Height();
	//设置窗口大小
	MoveWindow(0, 0, 800 + nSpanWidth, 600 + nSpanHeigth);
	CenterWindow();
}


void CGameDig::OnLButtonUp(UINT nFlags, CPoint point){
	//连线
	if (point.x < this->m_ptGameTop.x || point.y < this->m_ptGameTop.y) {
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	int nRow = (point.y - this->m_ptGameTop.y) / this->m_sizeElem.cy;
	int nCol = (point.x - this->m_ptGameTop.x) / this->m_sizeElem.cx;
	if(nRow>=MAX_ROW||nCol>=MAX_COL)
		return CDialogEx::OnLButtonUp(nFlags, point);

	if (this->m_bFirstPoint) {
		this->DrawTipFrame(nRow, nCol);
		this->m_gameControl.setFirstPoint(nRow, nCol);
	}
	else { 
		this->DrawTipFrame(nRow, nCol);
		this->m_gameControl.setSecPoint(nRow, nCol);
		//判断是否是相同图片
		Vertex avPath[MAX_NUM];
		int nVexNum;
		if (this->m_gameControl.Link(avPath,nVexNum)) {
			this->DrawTopLine(avPath, nVexNum);
			this->UpdateMap();
		}
		Sleep(200);
		InvalidateRect(this->m_rtGameRect,FALSE);
		this->JudgeWin();
	}
	this->m_bFirstPoint = !this->m_bFirstPoint;
}

void CGameDig::DrawTipFrame(int nRow, int nCol){
	//绘制矩形框
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFram;
	rtTipFram.left = this->m_ptGameTop.x + nCol * this->m_sizeElem.cx;
	rtTipFram.top = this->m_ptGameTop.y + nRow * this->m_sizeElem.cy;
	rtTipFram.right = rtTipFram.left + this->m_sizeElem.cx;
	rtTipFram.bottom = rtTipFram.top + this->m_sizeElem.cy;
	dc.FrameRect(rtTipFram, &brush);
}

void CGameDig::DrawTopLine(Vertex avPath[MAX_NUM], int nVexNum){
	// 绘制连线
	CClientDC dc(this);
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));
	CPen *pOldpen = dc.SelectObject(&penLine);
	for (int i = 0; i < nVexNum-1; i++) {
		dc.MoveTo(this->m_ptGameTop.x + avPath[i].col * this->m_sizeElem.cx + this->m_sizeElem.cx / 2,
			this->m_ptGameTop.y + avPath[i].row * this->m_sizeElem.cy + this->m_sizeElem.cy / 2);
		dc.LineTo(this->m_ptGameTop.x + avPath[i+1].col * this->m_sizeElem.cx + this->m_sizeElem.cx / 2,
			this->m_ptGameTop.y + avPath[i+1].row * this->m_sizeElem.cy + this->m_sizeElem.cy / 2);
	}
	dc.SelectObject(pOldpen);
}


void CGameDig::OnBnClickedBtnPrompt(){
	//提示按钮
	Vertex avPath[MAX_NUM];
	int nVexNum;
	if (this->m_gameControl.Help(avPath, nVexNum)) {
		this->DrawTipFrame(avPath[0].row, avPath[0].col);
		this->DrawTipFrame(avPath[nVexNum - 1].row, avPath[nVexNum - 1].col);
		this->DrawTopLine(avPath, nVexNum);
		this->UpdateMap();
	}
	else {
		MessageBox(_T("没有找到"));
	}
	Sleep(200);
	InvalidateRect(this->m_rtGameRect, FALSE);
}

void CGameDig::OnBnClickedBtnStop(){
	//暂停按钮
	if (this->m_bPause)
	{
		this->m_bPause = false;
		this->m_bePlaying = true;
		//打开定时器
		if (this->basicRelex == BASIC) {
			SetTimer(PLAY_TIME_ID, 1000, NULL);
		}
		this->UpdateMap();
		Invalidate(TRUE);
	}
	else if (this->m_bePlaying)
	{
		this->m_bePlaying = false;
		this->m_bPause = true;
		//切断定时器
		if (this->basicRelex == BASIC) {
			KillTimer(PLAY_TIME_ID);
		}
	    this->m_dcMem.BitBlt(MAP_LITF,MAP_TOP, 
			MAP_LITF+ MAX_COL * PIC_WIDTH, 
			MAP_TOP+MAX_ROW* PIC_HIGHT, 
			&this->m_dcPause,0,0, SRCCOPY);
		Invalidate(TRUE);
	}
}


void CGameDig::OnBnClickedBtnRestart(){
	//重排按钮
	this->m_gameControl.ResetGraph();
	//更新界面
	this->UpdateMap();
	//重绘界面	
	InvalidateRect(this->m_rtGameRect, FALSE);
}


void CGameDig::OnTimer(UINT_PTR nIDEvent){
	if (nIDEvent == PLAY_TIME_ID && this->m_bePlaying) {
		//游戏时间减少1秒
		this->m_GameProgress.StepIt();
	}
	this->JudgeWin();
	CDialogEx::OnTimer(nIDEvent);
}

void CGameDig::JudgeWin(){
	//判断胜负
	//获取游戏状态
	int bGameStatus = this->m_gameControl.isWin(this->m_GameProgress.GetPos());
	//判断是否继续
	if (bGameStatus == GAME_PLAY) {
		return;
	}
	else {
		//将游戏标示改为false
		this->m_bePlaying = false;
		//关闭定时器
		KillTimer(PLAY_TIME_ID);
		//提示获胜
		CString strTitle;
		this->GetWindowTextW(strTitle);
		if (bGameStatus == GAME_SUCCESS) {
			MessageBox(_T("获胜"),strTitle);
		}
		else if (bGameStatus == GAME_LOSE) {
			MessageBox(_T("很遗憾，时间到了"),strTitle);
		}
		//还原开始按钮
		this->GetDlgItem(IDC_BTN_START)->EnableWindow(true);
	}
}


void CGameDig::OnBnClickedBtnHelp(){
	//帮助按钮
	//创建窗口
	if (this->basicRelex == BASIC) {
		CHelpDialog dlg(1);
		//显示窗口
		dlg.DoModal();
	}
	else {
		CHelpDialog dlg(2);
		//显示窗口
		dlg.DoModal();
	}

	
}