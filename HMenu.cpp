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

HAUPTMENU HMenu::MENEU[6];
int HMenu::MeInAl = 0;

void HMenu::startinfo (void)
{
    HMenu::MENEU[0].HMWiMeIt_ID = 0;
    HMenu::MENEU[0].HMName = string("Hauptmenü");
    HMenu::MENEU[1].HMWiMeIt_ID = 1;
    HMenu::MENEU[1].HMName = string("Datei");
    HMenu::MENEU[2].HMWiMeIt_ID = 2;
    HMenu::MENEU[2].HMName = string("System");
    HMenu::MENEU[3].HMWiMeIt_ID = 3;
    HMenu::MENEU[3].HMName = string("Server");
    HMenu::MENEU[4].HMWiMeIt_ID = 4;
    HMenu::MENEU[4].HMName = string("Software");
    HMenu::MENEU[5].HMWiMeIt_ID = 5;
    HMenu::MENEU[5].HMName = string("Info");
}

void HMenu::Hauptmenu(void)
{
    HMenu::MENEU[0].HMWiMeIt_ID = 0;
    HMenu::MENEU[0].HMName = string("HAUPTMENÜ");
    HMenu::MENEU[0].HMItem = static_cast<ITEM **>(calloc(6, sizeof(ITEM *)));
    HMenu::MENEU[0].HMItem[0] = new_item("Datei", HMenu::MENEU[0].HMName.c_str());
    HMenu::MENEU[0].HMItem[1] = new_item("System", HMenu::MENEU[0].HMName.c_str());
    HMenu::MENEU[0].HMItem[2] = new_item("Server", HMenu::MENEU[0].HMName.c_str());
    HMenu::MENEU[0].HMItem[3] = new_item("Software", HMenu::MENEU[0].HMName.c_str());
    HMenu::MENEU[0].HMItem[4] = new_item("Info", HMenu::MENEU[0].HMName.c_str());
    HMenu::MENEU[0].HMItem[5] = nullptr;
    HMenu::MENEU[0].HMMenu = new_menu(HMenu::MENEU[0].HMItem);
    HMenu::MENEU[0].HMWin = newwin(1, STARTSYSMAN::max_xc-1, 0, 1);
    set_menu_win (HMenu::MENEU[0].HMMenu, HMenu::MENEU[0].HMWin);
    set_menu_sub(HMenu::MENEU[0].HMMenu, HMenu::MENEU[0].HMWin);
    //###############################################################
    set_menu_sub(HMenu::MENEU[1].HMMenu, HMenu::MENEU[0].HMWin);
    set_menu_sub(HMenu::MENEU[2].HMMenu, HMenu::MENEU[0].HMWin);
    set_menu_sub(HMenu::MENEU[3].HMMenu, HMenu::MENEU[0].HMWin);
    set_menu_sub(HMenu::MENEU[4].HMMenu, HMenu::MENEU[0].HMWin);
    set_menu_sub(HMenu::MENEU[5].HMMenu, HMenu::MENEU[0].HMWin);
    //###############################################################
    set_menu_spacing(HMenu::MENEU[0].HMMenu, 2, 0, 0);
    set_menu_format(HMenu::MENEU[0].HMMenu, 0, 6);
    menu_opts_off(HMenu::MENEU[0].HMMenu, O_SHOWDESC);
    menu_opts_off(HMenu::MENEU[0].HMMenu, O_NONCYCLIC);
    wbkgd(HMenu::MENEU[0].HMWin, COLOR_PAIR(VARSYSMAN::HaMeFe_HG)|A_BOLD);
    //set_menu_fore(HMenu::MENEU[0].HMMenu, COLOR_PAIR(12)|A_REVERSE|A_BOLD);
    set_menu_fore(HMenu::MENEU[0].HMMenu, COLOR_PAIR(VARSYSMAN::HaMe_FG)|A_REVERSE|A_BOLD);
    set_menu_back(HMenu::MENEU[0].HMMenu, COLOR_PAIR(VARSYSMAN::HaMe_HG));//|A_BOLD);
    set_menu_grey(HMenu::MENEU[0].HMMenu, COLOR_PAIR(VARSYSMAN::HaMe_grey)|A_BOLD);
    set_menu_mark(HMenu::MENEU[0].HMMenu,"");
    post_menu(HMenu::MENEU[0].HMMenu);
} /* Hauptmenü */

