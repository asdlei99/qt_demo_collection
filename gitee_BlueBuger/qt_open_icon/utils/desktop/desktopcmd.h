/**
 ** @author:	   浓咖啡
 ** @date:	   2016.7.11
 ** @brief:      桌面和其它进程通信所有用到的命令
 */
#ifndef DESKTOPCMD_H
#define DESKTOPCMD_H

//通用命令,这里只能预留,我没想到好的办法让它们看起来工整
enum DESKTOP_COMMON{
    PROCEDURE_SHOW = 0x00000000,
    PROCEDURE_HIDE = 0x00000001
};

#endif // DESKTOPCMD_H
