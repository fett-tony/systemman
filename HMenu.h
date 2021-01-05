#ifndef HMENU_H
#define HMENU_H

#include <VarSysMan.h>
#include <StartSysMan.h>

struct HAUPTMENU
{
    int HMWiMeIt_ID;
    string HMName;
    WINDOW *HMWin {nullptr};
    MENU *HMMenu {nullptr};
    ITEM **HMItem {nullptr};  
    //###############################################
    void delwinow(WINDOW *tmpwin){
        int E = item_count(HMMenu);
        unpost_menu(HMMenu);
        SAFE_DELETE(HMMenu);
        SAFE_DELETE_ARRAY(HMItem);
        wborder(HMWin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
        touchline(HMWin,0,E+1);
        delwin(HMWin);
        endwin();
        refresh();
        redrawwin(VARSYSMAN::clearwindow(tmpwin));
        wrefresh(VARSYSMAN::clearwindow(tmpwin));
    }
};

class HMenu
{
public:
    //############################variablen#########
    static HAUPTMENU MENEU[6];
    static int MeInAl;
    //##########MENÜ################################
    static void startinfo(void);
    static void Hauptmenu(void);
    static void Datei_menu(void);
    static void System_menu(void);
    static void Server_menu(void);
    static void Software_menu(void);
    static void Info_menu(void);
    static MENU *tmpMe(const char *name, int id);
    static WINDOW *tmpWi(const char *name, int id);
    static void quit(const char *name, string wahl);
    static void MenuWahl(void);
    static void MenuStart(void);
private:

protected:

};

#endif // HMENU_H

