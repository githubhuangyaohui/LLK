#include "pch.h"
#include "CGameControl.h"
void CGameControl::startGame() {
	//��ʼ��Ϸ
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
	//�ж��Ƿ�����
	CGameLogic logic;
	//�Ƿ���ͬһλ��
	if ((this->m_ptSelFirst.col == this->m_ptSelSec.col)
		&& (this->m_ptSelFirst.row == this->m_ptSelSec.row))
		return false;
	//�Ƿ���ͬһͼƬ
	else if (this->m_graph.GetVertex(this->m_ptSelFirst.row * MAX_COL + this->m_ptSelFirst.col)
		!= this->m_graph.GetVertex(this->m_ptSelSec.row * MAX_COL + this->m_ptSelSec.col)) {
		return false;
	}
	else {
		if (logic.isLink(this->m_graph,this->m_ptSelFirst,this->m_ptSelSec)) {
			//����
			logic.Clear(this->m_graph, this->m_ptSelFirst, this->m_ptSelSec);
			//����·������
			nVexNum = logic.GetVexPath(avPath);
			return true;
		}
		return false;
	}
}
int CGameControl::isWin(int nTime) {
	//�ж�ʤ��
	CGameLogic logic;
	if (nTime <= 0) {
		this->m_graph.ClearGraph();
		return GAME_LOSE;
	}
	//�ж��Ƿ����
	if (logic.isBlank(this->m_graph)) {
		this->m_graph.ClearGraph();
		return GAME_SUCCESS;
	}
	return GAME_PLAY;
}

int CGameControl::isWin() {
	//�ж�ʤ��
	CGameLogic logic;
	//�ж��Ƿ����
	if (logic.isBlank(this->m_graph)) {
		this->m_graph.ClearGraph();
		return GAME_SUCCESS;
	}
	return GAME_PLAY;
}

bool CGameControl::Help(Vertex avPath[MAX_NUM], int& nVexnum) {
	//��ʾ
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
	//����
	CGameLogic logic;
	logic.ResetGraph(this->m_graph);
}