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

VARSYSMAN::FENSTERAKSOFT VARSYSMAN::AKSOFT;
std::vector<std::string> SOFTAKINSTALL::LXApps;
int SOFTAKINSTALL::Smyr, SOFTAKINSTALL::Smxc, SOFTAKINSTALL::arrlae;
static int MinPadRow = STARTSYSMAN::max_yr-11;
//#########################################################################

void SOFTAKINSTALL::Software_Fenster(void)
{
    VARSYSMAN::AKSOFT.FEID = 4;
    VARSYSMAN::AKSOFT.FENAME = string("AK_Software");
    if (STARTSYSMAN::START.TMPWin3) {delwin(STARTSYSMAN::START.TMPWin3);}
    STARTSYSMAN::START.TMPWin3 = newwin(STARTSYSMAN::max_yr-1,STARTSYSMAN::max_xc,1,0); //-23
    wbkgd(STARTSYSMAN::START.TMPWin3,COLOR_PAIR(61));
    box(STARTSYSMAN::START.TMPWin3, 0, 0);
    mvwvline(STARTSYSMAN::START.TMPWin3, 1, 20, ACS_VLINE, STARTSYSMAN::max_yr-3);
    mvwvline(STARTSYSMAN::START.TMPWin3, 0, 20, ACS_TTEE,1);
    mvwvline(STARTSYSMAN::START.TMPWin3, STARTSYSMAN::max_yr-2, 20, ACS_BTEE,1);
    mvwhline(STARTSYSMAN::START.TMPWin3, 8, 21, ACS_HLINE, STARTSYSMAN::max_xc-22);
    mvwvline(STARTSYSMAN::START.TMPWin3, 8, 20, ACS_LTEE,1);
    mvwvline(STARTSYSMAN::START.TMPWin3, 8, STARTSYSMAN::max_xc-1, ACS_RTEE,1);
    wrefresh(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));

    VARSYSMAN::AKSOFT.TMPWin1 = newwin(STARTSYSMAN::max_yr-3,19,2,1);
    VARSYSMAN::AKSOFT.TMPWin1 = derwin(STARTSYSMAN::START.TMPWin3, STARTSYSMAN::max_yr-3, 19, 1, 1);
    wbkgd(VARSYSMAN::AKSOFT.TMPWin1,COLOR_PAIR(61));
    VARSYSMAN::AKSOFT.TMPWin2 = newwin(7,STARTSYSMAN::max_xc-22,2,21);
    STARTSYSMAN::START.TMPWin2 = derwin(VARSYSMAN::AKSOFT.TMPWin3, 7, STARTSYSMAN::max_xc-22, 1, 21);
    wbkgd(VARSYSMAN::AKSOFT.TMPWin2,COLOR_PAIR(VARSYSMAN::IlMeFe_HG));
    VARSYSMAN::AKSOFT.TMPWin3 = newpad(STARTSYSMAN::max_xc - 11, STARTSYSMAN::max_xc - 22);
    wsetscrreg(VARSYSMAN::AKSOFT.TMPWin3, 1, STARTSYSMAN::max_yr-2);
    scrollok(VARSYSMAN::AKSOFT.TMPWin3, true);
}

