#pragma once
#include"global.h"
#include"CGameLogic.h"
#include"CGraph.h"

class CGameControl
{
public:
	void startGame();
	int getElement(int nRow, int nCol);
	void setFirstPoint(int nRow, int nCol);
	void setSecPoint(int nRow, int nCol);
	bool Link(Vertex avPath[MAX_NUM], int& nVexNum);
	bool Help(Vertex avPath[MAX_NUM], int& nVexnum);	//提示
	int isWin(int nTime);			//判断是否赢得比赛
	int isWin();			//判断是否赢得比赛
	void ResetGraph();		//重排
protected:
	CGraph m_graph;	//游戏地图
	Vertex m_ptSelFirst;//选中的第一个点
	Vertex m_ptSelSec;	//传中的第二个点
};

