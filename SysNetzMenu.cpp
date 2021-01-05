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

using namespace std;

VARSYSMAN::FENSTERNETZMENU VARSYSMAN::NETZMENU;

string SYSNETZMENU::NETNMe;
int SYSNETZMENU::MeInA=0;
int SYSNETZMENU::MeInN=0;

void SYSNETZMENU::sys_netz_fenster(void)
{
    STARTSYSMAN::START.TMPWin3 = VARSYSMAN::DelTmpWin(STARTSYSMAN::START.TMPWin3);
    delwin(STARTSYSMAN::START.TMPWin3);
    VARSYSMAN::NETZMENU.TMPWin1 = newwin(1, STARTSYSMAN::max_xc, 1, 0); //-23
    wbkgd(VARSYSMAN::NETZMENU.TMPWin1,COLOR_PAIR(VARSYSMAN::HaMeFe_HG));
    //VARSYSMAN::NETZMENU.TMPWin1 = subwin(VARSYSMAN::NETZMENU.TMPWin2, 1, STARTSYSMAN::max_xc, 1, 0);
    STARTSYSMAN::START.TMPWin3 = newwin(STARTSYSMAN::max_yr-2, STARTSYSMAN::max_xc, 2, 0); //-23
    wbkgd(STARTSYSMAN::START.TMPWin3,COLOR_PAIR(61));
    box(STARTSYSMAN::START.TMPWin3, 0, 0);
}

void SYSNETZMENU::System_Me_Netzwerk(void)
{   VARSYSMAN::NETZMENU.TMPItem1 = static_cast<ITEM **>(calloc(6,sizeof(ITEM *)));
    VARSYSMAN::NETZMENU.TMPItem1[0] = new_item("Netzwerk", "");
    VARSYSMAN::NETZMENU.TMPItem1[1] = new_item("Einstellung", "");//12
    VARSYSMAN::NETZMENU.TMPItem1[2] = new_item("WPA-Wlan", "");
    VARSYSMAN::NETZMENU.TMPItem1[3] = new_item("Wlan", "");
    VARSYSMAN::NETZMENU.TMPItem1[4] = new_item("BlueTooth", "");
    VARSYSMAN::NETZMENU.TMPItem1[5] = nullptr;
    VARSYSMAN::NETZMENU.TMPMenu1 = new_menu(VARSYSMAN::NETZMENU.TMPItem1);
    VARSYSMAN::NETZMENU.TMPWin2 = newwin(1, STARTSYSMAN::max_xc-1, 1, 1);
    wbkgd(VARSYSMAN::NETZMENU.TMPWin2,COLOR_PAIR(VARSYSMAN::HaMeFe_HG));
    //box(VARSYSMAN::NETZMENU.TMPWin2,0,0);
    set_menu_win (VARSYSMAN::NETZMENU.TMPMenu1, VARSYSMAN::NETZMENU.TMPWin2);
    set_menu_sub (VARSYSMAN::NETZMENU.TMPMenu1, derwin(VARSYSMAN::NETZMENU.TMPWin2, 1, STARTSYSMAN::max_xc-1, 1, 0));
    set_menu_spacing(VARSYSMAN::NETZMENU.TMPMenu1, 2, 0, 0);
    set_menu_format(VARSYSMAN::NETZMENU.TMPMenu1, 0, 5);
    menu_opts_off(VARSYSMAN::NETZMENU.TMPMenu1, O_SHOWDESC);
    menu_opts_off(VARSYSMAN::NETZMENU.TMPMenu1, O_NONCYCLIC);
    //set_menu_fore(VARSYSMAN::NETZMENU.TMPMenu1, COLOR_PAIR(12)|A_REVERSE|A_BOLD);
    set_menu_fore(VARSYSMAN::NETZMENU.TMPMenu1, COLOR_PAIR(VARSYSMAN::HaMe_FG)|A_REVERSE|A_BOLD);
    set_menu_back(VARSYSMAN::NETZMENU.TMPMenu1, COLOR_PAIR(VARSYSMAN::HaMe_HG));//|A_BOLD);
    set_menu_grey(VARSYSMAN::NETZMENU.TMPMenu1, COLOR_PAIR(VARSYSMAN::HaMe_grey)|A_BOLD);
    set_menu_mark(VARSYSMAN::NETZMENU.TMPMenu1,"");
    //set_current_item(VARSYSMAN::NETZMENU.TMPMenu1, VARSYSMAN::NETZMENU.TMPItem1[0]);
    post_menu(VARSYSMAN::NETZMENU.TMPMenu1);
} /* System Untermenü NETZWERK */

void SYSNETZMENU::Netz_Me_Wa(const char *wahl)
{
    if (strcmp(wahl,"Netzwerk")==0){
        SYSNETZWERK::NetzMain();
    }else if (strcmp(wahl,"Einstellung")==0){
        SYSNETZIFACE::SYSNETZIFACE_START();
    }else  if (strcmp(wahl, "WPA-Wlan")==0){
        WPA_WLANSCAN::WPA_Start();
    }else if (strcmp(wahl,"Wlan")==0){
        WPA_CONNECT::Connection();
    }else if (strcmp(wahl,"Bluetooth")==0){
        //SYSNETZMENU::MeInA=3;
        //WPA_CONNECT::Connection();
    }
}

