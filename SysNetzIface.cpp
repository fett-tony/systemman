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

VARSYSMAN::FENSTERNETZIFACE VARSYSMAN::NETZIFACE;
static unsigned long maxlen = 0;
std::vector<std::string::size_type> SYSNETZIFACE::finden;

//static struct iw_statistics *stats;

int SYSNETZIFACE::getSignalInfo(signalInfo *sigInfo, char *iwname){
    iwreq req;
    strcpy(req.ifr_name, iwname);

    //iw_statistics *stats;
    //have to use a socket for ioctl
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    //make room for the iw_statistics object
    req.u.data.pointer = reinterpret_cast<iw_statistics *>(malloc(sizeof(iw_statistics)));
    req.u.data.length = sizeof(iw_statistics);
    req.u.data.flags = 1;
    
    //this will gather the signal strength
    if(ioctl(sockfd, SIOCGIWSTATS, &req) == -1){
        //die with error, invalid interface
        fprintf(stderr, "Invalid interface.\n");
        return(-1);
    }
    else if((reinterpret_cast<iw_statistics *>(req.u.data.pointer))->qual.updated & IW_QUAL_DBM){
        //signal is measured in dBm and is valid for us to use
        sigInfo->level=(reinterpret_cast<iw_statistics *>(req.u.data.pointer))->qual.level - 256;
    }

    //SIOCGIWESSID for ssid
    char buffer[32];
    memset(buffer, 0, 32);
    req.u.essid.pointer = buffer;
    req.u.essid.length = 32;
    //this will gather the SSID of the connected network
    if(ioctl(sockfd, SIOCGIWESSID, &req) == -1){
        //die with error, invalid interface
        return(-1);
    }
    else{
        memcpy(&sigInfo->ssid, req.u.essid.pointer, req.u.essid.length);
        memset(&sigInfo->ssid[req.u.essid.length],0,1);
    }

    //SIOCGIWRATE for bits/sec (convert to mbit)
    int bitrate=-1;
    //this will get the bitrate of the link
    if(ioctl(sockfd, SIOCGIWRATE, &req) == -1){
        fprintf(stderr, "bitratefail");
        return(-1);
    }else{
        memcpy(&bitrate, &req.u.bitrate, sizeof(int));
        sigInfo->bitrate=bitrate/1000000;
    }

    //SIOCGIFHWADDR for mac addr
    ifreq req2;
    strcpy(req2.ifr_name, iwname);
    //this will get the mac address of the interface
    if(ioctl(sockfd, SIOCGIFHWADDR, &req2) == -1){
        fprintf(stderr, "mac error");
        return(-1);
    }
    else{
        sprintf(sigInfo->mac, "%.2X", static_cast<unsigned char>(req2.ifr_hwaddr.sa_data[0]));
        for(int s=1; s<6; s++){
            sprintf(sigInfo->mac+strlen(sigInfo->mac), ":%.2X", static_cast<unsigned char>(req2.ifr_hwaddr.sa_data[s]));
        }
    }
    close(sockfd);
    return 0;
}

void SYSNETZIFACE::FensterDesign(void)
{
    VARSYSMAN::NETZIFACE.FEID = 6;
    VARSYSMAN::NETZIFACE.FENAME = string("Netzwerk");
    STARTSYSMAN::START.TMPWin3 = VARSYSMAN::DelTmpWin(STARTSYSMAN::START.TMPWin3);
    delwin(STARTSYSMAN::START.TMPWin3);
    STARTSYSMAN::START.TMPWin3 = newwin(STARTSYSMAN::max_yr-2, STARTSYSMAN::max_xc, 2, 0); //-23
    wbkgd(STARTSYSMAN::START.TMPWin3,COLOR_PAIR(61));
    box(STARTSYSMAN::START.TMPWin3, 0, 0);
    mvwhline(STARTSYSMAN::START.TMPWin3, 4, 1, ACS_HLINE, STARTSYSMAN::max_xc-2);
    mvwvline(STARTSYSMAN::START.TMPWin3, 4, STARTSYSMAN::max_xc-1, ACS_RTEE,1);
    mvwvline(STARTSYSMAN::START.TMPWin3, 4, 0, ACS_LTEE,1);
    VARSYSMAN::NETZIFACE.TMPWin1 = newwin( 3, STARTSYSMAN::max_xc-2, 3, 1); //-23
    wbkgd(VARSYSMAN::NETZIFACE.TMPWin1,COLOR_PAIR(61));
    scrollok(VARSYSMAN::NETZIFACE.TMPWin1, true);
    scroll(VARSYSMAN::NETZIFACE.TMPWin1);
    idlok(VARSYSMAN::NETZIFACE.TMPWin1, true);
    VARSYSMAN::NETZIFACE.TMPWin3 = newpad(STARTSYSMAN::max_yr-8,STARTSYSMAN::max_xc-2);
    wbkgd(VARSYSMAN::NETZIFACE.TMPWin3,COLOR_PAIR(61));
}

void SYSNETZIFACE::Menu_Ausfuehren(string Button, int Button_ID){
    string ausfuehren;

    if ((strcmp(Button.c_str(),"[   Speichern   ]") == 0) || (Button_ID == 0)){
        //string test = (string)item_name(current_item(VARSYSMAN::NETZIFACE.TMPMenu));
        //SYSNETZWERK::VendorDevice();
    } else if ((strcmp(Button.c_str(),"[    Abbruch    ]") == 0) || (Button_ID == 1)){

    } else if ((strcmp(Button.c_str(),"[ Netz Neustart ]") == 0) || (Button_ID == 2)){
        string instapp = "service networking restart";
        ausfuehren = VARSYSMAN::TERM_AUSGABE(instapp);
    } else if ((strcmp(Button.c_str(),"[ Netzwerk Stop ]") == 0) || (Button_ID == 3)){
        string instapp = "service networking stop";
        ausfuehren = VARSYSMAN::TERM_AUSGABE(instapp);
    } else if ((strcmp(Button.c_str(),"[   IFace Up    ]") == 0) || (Button_ID == 4)){
        string instapp = "ip link set dev eth0 up";
        ausfuehren = VARSYSMAN::TERM_AUSGABE(instapp);
    } else if ((strcmp(Button.c_str(),"[   IFace Down  ]") == 0) || (Button_ID == 5)){
        string instapp = "ip link set dev eth0 down";
        ausfuehren = VARSYSMAN::TERM_AUSGABE(instapp);
    }else{

    }
}