void HMenu::Datei_menu(void)
{
    HMenu::MENEU[1].HMWiMeIt_ID = 1;
    HMenu::MENEU[1].HMName = string("Datei");
    HMenu::HMenu::MENEU[1].HMWin = newwin(6, 13, 1, 0);
    wbkgd(HMenu::MENEU[1].HMWin,COLOR_PAIR(VARSYSMAN::UMeFe_HG));
    box(HMenu::MENEU[1].HMWin, 0, 0);
    HMenu::MENEU[1].HMItem = static_cast<ITEM **>(calloc(7, sizeof(ITEM *)));
    HMenu::MENEU[1].HMItem[0] = new_item("Man Page", HMenu::MENEU[1].HMName.c_str());
    HMenu::MENEU[1].HMItem[1] = new_item("Einstellung", HMenu::MENEU[1].HMName.c_str());
    HMenu::MENEU[1].HMItem[2] = new_item("Befehle", HMenu::MENEU[1].HMName.c_str());
    HMenu::MENEU[1].HMItem[3] = new_item("Beenden", HMenu::MENEU[1].HMName.c_str());
    HMenu::MENEU[1].HMItem[4] = nullptr;
    HMenu::MENEU[1].HMMenu = new_menu(HMenu::MENEU[1].HMItem);
    set_menu_win(HMenu::MENEU[1].HMMenu, HMenu::MENEU[1].HMWin);
    set_menu_sub (HMenu::MENEU[1].HMMenu, derwin(HMenu::MENEU[1].HMWin, 0, 0, 1, 1));
    set_menu_spacing(HMenu::MENEU[1].HMMenu, 0,0,0);
    set_menu_format(HMenu::MENEU[1].HMMenu, 5, 0);
    menu_opts_off(HMenu::MENEU[1].HMMenu, O_SHOWDESC);
    menu_opts_off(HMenu::MENEU[1].HMMenu, O_NONCYCLIC);
    //set_menu_fore(HMenu::MENEU[1].HMMenu, COLOR_PAIR(12)|A_REVERSE|A_BOLD);
    set_menu_fore(HMenu::MENEU[1].HMMenu, COLOR_PAIR(VARSYSMAN::HaMe_FG)|A_BOLD);
    set_menu_back(HMenu::MENEU[1].HMMenu, COLOR_PAIR(VARSYSMAN::HaMe_HG));//|A_BOLD);
    set_menu_grey(HMenu::MENEU[1].HMMenu, COLOR_PAIR(VARSYSMAN::HaMe_grey)|A_BOLD);
    set_menu_mark(HMenu::MENEU[1].HMMenu,"");
    set_current_item(HMenu::MENEU[1].HMMenu, HMenu::MENEU[1].HMItem[0]);
    post_menu(HMenu::MENEU[1].HMMenu);
} /* Datei Menü */

