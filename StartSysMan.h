#ifndef STARTSYSMAN_H
#define STARTSYSMAN_H

#include <VarSysMan.h>

struct FENSTER
{
    int FEID {0};
    string FENAME {""};
    WINDOW *TMPWin1 {nullptr};
    WINDOW *TMPWin2 {nullptr};
    WINDOW *TMPWin3 {nullptr};
    WINDOW *TMPWin4 {nullptr};
    WINDOW *TMPWin5 {nullptr};
    int TMPWinHigh {0};
    MENU *TMPMenu {nullptr};
    ITEM **TMPItem {nullptr};
    MENU *TMPMenu2 {nullptr};
    ITEM **TMPItem2 {nullptr};
    MENU *TMPMenu3 {nullptr};
    ITEM **TMPItem3 {nullptr};
    FORM *TMPForm1 {nullptr};
    FIELD **TMPField1 {nullptr};
    void delwinow(WINDOW *tmpwin){
        if(tmpwin){
            int mx,my,bx,by;
            getbegyx(tmpwin,by,bx);
            getmaxyx(tmpwin,my,mx);
            touchwin(tmpwin);
            wborder(tmpwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
            touchline(tmpwin,bx,mx);
            delwin(tmpwin);
            endwin();
            tmpwin=nullptr;
        }
    }
    void delmenu(WINDOW *tmpwin, MENU *tmpmenu, ITEM **tmpitem){
        if (tmpmenu){
            int E = item_count(tmpmenu);
            unpost_menu(tmpmenu);
            SAFE_DELETE(tmpmenu);
            SAFE_DELETE_ARRAY(tmpitem);
            wborder(tmpwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
            touchline(tmpwin,0,E+1);
            delwin(tmpwin);
            endwin();
        }
    }
    void delform(WINDOW *tmpwin, FORM *tmpform, FIELD **tmpfield){
        if (tmpform){
            int mx,my,bx,by;
            getbegyx(tmpwin,by,bx);
            getmaxyx(tmpwin,my,mx);
            unpost_form(tmpform);
            SAFE_DELETE(tmpform);
            SAFE_DELETE_ARRAY(tmpfield);
            wborder(tmpwin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
            touchline(tmpwin,bx,mx);
            delwin(tmpwin);
            endwin();
        }
    }
};

class STARTSYSMAN
{
public:
    static FENSTER START;
//    static FORM *EinstFo;
//    static FIELD **EinstFoFi;
    static int max_yr,rows,fmyr;
    static int max_xc,cols,fmxc;
    //#################MAIN#########################
    static void init_curse(void);
    static void AppColor(void);
    static void FensterDesign(void);
    static void ClearScreen();
    static void fensterwahl(const char *wahl);
    static void configR();
    static void ScrollPad(WINDOW * SubWin, int StartY, int StartX, int Height, int Width, int PadHeight);
    static void endeapp();
    static void einDa(void);
    //######################################
    static void DeletHMmenu(const char *namem);
    STARTSYSMAN();

private:


protected:

};

#endif // STARTSYSMAN_H
