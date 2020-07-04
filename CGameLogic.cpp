#include "pch.h"
#include "CGameLogic.h"


CGameLogic::CGameLogic() {
	this->m_nVexNum = 0;
	this->m_nCornerNum = 0;
}
//��ʼ����ͼ
void CGameLogic::initMap(CGraph &g) {
	//��ʼ������
	int anTemp[MAX_NUM];
	for (int i = 0; i < MAX_PIC_NUM; i++) {
		for (int j = 0; j < REPEAT_NUM; j++) {
			anTemp[i * REPEAT_NUM + j] = i;
		}
	}
	//�����������
	srand((unsigned)time(NULL));
	//���������������
	for (int i = 0; i < 100; i++) {
		//����õ���������
		int index1 = rand() % MAX_NUM;
		int index2 = rand() % MAX_NUM;
		//����������ֵ
		int temp = anTemp[index1];
		anTemp[index1] = anTemp[index2];
		anTemp[index2] = temp;
	}
	//��ʼ������
	for (int i = 0; i < MAX_NUM; i++)
		g.AddVertex(anTemp[i]);
	//��ʼ����
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COL; j++)
			this->UpdateArc(g, i, j);
}

void CGameLogic::UpdateArc(CGraph& g, int nRow, int nCol) {
	//���±�
	int nIndex1 = nRow * MAX_COL + nCol;
	//���
	if (nCol > 0) {
		int nIndex2 = nIndex1 - 1;
		int nInfo1 = g.GetVertex(nIndex1);
		int nInfo2 = g.GetVertex(nIndex2);
		if ((nInfo1 == nInfo2)||(nInfo1 ==BLANK)||(nInfo2 ==BLANK))
			g.AddArc(nIndex1,nIndex2);
	}
	//�ұ�
	if (nCol < MAX_COL -1) {
		int nIndex2 = nIndex1 + 1;
		int nInfo1 = g.GetVertex(nIndex1);
		int nInfo2 = g.GetVertex(nIndex2);
		if ((nInfo1 == nInfo2) || (nInfo1 == BLANK) || (nInfo2 == BLANK))
			g.AddArc(nIndex1, nIndex2);
	}
	//�ϱ�
	if (nRow > 0) {
		int nIndex2 = nIndex1 - MAX_COL;
		int nInfo1 = g.GetVertex(nIndex1);
		int nInfo2 = g.GetVertex(nIndex2);
		if ((nInfo1 == nInfo2) || (nInfo1 == BLANK )||(nInfo2 == BLANK))
			g.AddArc(nIndex1, nIndex2);
	}
	//�±�
	if (nRow < MAX_ROW - 1) {
		int nIndex2 = nIndex1 + MAX_COL;
		int nInfo1 = g.GetVertex(nIndex1);
		int nInfo2 = g.GetVertex(nIndex2);
		if ((nInfo1 == nInfo2) || (nInfo1 == BLANK) || (nInfo2 == BLANK))
			g.AddArc(nIndex1, nIndex2);
	}
}

void  CGameLogic::Clear(CGraph &g, Vertex v1, Vertex v2) {
	//������ӵĶ���
	//��ȡ���������е�������
	int nIndex1 = v1.row * MAX_COL + v1.col;
	int nIndex2 = v2.row * MAX_COL + v2.col;
	//���¶���
	g.UpdateVertex(nIndex1, BLANK);
	g.UpdateVertex(nIndex2, BLANK);
	//���±�
	for (int i = 0; i < MAX_ROW ; i++)
		for (int j = 0; j < MAX_COL; j++)
			this->UpdateArc(g, i, j);
}


bool  CGameLogic::isLink(CGraph &g, Vertex v1, Vertex v2) {
	//�ж��Ƿ�����
	//��ȡ���������е�������
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
	//����·���������
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
	//�����������·��	
	//�õ�������
	int nVexNum = g.GetVexNum();
	//����nV1��
	for (int nVi = 0; nVi < nVexNum; nVi++) {
		if (g.GetArc(nV1, nVi) && !this->isExit(nVi)) {
			//ѹ�붥�㣬��Ϊ��Ч·������Ч����
			this->PushVertex(nVi);
			if (this->m_nCornerNum > 2) {
				this->PopVertex();
				//this->m_nCornerNum = 0;
				continue;
			}
			//�ж��Ƿ�ͷ
			if (nVi != nV2) {
				//������ǿվͱ�ʾ��ͨ
				if (g.GetVertex(nVi) != BLANK) {
					this->PopVertex();
					continue;
				}
				//���Ϊ�գ��ݹ�
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
	//�ж�Ԫ���Ƿ񱣴浽��ͨ������
	for (int i = 0; i < this->m_nVexNum; i++) {
		if (this->m_anPath[i] == nVi)
			return true;
	}
	return false;
}

bool CGameLogic::isCorner() {
	//�ж��Ƿ��ǹյ�
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
	//�ж�ͼ�Ƿ�Ϊ��
	int nVertex = g.GetVexNum();
	for (int i = 0; i < nVertex; i++) {
		if (g.GetVertex(i) != BLANK) {
			return false;
		}
	}
	return true;
}

bool CGameLogic::SrearchValidPath(CGraph& g) {
	//������ͨ·��
	int nVertex = g.GetVexNum();
	//���ҵ�һ����Ϊ�յĵ�
	for (int i = 0; i < nVertex; i++) {
		if (g.GetVertex(i) != BLANK) {
			//�ҵ����һ��ͼƬ��ͬ�ĵ�
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
	//����
	//�����������
	srand((int)time(NULL));
	//���������������
	for (int i = 0; i < 100; i++) {
		//����õ���������
		int index1 = rand() % MAX_NUM;
		int index2 = rand() % MAX_NUM;
		//����������ֵ
		int temp = g.GetVertex(index1);
		g.SetVertex(index1, g.GetVertex(index2));
		g.SetVertex(index2, temp);
	}
	//���±�
	for (int i = 0; i < MAX_ROW; i++)
		for (int j = 0; j < MAX_COL; j++)
			this->UpdateArc(g, i, j);
}