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
	bool Help(Vertex avPath[MAX_NUM], int& nVexnum);	//��ʾ
	int isWin(int nTime);			//�ж��Ƿ�Ӯ�ñ���
	int isWin();			//�ж��Ƿ�Ӯ�ñ���
	void ResetGraph();		//����
protected:
	CGraph m_graph;	//��Ϸ��ͼ
	Vertex m_ptSelFirst;//ѡ�еĵ�һ����
	Vertex m_ptSelSec;	//���еĵڶ�����
};

