#ifndef SYSNETZMENU_H
#define SYSNETZMENU_H

#include <VarSysMan.h>

class SYSNETZMENU
{
public:
    static string NETNMe;
//##################################################
    static void System_Me_Netzwerk(void);
    static void sys_netz_fenster(void);
    static int sys_main(void);
    static void Netz_Me_Wa(const char *wahl);
    static void SYS_quit(int index);

private:
    static int MeInA;
    static int MeInN;

};

#endif // SYSNETZMENU_H

