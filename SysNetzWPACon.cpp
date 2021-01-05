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

VARSYSMAN::FENSTERWPACONNECT VARSYSMAN::WPACONNECT;

string WPA_CONNECT::wlanstatus;
string WPA_CONNECT::VG1;

void WPA_CONNECT::fensterdesign(void)
{
    VARSYSMAN::WPACONNECT.FEID = 6;
    VARSYSMAN::WPACONNECT.FENAME = string("Wlan");
    STARTSYSMAN::START.TMPWin3 = VARSYSMAN::DelTmpWin(STARTSYSMAN::START.TMPWin3);
    delwin(STARTSYSMAN::START.TMPWin3);
    STARTSYSMAN::START.TMPWin3 = newwin(STARTSYSMAN::max_yr-2,STARTSYSMAN::max_xc,2,0); //-23
    wbkgd(STARTSYSMAN::START.TMPWin3,COLOR_PAIR(61));
    box(STARTSYSMAN::START.TMPWin3, 0, 0);
    VARSYSMAN::WPACONNECT.TMPWinHigh = STARTSYSMAN::max_yr-9;
    VARSYSMAN::WPACONNECT.TMPWin1 = newpad(VARSYSMAN::WPACONNECT.TMPWinHigh, STARTSYSMAN::max_xc-2);
    //VARSYSMAN::WPACONNECT.TMPWin1 = subpad(STARTSYSMAN::START.TMPWin3, VARSYSMAN::WPACONNECT.TMPWinHigh, STARTSYSMAN::max_xc-2, 8, 1); //,5,1);
    wbkgd(VARSYSMAN::WPACONNECT.TMPWin1,COLOR_PAIR(11));
    STARTSYSMAN::START.TMPWin3 = derwin(VARSYSMAN::WPACONNECT.TMPWin1, VARSYSMAN::WPACONNECT.TMPWinHigh, STARTSYSMAN::max_xc-2, 8, 1);
    wsetscrreg(VARSYSMAN::WPACONNECT.TMPWin1, 0, STARTSYSMAN::max_yr-3);
    scrollok(VARSYSMAN::WPACONNECT.TMPWin1, true);
    //  scroll(VARSYSMAN::WPACONNECT.TMPWin1);
}

