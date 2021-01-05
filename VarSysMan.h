#ifndef VARSYSMAN_H
#define VARSYSMAN_H

#include <ncursesw/cursesapp.h>
#include <ncursesw/ncurses.h>
#include <ncursesw/menu.h>
#include <ncursesw/form.h>
#include <ncursesw/panel.h>
#include <ncursesw/unctrl.h>
//#include <ncurses.h>
//#include <menu.h>
//#include <form.h>
//#include <panel.h>
//#include <unctrl.h>
//#include <sys/pci.h>
#include <sys/dir.h>
#include <sys/select.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <net/if.h>
#include <netinet/ether.h>
#include <netinet/in.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <arpa/inet.h>
#include <arpa/nameser.h>
#include <resolv.h>
#include <linux/sockios.h>
//#include <linux/if_arp.h>
#include <linux/netlink.h>
#include <linux/wireless.h>
#include <linux/route.h> 
#include <linux/rtnetlink.h>
#include <linux/if.h>
#include <linux/ethtool.h>
#include <asm/types.h>
#include <dirent.h>
#include <exception>
#include <utility>
#include <locale.h>
//#include <csignal>
#include <signal.h>
#include <iostream>
#include <sstream>
#include <cstring>
#include <string>
#include <stdio.h>
#include <cstdlib>
#include <unistd.h>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <vector>
#include <pthread.h>
#include <termios.h>
#include <term.h>
#include <fcntl.h>
#include <ctype.h> 
#include <stdnoreturn.h>
#include <set>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include <memory>
#include <yaml-cpp/yaml.h>

#define BUFSIZE 8192

//#if defined POSIX
#define CLEARSCR system ( "clear" )
//#elif defined MSDOS || defined WIN32
//#define CLEARSCR system ( "cls" )
//#endif
//#ifndef SAFE_DELETE
#define SAFE_DELETE(p) { if(p) { delete (p); (p) = nullptr; } }
//#endif
//#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p); (p) = nullptr; } }
//#endif

#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define CTRLD 	4
#define SIZEOF(table) (sizeof(table) / sizeof(table[0]))

using namespace std;

#pragma pack(push,1)

struct NETZ_IF
{
    string  IF_Name[3];
    string  IF_Typ;
    string  IF_MAC;
    string  IF_IPv4[4];
    string  IF_IPv6[4]{""};
    string  IF_NETMASK[4]{""};
    string  GW_IPv4[4]{""};
    string  IF_BROADCAST[4]{""};
    string  IF_NETWORK[4]{""};
    string  DNS_SEARCH[4]{""};
    string  DNS_NAMESERVERS[4]{""};
    string  IF_MTU{""};
    string  IF_DRIVER{""};
    string  IF_VendorID{""};
    string  IF_VendorName{""};
    string  IF_DeviceID{""};
    string  IF_DeviceName{""};
    string  IF_CLASS{""};
    string  IF_MODE{""};
    string  IF_WPA_Driver[3]{""};
    string  IF_WPA_CONF[3]{""};
    int     IF_ID;
};
struct GW_ROUTE
{
    string GW_IPv4{""};
    string GW_IPv6{""};
    string GW_NAME{""};
    string IF_NAME{""};
    int GW_ID;
};
class VARSYSMAN
{
public:
    struct FENSTERBEFEHLE
    {
        int FEID;
        string FENAME{""};
        WINDOW *TMPWin1{nullptr};
        WINDOW *TMPWin2{nullptr};
        WINDOW *TMPWin3{nullptr};
        int TMPWinHigh{0};
        MENU *TMPMenu1{nullptr};
        ITEM **TMPItem1{nullptr};
        FORM *TMPForm{nullptr};
        FIELD **TMPField{nullptr};
    };                             //-----Fenster Befehle-----------
    static VARSYSMAN::FENSTERBEFEHLE BEFEHLE;              //-----Fenster Befehle-----------
    struct FENSTERMANPAGE
    {
        int FEID{0};
        string FENAME{""};
        WINDOW *TMPWin1{nullptr};
        WINDOW *TMPWin2{nullptr};
        int TMPWinHigh{0};
        MENU *TMPMenu1{nullptr};
        ITEM **TMPItem1{nullptr};
    };                             //-----Fenster ManPage-----------
    static VARSYSMAN::FENSTERMANPAGE MANPAGE;              //-----Fenster ManPage-----------
    struct FENSTERAKSOFT
    {
        int FEID{0};
        string FENAME{""};
        WINDOW *TMPWin1{nullptr};
        WINDOW *TMPWin2{nullptr};
        WINDOW *TMPWin3{nullptr};
        int TMPWinHigh{0};
        MENU *TMPMenu1{nullptr};
        ITEM **TMPItem1{nullptr};
        MENU *TMPMenu2{nullptr};
        ITEM **TMPItem2{nullptr};
    };                             //-----AK install Software-------
    static VARSYSMAN::FENSTERAKSOFT AKSOFT;                //-----AK install Software-------
    struct FENSTERDATEIRECHTE
    {
        int FEID{0};
        string FENAME{""};
        WINDOW *TMPWin1{nullptr};
        WINDOW *TMPWin2{nullptr};
        WINDOW *TMPWin3{nullptr};
        WINDOW *TMPWin4{nullptr};
        int TMPWinHigh{0};
        MENU *TMPMenu1{nullptr};
        ITEM **TMPItem1{nullptr};
        FORM *TMPForm{nullptr};
        FIELD **TMPField{nullptr};
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
    };                             //-----Dateirechte Speichern-----
    static VARSYSMAN::FENSTERDATEIRECHTE DATEIRECHTE;      //-----Dateirechte Speichern-----
    struct FENSTERNETZWERK
    {
        int FEID{0};
        string FENAME{""};
        WINDOW *TMPWin1{nullptr};
        WINDOW *TMPWin2{nullptr};
        MENU *TMPMenu1{nullptr};
        ITEM **TMPItem1{nullptr};
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
    };                             //-----Netzwerk Fenster----------
    static VARSYSMAN::FENSTERNETZWERK NETZWERK;            //-----Netzwerk Fenster----------
    struct FENSTERNETZIFACE
    {
        int FEID{0};
        string FENAME{""};
        WINDOW *TMPWin1{nullptr};
        WINDOW *TMPWin2{nullptr};
        WINDOW *TMPWin3{nullptr};
        WINDOW *TMPWin4{nullptr};
        int TMPWinHigh{0};
        MENU *TMPMenu1{nullptr};
        ITEM **TMPItem1{nullptr};
        MENU *TMPMenu2{nullptr};
        ITEM **TMPItem2{nullptr};
        MENU *TMPMenu3{nullptr};//Me_Method
        ITEM **TMPItem3{nullptr};//It_Method
        MENU *TMPMenu4{nullptr};//Me_net_class
        ITEM **TMPItem4{nullptr};//It_net_class
        FORM *TMPForm1{nullptr};//Fo_Net_config
        FIELD **TMPField1{nullptr};//Fi_Net_conf
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
    };                             //-----Netzwerk Interfaces-------
    static VARSYSMAN::FENSTERNETZIFACE NETZIFACE;          //-----Netzwerk Interfaces-------
    struct FENSTERNETZMENU
    {
        int FEID{0};
        string FENAME{""};
        WINDOW *TMPWin1{nullptr};
        WINDOW *TMPWin2{nullptr};
        WINDOW *TMPWin3{nullptr};
        int TMPWinHigh{0};
        MENU *TMPMenu1{nullptr};
        ITEM **TMPItem1{nullptr};
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
    };                             //-----Netzwerk Menu-------------
    static VARSYSMAN::FENSTERNETZMENU NETZMENU;            //-----Netzwerk Menu-------------
    struct FENSTERWPACONNECT
    {
        int FEID{0};
        string FENAME{""};
        WINDOW *TMPWin1{nullptr};
        WINDOW *TMPWin2{nullptr};
        int TMPWinHigh{0};
        MENU *TMPMenu1{nullptr};
        ITEM **TMPItem1{nullptr};
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
    };                             //-----Netzwerk WPA Connect------
    static VARSYSMAN::FENSTERWPACONNECT WPACONNECT;        //-----Netzwerk WPA Connect------
    struct FENSTERWLANSCAN
    {
        int FEID{0};
        string FENAME{""};
        WINDOW *TMPWin1{nullptr};
        WINDOW *TMPWin2{nullptr};
        WINDOW *TMPWin3{nullptr};
        int TMPWinHigh1{0};
        MENU *TMPMenu1{nullptr};
        ITEM **TMPItem1{nullptr};
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
    };                             //-----Netzwerk WLAN Scan--------
    static VARSYSMAN::FENSTERWLANSCAN WLANSCAN;            //-----Netzwerk WLAN Scan--------

