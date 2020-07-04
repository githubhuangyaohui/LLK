#pragma once
#include"global.h"
#include"CGraph.h"
class CGameLogic
{
protected:
	int m_nVexNum;						//·���������
	int m_anPath[MAX_NUM];				//��ͨ����
	int m_nCornerNum;					//�յ����
public:
	CGameLogic();									//���캯��
	void initMap(CGraph& g);						//��ʼ��ͼ
	bool isLink(CGraph &g, Vertex v1, Vertex v2);	//���������Ƿ�����
	void Clear(CGraph &g, Vertex v1, Vertex v2);	//������ӵĶ���
	int GetVexPath(Vertex avPath[MAX_NUM]);			//��������·��·��
	void PushVertex(int v);							//·������ѹջ
	void PopVertex();								//·�������ջ
	bool SearchPathW(CGraph& g, int nV1, int nV2);	//�����������·��
	bool isExit(int nVi);							//�ж�Ԫ���Ƿ񱣴浽��ͨ������
	bool isBlank(CGraph& g);						//�ж�ͼ�Ƿ�Ϊ��
	bool SrearchValidPath(CGraph& g);				//������ͨ·��
	void ResetGraph(CGraph& g);						//����
protected:
	void UpdateArc(CGraph& g,int nRow,int nCol);	//����ͼ�ı�
	bool isCorner();								//�ж��Ƿ��ǹյ�
};
 