void SYSNETZIFACE::Einstellung_IF_Menu(void)
{   VARSYSMAN::NETZIFACE.TMPWin4 = newpad(3,37); //-23
    wbkgd(VARSYSMAN::NETZIFACE.TMPWin4,COLOR_PAIR(VARSYSMAN::IlMeFe_HG));
    VARSYSMAN::NETZIFACE.TMPItem2 = static_cast<ITEM **>(calloc(7, sizeof(ITEM *)));
    VARSYSMAN::NETZIFACE.TMPItem2[0] = new_item("[   Speichern   ]","");
    VARSYSMAN::NETZIFACE.TMPItem2[1] = new_item("[    Abbruch    ]","");
    VARSYSMAN::NETZIFACE.TMPItem2[2] = new_item("[ Netz Neustart ]","");
    VARSYSMAN::NETZIFACE.TMPItem2[3] = new_item("[ Netzwerk Stop ]","");
    VARSYSMAN::NETZIFACE.TMPItem2[4] = new_item("[   IFace Up    ]","");
    VARSYSMAN::NETZIFACE.TMPItem2[5] = new_item("[  IFace Down   ]","");
    VARSYSMAN::NETZIFACE.TMPItem2[6] = nullptr;
    VARSYSMAN::NETZIFACE.TMPMenu2 = new_menu(VARSYSMAN::NETZIFACE.TMPItem2);
    set_menu_win (VARSYSMAN::NETZIFACE.TMPMenu2, VARSYSMAN::NETZIFACE.TMPWin4);
    set_menu_sub (VARSYSMAN::NETZIFACE.TMPMenu2, derwin(VARSYSMAN::NETZIFACE.TMPWin4, 3, 37, STARTSYSMAN::max_yr - 1, 34));// STARTSYSMAN::max_xc-45));
    set_menu_spacing(VARSYSMAN::NETZIFACE.TMPMenu2, 1, 1, 1);
    set_menu_format(VARSYSMAN::NETZIFACE.TMPMenu2, 3, 2);
    set_menu_mark(VARSYSMAN::NETZIFACE.TMPMenu2, "");
    set_menu_pad(VARSYSMAN::NETZIFACE.TMPMenu2, 1);
    menu_opts_off(VARSYSMAN::NETZIFACE.TMPMenu2, O_NONCYCLIC);
    menu_opts_off(VARSYSMAN::NETZIFACE.TMPMenu2, O_SHOWDESC);
    set_menu_fore(VARSYSMAN::NETZIFACE.TMPMenu2, COLOR_PAIR(VARSYSMAN::IlMe_FG)|A_BOLD);
    set_menu_back(VARSYSMAN::NETZIFACE.TMPMenu2, COLOR_PAIR(VARSYSMAN::IlMe_HG)|A_BOLD);
    set_menu_grey(VARSYSMAN::NETZIFACE.TMPMenu2, COLOR_PAIR(VARSYSMAN::IlMe_grey)|A_BOLD);
    post_menu(VARSYSMAN::NETZIFACE.TMPMenu2);
}

void SYSNETZIFACE::Netzwerk_IF_Menu(void)
{
    //int Y=0;
    int X=0;
    int mrows, mcols;
    VARSYSMAN::NETZIFACE.TMPItem1 = static_cast<ITEM **>(calloc(static_cast<unsigned long>(SYSNETZWERK::maxIface+2), sizeof(ITEM *)));
    while (X!=(SYSNETZWERK::maxIface+1)){
        if (maxlen < static_cast<unsigned long>(VARSYSMAN::NETZWERK_IF[X].IF_Name[0].length())){
            maxlen = static_cast<unsigned long>(VARSYSMAN::NETZWERK_IF[X].IF_Name[0].length());
        }
        VARSYSMAN::NETZIFACE.TMPItem1[X] = new_item(VARSYSMAN::NETZWERK_IF[X].IF_Name[0].c_str()
                                              ,VARSYSMAN::NETZWERK_IF[X].IF_DeviceName.c_str());
        X++;
    }
    maxlen = maxlen + SYSNETZWERK::maxIfaceL;
    VARSYSMAN::NETZIFACE.TMPItem1[SYSNETZWERK::maxIface+1] = nullptr;
    VARSYSMAN::NETZIFACE.TMPMenu1 = new_menu(VARSYSMAN::NETZIFACE.TMPItem1);
    scale_menu(VARSYSMAN::NETZIFACE.TMPMenu1, &mrows, &mcols);
    set_menu_win(VARSYSMAN::NETZIFACE.TMPMenu1, VARSYSMAN::NETZIFACE.TMPWin1);
    set_menu_sub (VARSYSMAN::NETZIFACE.TMPMenu1, derwin(VARSYSMAN::NETZIFACE.TMPWin1, 3, STARTSYSMAN::max_xc-4, 1, STARTSYSMAN::max_xc-2));
    set_menu_spacing(VARSYSMAN::NETZIFACE.TMPMenu1, 0, 0, 0);
    set_menu_format(VARSYSMAN::NETZIFACE.TMPMenu1, 3, 1);
    set_menu_mark(VARSYSMAN::NETZIFACE.TMPMenu1, ">");
    set_menu_pad(VARSYSMAN::NETZIFACE.TMPMenu1, 1);
    menu_opts_on(VARSYSMAN::NETZIFACE.TMPMenu1, O_ONEVALUE);
    menu_opts_on(VARSYSMAN::NETZIFACE.TMPMenu1, O_SHOWDESC);
    set_menu_fore(VARSYSMAN::NETZIFACE.TMPMenu1, COLOR_PAIR(61)|A_BOLD|A_REVERSE);
    set_menu_back(VARSYSMAN::NETZIFACE.TMPMenu1, COLOR_PAIR(61)|A_BOLD);
    post_menu(VARSYSMAN::NETZIFACE.TMPMenu1);
} /* System Untermenü NETZWERK */

