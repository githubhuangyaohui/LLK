#pragma once

#define BLANK -1		//空
#define MAX_COL 16		//列
#define MAX_ROW 10		//行
#define MAX_NUM 160		//定点数
#define MAX_PIC_NUM 16	//图片花色
#define REPEAT_NUM 10		//每种花色图片个数
#define	MAP_TOP 50		//游戏地图左上角纵坐标
#define MAP_LITF 20		//游戏地图左上角横坐标
#define PIC_WIDTH 40	//游戏图片宽度
#define PIC_HIGHT 40	//游戏图片高度
#define GAME_LOSE -1
#define GAME_SUCCESS 1
#define GAME_PLAY 0
#define PLAY_TIME_ID 1	//计时器ID
#define GAME_MODEL_BASE 1
#define GAME_MODEL_EASY 2
#define GAME_MAIN_FRAME 3
#define RELEX 0			//休闲模式
#define BASIC 1			//基本模式

typedef struct tagVertex {
	int row;	//行
	int col;	//列
	int info;	//信息
}Vertex;