#include "pch.h"
#include "CGraph.h"

CGraph::CGraph() {
	this->InitGraph();
}

void CGraph::InitGraph() {
	//初始化顶点
	for (int i = 0; i < MAX_NUM; i++) {
		this->m_Vertices[i] = -1;
	}
	//初始化边
	for (int i = 0; i < MAX_NUM; i++) {
		for (int j = 0; j < MAX_NUM; j++) {
			this->m_AdjMatrix[i][j] = 0;
		}
	}
	this->m_nArcnum = 0;
	this->m_nVexNum = 0;
}

int CGraph::AddVertex(int info) {
	if (this->m_nVexNum >= MAX_NUM)
		return this->m_nVexNum;
	this->m_Vertices[this->m_nVexNum] = info;
	this->m_nVexNum++;
	return this->m_nVexNum;
}

int CGraph::GetVertex(int nIndex) {
	return this->m_Vertices[nIndex];
}

void CGraph::AddArc(int nV1Index, int nV2Index) {
	this->m_AdjMatrix[nV1Index][nV2Index] = true;
	this->m_AdjMatrix[nV2Index][nV1Index] = true;
}

bool CGraph::GetArc(int nV1Index, int nV2Index) {
	return this->m_AdjMatrix[nV1Index][nV2Index];
}

int CGraph::GetVexNum() {
	return this->m_nVexNum;
}

void CGraph::UpdateVertex(int nIndex, int info) {
	this->m_Vertices[nIndex] = info;
}

void CGraph::ClearGraph(){
	this->InitGraph();
}
void CGraph::SetVertex(int nIndex,int number) {
	//设置数据
	this->m_Vertices[nIndex] = number;
}