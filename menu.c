#include "menu.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
 * 描述：根据输入的名称查找菜单序号并返回
 */
int cMenuSerch(char **menuItems, char *interFcaeName, unsigned char lenth) {
    int cnt = 0;
    for (cnt = 0; cnt < lenth; cnt++) {
        if (menuItems[cnt] == interFcaeName)
            return cnt;
    }
    return -1;
}
/**
 * 描述：根据输入的名称查找菜单的地址并返回,利用递归的方法寻找
 */
Menu *pMenuSerch(Menu *rootMem, char *interFaceName) {
    Menu *pMem = rootMem, *pMem1 = rootMem, *pMem2 = rootMem;
    int cnt = 0;
    int _serial = 0;
    if (rootMem == NULL || interFaceName == NULL)
        return NULL;
    _serial = cMenuSerch(pMem->menuItems, interFaceName, pMem->itemCount);
    if (_serial != -1)
        return pMem;
    else {
        for (cnt = 0; cnt < pMem->itemCount; cnt++) {
            if (pMem->subMenus[cnt] != NULL) {
                pMem1 = pMem->subMenus[cnt];
                pMem2 = pMenuSerch(pMem1, interFaceName);
                if (pMem2 != NULL) {
                    return pMem2;
                }
            }
        }
        return NULL;
    }
}
/**
 * 描述：创建一个菜单界面，返回值：创建结果，失败返回 NULL
 */
Menu *createInterface(
    Menu *rootMem,                //根目录
    char *interFcaeName,          //要创建的界面名称
    unsigned char range_from,     //当前项的开始序号
    unsigned char range_to,       //当前项的结束序号
    unsigned char itemCount,      //项目总数
    unsigned char selected,       //当前选择项
    char **menuItems,             //项目的显示名称
    void(**func)(int *arg)      //每个项目选中后要执行的函数组
)
{
    Menu* menu = malloc(sizeof(Menu));
    int serial = 0;
    if (!menu || !interFcaeName)
        return NULL;
    menu->func = malloc(sizeof(func) * itemCount);
    if (!menu->subMenus || !menu->func)
        return NULL;
    memset((char *)menu, (char)0, sizeof(Menu));
    if (rootMem == NULL) {
        goto root;
    }
    Menu* pmenu = pMenuSerch(rootMem, interFcaeName);
    menu->parent = pmenu;
    serial = cMenuSerch(pmenu->menuItems, interFcaeName, pmenu->itemCount);
    if(serial != -1)
        pmenu->subMenus[serial] = menu;
root:
    menu->interFaceName = interFcaeName;
    menu->range_from = range_from;
    menu->range_to = range_to;
    menu->itemCount = itemCount;
    menu->selected = selected;
    menu->menuItems = menuItems;
    menu->func = func;
    return menu;
}

/**
 * 设置初始化界面和输入函数
 */
int setInitInterFace(Menu* initmenu, Cmmond(*getCmmond)(int *arg)) {
    if (initmenu == NULL || getCmmond == NULL)
        return 0;
    initMenu = initmenu;
    currentMenu = initmenu;
    _getCmmond = getCmmond;
    return 1;
}
//LCD版本显示菜单
/*
void displayMenu(unsigned char line){
    int i;
    line = 3-(currentMenu->range_to-line);
    for(i = 0;i<4;i++)
    Display_LCD_String(i,currentMenu->menuItems[i+currentMenu->range_from],5);
    con_disp(line,1);
}
*/
//更新当前路径将变量保存在currentPath中
void getCurrenPath() {
    int cnt = 0;
    char pName[30][20];
    memset(currentPath, 0, 1024);
    Menu *pMenu = currentMenu;
    while (pMenu) {
        strcpy(pName[cnt], pMenu->interFaceName);
        pMenu = pMenu->parent;
        cnt++;
    }
    strcpy(currentPath,"PATH:");
    while (cnt) {
        strcat(currentPath,"/");
        strcat(currentPath, pName[cnt - 1]);
        cnt--;
    }
}
//控制台打印菜单版本
void displayMenu(unsigned char line) {
    int cnt = 0;
    system("clear");
    printf("   多级菜单的显示\n");
    getCurrenPath();
    printf("当前路径：%s\n", currentPath);
    line = 3 - (currentMenu->range_to - line);
    for (cnt = 0; cnt < 4; cnt++) {
        if (cnt == line)
            printf("   --> %s\n", currentMenu->menuItems[cnt + currentMenu->range_from]);
        else
            printf("       %s\n", currentMenu->menuItems[cnt + currentMenu->range_from]);
    }
    printf("W:向上 S:向下 A:确认 D:返回 Q:Home\n");
}
/**
 * 功能：菜单运行函数，arg为备用参数 备注：该函数应该占用一个线程
 */
void menuRun(int* arg) {
    displayMenu(currentMenu->selected);
    while (1) {
        Cmmond cmmond = _getCmmond(arg);
        switch (cmmond)
        {
        case affirm:
            if (currentMenu->func[currentMenu->selected] != NULL) {
                currentMenu->func[currentMenu->selected](arg);
                displayMenu(currentMenu->selected);
            }
            if (currentMenu->subMenus[currentMenu->selected] != NULL) {
                currentMenu = currentMenu->subMenus[currentMenu->selected];
                displayMenu(currentMenu->selected);
            }
            break;
        case back:
            if (currentMenu->parent != NULL) {
                currentMenu = currentMenu->parent;
                displayMenu(currentMenu->selected);
            }
            break;
        case up:
            if (currentMenu->selected == 0)
                break;
            else {
                currentMenu->selected--;
                if (currentMenu->selected < currentMenu->range_from) {
                    currentMenu->range_from = currentMenu->selected;
                    currentMenu->range_to = currentMenu->range_from + 3;
                }
                displayMenu(currentMenu->selected);
            }
            break;
        case down:
            if (currentMenu->selected == currentMenu->itemCount - 1)
                break;
            else {
                currentMenu->selected++;
                if (currentMenu->selected > currentMenu->range_to) {
                    currentMenu->range_to = currentMenu->selected;
                    currentMenu->range_from = currentMenu->range_to - 3;
                }
                displayMenu(currentMenu->selected);
            }
            break;
        case home:
            currentMenu = initMenu;
            displayMenu(currentMenu->selected);
            break;
        default:
            break;
        }

    }
}