void WPA_CONNECT::Wlan_button(void)
{
    VARSYSMAN::WPACONNECT.TMPWin2 = newwin(5,STARTSYSMAN::max_xc-14,3,7);
    wbkgd(VARSYSMAN::WPACONNECT.TMPWin2,COLOR_PAIR(VARSYSMAN::IlMeFe_HG));
    VARSYSMAN::WPACONNECT.TMPItem1 = static_cast<ITEM **>(calloc(10, sizeof(ITEM *)));
    VARSYSMAN::WPACONNECT.TMPItem1[0] = new_item("[  Starten   ]","");
    VARSYSMAN::WPACONNECT.TMPItem1[1] = new_item("[  Beenden   ]","");
    VARSYSMAN::WPACONNECT.TMPItem1[2] = new_item("[ Verbinden  ]","");
    VARSYSMAN::WPACONNECT.TMPItem1[3] = new_item("[  Trennen   ]","");
    VARSYSMAN::WPACONNECT.TMPItem1[4] = new_item("[   Status   ]","");
    VARSYSMAN::WPACONNECT.TMPItem1[5] = new_item("[ Scan WLAN  ]","");
    VARSYSMAN::WPACONNECT.TMPItem1[6] = new_item("[  WPA INST  ]","");
    VARSYSMAN::WPACONNECT.TMPItem1[7] = new_item("[ WPA DELETE ]","");
    VARSYSMAN::WPACONNECT.TMPItem1[8] = new_item("[ Wlan IFace ]","");
    VARSYSMAN::WPACONNECT.TMPItem1[9] = nullptr;
    VARSYSMAN::WPACONNECT.TMPMenu1 = new_menu(VARSYSMAN::WPACONNECT.TMPItem1);
    set_menu_win(VARSYSMAN::WPACONNECT.TMPMenu1, VARSYSMAN::WPACONNECT.TMPWin2);
    set_menu_sub(VARSYSMAN::WPACONNECT.TMPMenu1, VARSYSMAN::WPACONNECT.TMPWin2);
    set_menu_spacing(VARSYSMAN::WPACONNECT.TMPMenu1, 1, 0, 0);
    set_menu_format(VARSYSMAN::WPACONNECT.TMPMenu1, 3, 3);
    set_menu_mark(VARSYSMAN::WPACONNECT.TMPMenu1, "");
    set_menu_pad(VARSYSMAN::WPACONNECT.TMPMenu1, 1);
    menu_opts_off(VARSYSMAN::WPACONNECT.TMPMenu1, O_NONCYCLIC);
    menu_opts_off(VARSYSMAN::WPACONNECT.TMPMenu1, O_SHOWDESC);
    set_menu_fore(VARSYSMAN::WPACONNECT.TMPMenu1, COLOR_PAIR(VARSYSMAN::IlMe_FG)|WA_BOLD);
    set_menu_back(VARSYSMAN::WPACONNECT.TMPMenu1, COLOR_PAIR(VARSYSMAN::IlMe_HG)|WA_BOLD);
    set_menu_grey(VARSYSMAN::WPACONNECT.TMPMenu1, COLOR_PAIR(VARSYSMAN::IlMe_grey)|WA_BOLD);
    STARTSYSMAN::START.TMPWin3 = subwin(VARSYSMAN::WPACONNECT.TMPWin2, 5, STARTSYSMAN::max_xc-14, 3, 7);
    post_menu(VARSYSMAN::WPACONNECT.TMPMenu1);
    refresh();
    touchwin(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
    wrefresh(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
    wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::WPACONNECT.TMPWin2));
    prefresh(VARSYSMAN::clearwindow(VARSYSMAN::WPACONNECT.TMPWin1), 0, 0, 8, 1, STARTSYSMAN::max_yr -1, STARTSYSMAN::max_xc -1);
} /* WLAN MENU */