void SOFTAKINSTALL::AK_SOFT_LIST(void)
{
    scrollok(VARSYSMAN::AKSOFT.TMPWin1, true);
    vector<string>().swap(SOFTAKINSTALL::LXApps);
    string tmparr;
    int mrows, mcols;
    unsigned long i = 0,s = 0;
    stringstream ssin(VARSYSMAN::ConfigDateiList[19]);
    while (std::getline(ssin, tmparr, ';')){
        SOFTAKINSTALL::LXApps.push_back(tmparr);
        ++i;
    }

    VARSYSMAN::AKSOFT.TMPItem2 = static_cast<ITEM **>(calloc(i+1, sizeof(ITEM *)));
    for (s = 0; s <= i; s++)
    {
        VARSYSMAN::AKSOFT.TMPItem2[s] = new_item(SOFTAKINSTALL::LXApps[s].c_str() , "");
    }
    VARSYSMAN::AKSOFT.TMPItem2[s+1] = nullptr;
    VARSYSMAN::AKSOFT.TMPMenu2 = new_menu(VARSYSMAN::AKSOFT.TMPItem2);
    set_menu_win(VARSYSMAN::AKSOFT.TMPMenu2, VARSYSMAN::AKSOFT.TMPWin1);
    set_menu_sub(VARSYSMAN::AKSOFT.TMPMenu2, derwin(VARSYSMAN::AKSOFT.TMPWin1, STARTSYSMAN::max_yr-3, 19, 0, 0));
    set_menu_format(VARSYSMAN::AKSOFT.TMPMenu2, STARTSYSMAN::max_yr-3, 1);
    scale_menu(VARSYSMAN::AKSOFT.TMPMenu2, &mrows, &mcols);
    menu_opts_off(VARSYSMAN::AKSOFT.TMPMenu2, O_SHOWDESC);
    menu_opts_on(VARSYSMAN::AKSOFT.TMPMenu2, O_NONCYCLIC);
    set_menu_fore(VARSYSMAN::AKSOFT.TMPMenu2, COLOR_PAIR(61)|A_REVERSE);
    set_menu_back(VARSYSMAN::AKSOFT.TMPMenu2, COLOR_PAIR(61));
    set_menu_grey(VARSYSMAN::AKSOFT.TMPMenu2, COLOR_PAIR(05));
    menu_opts_off(VARSYSMAN::AKSOFT.TMPMenu2, O_ONEVALUE);
    set_menu_mark(VARSYSMAN::AKSOFT.TMPMenu2, "");
    post_menu(VARSYSMAN::AKSOFT.TMPMenu2);
}

void SOFTAKINSTALL::AK_SOFT_Menu(void)
{
    scrollok(VARSYSMAN::AKSOFT.TMPWin2, true);
    VARSYSMAN::AKSOFT.TMPItem1 = static_cast<ITEM **>(calloc(9, sizeof(ITEM *)));
    VARSYSMAN::AKSOFT.TMPItem1[0] = new_item("[ Auswahl Install ]","");
    VARSYSMAN::AKSOFT.TMPItem1[1] = new_item("[     Löschen     ]","");
    VARSYSMAN::AKSOFT.TMPItem1[2] = new_item("[   TUI Install   ]","");
    VARSYSMAN::AKSOFT.TMPItem1[3] = new_item("[   TUI Löschen   ]","");
    VARSYSMAN::AKSOFT.TMPItem1[4] = new_item("[  Gnome Install  ]","");
    VARSYSMAN::AKSOFT.TMPItem1[5] = new_item("[  Gnome Löschen  ]","");
    VARSYSMAN::AKSOFT.TMPItem1[6] = new_item("[  LXQT Install   ]","");
    VARSYSMAN::AKSOFT.TMPItem1[7] = new_item("[  LXQT Löschen   ]","");
    VARSYSMAN::AKSOFT.TMPItem1[8] = nullptr;
    VARSYSMAN::AKSOFT.TMPMenu1 = new_menu(VARSYSMAN::AKSOFT.TMPItem1);
    set_menu_win (VARSYSMAN::AKSOFT.TMPMenu1, VARSYSMAN::AKSOFT.TMPWin2);
    set_menu_sub (VARSYSMAN::AKSOFT.TMPMenu1, derwin(VARSYSMAN::AKSOFT.TMPWin2, 7, STARTSYSMAN::max_xc-22, 2, 22));
    set_menu_spacing(VARSYSMAN::AKSOFT.TMPMenu1, 1, 1, 1);
    set_menu_format(VARSYSMAN::AKSOFT.TMPMenu1, 4, 2);
    set_menu_mark(VARSYSMAN::AKSOFT.TMPMenu1, "");
    menu_opts_off(VARSYSMAN::AKSOFT.TMPMenu1, O_NONCYCLIC);
    menu_opts_off(VARSYSMAN::AKSOFT.TMPMenu1, O_SHOWDESC);
    set_menu_fore(VARSYSMAN::AKSOFT.TMPMenu1, COLOR_PAIR(VARSYSMAN::IlMe_FG)|A_BOLD);
    set_menu_back(VARSYSMAN::AKSOFT.TMPMenu1, COLOR_PAIR(VARSYSMAN::IlMe_HG)|A_BOLD);
    set_menu_grey(VARSYSMAN::AKSOFT.TMPMenu1, COLOR_PAIR(VARSYSMAN::IlMe_grey)|A_BOLD);
    post_menu(VARSYSMAN::AKSOFT.TMPMenu1);
}

