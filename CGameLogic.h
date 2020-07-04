#pragma once
#include"global.h"
#include"CGraph.h"
class CGameLogic
{
protected:
	int m_nVexNum;						//路径顶点个数
	int m_anPath[MAX_NUM];				//连通数组
	int m_nCornerNum;					//拐点个数
public:
	CGameLogic();									//构造函数
	void initMap(CGraph& g);						//初始化图
	bool isLink(CGraph &g, Vertex v1, Vertex v2);	//两个顶点是否连接
	void Clear(CGraph &g, Vertex v1, Vertex v2);	//清除连接的顶点
	int GetVexPath(Vertex avPath[MAX_NUM]);			//返回连接路径路径
	void PushVertex(int v);							//路径顶点压栈
	void PopVertex();								//路径顶点出栈
	bool SearchPathW(CGraph& g, int nV1, int nV2);	//深度优先搜索路径
	bool isExit(int nVi);							//判断元素是否保存到连通数组中
	bool isBlank(CGraph& g);						//判断图是否为空
	bool SrearchValidPath(CGraph& g);				//查找连通路径
	void ResetGraph(CGraph& g);						//重拍
protected:
	void UpdateArc(CGraph& g,int nRow,int nCol);	//更新图的边
	bool isCorner();								//判断是否是拐点
};
 
