#ifndef SOFTAKINSTALL_H
#define SOFTAKINSTALL_H

#include <VarSysMan.h>
#include <StartSysMan.h>

class SOFTAKINSTALL
{
public:
    static std::vector<std::string> LXApps;
    //static string softarr[100];
    static int Smyr, Smxc, arrlae;
    //#########################################################################
    static int Zeilen(string data, int maxbreite);
    static void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);
    static void Software_Fenster(void);
    static string BefZusa(string name);
    static void AK_SOFT_Menu(void);
    static void AK_SOFT_Inst_Button(string liste);
    static void AK_SOFT_Remo_Button(string liste);
    static void AK_UB_start(void);
    static void AK_SOFT_LIST(void);
    static void AK_DESC_Anzeigen(string DescPad_tmp);
    static void menu_surf(string name, int id);
    static void QUIT_AK_UB_INST();

private:


protected:

};

#endif //SOFTAKINSTALL_H