void SYSNETZMENU::SYS_quit(int index)
{
    int i,e=0;//,res=0;
    try
    {
        SYSNETZMENU::MeInA = item_index(current_item(VARSYSMAN::NETZMENU.TMPMenu1));
        if (SYSNETZMENU::MeInA != index)
        {
            if (index == 0)
            {

            }else if (index == 1){
                e = item_count(VARSYSMAN::NETZWERK.TMPMenu1);
                if (e>0){
                    unpost_menu(VARSYSMAN::NETZWERK.TMPMenu1);
                    wborder(VARSYSMAN::NETZWERK.TMPWin1, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
                    delwin(VARSYSMAN::NETZWERK.TMPWin1);
                    free_menu(VARSYSMAN::NETZWERK.TMPMenu1);
                    for(i=0; i<=e-1; i++) {
                        free_item(VARSYSMAN::NETZWERK.TMPItem1[i]);
                    }
                    wclear(VARSYSMAN::NETZWERK.TMPWin2);
                    werase(VARSYSMAN::NETZWERK.TMPWin2);
                    delwin(VARSYSMAN::NETZWERK.TMPWin2);
                    wclear(STARTSYSMAN::START.TMPWin3);
                    werase(STARTSYSMAN::START.TMPWin3);
                    delwin(STARTSYSMAN::START.TMPWin3);
                    endwin();
                }
            }else if (index == 2){

            }else if (index == 3){
                e = item_count(VARSYSMAN::WPACONNECT.TMPMenu1);
                if (e>0){
                    unpost_menu(VARSYSMAN::WPACONNECT.TMPMenu1);
                    delwin(VARSYSMAN::WPACONNECT.TMPWin2);
                    free_menu(VARSYSMAN::WPACONNECT.TMPMenu1);
                    for(i=0; i<=e-1; i++) {
                        free_item(VARSYSMAN::WPACONNECT.TMPItem1[i]);
                    }
                    wclear(VARSYSMAN::WPACONNECT.TMPWin1);
                    werase(VARSYSMAN::WPACONNECT.TMPWin1);
                    delwin(VARSYSMAN::WPACONNECT.TMPWin1);
                    wborder(STARTSYSMAN::START.TMPWin3, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
                    wclear(STARTSYSMAN::START.TMPWin3);
                    werase(STARTSYSMAN::START.TMPWin3);
                    delwin(STARTSYSMAN::START.TMPWin3);
                    endwin();
                }
            }else {

            }
            refresh();
            wrefresh(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin2));
        }
    } catch (const NCursesException *e) {
        endwin();
        std::cerr << e->message << std::endl;
        //res = e->errorno;
    } catch (const NCursesException &e) {
        endwin();
        std::cerr << e.message << std::endl;
        //res = e.errorno;
    } catch (const std::exception &e) {
        endwin();
        std::cerr << "Exception: " << e.what() << std::endl;
        //res = EXIT_FAILURE;
    }
}

int SYSNETZMENU::sys_main(void)
{
    int res;
    try {
        int c;
        SYSNETZMENU::System_Me_Netzwerk();
        SYSNETZMENU::sys_netz_fenster();

        refresh();
        wrefresh(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
        wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::NETZMENU.TMPWin1));
        touchwin(VARSYSMAN::clearwindow(VARSYSMAN::NETZMENU.TMPWin2));
        wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::NETZMENU.TMPWin2));

        keypad(stdscr,true);

        while ((c = getch()) != KEY_F(10)){
            switch (c) {
            case KEY_RIGHT:
                menu_driver(VARSYSMAN::NETZMENU.TMPMenu1, REQ_RIGHT_ITEM);
                break;
            case KEY_LEFT:
                menu_driver(VARSYSMAN::NETZMENU.TMPMenu1, REQ_LEFT_ITEM);
                break;
            case 0x0A:
                SYSNETZMENU::SYS_quit(SYSNETZMENU::MeInN);
                SYSNETZMENU::MeInN = item_index(current_item(VARSYSMAN::NETZMENU.TMPMenu1));
                SYSNETZMENU::NETNMe = string(item_name(current_item(VARSYSMAN::NETZMENU.TMPMenu1)));
                SYSNETZMENU::Netz_Me_Wa(item_name(current_item(VARSYSMAN::NETZMENU.TMPMenu1)));
                break;
            }
            refresh();
            wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::NETZMENU.TMPWin2));
            wrefresh(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
        }
        return 0;
    } catch (const NCursesException *e) {
        endwin();
        std::cerr << e->message << std::endl;
        res = e->errorno;
    } catch (const NCursesException &e) {
        endwin();
        std::cerr << e.message << std::endl;
        res = e.errorno;
    } catch (const std::exception &e) {
        endwin();
        std::cerr << "Exception: " << e.what() << std::endl;
        res = EXIT_FAILURE;
    }
    return res;
}
