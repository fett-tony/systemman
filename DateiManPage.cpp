#include <VarSysMan.h>
#include <StartSysMan.h>
#include <DateiBefehle.h>
#include <DateiManPage.h>
#include <HMenu.h>
#include <SoftAKInst.h>
#include <SysDateiRechte.h>
#include <SysNetzwerk.h>
#include <SysNetzIface.h>
#include <SysNetzMenu.h>
#include <SysNetzWPACon.h>
#include <SysNetzWPAScan.h>
#include <test.h>


VARSYSMAN::FENSTERMANPAGE VARSYSMAN::MANPAGE;
std::vector<std::string> DATEIMANPAGE::LXTermApps;
unsigned long DATEIMANPAGE::count;

void DATEIMANPAGE::FensterDesign()
{
    VARSYSMAN::MANPAGE.FEID = 1;
    VARSYSMAN::MANPAGE.FENAME = string("Man Page");
    delwin(STARTSYSMAN::START.TMPWin3);
    VARSYSMAN::MANPAGE.TMPWinHigh = STARTSYSMAN::max_yr-3;
    STARTSYSMAN::START.TMPWin3 = newwin(STARTSYSMAN::max_yr-1,STARTSYSMAN::max_xc,1,0); //-23
    wbkgd(STARTSYSMAN::START.TMPWin3,COLOR_PAIR(61));
    box(STARTSYSMAN::START.TMPWin3, 0, 0);
    mvwvline(STARTSYSMAN::START.TMPWin3, 1, 21, ACS_VLINE, STARTSYSMAN::max_yr-3);
    mvwvline(STARTSYSMAN::START.TMPWin3, 0, 21, ACS_TTEE,1);
    mvwvline(STARTSYSMAN::START.TMPWin3, STARTSYSMAN::max_yr-2, 21, ACS_BTEE,1);
    wrefresh(STARTSYSMAN::START.TMPWin3);
    VARSYSMAN::MANPAGE.TMPWin1 = newpad(STARTSYSMAN::max_yr-2, 40); //, 2, 1); //-23SYSDESIGN::max_yr-3
    STARTSYSMAN::START.TMPWin3 = derwin(VARSYSMAN::MANPAGE.TMPWin1, STARTSYSMAN::max_yr-2, 20, 2, 1);
    wbkgd(VARSYSMAN::MANPAGE.TMPWin1,COLOR_PAIR(61));
    VARSYSMAN::MANPAGE.TMPWin2 = newpad(STARTSYSMAN::max_yr-3, STARTSYSMAN::max_xc-23); //, 2, 22); //-23
    STARTSYSMAN::START.TMPWin3 = derwin(VARSYSMAN::MANPAGE.TMPWin2, STARTSYSMAN::max_yr, STARTSYSMAN::max_xc, 2, 22);
    wbkgd(VARSYSMAN::MANPAGE.TMPWin2,COLOR_PAIR(11));
    wsetscrreg(VARSYSMAN::MANPAGE.TMPWin2, 1, STARTSYSMAN::max_yr-2);
    scrollok(VARSYSMAN::MANPAGE.TMPWin2, true);
    scroll(VARSYSMAN::MANPAGE.TMPWin2);
    idlok(VARSYSMAN::MANPAGE.TMPWin2, true);
}

unsigned long DATEIMANPAGE::DirCount(string Pfad)
{
    unsigned long count = 0;
    struct dirent *datei;
    DIR *Folder = opendir(Pfad.c_str());
    while((datei = readdir(Folder)) != nullptr){
        count++;
    }
    closedir(Folder);
    return count;
}