void SYSNETZIFACE::Netz_einstellung()
{
    int frow,fcol;
    VARSYSMAN::NETZIFACE.TMPField1 = static_cast<FIELD **>(calloc(15, sizeof(FIELD *)));
    VARSYSMAN::NETZIFACE.TMPField1[0] = new_field(1, 17, 5, 12, 0, 0); //ip
    VARSYSMAN::NETZIFACE.TMPField1[1] = new_field(1, 17, 6, 12, 0, 0); //Network
    VARSYSMAN::NETZIFACE.TMPField1[2] = new_field(1, 17, 7, 12, 0, 0); //Gateway
    VARSYSMAN::NETZIFACE.TMPField1[3] = new_field(1, 17, 8, 12, 0, 0); //Netmask
    VARSYSMAN::NETZIFACE.TMPField1[4] = new_field(1, 17, 9, 12, 0, 0); //Broadcast
    VARSYSMAN::NETZIFACE.TMPField1[5] = new_field(1, 17, 10, 12, 0, 0); //dns-search
    VARSYSMAN::NETZIFACE.TMPField1[6] = new_field(3, 17, 11, 12, 0, 0); //dns-name
    VARSYSMAN::NETZIFACE.TMPField1[7] = new_field(1, 35, 0, 42, 0, 0); //mac
    VARSYSMAN::NETZIFACE.TMPField1[8] = new_field(1, 17, 14, 12, 0, 0); //name
    VARSYSMAN::NETZIFACE.TMPField1[9] = new_field(1, 17, 15, 12, 0, 0); //driver
    VARSYSMAN::NETZIFACE.TMPField1[10] = new_field(3, 35, 1, 42, 0, 0); //hersteller
    VARSYSMAN::NETZIFACE.TMPField1[11] = new_field(1, 47, 5, 30, 0, 0); //IPv6
    VARSYSMAN::NETZIFACE.TMPField1[12] = new_field(1, 35, 6, 42, 0, 0); //WPA-driver
    VARSYSMAN::NETZIFACE.TMPField1[13] = new_field(2, 47, 8, 30, 0, 0); //WPA-confdatei
    VARSYSMAN::NETZIFACE.TMPField1[14] = nullptr;
    VARSYSMAN::NETZIFACE.TMPForm1 = new_form(VARSYSMAN::NETZIFACE.TMPField1);
    scale_form(VARSYSMAN::NETZIFACE.TMPForm1,&frow,&fcol);

    for (int i = 0; i < field_count( VARSYSMAN::NETZIFACE.TMPForm1 ); i++){
        set_field_fore( VARSYSMAN::NETZIFACE.TMPField1[i], COLOR_PAIR(71)|A_BOLD);
        set_field_back( VARSYSMAN::NETZIFACE.TMPField1[i], COLOR_PAIR(72));//|A_BOLD); //|A_REVERSE
        field_opts_on( VARSYSMAN::NETZIFACE.TMPField1[i], O_VISIBLE);
        if ((i == 7) || (i == 8) || (i == 9) || (i == 10)){
            set_field_fore( VARSYSMAN::NETZIFACE.TMPField1[i], COLOR_PAIR(72)|A_BOLD);
            field_opts_off( VARSYSMAN::NETZIFACE.TMPField1[i], O_EDIT);
            field_opts_off( VARSYSMAN::NETZIFACE.TMPField1[i], O_ACTIVE);
        }else{
            field_opts_on( VARSYSMAN::NETZIFACE.TMPField1[i], O_EDIT);
            field_opts_on( VARSYSMAN::NETZIFACE.TMPField1[i], O_ACTIVE);
        }
        field_opts_on( VARSYSMAN::NETZIFACE.TMPField1[i], O_SELECTABLE);
        set_field_just( VARSYSMAN::NETZIFACE.TMPField1[i], JUSTIFY_CENTER);
    }
    set_field_just( VARSYSMAN::NETZIFACE.TMPField1[13], JUSTIFY_CENTER);
    field_opts_on( VARSYSMAN::NETZIFACE.TMPField1[13], O_WRAP);
    set_field_just( VARSYSMAN::NETZIFACE.TMPField1[11], JUSTIFY_CENTER);
    field_opts_on( VARSYSMAN::NETZIFACE.TMPField1[11], O_WRAP);
    set_field_just( VARSYSMAN::NETZIFACE.TMPField1[8], JUSTIFY_CENTER);
    field_opts_on( VARSYSMAN::NETZIFACE.TMPField1[8], O_WRAP);

    set_form_win(VARSYSMAN::NETZIFACE.TMPForm1, VARSYSMAN::NETZIFACE.TMPWin3);
    set_form_sub(VARSYSMAN::NETZIFACE.TMPForm1, VARSYSMAN::NETZIFACE.TMPWin3);
    //set_form_sub(VARSYSMAN::NETZIFACE.TMPForm1, derwin(VARSYSMAN::NETZIFACE.TMPWin3,STARTSYSMAN::max_yr-8,STARTSYSMAN::max_xc-2,0,0));
    post_form(VARSYSMAN::NETZIFACE.TMPForm1);

    //###############################################
    int mrows, mcols;
    VARSYSMAN::NETZIFACE.TMPItem3 = static_cast<ITEM **>(calloc(3, sizeof(ITEM *)));
    VARSYSMAN::NETZIFACE.TMPItem3[0] = new_item("DHCP            ","dhcp");
    VARSYSMAN::NETZIFACE.TMPItem3[1] = new_item("Static          ","static");
    VARSYSMAN::NETZIFACE.TMPItem3[2] = nullptr;
    item_opts_on(VARSYSMAN::NETZIFACE.TMPItem3[0], O_SELECTABLE);
    item_opts_on(VARSYSMAN::NETZIFACE.TMPItem3[1], O_SELECTABLE);
    VARSYSMAN::NETZIFACE.TMPMenu3 = new_menu(VARSYSMAN::NETZIFACE.TMPItem3);
    scale_menu(VARSYSMAN::NETZIFACE.TMPMenu3, &mrows, &mcols);
    set_menu_win(VARSYSMAN::NETZIFACE.TMPMenu3, VARSYSMAN::NETZIFACE.TMPWin3);
    set_menu_sub (VARSYSMAN::NETZIFACE.TMPMenu3, derwin(VARSYSMAN::NETZIFACE.TMPWin3, 2, 17, 0, 12));
    set_menu_spacing(VARSYSMAN::NETZIFACE.TMPMenu3, 0, 0, 1);
    set_menu_format(VARSYSMAN::NETZIFACE.TMPMenu3, 3, 1);
    set_menu_mark(VARSYSMAN::NETZIFACE.TMPMenu3, "->");
    menu_opts_on(VARSYSMAN::NETZIFACE.TMPMenu3, O_ONEVALUE);
    menu_opts_off(VARSYSMAN::NETZIFACE.TMPMenu3, O_SHOWDESC);
    set_menu_fore(VARSYSMAN::NETZIFACE.TMPMenu3, COLOR_PAIR(72)|A_BOLD); //|A_REVERSE
    set_menu_back(VARSYSMAN::NETZIFACE.TMPMenu3, COLOR_PAIR(71));//|A_BOLD);
    set_menu_grey(VARSYSMAN::NETZIFACE.TMPMenu3, COLOR_PAIR(53));//|A_BOLD);
    post_menu(VARSYSMAN::NETZIFACE.TMPMenu3);
    //################################################
    int mrows2, mcols2;
    VARSYSMAN::NETZIFACE.TMPItem4 = static_cast<ITEM **>(calloc(4, sizeof(ITEM *)));
    VARSYSMAN::NETZIFACE.TMPItem4[0] = new_item("allow-hotplug   ","allow-hotplug");
    VARSYSMAN::NETZIFACE.TMPItem4[1] = new_item("auto            ","auto");
    VARSYSMAN::NETZIFACE.TMPItem4[2] = new_item("manual          ","manual");
    VARSYSMAN::NETZIFACE.TMPItem4[3] = nullptr;
    item_opts_on(VARSYSMAN::NETZIFACE.TMPItem4[0], O_SELECTABLE);
    item_opts_on(VARSYSMAN::NETZIFACE.TMPItem4[1], O_SELECTABLE);
    item_opts_on(VARSYSMAN::NETZIFACE.TMPItem4[2], O_SELECTABLE);
    VARSYSMAN::NETZIFACE.TMPMenu4 = new_menu(VARSYSMAN::NETZIFACE.TMPItem4);
    scale_menu(VARSYSMAN::NETZIFACE.TMPMenu4, &mrows2, &mcols2);
    set_menu_win(VARSYSMAN::NETZIFACE.TMPMenu4, VARSYSMAN::NETZIFACE.TMPWin3);
    set_menu_sub (VARSYSMAN::NETZIFACE.TMPMenu4, derwin(VARSYSMAN::NETZIFACE.TMPWin3, 3, 17, 2, 12));
    set_menu_spacing(VARSYSMAN::NETZIFACE.TMPMenu4, 0, 0, 0);
    set_menu_format(VARSYSMAN::NETZIFACE.TMPMenu4, 4, 1);
    set_menu_mark(VARSYSMAN::NETZIFACE.TMPMenu4, "->");
    //set_menu_pattern(VARSYSMAN::NETZIFACE.TMPMenu4, "X");
    menu_opts_on(VARSYSMAN::NETZIFACE.TMPMenu4, O_ONEVALUE);
    menu_opts_off(VARSYSMAN::NETZIFACE.TMPMenu4, O_SHOWDESC);
    set_menu_fore(VARSYSMAN::NETZIFACE.TMPMenu4, COLOR_PAIR(72)|A_BOLD);//|A_REVERSE
    set_menu_back(VARSYSMAN::NETZIFACE.TMPMenu4, COLOR_PAIR(71));//|A_BOLD);
    set_menu_grey(VARSYSMAN::NETZIFACE.TMPMenu4, COLOR_PAIR(53));//|A_BOLD);
    post_menu(VARSYSMAN::NETZIFACE.TMPMenu4);
    //################################################

    wattr_on(VARSYSMAN::NETZIFACE.TMPWin3, COLOR_PAIR(61)|WA_BOLD,nullptr);
    mvwaddstr(VARSYSMAN::NETZIFACE.TMPWin3, 0, 0, "Method:     ");
    mvwaddstr(VARSYSMAN::NETZIFACE.TMPWin3, 2, 0, "Class:      ");
    mvwaddstr(VARSYSMAN::NETZIFACE.TMPWin3, 5, 0, "IPv4:       ");
    mvwaddstr(VARSYSMAN::NETZIFACE.TMPWin3, 6, 0, "Network:    ");
    mvwaddstr(VARSYSMAN::NETZIFACE.TMPWin3, 7, 0, "Gateway:    ");
    mvwaddstr(VARSYSMAN::NETZIFACE.TMPWin3, 8, 0, "Netmask:    ");
    mvwaddstr(VARSYSMAN::NETZIFACE.TMPWin3, 9, 0, "Broadcast:  ");
    mvwaddstr(VARSYSMAN::NETZIFACE.TMPWin3, 10, 0,"DNS Search: ");
    mvwaddstr(VARSYSMAN::NETZIFACE.TMPWin3, 11, 0,"DNS Server: "); //11
    mvwaddstr(VARSYSMAN::NETZIFACE.TMPWin3, 0, 30,"MAC Adresse:"); //12
    mvwaddstr(VARSYSMAN::NETZIFACE.TMPWin3, 14, 0,"Interface:  ");
    mvwaddstr(VARSYSMAN::NETZIFACE.TMPWin3, 15, 0,"Treiber:    ");
    mvwaddstr(VARSYSMAN::NETZIFACE.TMPWin3, 1, 30,"Hersteller: ");
    mvwaddstr(VARSYSMAN::NETZIFACE.TMPWin3, 4, 30,"IPv6:       ");
    mvwaddstr(VARSYSMAN::NETZIFACE.TMPWin3, 6, 30,"WPA-driver: ");
    mvwaddstr(VARSYSMAN::NETZIFACE.TMPWin3, 7, 30,"WPA-Config: ");
    wattr_off(VARSYSMAN::NETZIFACE.TMPWin3, COLOR_PAIR(61)|WA_BOLD,nullptr);

    set_field_just( VARSYSMAN::NETZIFACE.TMPField1[1], JUSTIFY_CENTER);
    SYSNETZIFACE::Einstellung_IF_Menu();
    SYSNETZIFACE::next_Iface();
}