void HMenu::System_menu(void)
{
    HMenu::MENEU[2].HMWiMeIt_ID = 2;
    HMenu::MENEU[2].HMName = string("System");
    HMenu::MENEU[2].HMWin = newwin(10, 14, 1, 9);
    wbkgd(HMenu::MENEU[2].HMWin, COLOR_PAIR(VARSYSMAN::UMeFe_HG));
    box(HMenu::MENEU[2].HMWin, 0, 0);
    HMenu::MENEU[2].HMItem = static_cast<ITEM **>(calloc(9,sizeof(ITEM *)));
    HMenu::MENEU[2].HMItem[0] = new_item("Netzwerk", HMenu::MENEU[2].HMName.c_str());
    HMenu::MENEU[2].HMItem[1] = new_item("Samba-client", HMenu::MENEU[2].HMName.c_str());//12
    HMenu::MENEU[2].HMItem[2] = new_item("Benutzer", HMenu::MENEU[2].HMName.c_str());
    HMenu::MENEU[2].HMItem[3] = new_item("Firewall", HMenu::MENEU[2].HMName.c_str());
    HMenu::MENEU[2].HMItem[4] = new_item("Service", HMenu::MENEU[2].HMName.c_str());
    HMenu::MENEU[2].HMItem[5] = new_item("Hardware", HMenu::MENEU[2].HMName.c_str());
    HMenu::MENEU[2].HMItem[6] = new_item("Grub", HMenu::MENEU[2].HMName.c_str());
    HMenu::MENEU[2].HMItem[7] = new_item("Datei Rechte", HMenu::MENEU[2].HMName.c_str());
    HMenu::MENEU[2].HMItem[8] = nullptr;
    HMenu::MENEU[2].HMMenu = new_menu(HMenu::MENEU[2].HMItem);
    set_menu_win (HMenu::MENEU[2].HMMenu, HMenu::MENEU[2].HMWin);
    set_menu_sub (HMenu::MENEU[2].HMMenu, derwin(HMenu::MENEU[2].HMWin, 0, 0, 1, 1));
    set_menu_spacing(HMenu::MENEU[2].HMMenu, 0, 1, 0);
    set_menu_format(HMenu::MENEU[2].HMMenu, 8, 1);
    menu_opts_off(HMenu::MENEU[2].HMMenu, O_SHOWDESC);
    menu_opts_off(HMenu::MENEU[2].HMMenu, O_NONCYCLIC);
    //set_menu_fore(HMenu::MENEU[2].HMMenu, COLOR_PAIR(12)|A_REVERSE|A_BOLD);
    set_menu_fore(HMenu::MENEU[2].HMMenu, COLOR_PAIR(VARSYSMAN::HaMe_FG)|A_BOLD);
    set_menu_back(HMenu::MENEU[2].HMMenu, COLOR_PAIR(VARSYSMAN::HaMe_HG));//|A_BOLD);
    set_menu_grey(HMenu::MENEU[2].HMMenu, COLOR_PAIR(VARSYSMAN::HaMe_grey)|A_BOLD);
    set_menu_mark(HMenu::MENEU[2].HMMenu,"");
    set_current_item(HMenu::MENEU[2].HMMenu, HMenu::MENEU[2].HMItem[0]);
    post_menu(HMenu::MENEU[2].HMMenu);

} /* System Untermenü */