    static string filename;
    //------------------------------------
    typedef struct
    {
        int min;
        int max;
        int count(){return max - min;}
        int range{1};
    } RANGE;
    static NETZ_IF NETZWERK_IF[10];
    static GW_ROUTE GATEWAY_IF[10];

    static int HaMeFe_HG, HaMe_FG, HaMe_HG, HaMe_grey, UMeFe_HG;
    static int IlMeFe_HG, IlMe_FG, IlMe_HG, IlMe_grey, IlUMeFe_HG;
    //static sig_atomic_t signaled;

    static time_t Zeitstempel;
    static tm *UHRZEIT;
    static char UHRZEITchar[19];
    static string UHRZEITstr;
    static struct sigaction sa;
    static struct itimerval timer;
    static void timer_handler (int); //int signum);
    static void *uhrzeit_anzeigen(void*);
    static void KEYCATCH_handler(void *); //int signum);
    static pthread_t Tzeit, KeyCat;
    static std::vector<std::string> ConfigDateiList;
    static int CountConfigDatei;
    //------------------------------------
    static WINDOW *clearwindow(WINDOW *W);
    static WINDOW *DelTmpWin(WINDOW *tmpw);
    static void termquit(int );
    static int Datei_Letzte_Line(string DateiName);
    static string Datei_Zeile_Nr(string Datei, int zeile);
    static void Folder(void);
    static bool DirectoryExists(const char* pzPath);
    static string IP_Uint_to_IP_String(unsigned long IP);
    static int zahlenwerk(int zahlen, string i, int max);
    static void find_and_replace(string& source, string const& find, string const& replace);
    static string TERM_AUSGABE(string cmd);
    static string exec(string cmd);
    static string ssystem(string cmd);
    static void test(void);
    static int ZahlenBerechnen(int posa, VARSYSMAN::RANGE range, string wahl);
    static int ZahlenWerk(int mina, int posa, int maxa, string wahl);
    static int kbhit(void);
    string MAC_Uchar_to_MAC_String(unsigned char IF_MAC_tmp[8]);

    ~VARSYSMAN();
private:
    static sig_atomic_t signaled;
protected:

};

#pragma pack(pop)

#endif // VARSYSMAN_H