void SYSNETZIFACE::next_Iface(){
    for (int Z = 0;Z<=SYSNETZWERK::maxIface;Z++){
        if(VARSYSMAN::NETZWERK_IF[Z].IF_Name[0] == item_name(current_item(VARSYSMAN::NETZIFACE.TMPMenu1))){
            string NewName = VARSYSMAN::NETZWERK_IF[Z].IF_VendorName;
            NewName.append(" ");
            NewName.append(VARSYSMAN::NETZWERK_IF[Z].IF_DeviceName);
            set_field_buffer(VARSYSMAN::NETZIFACE.TMPField1[0], 0, VARSYSMAN::NETZWERK_IF[Z].IF_IPv4[0].c_str());
            set_field_buffer(VARSYSMAN::NETZIFACE.TMPField1[1], 0, VARSYSMAN::NETZWERK_IF[Z].IF_NETWORK[0].c_str());
            set_field_buffer(VARSYSMAN::NETZIFACE.TMPField1[2], 0, VARSYSMAN::NETZWERK_IF[Z].GW_IPv4[0].c_str());
            set_field_buffer(VARSYSMAN::NETZIFACE.TMPField1[3], 0, VARSYSMAN::NETZWERK_IF[Z].IF_NETMASK[0].c_str());
            set_field_buffer(VARSYSMAN::NETZIFACE.TMPField1[4], 0, VARSYSMAN::NETZWERK_IF[Z].IF_BROADCAST[0].c_str());
            set_field_buffer(VARSYSMAN::NETZIFACE.TMPField1[5], 0, VARSYSMAN::NETZWERK_IF[Z].DNS_SEARCH[0].c_str());
            set_field_buffer(VARSYSMAN::NETZIFACE.TMPField1[6], 0, VARSYSMAN::NETZWERK_IF[Z].DNS_NAMESERVERS[0].c_str());
            set_field_buffer(VARSYSMAN::NETZIFACE.TMPField1[7], 0, VARSYSMAN::NETZWERK_IF[Z].IF_MAC.c_str());
            set_field_buffer(VARSYSMAN::NETZIFACE.TMPField1[8], 0, VARSYSMAN::NETZWERK_IF[Z].IF_Name[0].c_str());
            set_field_buffer(VARSYSMAN::NETZIFACE.TMPField1[9], 0, VARSYSMAN::NETZWERK_IF[Z].IF_DRIVER.c_str());
            set_field_buffer(VARSYSMAN::NETZIFACE.TMPField1[10], 0, NewName.c_str());
            set_field_buffer(VARSYSMAN::NETZIFACE.TMPField1[11], 0, VARSYSMAN::NETZWERK_IF[Z].IF_IPv6[0].c_str());
            set_field_buffer(VARSYSMAN::NETZIFACE.TMPField1[12], 0, VARSYSMAN::NETZWERK_IF[Z].IF_WPA_Driver[0].c_str());
            set_field_buffer(VARSYSMAN::NETZIFACE.TMPField1[13], 0, VARSYSMAN::NETZWERK_IF[Z].IF_WPA_CONF[0].c_str());

            if (VARSYSMAN::NETZWERK_IF[Z].IF_CLASS.compare("auto")==0){
                set_current_item(VARSYSMAN::NETZIFACE.TMPMenu4,VARSYSMAN::NETZIFACE.TMPItem4[1]);
            }else if(VARSYSMAN::NETZWERK_IF[Z].IF_CLASS.compare("allow-hotplug")==0){
                set_current_item(VARSYSMAN::NETZIFACE.TMPMenu4,VARSYSMAN::NETZIFACE.TMPItem4[0]);
            }else if(VARSYSMAN::NETZWERK_IF[Z].IF_CLASS.compare("manual")==0){
                set_current_item(VARSYSMAN::NETZIFACE.TMPMenu4,VARSYSMAN::NETZIFACE.TMPItem4[2]);
            }
            if (VARSYSMAN::NETZWERK_IF[Z].IF_MODE.compare("dhcp")==0){
                set_current_item(VARSYSMAN::NETZIFACE.TMPMenu3,VARSYSMAN::NETZIFACE.TMPItem3[0]);
            }else if(VARSYSMAN::NETZWERK_IF[Z].IF_MODE.compare("static")==0){
                set_current_item(VARSYSMAN::NETZIFACE.TMPMenu3,VARSYSMAN::NETZIFACE.TMPItem3[1]);
            }
        }
    }
}

