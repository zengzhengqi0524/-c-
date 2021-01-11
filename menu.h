#ifndef _MENU_H_
#define _MENU_H_

//命令类型
typedef enum {
    affirm = 1,
    back = 2,
    up = 3,
    down = 4,
    home = 5
} Cmmond;
//获取命令的函数类型
Cmmond(*_getCmmond)(int *arg);
/* 当前路径 */
char currentPath[1024];
/*菜单结构体*/
typedef struct menu
{
    //当前界面名称
    char *interFaceName;
    //当前选择的项开始及结束符号
    unsigned char range_from, range_to;
    //项目总数
    unsigned char itemCount;
    //当前选择项
    unsigned char selected;
    //菜单项目
    char **menuItems;
    //选择相应命令后执行的函数
    void(**func)(int *arg);
    //子菜单
    struct menu *subMenus[100];
    //上级菜单，若是主菜单则为null
    struct menu *parent;
}Menu;
Menu *currentMenu;//当前菜单
Menu *initMenu; //初始界面

Menu *createInterface(Menu *rootMem, char *interFcaeName,unsigned char range_from,     //当前项的开始序号
    unsigned char range_to, unsigned char itemCount, unsigned char selected, char **menuItems, void(**func)(int *arg));
void menuRun(int* arg);
int setInitInterFace(Menu* initmenu, Cmmond (*_getCmmond)(int *arg));
#endif