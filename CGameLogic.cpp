#include "pch.h"
#include "CGameLogic.h"


CGameLogic::CGameLogic() {
	this->m_nVexNum = 0;
	this->m_nCornerNum = 0;
}
//初始化地图
void CGameLogic::initMap(CGraph &g) {
	//初始化顶点
	int anTemp[MAX_NUM];
	for (int i = 0; i < MAX_PIC_NUM; i++) {
		for (int j = 0; j < REPEAT_NUM; j++) {
			anTemp[i * REPEAT_NUM + j] = i;
		}
	}
	//设置随机种子
	srand((unsigned)time(NULL));
	//随机交换两个数字
	for (int i = 0; i < 100; i++) {
		//随机得到两个坐标
		int index1 = rand() % MAX_NUM;
		int index2 = rand() % MAX_NUM;
		//交换两个数值
		int temp = anTemp[index1];
		anTemp[index1] = anTemp[index2];
		anTemp[index2] = temp;
	}
	//初始化顶点
	for (int i = 0; i < MAX_NUM; i++)
		g.AddVertex(anTemp[i]);
	//初始化边
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COL; j++)
			this->UpdateArc(g, i, j);
}

void CGameLogic::UpdateArc(CGraph& g, int nRow, int nCol) {
	//更新边
	int nIndex1 = nRow * MAX_COL + nCol;
	//左边
	if (nCol > 0) {
		int nIndex2 = nIndex1 - 1;
		int nInfo1 = g.GetVertex(nIndex1);
		int nInfo2 = g.GetVertex(nIndex2);
		if ((nInfo1 == nInfo2)||(nInfo1 ==BLANK)||(nInfo2 ==BLANK))
			g.AddArc(nIndex1,nIndex2);
	}
	//右边
	if (nCol < MAX_COL -1) {
		int nIndex2 = nIndex1 + 1;
		int nInfo1 = g.GetVertex(nIndex1);
		int nInfo2 = g.GetVertex(nIndex2);
		if ((nInfo1 == nInfo2) || (nInfo1 == BLANK) || (nInfo2 == BLANK))
			g.AddArc(nIndex1, nIndex2);
	}
	//上边
	if (nRow > 0) {
		int nIndex2 = nIndex1 - MAX_COL;
		int nInfo1 = g.GetVertex(nIndex1);
		int nInfo2 = g.GetVertex(nIndex2);
		if ((nInfo1 == nInfo2) || (nInfo1 == BLANK )||(nInfo2 == BLANK))
			g.AddArc(nIndex1, nIndex2);
	}
	//下边
	if (nRow < MAX_ROW - 1) {
		int nIndex2 = nIndex1 + MAX_COL;
		int nInfo1 = g.GetVertex(nIndex1);
		int nInfo2 = g.GetVertex(nIndex2);
		if ((nInfo1 == nInfo2) || (nInfo1 == BLANK) || (nInfo2 == BLANK))
			g.AddArc(nIndex1, nIndex2);
	}
}

void  CGameLogic::Clear(CGraph &g, Vertex v1, Vertex v2) {
	//清空连接的顶点
	//获取顶点数组中的索引号
	int nIndex1 = v1.row * MAX_COL + v1.col;
	int nIndex2 = v2.row * MAX_COL + v2.col;
	//更新顶点
	g.UpdateVertex(nIndex1, BLANK);
	g.UpdateVertex(nIndex2, BLANK);
	//更新边
	for (int i = 0; i < MAX_ROW ; i++)
		for (int j = 0; j < MAX_COL; j++)
			this->UpdateArc(g, i, j);
}


bool  CGameLogic::isLink(CGraph &g, Vertex v1, Vertex v2) {
	//判断是否连接
	//获取顶点数组中的索引号
	int nIndex1 = v1.row * MAX_COL + v1.col;
	int nIndex2 = v2.row * MAX_COL + v2.col;
	this->PushVertex(nIndex1);
	if (this->SearchPathW(g,nIndex1,nIndex2)) {
		this->PushVertex(nIndex2);
		return true;
	}
	else {
		this->PopVertex();
		return false;
	}
}