void SYSNETZIFACE::NETZ_KEY_PAD()
{
    int c;
    int tabspace = 1;
    keypad(stdscr,true);

    SYSNETZIFACE::Netz_einstellung();

    refresh();
    touchwin(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
    wrefresh(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
    wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::NETZIFACE.TMPWin1));
    prefresh(VARSYSMAN::clearwindow(VARSYSMAN::NETZIFACE.TMPWin3), 0, 0, 7, 1, STARTSYSMAN::max_yr,STARTSYSMAN::max_xc-1);
    prefresh(VARSYSMAN::clearwindow(VARSYSMAN::NETZIFACE.TMPWin4), 0, 0, 20,39,22,79);//STARTSYSMAN::max_yr-4, 35, STARTSYSMAN::max_yr-1,STARTSYSMAN::max_xc-1);

    while ((c = getch()) != KEY_F(10)){
        switch(tabspace){
        case 1:{
            switch (c) {
            case KEY_UP:
                menu_driver(VARSYSMAN::NETZIFACE.TMPMenu1, REQ_UP_ITEM);
                //tab = VARSYSMAN::zahlenwerk(1,"++",5);
                SYSNETZIFACE::next_Iface();
                break;
            case KEY_DOWN:
                menu_driver(VARSYSMAN::NETZIFACE.TMPMenu1, REQ_DOWN_ITEM);
                //tab = VARSYSMAN::zahlenwerk(1,"++",5);
                SYSNETZIFACE::next_Iface();
                break;
            case 0x09: //strg+y
                tabspace = VARSYSMAN::zahlenwerk(1,"++",5);
                break;
            case KEY_BTAB: //strg+x
                tabspace = VARSYSMAN::zahlenwerk(1,"--",5);
                break;
            case 0x0A:
                tabspace = VARSYSMAN::zahlenwerk(1,"++",5);
                SYSNETZIFACE::next_Iface();
                //SYSNETZIFACE::NETZ_KEY_PAD();
                break;
            }
            break;
        }
        case 2:{
            switch (c) {
            case KEY_UP:
                menu_driver(VARSYSMAN::NETZIFACE.TMPMenu3, REQ_UP_ITEM);
                break;
            case KEY_DOWN:
                menu_driver(VARSYSMAN::NETZIFACE.TMPMenu3, REQ_DOWN_ITEM);
                break;
            case 0x20: //Leertasten
                menu_driver(VARSYSMAN::NETZIFACE.TMPMenu3, REQ_TOGGLE_ITEM);
                break;
            case 0x09: //strg+y
                tabspace = VARSYSMAN::zahlenwerk(2,"++",5);
                break;
            case KEY_BTAB: //strg+x
                tabspace = VARSYSMAN::zahlenwerk(2,"--",5);
                break;
            }
            break;
        }
        case 3:{
            switch (c) {
            case KEY_UP:
                menu_driver(VARSYSMAN::NETZIFACE.TMPMenu4, REQ_UP_ITEM);
                break;
            case KEY_DOWN:
                menu_driver(VARSYSMAN::NETZIFACE.TMPMenu4, REQ_DOWN_ITEM);
                break;
            case 0x20: //Leertasten
                menu_driver(VARSYSMAN::NETZIFACE.TMPMenu4, REQ_TOGGLE_ITEM);
                break;
            case 0x09: //strg+y
                tabspace = VARSYSMAN::zahlenwerk(3,"++",5);
                break;
            case KEY_BTAB: //strg+x
                tabspace = VARSYSMAN::zahlenwerk(3,"--",5);
                break;
            }
            break;
        }
        case 4:{
            switch (c) {
            case KEY_NPAGE:
                form_driver(VARSYSMAN::NETZIFACE.TMPForm1, REQ_FIRST_FIELD);
                break;
            case KEY_PPAGE:
                form_driver(VARSYSMAN::NETZIFACE.TMPForm1, REQ_LAST_FIELD);
                break;
                // Delete the char before cursor
            case KEY_BACKSPACE:
            case 127:
                form_driver(VARSYSMAN::NETZIFACE.TMPForm1, REQ_DEL_PREV);
                break;
                // Delete the char under the cursor
            case KEY_DC:
                form_driver(VARSYSMAN::NETZIFACE.TMPForm1, REQ_DEL_CHAR);
                break;
                //case KEY_DOWN:
            case 0x09: //strg+y
                if(field_index(current_field(VARSYSMAN::NETZIFACE.TMPForm1))==(field_count(VARSYSMAN::NETZIFACE.TMPForm1)-1)){
                    tabspace = VARSYSMAN::zahlenwerk(4,"++",5);
                }else{
                    form_driver(VARSYSMAN::NETZIFACE.TMPForm1, REQ_NEXT_FIELD);
                }
                break;
                //case KEY_UP:
            case KEY_BTAB: //strg+x
                if(field_index(current_field(VARSYSMAN::NETZIFACE.TMPForm1))==0){
                    tabspace = VARSYSMAN::zahlenwerk(4,"--",5);
                }else{
                    form_driver(VARSYSMAN::NETZIFACE.TMPForm1, REQ_PREV_FIELD);
                }
                break;
            default:
                form_driver(VARSYSMAN::NETZIFACE.TMPForm1, c);
                break;
            }
            break;
        }
        case 5:{
            switch (c) {
            case KEY_UP:
                menu_driver(VARSYSMAN::NETZIFACE.TMPMenu2, REQ_UP_ITEM);
                break;
            case KEY_DOWN:
                menu_driver(VARSYSMAN::NETZIFACE.TMPMenu2, REQ_DOWN_ITEM);
                break;
            case KEY_LEFT:
                menu_driver(VARSYSMAN::NETZIFACE.TMPMenu2, REQ_LEFT_ITEM);
                break;
            case KEY_RIGHT:
                menu_driver(VARSYSMAN::NETZIFACE.TMPMenu2, REQ_RIGHT_ITEM);
                break;
            case 0x09: //strg+y
                tabspace = VARSYSMAN::zahlenwerk(5,"++",5);
                break;
            case KEY_BTAB: //strg+x
                tabspace = VARSYSMAN::zahlenwerk(5,"--",5);
                break;
            case 10:
                SYSNETZIFACE::Menu_Ausfuehren(item_name(current_item(VARSYSMAN::NETZIFACE.TMPMenu2)),
                                             item_index(current_item(VARSYSMAN::NETZIFACE.TMPMenu2)));
            }
            break;
        }
        }
        wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::NETZIFACE.TMPWin1));
        prefresh(VARSYSMAN::clearwindow(VARSYSMAN::NETZIFACE.TMPWin3), 0, 0, 7, 1, STARTSYSMAN::max_yr,STARTSYSMAN::max_xc-1);
        prefresh(VARSYSMAN::clearwindow(VARSYSMAN::NETZIFACE.TMPWin4), 0, 0, 20,39,22,79);//STARTSYSMAN::max_yr-4, 35, STARTSYSMAN::max_yr-1,STARTSYSMAN::max_xc-1);
    }
}

