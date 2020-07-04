#pragma once
#include"global.h"
class CGraph{
public:
	typedef int Vertices[MAX_NUM];
	typedef bool AdjMatrix[MAX_NUM][MAX_NUM];
	CGraph();
	void InitGraph();			//��ʼ��ͼ
	int AddVertex(int info);	//������info��ӵ�����������
	int GetVertex(int nIndex);	//��ȡ��������������ΪnIndex�Ķ���
	void AddArc(int nV1Index, int nV2Index);	//��ӹ�ϵ����
	bool GetArc(int nV1Index, int nV2Index);	//��ӹ�ϵ����
	int GetVexNum();			//��ȡ���������еĶ�����
	void UpdateVertex(int nIndex, int info);	//���½ڵ���Ϣ
	void ClearGraph();							//����ͼ�ṹ
	void SetVertex(int nIndex,int number);		//��������
protected:
	Vertices m_Vertices;		//��������
	AdjMatrix m_AdjMatrix;		//��ϵ����
	int m_nVexNum;				//��������
	int m_nArcnum;				//�ߵ�����
};