int CGameLogic::GetVexPath(Vertex avPath[MAX_NUM]) {
	//返回路径顶点个数
	for (int i = 0; i < this->m_nVexNum; i++) {
		avPath[i].col = this->m_anPath[i]% MAX_COL;
		avPath[i].row = this->m_anPath[i]/ MAX_COL;
	}
	int m = this->m_nVexNum;
	//this->m_nVexNum = 0;
	return m;
}

void CGameLogic::PushVertex(int v) {
	this->m_anPath[this->m_nVexNum] = v;
	this->m_nVexNum++;
	if (this->isCorner())
		this->m_nCornerNum++;
}

void CGameLogic::PopVertex() {
	if (this->isCorner())
		this->m_nCornerNum--;
	this->m_nVexNum--;
}

bool CGameLogic::SearchPathW(CGraph& g, int nV1, int nV2) {
	//深度优先搜索路径	
	//得到顶点数
	int nVexNum = g.GetVexNum();
	//遍历nV1行
	for (int nVi = 0; nVi < nVexNum; nVi++) {
		if (g.GetArc(nV1, nVi) && !this->isExit(nVi)) {
			//压入顶点，作为有效路劲的有效顶点
			this->PushVertex(nVi);
			if (this->m_nCornerNum > 2) {
				this->PopVertex();
				//this->m_nCornerNum = 0;
				continue;
			}
			//判断是否到头
			if (nVi != nV2) {
				//如果不是空就表示不通
				if (g.GetVertex(nVi) != BLANK) {
					this->PopVertex();
					continue;
				}
				//如果为空，递归
				if (this->SearchPathW(g, nVi, nV2)) {
					return true;
				}
			}
			else {
				return true;
			}
			this->PopVertex();
		}
	}
	return false;
}

bool CGameLogic::isExit(int nVi) {
	//判断元素是否保存到连通数组中
	for (int i = 0; i < this->m_nVexNum; i++) {
		if (this->m_anPath[i] == nVi)
			return true;
	}
	return false;
}

bool CGameLogic::isCorner() {
	//判断是否是拐点
	if (this->m_nVexNum >= 3) {
		if ((this->m_anPath[this->m_nVexNum - 1] +
			this->m_anPath[this->m_nVexNum - 3]) / 2
			== this->m_anPath[this->m_nVexNum - 2]) {
			return false;
		}
		else
			return true;
	}
	return false;
}

bool CGameLogic::isBlank(CGraph& g){
	//判断图是否为空
	int nVertex = g.GetVexNum();
	for (int i = 0; i < nVertex; i++) {
		if (g.GetVertex(i) != BLANK) {
			return false;
		}
	}
	return true;
}

bool CGameLogic::SrearchValidPath(CGraph& g) {
	//查找连通路径
	int nVertex = g.GetVexNum();
	//查找第一个不为空的点
	for (int i = 0; i < nVertex; i++) {
		if (g.GetVertex(i) != BLANK) {
			//找到与第一个图片相同的点
			for (int j = 0; j < nVertex; j++) {
				if ((i != j)&&(g.GetVertex(j) != BLANK)&&(g.GetVertex(i)== g.GetVertex(j))) {
					Vertex v1;
					Vertex v2;
					v1.col = i% MAX_COL;
		            v1.row = i/ MAX_COL;
					v2.col = j% MAX_COL;
		            v2.row = j/ MAX_COL;
					if (this->isLink(g, v1, v2))
						return true;
					else
						this->m_nVexNum = 0;
				}
			}
		}
	}
	return false;
}

void CGameLogic::ResetGraph(CGraph& g) {
	//重排
	//设置随机种子
	srand((int)time(NULL));
	//随机交换两个数字
	for (int i = 0; i < 100; i++) {
		//随机得到两个坐标
		int index1 = rand() % MAX_NUM;
		int index2 = rand() % MAX_NUM;
		//交换两个数值
		int temp = g.GetVertex(index1);
		g.SetVertex(index1, g.GetVertex(index2));
		g.SetVertex(index2, temp);
	}
	//更新边
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COL; j++)
			this->UpdateArc(g, i, j);
}