string SOFTAKINSTALL::BefZusa(string name)
{
    //int len;
    string BezAppInst1("apt-cache show ");
    string BezAppInst2(""); //("|grep -w Description -A 8");
    //string s("dpkg-query --show --showformat='${Package}\n${Version}\n${Description}' ");
    BezAppInst1.append (name);
    //BezAppInst1.append (BezAppInst2);
    return BezAppInst1;
    /*len = s.length ();
  s.insert(len,name);
  len = s.length();
  s.insert(len,s2);
  return s;*/
}

int SOFTAKINSTALL::Zeilen(string data, int maxbreite){
    int rownr = 0;
    double zeiBr = (data.length() / static_cast<double>(maxbreite));
    int zeiBr2;
    stringstream datast(data);
    string line;
    for (rownr = 0; std::getline(datast, line); ++rownr){}
    zeiBr2 = static_cast<int>(ceil(zeiBr));
    return (rownr + zeiBr2);
}

void SOFTAKINSTALL::menu_surf(string name, int id){
    //quit(HMenu::MeNa_alt);
    if ((strcmp(name.c_str(),"[ Auswahl Install ]")==0) || (id==0)){
        ITEM **items;
        string instapp;
        items = menu_items(VARSYSMAN::AKSOFT.TMPMenu2);
        for(int i = 0; i < item_count(VARSYSMAN::AKSOFT.TMPMenu2); ++i)
        {
            if(item_value(items[i]) == TRUE)
            {
                instapp.append(" ");
                instapp.append(item_name(items[i]));
            }
        }
        SOFTAKINSTALL::AK_SOFT_Inst_Button(instapp);
    }else if ((strcmp(name.c_str(),"[     Löschen     ]")==0) || (id==1)){
        ITEM **items;
        string instapp;
        items = menu_items(VARSYSMAN::AKSOFT.TMPMenu2);
        for(int i = 0; i < item_count(VARSYSMAN::AKSOFT.TMPMenu2); ++i)
        {
            if(item_value(items[i]) == TRUE)
            {
                instapp.append(" ");
                instapp.append(item_name(items[i]));
            }
        }
        SOFTAKINSTALL::AK_SOFT_Remo_Button(instapp);
    } else if ((strcmp(name.c_str(),"[   TUI Install   ]")==0) || (id==2)){
        string instapp = "mc gpm elinks aptitude wavemon ncdu iotop apachetop htop nmap netcat iptraf ethstatus "
                         "tshark mtr cmus moc alsa ceni sysv_rc_conf lynis goaccess jnettop partimage lshw lshw-gtk "
                         "inxi btscanner btmon wicd-curses wireless-tools wpasupplicant";
        SOFTAKINSTALL::AK_SOFT_Inst_Button(instapp);
    }  else if ((strcmp(name.c_str(),"[   TUI Löschen  ]")==0) || (id==3)){
        string instapp = "mc gpm elinks aptitude wavemon ncdu iotop apachetop htop nmap netcat iptraf ethstatus "
                         "tshark mtr cmus moc alsa ceni sysv_rc_conf lynis goaccess jnettop partimage lshw lshw-gtk "
                         "inxi btscanner btmon wicd-curses wireless-tools wpasupplicant";
        SOFTAKINSTALL::AK_SOFT_Remo_Button(instapp);
    }  else if ((strcmp(name.c_str(),"[  Gnome Install  ]")==0) || (id==4)){
        string instapp = "gnome-shell gnome-terminal gnome-tweak-tool software-center synaptic firefox gedit nautilus "
                         "sysinfo gparted nautilus-admin nautilus-hide nautilus-share file-roller alacarte gdebi "
                         "build-essential gnome-builder xserver-xorg xinit xterm";
        SOFTAKINSTALL::AK_SOFT_Inst_Button(instapp);
    }  else if ((strcmp(name.c_str(),"[  Gnome Löschen ]")==0) || (id==4)){
        string instapp = "gnome-shell gnome-terminal gnome-tweak-tool software-center synaptic firefox gedit nautilus "
                         "sysinfo gparted nautilus-admin nautilus-hide nautilus-share file-roller alacarte gdebi "
                         "build-essential gnome-builder xserver-xorg xinit xterm";
        SOFTAKINSTALL::AK_SOFT_Remo_Button(instapp);
    }  else if ((strcmp(name.c_str(),"[  LXQT install   ]")==0) || (id==4)){
        string instapp = "gnome-terminal software-center synaptic firefox gedit nautilus "
                         "sysinfo gparted nautilus-admin nautilus-hide nautilus-share file-roller alacarte gdebi "
                         "build-essential gnome-builder qtcreator qtbase5-dev-tools gcc g++ gdb flex bison xserver-xorg "
                         "xinit xterm lximage-qt lxqt lxqt-about lxqt-admin lxqt-build-tools lxqt-common lxqt-config "
                         "lxqt-core lxqt-globalkeys lxqt-notificationd lxqt-openssh-askpass lxqt-panel lxqt-policykit "
                         "lxqt-powermanagement lxqt-qtplugin lxqt-runner lxqt-session lxqt-sudo";
        SOFTAKINSTALL::AK_SOFT_Inst_Button(instapp);
    }  else if ((strcmp(name.c_str(),"[  LXQT Löschen  ]")==0) || (id==4)){
        string instapp = "gnome-terminal software-center synaptic firefox gedit nautilus "
                         "sysinfo gparted nautilus-admin nautilus-hide nautilus-share file-roller alacarte gdebi "
                         "build-essential gnome-builder qtcreator qtbase5-dev-tools gcc g++ gdb flex bison xserver-xorg "
                         "xinit xterm lximage-qt lxqt lxqt-about lxqt-admin lxqt-build-tools lxqt-common lxqt-config "
                         "lxqt-core lxqt-globalkeys lxqt-notificationd lxqt-openssh-askpass lxqt-panel lxqt-policykit "
                         "lxqt-powermanagement lxqt-qtplugin lxqt-runner lxqt-session lxqt-sudo";
        SOFTAKINSTALL::AK_SOFT_Remo_Button(instapp);
    }else{

    }
}