void HMenu::Server_menu(void)
{
    HMenu::MENEU[3].HMWiMeIt_ID = 3;
    HMenu::MENEU[3].HMName = string("Server");
    HMenu::MENEU[3].HMWin = newwin(10, 14, 1, 18);
    wbkgd(HMenu::MENEU[3].HMWin, COLOR_PAIR(VARSYSMAN::UMeFe_HG));
    box(HMenu::MENEU[3].HMWin, 0, 0);
    HMenu::MENEU[3].HMItem = static_cast<ITEM **>(calloc(9, sizeof(ITEM *)));
    HMenu::MENEU[3].HMItem[0] = new_item("LDAP", HMenu::MENEU[3].HMName.c_str());
    HMenu::MENEU[3].HMItem[1] = new_item("Samba-Server", HMenu::MENEU[3].HMName.c_str());//12
    HMenu::MENEU[3].HMItem[2] = new_item("Kerberos", HMenu::MENEU[3].HMName.c_str());
    HMenu::MENEU[3].HMItem[3] = new_item("DHCP", HMenu::MENEU[3].HMName.c_str());
    HMenu::MENEU[3].HMItem[4] = new_item("DNS-Server", HMenu::MENEU[3].HMName.c_str());
    HMenu::MENEU[3].HMItem[5] = new_item("FreeRadius", HMenu::MENEU[3].HMName.c_str());
    HMenu::MENEU[3].HMItem[6] = new_item("Netboot", HMenu::MENEU[3].HMName.c_str());
    HMenu::MENEU[3].HMItem[7] = new_item("WLan-AP", HMenu::MENEU[3].HMName.c_str());
    HMenu::MENEU[3].HMItem[8] = nullptr;
    HMenu::MENEU[3].HMMenu = new_menu(HMenu::MENEU[3].HMItem);
    set_menu_win (HMenu::MENEU[3].HMMenu, HMenu::MENEU[3].HMWin);
    set_menu_sub (HMenu::MENEU[3].HMMenu, derwin(HMenu::MENEU[3].HMWin, 0, 0, 1, 1));
    set_menu_spacing(HMenu::MENEU[3].HMMenu, 0, 0, 0);
    set_menu_format(HMenu::MENEU[3].HMMenu, 9, 0);
    menu_opts_off(HMenu::MENEU[3].HMMenu, O_SHOWDESC);
    menu_opts_off(HMenu::MENEU[3].HMMenu, O_NONCYCLIC);
    //set_menu_fore(HMenu::MENEU[3].HMMenu, COLOR_PAIR(12)|A_REVERSE|A_BOLD);
    set_menu_fore(HMenu::MENEU[3].HMMenu, COLOR_PAIR(VARSYSMAN::HaMe_FG)|A_BOLD);
    set_menu_back(HMenu::MENEU[3].HMMenu, COLOR_PAIR(VARSYSMAN::HaMe_HG));//|A_BOLD);
    set_menu_grey(HMenu::MENEU[3].HMMenu, COLOR_PAIR(VARSYSMAN::HaMe_grey)|A_BOLD);
    set_menu_mark(HMenu::MENEU[3].HMMenu,"");
    set_current_item(HMenu::MENEU[3].HMMenu, HMenu::MENEU[3].HMItem[0]);
    post_menu(HMenu::MENEU[3].HMMenu);
} /* Server Untermenü */

void HMenu::Software_menu(void)
{
    HMenu::MENEU[4].HMWiMeIt_ID = 4;
    HMenu::MENEU[4].HMName = string("Software");
    HMenu::MENEU[4].HMWin = newwin(6, 17, 1, 27);
    wbkgd(HMenu::MENEU[4].HMWin,COLOR_PAIR(VARSYSMAN::UMeFe_HG));
    box(HMenu::MENEU[4].HMWin,0,0);
    HMenu::MENEU[4].HMItem = static_cast<ITEM **>(calloc(5,sizeof(ITEM *)));
    HMenu::MENEU[4].HMItem[0] = new_item("Installiert", HMenu::MENEU[4].HMName.c_str());
    HMenu::MENEU[4].HMItem[1] = new_item("Software-Center", HMenu::MENEU[4].HMName.c_str());//15
    HMenu::MENEU[4].HMItem[2] = new_item("AK-UB-conf", HMenu::MENEU[4].HMName.c_str());
    HMenu::MENEU[4].HMItem[3] = new_item("Starten", HMenu::MENEU[4].HMName.c_str());
    HMenu::MENEU[4].HMItem[4] = nullptr;
    HMenu::MENEU[4].HMMenu = new_menu(HMenu::MENEU[4].HMItem);
    set_menu_win (HMenu::MENEU[4].HMMenu, HMenu::MENEU[4].HMWin);
    set_menu_sub (HMenu::MENEU[4].HMMenu, derwin(HMenu::MENEU[4].HMWin, 0, 0, 1, 1));
    set_menu_spacing(HMenu::MENEU[4].HMMenu, 0, 0, 0);
    set_menu_format(HMenu::MENEU[4].HMMenu, 5, 0);
    menu_opts_off(HMenu::MENEU[4].HMMenu, O_SHOWDESC);
    menu_opts_off(HMenu::MENEU[4].HMMenu, O_NONCYCLIC);
    //set_menu_fore(HMenu::MENEU[4].HMMenu, COLOR_PAIR(12)|A_REVERSE|A_BOLD);
    set_menu_fore(HMenu::MENEU[4].HMMenu, COLOR_PAIR(VARSYSMAN::HaMe_FG)|A_BOLD);
    set_menu_back(HMenu::MENEU[4].HMMenu, COLOR_PAIR(VARSYSMAN::HaMe_HG));//|A_BOLD);
    set_menu_grey(HMenu::MENEU[4].HMMenu, COLOR_PAIR(VARSYSMAN::HaMe_grey)|A_BOLD);
    set_menu_mark(HMenu::MENEU[4].HMMenu,"");
    set_current_item(HMenu::MENEU[4].HMMenu, HMenu::MENEU[4].HMItem[0]);
    post_menu(HMenu::MENEU[4].HMMenu);
} /* Software Untermenü */