void DATEIMANPAGE::FolderList(void)
{
    vector<string>().swap(DATEIMANPAGE::LXTermApps);
    string Pfad[4] = {"/usr/bin/","/usr/sbin/","/bin/","/sbin/"};
    //string Pfad = "/usr/bin/";
    DATEIMANPAGE::count = 0;
    struct dirent *datei;

    for (int X = 0; X < 2; X++)
    {
        DIR *Folder = opendir(Pfad[X].c_str());
    //DIR *Folder = opendir(Pfad.c_str());
    while((datei = readdir(Folder)) != nullptr){
        if(datei->d_type == 4){

            }else {
            DATEIMANPAGE::LXTermApps.push_back(datei->d_name);
        DATEIMANPAGE::count++;
        }
    }
    closedir(Folder);
    }

    std::multiset<std::string> g(DATEIMANPAGE::LXTermApps.begin(), DATEIMANPAGE::LXTermApps.end()); // """sort"""
    std::vector<std::string> tmparr (g.begin(), g.end());
    DATEIMANPAGE::LXTermApps.clear();

    for (unsigned long i = 0; i < tmparr.size(); i++) {
        DATEIMANPAGE::LXTermApps.push_back(tmparr[i]);
    }
    tmparr.clear();
    g.clear();
}

void DATEIMANPAGE::ManPageMenu()
{
    int mrows = 0;
    int mcols = 0;

    VARSYSMAN::MANPAGE.TMPItem1 = static_cast<ITEM **>(calloc(DATEIMANPAGE::count, sizeof(ITEM *)));

    for (unsigned long i = 0; i <= DATEIMANPAGE::count+1; i++)
    {
        VARSYSMAN::MANPAGE.TMPItem1[i] = new_item(DATEIMANPAGE::LXTermApps[i].c_str(), "");
    }
    VARSYSMAN::MANPAGE.TMPItem1[DATEIMANPAGE::count+1] = nullptr;

    VARSYSMAN::MANPAGE.TMPMenu1 = new_menu(VARSYSMAN::MANPAGE.TMPItem1);

    scale_menu(VARSYSMAN::MANPAGE.TMPMenu1, &mrows, &mcols);
    //wresize(VARSYSMAN::MANPAGE.TMPWin1, mrows, mcols);
    set_menu_win(VARSYSMAN::MANPAGE.TMPMenu1, VARSYSMAN::MANPAGE.TMPWin1);
    set_menu_sub(VARSYSMAN::MANPAGE.TMPMenu1, derwin(VARSYSMAN::MANPAGE.TMPWin1, STARTSYSMAN::max_yr-3, 20, 2, 1));
    set_menu_format(VARSYSMAN::MANPAGE.TMPMenu1, STARTSYSMAN::max_yr-3, 1);
    set_menu_spacing(VARSYSMAN::MANPAGE.TMPMenu1, 0, 0, 0);
    menu_opts_off(VARSYSMAN::MANPAGE.TMPMenu1, O_SHOWDESC);
    set_menu_fore(VARSYSMAN::MANPAGE.TMPMenu1, COLOR_PAIR(61)|A_BOLD|A_REVERSE);
    set_menu_back(VARSYSMAN::MANPAGE.TMPMenu1, COLOR_PAIR(61)|A_BOLD);
    set_menu_grey(VARSYSMAN::MANPAGE.TMPMenu1, COLOR_PAIR(13));
    //menu_opts_off(VARSYSMAN::MANPAGE.TMPMenu, O_ONEVALUE);
    set_menu_mark(VARSYSMAN::MANPAGE.TMPMenu1, "");
    post_menu(VARSYSMAN::MANPAGE.TMPMenu1);
}