void WPA_CONNECT::Wlan_Iface(void)
{
    int X;
    int maxlenname = 0;
    VARSYSMAN::WPACONNECT.TMPItem1 = static_cast<ITEM **>(calloc(10, sizeof(ITEM *)));
    for (X = 0; X <= 4; X++){
        if (maxlenname < static_cast<signed>(VARSYSMAN::NETZWERK_IF[X].IF_Name[0].length())){
            maxlenname = static_cast<signed>(VARSYSMAN::NETZWERK_IF[X].IF_Name[0].length());
        }
        VARSYSMAN::WPACONNECT.TMPItem1[X] = new_item(VARSYSMAN::NETZWERK_IF[X].IF_Name[0].c_str(),"");
    }
    VARSYSMAN::WPACONNECT.TMPItem1[X+1] = nullptr;
    VARSYSMAN::WPACONNECT.TMPMenu1 = new_menu(VARSYSMAN::WPACONNECT.TMPItem1);
    // VARSYSMAN::WPACONNECT.TMPWin1 = newwin(3+2,maxlenname+3,3,1);
    VARSYSMAN::WPACONNECT.TMPWin1 = newwin(3,6,3,1);
    wbkgd(VARSYSMAN::WPACONNECT.TMPWin1, COLOR_PAIR(03));
    //box(VARSYSMAN::WPACONNECT.TMPWin1,0,0);
    set_menu_win(VARSYSMAN::WPACONNECT.TMPMenu1, VARSYSMAN::WPACONNECT.TMPWin1);
    set_menu_sub (VARSYSMAN::WPACONNECT.TMPMenu1, derwin(VARSYSMAN::WPACONNECT.TMPWin1, 3, 6, 3, 1));
    set_menu_spacing(VARSYSMAN::WPACONNECT.TMPMenu1, 1, 1, 1);
    set_menu_format(VARSYSMAN::WPACONNECT.TMPMenu1, 3, 1);
    set_menu_mark(VARSYSMAN::WPACONNECT.TMPMenu1, "");
    set_menu_pad(VARSYSMAN::WPACONNECT.TMPMenu1, 1);
    menu_opts_on(VARSYSMAN::WPACONNECT.TMPMenu1, O_NONCYCLIC);
    menu_opts_off(VARSYSMAN::WPACONNECT.TMPMenu1, O_SHOWDESC);
    set_menu_fore(VARSYSMAN::WPACONNECT.TMPMenu1, COLOR_PAIR(03)|WA_BOLD|WA_REVERSE);
    set_menu_back(VARSYSMAN::WPACONNECT.TMPMenu1, COLOR_PAIR(03)|WA_BOLD);
    post_menu(VARSYSMAN::WPACONNECT.TMPMenu1);
    wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::WPACONNECT.TMPWin1));

    int c1;
    while ((c1= getch()) != KEY_F(10))
    {
        switch (c1)
        {
        case KEY_DOWN:
        {
            menu_driver(VARSYSMAN::WPACONNECT.TMPMenu1, REQ_DOWN_ITEM);
            break;
        }
        case KEY_UP:
        {
            menu_driver(VARSYSMAN::WPACONNECT.TMPMenu1, REQ_UP_ITEM);
            break;
        }
        case 0x0A:
        {
            werase(VARSYSMAN::clearwindow(VARSYSMAN::WPACONNECT.TMPWin1));
            //WPA_CONNECT::wlanstatus = string(item_name(current_item(VARSYSMAN::WPACONNECT.TMPMenu)));
            SYSNETZWERK::NETNMeWaNe = string(item_name(current_item(VARSYSMAN::WPACONNECT.TMPMenu1)));
            WPA_CONNECT::BefZusa("first check");
            has_key(KEY_F(10));
            break;
        }
        }
        wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::WPACONNECT.TMPWin1));
    }
    int e;
    e = item_count(VARSYSMAN::WPACONNECT.TMPMenu1);
    unpost_menu(VARSYSMAN::WPACONNECT.TMPMenu1);
    for(int i=0; i<=e-1; i++) {
        free_item(VARSYSMAN::WPACONNECT.TMPItem1[i]);
    }
    free_menu(VARSYSMAN::WPACONNECT.TMPMenu1);
    wborder(VARSYSMAN::WPACONNECT.TMPWin1, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wclear(VARSYSMAN::WPACONNECT.TMPWin1);
    werase(VARSYSMAN::WPACONNECT.TMPWin1);
    delwin(VARSYSMAN::WPACONNECT.TMPWin1);
    endwin();
}