void HMenu::Info_menu(void)
{
    HMenu::MENEU[5].HMWiMeIt_ID = 5;
    HMenu::MENEU[5].HMName = string("Info");
    HMenu::MENEU[5].HMWin = newwin(5,11,1,36 );
    wbkgd(HMenu::MENEU[5].HMWin,COLOR_PAIR(VARSYSMAN::UMeFe_HG));
    box(HMenu::MENEU[5].HMWin,0,0);
    //HMenu::MENEU[5].HMItem = (ITEM **)calloc(4, sizeof(ITEM *));
    HMenu::MENEU[5].HMItem = static_cast<ITEM **>(calloc(4, sizeof(ITEM *)));
    HMenu::MENEU[5].HMItem[0] = new_item("Code", HMenu::MENEU[5].HMName.c_str());
    HMenu::MENEU[5].HMItem[1] = new_item("E-Mail", HMenu::MENEU[5].HMName.c_str());
    HMenu::MENEU[5].HMItem[2] = new_item("Beenden", HMenu::MENEU[5].HMName.c_str());
    HMenu::MENEU[5].HMItem[3] = nullptr;
    HMenu::MENEU[5].HMMenu = new_menu(HMenu::MENEU[5].HMItem);
    set_menu_win(HMenu::MENEU[5].HMMenu, HMenu::MENEU[5].HMWin);
    set_menu_sub (HMenu::MENEU[5].HMMenu, derwin(HMenu::MENEU[5].HMWin, 0, 0, 1, 1));
    set_menu_spacing(HMenu::MENEU[5].HMMenu, 0,0,0);
    set_menu_format(HMenu::MENEU[5].HMMenu, 5, 0);
    menu_opts_off(HMenu::MENEU[5].HMMenu, O_SHOWDESC);
    menu_opts_off(HMenu::MENEU[5].HMMenu, O_NONCYCLIC);
    //set_menu_fore(HMenu::MENEU[5].HMMenu, COLOR_PAIR(12)|A_REVERSE|A_BOLD);
    set_menu_fore(HMenu::MENEU[5].HMMenu, COLOR_PAIR(VARSYSMAN::HaMe_FG)|A_BOLD);
    set_menu_back(HMenu::MENEU[5].HMMenu, COLOR_PAIR(VARSYSMAN::HaMe_HG));//|A_BOLD);
    set_menu_grey(HMenu::MENEU[5].HMMenu, COLOR_PAIR(VARSYSMAN::HaMe_grey)|A_BOLD);
    set_menu_mark(HMenu::MENEU[5].HMMenu,"");
    set_current_item(HMenu::MENEU[5].HMMenu, HMenu::MENEU[5].HMItem[0]);
    post_menu(HMenu::MENEU[5].HMMenu);
} /* Info Menü */

