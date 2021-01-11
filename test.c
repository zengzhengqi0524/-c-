#include "menu.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
char *root[10] = {
    "一级项目一",
    "一级项目二",
    "一级项目三",
    "一级项目四",
    "一级项目五",
    "一级项目六"
};
char *root1[12] = {
    "二级-2项目一",
    "二级-2项目二",
    "二级-2项目三",
    "二级-2项目四",
    "二级-2项目五",
    "二级-2项目六"
};
char *root2[12] = {
    "二级-3项目一",
    "二级-3项目二",
    "二级-3项目三",
    "二级-3项目四",
    "二级-3项目五",
    "二级-3项目六"
};
char *root3[12] = {
    "三级-1项目一",
    "三级-1项目二",
    "三级-1项目三",
    "三级-1项目四",
    "三级-1项目五",
    "三级-1项目六"
};

void fun(int *arg) {
    if (arg == NULL) {
        printf("测试\n");
        return;
    }
    printf("项目%d测试成功!\n", *arg);
}

void(*func[3])(int *arg) = {
    &fun,
    &fun,
    &fun,
};

int keyInt() {
    int key = getchar();
    switch (key) {
    case 'w':
        return 3;
        break;
    case 's':
        return 4;
        break;
    case 'a':
        return 1;
        break;
    case 'd':
        return 2;
    break;
    case 'q':
        return 5;
        break;
    default:
        return 0;
        break;
    }
    return 0;
}
int menuInit() {
    //创建根目录 一级界面
    Menu *rootMenu = createInterface(
        0,
        "主界面",       //要创建的界面名称
        0,              //当前项的开始序号
        3,              //当前项的结束序号
        6,              //项目总数
        0,              //当前选择项
        root,           //项目的显示名称
        func            //每个项目选中后要执行的函数组
    );
    //二级界面
    createInterface(
        rootMenu,
        "一级项目一", //要创建的界面名称
        0,              //当前项的开始序号
        3,              //当前项的结束序号
        6,              //项目总数
        0,              //当前选择项
        root1,          //项目的显示名称
        func            //每个项目选中后要执行的函数组
    );
    //二级界面
    createInterface(
        rootMenu,
        "一级项目二",   //要创建的界面名称
        0,              //当前项的开始序号
        3,              //当前项的结束序号
        6,              //项目总数
        0,              //当前选择项
        root2,          //项目的显示名称
        func            //每个项目选中后要执行的函数组
    );
    //三级界面
    createInterface(
        rootMenu,
        "二级-3项目四",  //要创建的界面名称
        0,              //当前项的开始序号
        3,              //当前项的结束序号
        6,              //项目总数
        0,              //当前选择项
        root3,          //项目的显示名称
        func            //每个项目选中后要执行的函数组
    );
    setInitInterFace(rootMenu, &keyInt);
    return 1;
}
int main(int arg, char **argv) {
    menuInit();
    menuRun(0);
    while (1);
    return 0;
}