void WPA_CONNECT::GetStdoutFromCommand(string cmd,int opt)
{
    //int res;
    try {
        string data;
        FILE *stream;
        //touchwin(STARTSYSMAN::START.TMPWin3);

        const int max_buffer = 1024;
        char buffer[max_buffer];
        cmd.append(" 2>&1");
        stream = popen(cmd.c_str(), "r");
        if (stream){
            while (!feof(stream))
                if (fgets(buffer, max_buffer, stream) != nullptr) data.append(buffer);
            pclose(stream);
        }
        if(opt==1){
            if(strstr(data.c_str(),"wpa_state=COMPLETED")){
                WPA_CONNECT::wlanstatus = "Connected!    ";
            }else if (strstr(data.c_str(),"wpa_state=DISCONNECTED")){
                WPA_CONNECT::wlanstatus = "Disconnected! ";
            }else{
                //(strcmp(WPA_CONNECT::wlanstatus.c_str(),WPA_CONNECT::VG1.c_str())==0);
                WPA_CONNECT::VG1 = "";
                WPA_CONNECT::VG1.append(SYSNETZWERK::NETNMeWaNe);
                WPA_CONNECT::VG1.append(" inaktiv!");
                WPA_CONNECT::wlanstatus = VG1;
                wattr_on(VARSYSMAN::WPACONNECT.TMPWin2, COLOR_PAIR(62)|WA_BOLD,nullptr);
                mvwaddstr(VARSYSMAN::WPACONNECT.TMPWin2,0,STARTSYSMAN::max_xc-25,WPA_CONNECT::wlanstatus.c_str());
                wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::WPACONNECT.TMPWin2));
                wattr_off(VARSYSMAN::WPACONNECT.TMPWin2, COLOR_PAIR(62)|WA_BOLD,nullptr);
                waddnstr(VARSYSMAN::WPACONNECT.TMPWin1,data.c_str(),-1);
                touchwin(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
                prefresh(VARSYSMAN::clearwindow(VARSYSMAN::WPACONNECT.TMPWin1), 0, 0, 8, 1, STARTSYSMAN::max_yr -1, STARTSYSMAN::max_xc -1);
            }
        }else{
            int maxbreite = STARTSYSMAN::max_xc-2;
            int rownr = 0;
            stringstream datast(data);
            string line;
            for (rownr = 0; std::getline(datast, line); ++rownr)
            {
                double zeiBr = line.length() / static_cast<unsigned long>(maxbreite);
                rownr = rownr + static_cast<int>(ceil(zeiBr));
            }
            if (VARSYSMAN::WPACONNECT.TMPWinHigh<=rownr){
                int buff = (rownr - VARSYSMAN::WPACONNECT.TMPWinHigh);
                VARSYSMAN::WPACONNECT.TMPWinHigh = VARSYSMAN::WPACONNECT.TMPWinHigh + buff;
                delwin(VARSYSMAN::WPACONNECT.TMPWin1);
                VARSYSMAN::WPACONNECT.TMPWin1 = newpad(VARSYSMAN::WPACONNECT.TMPWinHigh,STARTSYSMAN::max_xc-2);
            }
            waddnstr(VARSYSMAN::WPACONNECT.TMPWin1,data.c_str(),-1);
            touchwin(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
            prefresh(VARSYSMAN::clearwindow(VARSYSMAN::WPACONNECT.TMPWin1), 0, 0, 8, 1, STARTSYSMAN::max_yr -1, STARTSYSMAN::max_xc -1);
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
    //return (res);
}

void WPA_CONNECT::BefZusa(string name)
{
    string Wl2;
    WPA_CONNECT::VG1 = "";
    WPA_CONNECT::VG1.append(SYSNETZWERK::NETNMeWaNe);
    WPA_CONNECT::VG1.append(" inaktiv!");

    if (strcmp(name.c_str(),"[  Starten   ]")==0){
        if(strcmp(WPA_CONNECT::wlanstatus.c_str(),WPA_CONNECT::VG1.c_str())==0){
            wattr_on(VARSYSMAN::WPACONNECT.TMPWin1, COLOR_PAIR(63)|WA_BOLD,nullptr);
            wprintw(VARSYSMAN::WPACONNECT.TMPWin1,"%s Interface wird gestartet!\n",SYSNETZWERK::NETNMeWaNe.c_str());
            wattr_off(VARSYSMAN::WPACONNECT.TMPWin1, COLOR_PAIR(63)|WA_BOLD,nullptr);
            Wl2 = "ip link set dev ";
            Wl2.append(SYSNETZWERK::NETNMeWaNe);
            Wl2.append(" up");
            WPA_CONNECT::GetStdoutFromCommand(Wl2,0);
            waddnstr(VARSYSMAN::WPACONNECT.TMPWin1,"mit Netzwerk wird Verbunden!\n",-1);
            Wl2 = "wpa_supplicant -B -i";
            Wl2.append(SYSNETZWERK::NETNMeWaNe);
            Wl2.append(" -c/etc/wpa_supplicant/");
            Wl2.append(SYSNETZWERK::NETNMeWaNe);
            Wl2.append("-wpa.conf");
            WPA_CONNECT::GetStdoutFromCommand(Wl2,0);
            waddnstr(VARSYSMAN::WPACONNECT.TMPWin1,"DHCP wird angefordert!\n",-1);
            Wl2 = "dhclient -v ";
            Wl2.append(SYSNETZWERK::NETNMeWaNe);
            WPA_CONNECT::GetStdoutFromCommand(Wl2,0);
            wattr_on(VARSYSMAN::WPACONNECT.TMPWin1, COLOR_PAIR(63),nullptr);
            wprintw(VARSYSMAN::WPACONNECT.TMPWin1,"%s Verbindung ist hergestellt!\n",SYSNETZWERK::NETNMeWaNe.c_str());
            wattr_off(VARSYSMAN::WPACONNECT.TMPWin1, COLOR_PAIR(62),nullptr);
            WPA_CONNECT::wlanstatus = "Connected!    ";
            SYSNETZWERK::Start_Route();
            SYSNETZWERK::IFACENAME();
            SYSNETZWERK::VendorDevice();
        }else if(strcmp(WPA_CONNECT::wlanstatus.c_str(),"Disconnected! ")==0){
            waddnstr(VARSYSMAN::WPACONNECT.TMPWin1,"WPA ist aktiv bitte verbinden!\n",-1);
        }else{
            wprintw(VARSYSMAN::WPACONNECT.TMPWin1,"%s ist bereits Verbunden!\n",SYSNETZWERK::NETNMeWaNe.c_str());
        }
    }else if (strcmp(name.c_str(),"[  Beenden   ]")==0){
        if((strcmp(WPA_CONNECT::wlanstatus.c_str(),"Disconnected! ")==0) || (strcmp(WPA_CONNECT::wlanstatus.c_str(),"Connected!    ")==0)){
            wattr_on(VARSYSMAN::WPACONNECT.TMPWin1, COLOR_PAIR(63),nullptr);
            waddnstr(VARSYSMAN::WPACONNECT.TMPWin1,"Verbindung wird getrennt!\n",-1);
            wattr_on(VARSYSMAN::WPACONNECT.TMPWin1, COLOR_PAIR(62),nullptr);
            string Wl4("wpa_cli disconnect");
            WPA_CONNECT::GetStdoutFromCommand(Wl4,0);
            string Wl43("pkill dhclient");
            WPA_CONNECT::GetStdoutFromCommand(Wl43,0);
            string Wl432("pkill wpa_supplicant");
            WPA_CONNECT::GetStdoutFromCommand(Wl432,0);
            wprintw(VARSYSMAN::WPACONNECT.TMPWin1,"%s Interface wird runtergefahren!\n",SYSNETZWERK::NETNMeWaNe.c_str());
            Wl2 = "ip link set dev ";
            Wl2.append(SYSNETZWERK::NETNMeWaNe);
            Wl2.append(" down");
            WPA_CONNECT::GetStdoutFromCommand(Wl2,0);
            waddnstr(VARSYSMAN::WPACONNECT.TMPWin1,"Prozesse werden beendet!\n",-1);
            Wl2 = "ip addr flush dev ";
            Wl2.append(SYSNETZWERK::NETNMeWaNe);
            WPA_CONNECT::GetStdoutFromCommand(Wl2,0);
            wattr_on(VARSYSMAN::WPACONNECT.TMPWin1, COLOR_PAIR(63), nullptr);
            wprintw(VARSYSMAN::WPACONNECT.TMPWin1,"%s ist nun getrennt!\n",SYSNETZWERK::NETNMeWaNe.c_str());
            wattr_on(VARSYSMAN::WPACONNECT.TMPWin1, COLOR_PAIR(62),nullptr);
            WPA_CONNECT::wlanstatus = VG1;
        }else{
            wprintw(VARSYSMAN::WPACONNECT.TMPWin1,"%s ist Beendet!\n",SYSNETZWERK::NETNMeWaNe.c_str());
        }
    }else if (strcmp(name.c_str(),"[ Verbinden  ]")==0){
        if(strcmp(WPA_CONNECT::wlanstatus.c_str(),"Disconnected! ")==0){
            wattr_on(VARSYSMAN::WPACONNECT.TMPWin1, COLOR_PAIR(63),nullptr);
            waddnstr(VARSYSMAN::WPACONNECT.TMPWin1,"Verbindung wird hergestellt!\n",-1);
            wattr_on(VARSYSMAN::WPACONNECT.TMPWin1, COLOR_PAIR(62),nullptr);
            string Wl8("wpa_cli reconnect");
            WPA_CONNECT::GetStdoutFromCommand(Wl8,0);
            WPA_CONNECT::wlanstatus = "Connected!    ";
        }else if(strcmp(WPA_CONNECT::wlanstatus.c_str(),"Connected!    ")==0){
            waddnstr(VARSYSMAN::WPACONNECT.TMPWin1,"Sie sind bereits Verbunden!\n",-1);
        }else{
            waddnstr(VARSYSMAN::WPACONNECT.TMPWin1,"WPA ist nicht ge?ffnet bitte Starten!\n",-1);
        }
    }else if (strcmp(name.c_str(),"[  Trennen   ]")==0){
        if(strcmp(WPA_CONNECT::wlanstatus.c_str(),"Connected!    ")==0){
            wattr_on(VARSYSMAN::WPACONNECT.TMPWin1, COLOR_PAIR(63), nullptr);
            waddnstr(VARSYSMAN::WPACONNECT.TMPWin1,"Verbindung wird getrennt!\n",-1);
            wattr_on(VARSYSMAN::WPACONNECT.TMPWin1, COLOR_PAIR(62), nullptr);
            string Wl9("wpa_cli disconnect");
            WPA_CONNECT::GetStdoutFromCommand(Wl9,0);
            WPA_CONNECT::wlanstatus = "Disconnected! ";
        }else if(strcmp(WPA_CONNECT::wlanstatus.c_str(),"Disconnected! ")==0){
            waddnstr(VARSYSMAN::WPACONNECT.TMPWin1,"Verbindung ist bereits getrennt!\n",-1);
        }else{
            waddnstr(VARSYSMAN::WPACONNECT.TMPWin1,"WPA Verbindung ist nicht ge?ffnet!\n",-1);
        }
    }else if (strcmp(name.c_str(),"[   Status   ]")==0){
        if(strcmp(WPA_CONNECT::wlanstatus.c_str(),VG1.c_str())==0){
            waddnstr(VARSYSMAN::WPACONNECT.TMPWin1,"WPA nicht Aktiv bitte Starten!\n",-1);
        }else{
            string Wl10("wpa_cli status");
            WPA_CONNECT::GetStdoutFromCommand(Wl10,0);
        }
    }else if (strcmp(name.c_str(),"[ Scan WLAN  ]")==0){
        if(strcmp(WPA_CONNECT::wlanstatus.c_str(),VG1.c_str())==0){
            waddnstr(VARSYSMAN::WPACONNECT.TMPWin1,"WPA nicht Aktiv bitte Starten!\n",-1);
        }else{
            string Wl11("wpa_cli scan");
            string Wl12("wpa_cli scan_results");
            WPA_CONNECT::GetStdoutFromCommand(Wl11,0);
            WPA_CONNECT::GetStdoutFromCommand(Wl12,0);
        }
    }else if (strcmp(name.c_str(),"[  WPA INST  ]")==0){
        string Wl14("apt-get -y install wpasupplicant wireless-tools wicd-curses");
        WPA_CONNECT::GetStdoutFromCommand(Wl14,0);
    }else if (strcmp(name.c_str(),"[ WPA DELETE ]")==0){
        string Wl14("apt-get -y purge wpasupplicant wireless-tools wicd-curses");
        WPA_CONNECT::GetStdoutFromCommand(Wl14,0);
    }else if (strcmp(name.c_str(),"[ Wlan IFace ]")==0){
        WPA_CONNECT::Wlan_Iface();
        wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::WPACONNECT.TMPWin1));
    }else if (strcmp(name.c_str(),"first check")==0){
        string Wl14("wpa_cli status | grep wpa_state=");
        WPA_CONNECT::GetStdoutFromCommand(Wl14,1);
    }else{
        waddnstr(VARSYSMAN::WPACONNECT.TMPWin1,"fehler keine option gewaehlt\n",-1);
    }
    touchwin(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
    wattr_on(VARSYSMAN::WPACONNECT.TMPWin2, COLOR_PAIR(62)|WA_BOLD,nullptr);
    mvwaddstr(VARSYSMAN::WPACONNECT.TMPWin2,0,STARTSYSMAN::max_xc-25,WPA_CONNECT::wlanstatus.c_str());
    wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::WPACONNECT.TMPWin2));
    wattr_off(VARSYSMAN::WPACONNECT.TMPWin2, COLOR_PAIR(62)|WA_BOLD,nullptr);
    prefresh(VARSYSMAN::clearwindow(VARSYSMAN::WPACONNECT.TMPWin1), 0, 0, 8, 1, STARTSYSMAN::max_yr -1, STARTSYSMAN::max_xc -1);
}