void SOFTAKINSTALL::AK_SOFT_Inst_Button(string liste)
{
    string instSoft = "apt-get -y install ";
    instSoft.append(liste);

    werase(VARSYSMAN::AKSOFT.TMPWin3);
    string ls = VARSYSMAN::TERM_AUSGABE(instSoft);
    VARSYSMAN::AKSOFT.TMPWinHigh = SOFTAKINSTALL::Zeilen(ls,STARTSYSMAN::max_xc-22);
    VARSYSMAN::AKSOFT.TMPWin3 = newpad(VARSYSMAN::AKSOFT.TMPWinHigh+4,STARTSYSMAN::max_xc-22);
    VARSYSMAN::AKSOFT.TMPWin3 = derwin(STARTSYSMAN::START.TMPWin3,STARTSYSMAN::max_yr-11,STARTSYSMAN::max_xc-22,9,21);
    wbkgd(VARSYSMAN::AKSOFT.TMPWin3,COLOR_PAIR(61));
    wsetscrreg(VARSYSMAN::AKSOFT.TMPWin3,STARTSYSMAN::max_yr-11,STARTSYSMAN::max_xc-22);
    scrollok(VARSYSMAN::AKSOFT.TMPWin3,true);
    scroll(VARSYSMAN::AKSOFT.TMPWin3);
    waddnstr(VARSYSMAN::AKSOFT.TMPWin3, ls.c_str(),-1);
    //wrefresh(VARSYSMAN::AKSOFT.TMPWin1);
    prefresh(VARSYSMAN::clearwindow(VARSYSMAN::AKSOFT.TMPWin3), 0, 0, 9, 21, STARTSYSMAN::max_yr-1, STARTSYSMAN::max_xc-1);
}