MENU *HMenu::tmpMe(const char *name, int id)
{
    MENU *tmpm = nullptr;
    int X;
    for (X = 1; X <= 5; X++){
        if ((strcmp(name,HMenu::MENEU[X].HMName.c_str())==0) || (id==X)){
            tmpm = HMenu::MENEU[X].HMMenu;
        }
    }
    return tmpm;
}

WINDOW *HMenu::tmpWi(const char *name, int id)
{
    WINDOW *tmpw = nullptr;

    if ((strcmp(name,HMenu::MENEU[1].HMName.c_str())==0) || (id==1)){ Datei_menu();
    }else if ((strcmp(name,HMenu::MENEU[2].HMName.c_str())==0) || (id==2)){ System_menu();
    }else if ((strcmp(name,HMenu::MENEU[3].HMName.c_str())==0) || (id==3)){ Server_menu();
    }else if ((strcmp(name,HMenu::MENEU[4].HMName.c_str())==0) || (id==4)){ Software_menu();
    }else if ((strcmp(name,HMenu::MENEU[5].HMName.c_str())==0) || (id==5)){ Info_menu();
    }

    int X;
    for (X = 1; X <= 5; X++){
        if ((strcmp(name,HMenu::MENEU[X].HMName.c_str())==0) || (id==HMenu::MENEU[X].HMWiMeIt_ID)){
            wrefresh(VARSYSMAN::clearwindow(HMenu::MENEU[X].HMWin));
            tmpw = HMenu::MENEU[X].HMWin;
        }
    }
    return tmpw;
}

