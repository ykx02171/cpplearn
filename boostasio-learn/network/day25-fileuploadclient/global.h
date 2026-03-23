#ifndef GLOBAL_H
#define GLOBAL_H

#include<QString>

//单元格像素
#define CELL_WH 60
//地图单元格列数
#define MAP_COLS 20
//地图单元格行数
#define MAP_ROWS 16

//地图宽高
#define MAP_WIDTH MAP_COLS*CELL_WH
#define MAP_HEIGHT MAP_ROWS*CELL_WH

//英雄图片素材宽度
#define IMG_WIDTH 32
//英雄图片素材高度
#define IMG_HEIGHT 48
//英雄图片素材数量
#define IMG_COUNT 10

//英雄下移
#define ACT_DOWN 0
//英雄左移
#define ACT_LEFT 1
//英雄右移
#define ACT_RIGHT 2
//英雄上移
#define ACT_UP 3

//移动动作帧数量
#define STEP_COUNT 4
//移动动作帧编号
#define STEP1 0
#define STEP2 1
#define STEP3 2
#define STEP4 3

//英雄移动步长
#define MOVE_STEP 5

//TCP包头长度
#define TCP_HEAD_LEN 6
//TCP ID长度
#define TCP_ID_LEN 2
//TCP 长度字段的长度
#define TCP_LEN_LEN 4
//最大文件长度
#define MAX_FILE_LEN 2048

enum MsgId {
    ID_TEST_MSG_REQ = 1001,       //测试消息
    ID_TEST_MSG_RSP = 1002,       //测试消息回包
    ID_UPLOAD_FILE_REQ = 1003,    //发送文件请求
    ID_UPLOAD_FILE_RSP = 1004,    //发送文件回复
};

enum RspErr{
    RSP_SUCCESS = 0,          //正常回包
    RSP_INVALID_ID = 1,       //消息id不正确
};

extern QString generateUniqueId();

#endif // GLOBAL_H