void SYSNETZIFACE::InterfacesIfaceNr()
{
    int lineNr = 0;
    string Lesen;

    for (int Q = 0; Q <= SYSNETZWERK::maxIface; Q++)
    {
        lineNr = 0;
        ifstream filestream(VARSYSMAN::ConfigDateiList[0].c_str());
        string IFacesearch = " ";
        IFacesearch.append(VARSYSMAN::NETZWERK_IF[Q].IF_Name[0]);
        if (filestream.is_open())
        {
            while (getline(filestream,Lesen))
            {
                lineNr++;
                std::string::size_type found = Lesen.find(IFacesearch);
                if(found!=std::string::npos){
                    VARSYSMAN::NETZWERK_IF[Q].IF_Name[1] = std::to_string(lineNr);
                    break;
                }
            }
        }else {
            cout << "File opening is fail."<<endl;
        }
        filestream.close();
    }
    SYSNETZIFACE::InterfacesDatei();
}

void SYSNETZIFACE::InterfacesDatei()
{
    int lineNr = 0;
    string Lesen;
    string NextLesen;
    for (int Q = 0; Q <= SYSNETZWERK::maxIface; Q++)
    {
        lineNr = 0;
        ifstream filestream(VARSYSMAN::ConfigDateiList[0].c_str());
        if (filestream.is_open())
        {
            while (getline(filestream,Lesen))
            {
                lineNr++;
                std::string::size_type Ffail = Lesen.find("#");
                NextLesen = VARSYSMAN::Datei_Zeile_Nr(VARSYSMAN::ConfigDateiList[0],lineNr+1);
                std::string::size_type NFIFname = NextLesen.find(VARSYSMAN::NETZWERK_IF[Q].IF_Name[0]);
                std::string::size_type NFauto = NextLesen.find("auto");
                std::string::size_type NFallow_hotplug = NextLesen.find("allow-hotplug");
                std::string::size_type NFmanual = NextLesen.find("manual");
                std::string::size_type NFLoopback = NextLesen.find("loopback");
                std::string::size_type NFdhcp = NextLesen.find("dhcp");
                std::string::size_type NFstatic = NextLesen.find("static");

                if(lineNr >= std::stoi(VARSYSMAN::NETZWERK_IF[Q].IF_Name[1]) &&
                        Ffail == std::string::npos &&
                        Lesen.empty() == false)
                {
                    unsigned long LesenLeange = Lesen.length();
                    std::string::size_type FIFname = Lesen.find(VARSYSMAN::NETZWERK_IF[Q].IF_Name[0]);
                    std::string::size_type Fauto = Lesen.find("auto");
                    std::string::size_type Fallow_hotplug = Lesen.find("allow-hotplug");
                    std::string::size_type Fmanual = Lesen.find("manual");
                    std::string::size_type FLoopback = Lesen.find("loopback");
                    std::string::size_type Fdhcp = Lesen.find("dhcp");
                    std::string::size_type Fstatic = Lesen.find("static");

                    std::string::size_type Faddr = Lesen.find("address"); //8
                    std::string::size_type Fmask = Lesen.find("netmask"); //8
                    std::string::size_type Fgw = Lesen.find("gateway"); //8
                    std::string::size_type Fnetw = Lesen.find("network"); //8
                    std::string::size_type Fbroc = Lesen.find("broadcast"); //10
                    std::string::size_type Fdnsn = Lesen.find("dns-nameservers"); //17
                    std::string::size_type Fdnss = Lesen.find("dns-search"); //11
                    std::string::size_type Fwpad = Lesen.find("wpa-driver"); //11
                    std::string::size_type Fwpaconf = Lesen.find("wpa-conf"); //9

                    if (FIFname != std::string::npos && (Fauto != std::string::npos || Fallow_hotplug != std::string::npos ||
                             Fmanual != std::string::npos || FLoopback != std::string::npos || Fdhcp != std::string::npos ||
                             Fstatic != std::string::npos))
                    {
                        if(Fauto != std::string::npos &&
                                Fallow_hotplug == std::string::npos &&
                                Fmanual == std::string::npos){
                            VARSYSMAN::NETZWERK_IF[Q].IF_CLASS = "auto";
                        }else if(Fauto == std::string::npos &&
                                 Fallow_hotplug != std::string::npos &&
                                 Fmanual == std::string::npos){
                            VARSYSMAN::NETZWERK_IF[Q].IF_CLASS = "allow-hotplug";
                        }else if(Fauto == std::string::npos &&
                                 Fallow_hotplug == std::string::npos &&
                                 Fmanual != std::string::npos){
                            VARSYSMAN::NETZWERK_IF[Q].IF_CLASS = "manual";
                        }else if(Fauto == std::string::npos &&
                                 Fallow_hotplug == std::string::npos &&
                                 Fmanual == std::string::npos){
                            if(FLoopback != std::string::npos &&
                                    Fdhcp == std::string::npos &&
                                    Fstatic == std::string::npos){
                                VARSYSMAN::NETZWERK_IF[Q].IF_MODE = Lesen.substr(LesenLeange-8,LesenLeange);
                            }else if(FLoopback == std::string::npos &&
                                     Fdhcp != std::string::npos &&
                                     Fstatic == std::string::npos){
                                VARSYSMAN::NETZWERK_IF[Q].IF_MODE = Lesen.substr(LesenLeange-4,LesenLeange);
                            }else if(FLoopback == std::string::npos &&
                                     Fdhcp == std::string::npos &&
                                     Fstatic != std::string::npos){
                                VARSYSMAN::NETZWERK_IF[Q].IF_MODE = Lesen.substr(LesenLeange-6,LesenLeange);
                            }
                        }
                    }else if(Faddr != std::string::npos || Fmask != std::string::npos ||
                              Fgw != std::string::npos || Fnetw != std::string::npos || Fbroc != std::string::npos ||
                              Fdnsn != std::string::npos || Fdnss != std::string::npos || Fwpad != std::string::npos ||
                              Fwpaconf != std::string::npos){
                        if(Faddr != std::string::npos){
                            VARSYSMAN::NETZWERK_IF[Q].IF_IPv4[0] = Lesen.substr(Faddr+8,LesenLeange);
                            VARSYSMAN::NETZWERK_IF[Q].IF_IPv4[1] = std::to_string(lineNr);
                            VARSYSMAN::NETZWERK_IF[Q].IF_IPv4[3] = std::to_string(Faddr+8);
                        }else if(Fmask != std::string::npos){
                            VARSYSMAN::NETZWERK_IF[Q].IF_NETMASK[0] = Lesen.substr(Fmask+8,LesenLeange);
                            VARSYSMAN::NETZWERK_IF[Q].IF_NETMASK[1] = std::to_string(lineNr);
                            VARSYSMAN::NETZWERK_IF[Q].IF_NETMASK[3] = std::to_string(Fmask+8);
                        }else if(Fgw != std::string::npos){
                            VARSYSMAN::NETZWERK_IF[Q].GW_IPv4[0] = Lesen.substr(Fgw+8,LesenLeange);
                            VARSYSMAN::NETZWERK_IF[Q].GW_IPv4[1] = std::to_string(lineNr);
                            VARSYSMAN::NETZWERK_IF[Q].GW_IPv4[3] = std::to_string(Fgw+8);
                        }else if(Fnetw != std::string::npos){
                            VARSYSMAN::NETZWERK_IF[Q].IF_NETWORK[0] = Lesen.substr(Fnetw+8,LesenLeange);
                            VARSYSMAN::NETZWERK_IF[Q].IF_NETWORK[1] = std::to_string(lineNr);
                            VARSYSMAN::NETZWERK_IF[Q].IF_NETWORK[3] = std::to_string(Fnetw+8);
                        }else if(Fbroc != std::string::npos){
                            VARSYSMAN::NETZWERK_IF[Q].IF_BROADCAST[0] = Lesen.substr(Fbroc+10,LesenLeange);
                            VARSYSMAN::NETZWERK_IF[Q].IF_BROADCAST[1] = std::to_string(lineNr);
                            VARSYSMAN::NETZWERK_IF[Q].IF_BROADCAST[3] = std::to_string(Fbroc+10);
                        }else if(Fdnsn != std::string::npos){
                            VARSYSMAN::NETZWERK_IF[Q].DNS_NAMESERVERS[0] = Lesen.substr(Fdnsn+16,LesenLeange);
                            VARSYSMAN::NETZWERK_IF[Q].DNS_NAMESERVERS[1] = std::to_string(lineNr);
                            VARSYSMAN::NETZWERK_IF[Q].DNS_NAMESERVERS[3] = std::to_string(Fdnsn+16);
                        }else if(Fdnss != std::string::npos){
                            VARSYSMAN::NETZWERK_IF[Q].DNS_SEARCH[0] = Lesen.substr(Fdnss+11,LesenLeange);
                            VARSYSMAN::NETZWERK_IF[Q].DNS_SEARCH[1] = std::to_string(lineNr);
                            VARSYSMAN::NETZWERK_IF[Q].DNS_SEARCH[3] = std::to_string(Fdnss+11);
                        }else if(Fwpad != std::string::npos){
                            VARSYSMAN::NETZWERK_IF[Q].IF_WPA_Driver[0] = Lesen.substr(Fwpad+11,LesenLeange);
                            VARSYSMAN::NETZWERK_IF[Q].IF_WPA_Driver[1] = std::to_string(lineNr);
                            VARSYSMAN::NETZWERK_IF[Q].IF_WPA_Driver[2] = std::to_string(Fwpad+11);
                        }else if(Fwpaconf != std::string::npos){
                            VARSYSMAN::NETZWERK_IF[Q].IF_WPA_CONF[0] = Lesen.substr(Fwpaconf+9,LesenLeange);
                            VARSYSMAN::NETZWERK_IF[Q].IF_WPA_CONF[1] = std::to_string(lineNr);
                            VARSYSMAN::NETZWERK_IF[Q].IF_WPA_CONF[2] = std::to_string(Fwpaconf+9);
                        }
                    }
                }else if(lineNr >= std::stoi(VARSYSMAN::NETZWERK_IF[Q].IF_Name[1]) && Ffail == std::string::npos &&
                         Lesen.empty() == true && NFIFname == std::string::npos && (NFauto!=std::string::npos ||
                          NFallow_hotplug!=std::string::npos || NFmanual!=std::string::npos || NFLoopback!=std::string::npos ||
                          NFdhcp!=std::string::npos || NFstatic!=std::string::npos)){
                    break;
                }
            }
        }else{
            cout << "File opening is fail."<<endl;
        }
        filestream.close();
    }
}

void SYSNETZIFACE::SYSNETZIFACE_START()
{
    SYSNETZIFACE::FensterDesign();
    SYSNETZIFACE::InterfacesIfaceNr();
    SYSNETZIFACE::Netzwerk_IF_Menu();
    SYSNETZIFACE::NETZ_KEY_PAD();
}