void DATEIMANPAGE::Start_ManP()
{
    DATEIMANPAGE::FensterDesign();
    DATEIMANPAGE::FolderList();
    DATEIMANPAGE::ManPageMenu();

    refresh();
    touchwin(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
    wrefresh(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
    prefresh(VARSYSMAN::clearwindow(VARSYSMAN::MANPAGE.TMPWin1), 0, 0, 2, 1, STARTSYSMAN::max_yr -2, 20);
    prefresh(VARSYSMAN::clearwindow(VARSYSMAN::MANPAGE.TMPWin2), 0, 0, 2, 22, STARTSYSMAN::max_yr -2, STARTSYSMAN::max_xc-1);

    int c;
    int tabspace = 1;
    int rowy = STARTSYSMAN::max_yr-3;
    //int colx = STARTSYSMAN::max_xc-22;
    int ROWS = 0;

    keypad(STARTSYSMAN::START.TMPWin3, TRUE);

    while((c = getch()) !=KEY_F(10))
    {
        switch(tabspace){
        case 1:
            switch (c){
            case KEY_DOWN:
                menu_driver(VARSYSMAN::MANPAGE.TMPMenu1, REQ_DOWN_ITEM);
                break;
            case KEY_UP:
                menu_driver(VARSYSMAN::MANPAGE.TMPMenu1, REQ_UP_ITEM);
                break;
            case KEY_NPAGE:
                menu_driver(VARSYSMAN::MANPAGE.TMPMenu1, REQ_PREV_PAGE);
                break;
            case KEY_PPAGE:
                menu_driver(VARSYSMAN::MANPAGE.TMPMenu1, REQ_NEXT_PAGE);
                break;
            case 0x09:
                tabspace = VARSYSMAN::zahlenwerk(1,"++",2);
                break;
            case KEY_BTAB:
                tabspace = VARSYSMAN::zahlenwerk(1,"--",2);
                break;
            case 10:
                if (VARSYSMAN::MANPAGE.TMPWin2){werase(VARSYSMAN::MANPAGE.TMPWin2);delwin(VARSYSMAN::MANPAGE.TMPWin2);}
                string tmpSTR = "man -P cat ";
                tmpSTR.append(string(item_name(current_item(VARSYSMAN::MANPAGE.TMPMenu1))));
                string ls = VARSYSMAN::TERM_AUSGABE(tmpSTR); //VARSYSMAN::TERM_AUSGABE(string(item_name(current_item(VARSYSMAN::MANPAGE.TMPMenu))));
                VARSYSMAN::MANPAGE.TMPWinHigh = SOFTAKINSTALL::Zeilen(ls, STARTSYSMAN::max_xc-22);
                VARSYSMAN::MANPAGE.TMPWin2 = newpad(VARSYSMAN::MANPAGE.TMPWinHigh, STARTSYSMAN::max_xc-23);
                STARTSYSMAN::START.TMPWin3 = derwin(VARSYSMAN::MANPAGE.TMPWin2, STARTSYSMAN::max_yr-3, STARTSYSMAN::max_xc-23, 2, 22);
                mvwaddstr(VARSYSMAN::MANPAGE.TMPWin2, 0, 0, ls.c_str());
                break;
            }
            break;
        case 2:
            switch (c){
            case KEY_DOWN:
                if ((ROWS + rowy +1) >= VARSYSMAN::MANPAGE.TMPWinHigh){
                    ROWS = VARSYSMAN::MANPAGE.TMPWinHigh;
                }else {
                    ROWS++;
                }
                break;
            case KEY_UP:
                if (ROWS <= 0){
                    ROWS = 0;
                }else {
                    ROWS--;
                }
                break;
            case 0x09:
                tabspace = VARSYSMAN::zahlenwerk(2,"++",2);
                break;
            case KEY_BTAB:
                tabspace = VARSYSMAN::zahlenwerk(2,"--",2);
                break;
            }
            break;
        }
        refresh();
//        touchwin(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
//        wrefresh(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
        prefresh(VARSYSMAN::clearwindow(VARSYSMAN::MANPAGE.TMPWin1), 0, 0, 2, 1, STARTSYSMAN::max_yr -2, 20);
        prefresh(VARSYSMAN::clearwindow(VARSYSMAN::MANPAGE.TMPWin2), ROWS, 0, 2, 22, STARTSYSMAN::max_yr -2, STARTSYSMAN::max_xc-1);
    }
    DATEIMANPAGE::QUIT_MANP();
}

void DATEIMANPAGE::QUIT_MANP()
{
    int e,i;

    e = item_count(VARSYSMAN::MANPAGE.TMPMenu1);
    unpost_menu(VARSYSMAN::MANPAGE.TMPMenu1);
    DATEIMANPAGE::LXTermApps.clear();
    std::vector<std::string>(DATEIMANPAGE::LXTermApps).swap (DATEIMANPAGE::LXTermApps);
    for(i=0; i<=e-1; i++) {
        free_item(VARSYSMAN::MANPAGE.TMPItem1[i]);
    }
    free_menu(VARSYSMAN::MANPAGE.TMPMenu1);
    delwin(VARSYSMAN::MANPAGE.TMPWin1);
    delwin(VARSYSMAN::MANPAGE.TMPWin2);
    endwin();

    refresh();
}

DATEIMANPAGE::DATEIMANPAGE()
{

}