void WPA_CONNECT::Connection(void)
{
    WPA_CONNECT::fensterdesign();
    WPA_CONNECT::Wlan_button();
    keypad(STARTSYSMAN::START.TMPWin3, true);
    WPA_CONNECT::BefZusa("first check");
    int c1;
    refresh();
    wrefresh(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
    touchwin(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
    wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::WPACONNECT.TMPWin2));
    prefresh(VARSYSMAN::clearwindow(VARSYSMAN::WPACONNECT.TMPWin1), 0, 0, 8, 1, STARTSYSMAN::max_yr -1, STARTSYSMAN::max_xc -1);

    while ((c1= getch()) != KEY_F(10))
    {
        switch (c1)
        {
        case KEY_DOWN:
        {
            menu_driver(VARSYSMAN::WPACONNECT.TMPMenu1, REQ_DOWN_ITEM);
            break;
        }
        case KEY_UP:
        {
            menu_driver(VARSYSMAN::WPACONNECT.TMPMenu1, REQ_UP_ITEM);
            break;
        }
        case KEY_LEFT:
        {
            menu_driver(VARSYSMAN::WPACONNECT.TMPMenu1, REQ_LEFT_ITEM);
            break;
        }
        case KEY_RIGHT:
        {
            menu_driver(VARSYSMAN::WPACONNECT.TMPMenu1, REQ_RIGHT_ITEM);
            break;
        }
        case 0x0A:
        {
            werase(VARSYSMAN::WPACONNECT.TMPWin1);
            WPA_CONNECT::BefZusa(item_name(current_item(VARSYSMAN::WPACONNECT.TMPMenu1)));
            break;
        }

        }
        wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::WPACONNECT.TMPWin2));
        wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::WPACONNECT.TMPWin1));
        //        prefresh(VARSYSMAN::WPACONNECT.TMPWin1, 0, 0, 8, 1, STARTSYSMAN::max_yr -1, STARTSYSMAN::max_xc -1);
    }
WPA_CONNECT::QuitWPACon();
}

void WPA_CONNECT::QuitWPACon(){
    int e,i;

    e = item_count(VARSYSMAN::WPACONNECT.TMPMenu1);
    unpost_menu(VARSYSMAN::WPACONNECT.TMPMenu1);
    for(i=0; i<=e-1; i++) {
        free_item(VARSYSMAN::WPACONNECT.TMPItem1[i]);
    }
    free_menu(VARSYSMAN::WPACONNECT.TMPMenu1);
    delwin(VARSYSMAN::WPACONNECT.TMPWin1);
    delwin(VARSYSMAN::WPACONNECT.TMPWin2);
    endwin();

    refresh();
}