void SOFTAKINSTALL::AK_SOFT_Remo_Button(string liste)
{
    string instSoft = "apt-get -y remove --purge ";
    instSoft.append(liste);

    werase(VARSYSMAN::AKSOFT.TMPWin3);
    string ls = VARSYSMAN::TERM_AUSGABE(instSoft);
    VARSYSMAN::AKSOFT.TMPWinHigh = SOFTAKINSTALL::Zeilen(ls,STARTSYSMAN::max_xc-22);
    VARSYSMAN::AKSOFT.TMPWin3 = newpad(VARSYSMAN::AKSOFT.TMPWinHigh+4,STARTSYSMAN::max_xc-22);
    VARSYSMAN::AKSOFT.TMPWin3 = derwin(STARTSYSMAN::START.TMPWin3,STARTSYSMAN::max_yr-11,STARTSYSMAN::max_xc-22,9,21);
    wbkgd(VARSYSMAN::AKSOFT.TMPWin3,COLOR_PAIR(61));
    wsetscrreg(VARSYSMAN::AKSOFT.TMPWin3,STARTSYSMAN::max_yr-11,STARTSYSMAN::max_xc-22);
    scrollok(VARSYSMAN::AKSOFT.TMPWin3,true);
    scroll(VARSYSMAN::AKSOFT.TMPWin3);
    waddnstr(VARSYSMAN::AKSOFT.TMPWin3, ls.c_str(),-1);
    prefresh(VARSYSMAN::clearwindow(VARSYSMAN::AKSOFT.TMPWin3), 0, 0, 9, 21, STARTSYSMAN::max_yr-1, STARTSYSMAN::max_xc-1);
}

void SOFTAKINSTALL::AK_DESC_Anzeigen(string DescPad_tmp)
{
    if (VARSYSMAN::AKSOFT.TMPWin3) {werase(VARSYSMAN::AKSOFT.TMPWin3); delwin(STARTSYSMAN::START.TMPWin3);}
    string ls = VARSYSMAN::TERM_AUSGABE(DescPad_tmp);
    VARSYSMAN::AKSOFT.TMPWinHigh = SOFTAKINSTALL::Zeilen(ls,STARTSYSMAN::max_xc-22);
    VARSYSMAN::AKSOFT.TMPWin3 = newpad(VARSYSMAN::AKSOFT.TMPWinHigh,STARTSYSMAN::max_xc-22);
    STARTSYSMAN::START.TMPWin3 = derwin(VARSYSMAN::AKSOFT.TMPWin3, MinPadRow, STARTSYSMAN::max_xc-22, 10, 21);
    wbkgd(VARSYSMAN::AKSOFT.TMPWin3,COLOR_PAIR(61));
    mvwaddstr(VARSYSMAN::AKSOFT.TMPWin3, 0, 0, ls.c_str());
}

