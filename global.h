#pragma once

#define BLANK -1		//��
#define MAX_COL 16		//��
#define MAX_ROW 10		//��
#define MAX_NUM 160		//������
#define MAX_PIC_NUM 16	//ͼƬ��ɫ
#define REPEAT_NUM 10		//ÿ�ֻ�ɫͼƬ����
#define	MAP_TOP 50		//��Ϸ��ͼ���Ͻ�������
#define MAP_LITF 20		//��Ϸ��ͼ���ϽǺ�����
#define PIC_WIDTH 40	//��ϷͼƬ���
#define PIC_HIGHT 40	//��ϷͼƬ�߶�
#define GAME_LOSE -1
#define GAME_SUCCESS 1
#define GAME_PLAY 0
#define PLAY_TIME_ID 1	//��ʱ��ID
#define GAME_MODEL_BASE 1
#define GAME_MODEL_EASY 2
#define GAME_MAIN_FRAME 3
#define RELEX 0			//����ģʽ
#define BASIC 1			//����ģʽ

typedef struct tagVertex {
	int row;	//��
	int col;	//��
	int info;	//��Ϣ
}Vertex;