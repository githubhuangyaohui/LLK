#include "pch.h"
#include "CGameControl.h"
void CGameControl::startGame() {
	//开始游戏
	CGameLogic gameLogic;
	gameLogic.initMap(this->m_graph);
}

int CGameControl::getElement(int nRow, int nCol) {
	return this->m_graph.GetVertex(nRow * MAX_COL + nCol);
}

void CGameControl::setFirstPoint(int nRow, int nCol) {
	this->m_ptSelFirst.row = nRow;
	this->m_ptSelFirst.col = nCol;

}
void CGameControl::setSecPoint(int nRow, int nCol) {
	this->m_ptSelSec.row = nRow;
	this->m_ptSelSec.col = nCol;
}
bool CGameControl::Link(Vertex avPath[MAX_NUM],int &nVexNum) {
	//判断是否连接
	CGameLogic logic;
	//是否是同一位置
	if ((this->m_ptSelFirst.col == this->m_ptSelSec.col)
		&& (this->m_ptSelFirst.row == this->m_ptSelSec.row))
		return false;
	//是否是同一图片
	else if (this->m_graph.GetVertex(this->m_ptSelFirst.row * MAX_COL + this->m_ptSelFirst.col)
		!= this->m_graph.GetVertex(this->m_ptSelSec.row * MAX_COL + this->m_ptSelSec.col)) {
		return false;
	}
	else {
		if (logic.isLink(this->m_graph,this->m_ptSelFirst,this->m_ptSelSec)) {
			//消子
			logic.Clear(this->m_graph, this->m_ptSelFirst, this->m_ptSelSec);
			//返回路径顶点
			nVexNum = logic.GetVexPath(avPath);
			return true;
		}
		return false;
	}
}
int CGameControl::isWin(int nTime) {
	//判断胜负
	CGameLogic logic;
	if (nTime <= 0) {
		this->m_graph.ClearGraph();
		return GAME_LOSE;
	}
	//判断是否清空
	if (logic.isBlank(this->m_graph)) {
		this->m_graph.ClearGraph();
		return GAME_SUCCESS;
	}
	return GAME_PLAY;
}

int CGameControl::isWin() {
	//判断胜负
	CGameLogic logic;
	//判断是否清空
	if (logic.isBlank(this->m_graph)) {
		this->m_graph.ClearGraph();
		return GAME_SUCCESS;
	}
	return GAME_PLAY;
}

bool CGameControl::Help(Vertex avPath[MAX_NUM], int& nVexnum) {
	//提示
	CGameLogic logic;
	if (logic.isBlank(this->m_graph))
		return false;
	else if (logic.SrearchValidPath(this->m_graph)) {
		nVexnum=logic.GetVexPath(avPath);
		return true;
	}
	else
		return false;
}

void CGameControl::ResetGraph() {
	//重排
	CGameLogic logic;
	logic.ResetGraph(this->m_graph);
}