void SOFTAKINSTALL::AK_UB_start(void)
{
    SOFTAKINSTALL::Software_Fenster();
    SOFTAKINSTALL::AK_SOFT_Menu();
    SOFTAKINSTALL::AK_SOFT_LIST();

    keypad(STARTSYSMAN::START.TMPWin3, true);

    refresh();
    touchwin(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
    wrefresh(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
    wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::AKSOFT.TMPWin1));
    wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::AKSOFT.TMPWin2));
    prefresh(VARSYSMAN::clearwindow(VARSYSMAN::AKSOFT.TMPWin3), 0, 0, 10, 21, STARTSYSMAN::max_yr-2, STARTSYSMAN::max_xc-1);

    int ROWS = 0;
    int c;
    int tabspace = 1;

    while ((c = getch()) != KEY_F(10))
    {
        switch(tabspace){
        case 1: //########################-Menu-#############################################
            switch(c){
            case KEY_UP:
                menu_driver(VARSYSMAN::AKSOFT.TMPMenu2, REQ_UP_ITEM);
                break;
            case KEY_DOWN:
                menu_driver(VARSYSMAN::AKSOFT.TMPMenu2, REQ_DOWN_ITEM);
                break;
            case KEY_NPAGE:
                menu_driver(VARSYSMAN::AKSOFT.TMPMenu2, REQ_LAST_ITEM);
                break;
            case KEY_PPAGE:
                menu_driver(VARSYSMAN::AKSOFT.TMPMenu2, REQ_FIRST_ITEM);
                break;
            case 0x20: //Leertasten
                menu_driver(VARSYSMAN::AKSOFT.TMPMenu2, REQ_TOGGLE_ITEM);
                break;
            case 0x09: //strg+y
                tabspace = VARSYSMAN::zahlenwerk(1,"++",3);
                break;
            case KEY_BTAB: //strg+x
                tabspace = VARSYSMAN::zahlenwerk(1,"--",3);
                break;
            case 10: //enter
                tabspace = VARSYSMAN::zahlenwerk(2,"++",3);
                break;
            }
            SOFTAKINSTALL::AK_DESC_Anzeigen(SOFTAKINSTALL::BefZusa(item_name(current_item(VARSYSMAN::AKSOFT.TMPMenu2))));
            ROWS = 0;
            break;
        case 2: //##############################-FORM-#########################################
            switch(c)
            {
            case KEY_UP:
                menu_driver(VARSYSMAN::AKSOFT.TMPMenu1, REQ_UP_ITEM);
                break;
            case KEY_DOWN:
                menu_driver(VARSYSMAN::AKSOFT.TMPMenu1, REQ_DOWN_ITEM);
                break;
            case KEY_LEFT:
                menu_driver(VARSYSMAN::AKSOFT.TMPMenu1, REQ_LEFT_ITEM);
                break;
            case KEY_RIGHT:
                menu_driver(VARSYSMAN::AKSOFT.TMPMenu1, REQ_RIGHT_ITEM);
                break;
            case 0x09:
                tabspace = VARSYSMAN::zahlenwerk(2,"++",3);
                break;
            case KEY_BTAB:
                tabspace = VARSYSMAN::zahlenwerk(2,"--",3);
                break;
            case 10:
                SOFTAKINSTALL::menu_surf(item_name(current_item(VARSYSMAN::AKSOFT.TMPMenu1)),
                                         item_index(current_item(VARSYSMAN::AKSOFT.TMPMenu1)));
                break;
            }
            break;
        case 3: //##############################-FORM-#########################################
            switch(c)
            {
            case KEY_UP:
                if (ROWS <= 0){
                    ROWS = 0;
                }else {
                    ROWS--;
                }
                break;
            case KEY_DOWN:
                if (ROWS >= VARSYSMAN::AKSOFT.TMPWinHigh){
                    ROWS = VARSYSMAN::AKSOFT.TMPWinHigh;
                }else {
                    ROWS++;
                }
                break;
            case 0x09: //strg+y
                tabspace = VARSYSMAN::zahlenwerk(3,"++",3);
                break;
            case KEY_BTAB: //strg+x
                tabspace = VARSYSMAN::zahlenwerk(3,"--",3);
                break;
            }
            break;
        }
        refresh();
        wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::AKSOFT.TMPWin1));
        wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::AKSOFT.TMPWin2));
        prefresh(VARSYSMAN::clearwindow(VARSYSMAN::AKSOFT.TMPWin3), ROWS, 0, 10, 21, STARTSYSMAN::max_yr-2, STARTSYSMAN::max_xc-1);
    }
    SOFTAKINSTALL::QUIT_AK_UB_INST();
}

void SOFTAKINSTALL::QUIT_AK_UB_INST()
{
    int e,i;

    SOFTAKINSTALL::LXApps.clear();
    std::vector<std::string>(SOFTAKINSTALL::LXApps).swap (SOFTAKINSTALL::LXApps);

    e = item_count(VARSYSMAN::AKSOFT.TMPMenu1);
    unpost_menu(VARSYSMAN::AKSOFT.TMPMenu1);
    for(i=0; i<=e-1; i++) {
        free_item(VARSYSMAN::AKSOFT.TMPItem1[i]);
    }
    free_menu(VARSYSMAN::AKSOFT.TMPMenu1);

    e = item_count(VARSYSMAN::AKSOFT.TMPMenu2);
    unpost_menu(VARSYSMAN::AKSOFT.TMPMenu2);

    for(i=0; i<=e-1; i++) {
        free_item(VARSYSMAN::AKSOFT.TMPItem2[i]);
    }
    free_menu(VARSYSMAN::AKSOFT.TMPMenu2);

    delwin(VARSYSMAN::AKSOFT.TMPWin1);
    delwin(VARSYSMAN::AKSOFT.TMPWin2);
    delwin(VARSYSMAN::AKSOFT.TMPWin3);
    endwin();

    refresh();
}
