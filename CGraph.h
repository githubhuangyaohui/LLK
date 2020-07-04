#pragma once
#include"global.h"
class CGraph{
public:
	typedef int Vertices[MAX_NUM];
	typedef bool AdjMatrix[MAX_NUM][MAX_NUM];
	CGraph();
	void InitGraph();			//初始化图
	int AddVertex(int info);	//将顶点info添加到顶点数组中
	int GetVertex(int nIndex);	//获取顶点数组中索引为nIndex的顶点
	void AddArc(int nV1Index, int nV2Index);	//添加关系矩阵
	bool GetArc(int nV1Index, int nV2Index);	//添加关系矩阵
	int GetVexNum();			//获取顶点数组中的顶点数
	void UpdateVertex(int nIndex, int info);	//更新节点信息
	void ClearGraph();							//清理图结构
	void SetVertex(int nIndex,int number);		//设置数据
protected:
	Vertices m_Vertices;		//顶点数组
	AdjMatrix m_AdjMatrix;		//关系矩阵
	int m_nVexNum;				//顶点数量
	int m_nArcnum;				//边的数量
};