void HMenu::quit(const char *name, string wahl)
{
    try {
        int tmpint;
        if (HMenu::MENEU[0].HMName.compare(name)==0){
        //if (strcmp(name,HMenu::MENEU[0].HMName.c_str())==0){
            if (HMenu::MENEU[0].HMWin){
                int E = item_count(HMenu::MENEU[0].HMMenu);
                unpost_menu(HMenu::MENEU[0].HMMenu);
                SAFE_DELETE(HMenu::MENEU[0].HMMenu);
                SAFE_DELETE_ARRAY(HMenu::MENEU[0].HMItem);
                wborder(HMenu::MENEU[0].HMWin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
                touchline(HMenu::MENEU[0].HMWin,0,E+1);
                delwin(HMenu::MENEU[0].HMWin);
                endwin();
            }
        }else{
            int X = 1;
            for (X = 1; X <= 5; X++){
                if (HMenu::MENEU[X].HMWin){
                    if (strcmp(name,HMenu::MENEU[X].HMName.c_str())!=0){
                        if(wahl.compare("++") == 0){
                            tmpint = VARSYSMAN::zahlenwerk(HMenu::MENEU[X].HMWiMeIt_ID,"++",5);
                            int E = item_count(HMenu::MENEU[tmpint].HMMenu);
                            unpost_menu(HMenu::MENEU[tmpint].HMMenu);
                            SAFE_DELETE(HMenu::MENEU[tmpint].HMMenu);
                            SAFE_DELETE_ARRAY(HMenu::MENEU[tmpint].HMItem);
                            wborder(HMenu::MENEU[tmpint].HMWin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
                            touchline(HMenu::MENEU[tmpint].HMWin,0,E+1);
                            delwin(HMenu::MENEU[tmpint].HMWin);
                            endwin();
                        }else if(wahl.compare("--") == 0){
                            tmpint = VARSYSMAN::zahlenwerk(HMenu::MENEU[X].HMWiMeIt_ID,"--",5);
                            int E = item_count(HMenu::MENEU[tmpint].HMMenu);
                            unpost_menu(HMenu::MENEU[tmpint].HMMenu);
                            SAFE_DELETE(HMenu::MENEU[tmpint].HMMenu);
                            SAFE_DELETE_ARRAY(HMenu::MENEU[tmpint].HMItem);
                            wborder(HMenu::MENEU[tmpint].HMWin, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
                            touchline(HMenu::MENEU[tmpint].HMWin,0,E+1);
                            delwin(HMenu::MENEU[tmpint].HMWin);
                            endwin();
                        }
                    }
                }
            }
        }
        refresh();
        redrawwin(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin2));
        wrefresh(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin2));

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

void HMenu::MenuStart(void)
{
    int ch;
    set_current_item(HMenu::MENEU[0].HMMenu, HMenu::MENEU[0].HMItem[HMenu::MeInAl]);
    WINDOW *tmpWi1 = HMenu::tmpWi(item_name(current_item(HMenu::MENEU[0].HMMenu)),
            item_index(current_item(HMenu::MENEU[0].HMMenu))+1);
    string tmpMeNa = string(item_name(current_item(HMenu::MENEU[0].HMMenu)));
    string MeAuWa = "";
    refresh();

    while((ch=getch()) != KEY_F(10)){
        switch(ch){
        case KEY_DOWN:{
                menu_driver(HMenu::tmpMe(item_name(current_item(HMenu::MENEU[0].HMMenu)),
                            item_index(current_item(HMenu::MENEU[0].HMMenu))+1), REQ_DOWN_ITEM);
                MeAuWa = string(item_name(current_item(HMenu::tmpMe(item_name(current_item(HMenu::MENEU[0].HMMenu)),
                                                       item_index(current_item(HMenu::MENEU[0].HMMenu))+1))));
            break;
        }
        case KEY_UP:{
                menu_driver(HMenu::tmpMe(item_name(current_item(HMenu::MENEU[0].HMMenu)),
                            item_index(current_item(HMenu::MENEU[0].HMMenu))+1), REQ_UP_ITEM);
                MeAuWa = string(item_name(current_item(HMenu::tmpMe(item_name(current_item(HMenu::MENEU[0].HMMenu)),
                                                       item_index(current_item(HMenu::MENEU[0].HMMenu))+1))));
            break;
        }
        case KEY_RIGHT:{
            menu_driver(HMenu::MENEU[0].HMMenu, REQ_RIGHT_ITEM);
            tmpMeNa = string(item_name(current_item(HMenu::MENEU[0].HMMenu)));
            HMenu::MENEU[VARSYSMAN::ZahlenWerk(1, item_index(current_item(HMenu::MENEU[0].HMMenu))+1 , 5, "+")].delwinow(STARTSYSMAN::START.TMPWin2);
            tmpWi1 = HMenu::tmpWi(item_name(current_item(HMenu::MENEU[0].HMMenu)),item_index(current_item(HMenu::MENEU[0].HMMenu))+1);
            break;
        }
        case KEY_LEFT:{
            menu_driver(HMenu::MENEU[0].HMMenu, REQ_LEFT_ITEM);
            tmpMeNa = string(item_name(current_item(HMenu::MENEU[0].HMMenu)));
            HMenu::MENEU[VARSYSMAN::ZahlenWerk(1, item_index(current_item(HMenu::MENEU[0].HMMenu))+1, 5, "-")].delwinow(STARTSYSMAN::START.TMPWin2);
            tmpWi1 = HMenu::tmpWi(item_name(current_item(HMenu::MENEU[0].HMMenu)),
                    item_index(current_item(HMenu::MENEU[0].HMMenu))+1);
            break;
        }
        case 10:{ //10:{ // 0xA:{
            HMenu::MeInAl = item_index(current_item(HMenu::MENEU[0].HMMenu));
                HMenu::MENEU[item_index(current_item(HMenu::MENEU[0].HMMenu))+1].delwinow(STARTSYSMAN::START.TMPWin2);
            STARTSYSMAN::fensterwahl(MeAuWa.c_str());
            break;
        }
        }
        wrefresh(VARSYSMAN::clearwindow(HMenu::MENEU[0].HMWin));
        wrefresh(VARSYSMAN::clearwindow(tmpWi1));
    }
}

