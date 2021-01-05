#include <VarSysMan.h>
#include <StartSysMan.h>
#include <DateiBefehle.h>
#include <DateiManPage.h>
#include <HMenu.h>
#include <SoftAKInst.h>
#include <SysDateiRechte.h>
#include <SysNetzwerk.h>
#include <SysNetzIface.h>
#include <SysNetzwerk.h>
#include <SysNetzWPACon.h>
#include <SysNetzWPAScan.h>
#include <test.h>

using namespace std;

VARSYSMAN::FENSTERNETZWERK VARSYSMAN::NETZWERK;

int SYSNETZWERK::maxIfaceL = 0;
int SYSNETZWERK::maxIface = 0;
int SYSNETZWERK::M = 0;
string SYSNETZWERK::NetIface[25];
string SYSNETZWERK::NETNMeWaNe;

static struct SYSNETZWERK::DNS_NASE
{
    int DNS_ID {0};
    string DNS_IP1 {""};
    string DNS_IP2 {""};
    string DNS_IP3 {""};
    string DNS_IP4 {""};
    string DNS_SEARCH {""};
    string IF_NAME {""};
} DNS_IF[10];

static struct SYSNETZWERK::HOSTS_NAME
{
    int HOST_ID {0};
    string HOST_NAME {""};
    string HOSTS_LIST {""};    /*Später mal als struct gedacht*/
} HST_NA[10];

static struct SYSNETZWERK::route_info {
    u_int dstAddr {0};
    u_int srcAddr {0};
    u_int gateWay {0};
    char ifName[IF_NAMESIZE] {""};
} *rtInfo;

void SYSNETZWERK::sys_netz1_fenster(void){
    STARTSYSMAN::START.TMPWin3 = VARSYSMAN::DelTmpWin(STARTSYSMAN::START.TMPWin3);
    delwin(STARTSYSMAN::START.TMPWin3);
    refresh();

    STARTSYSMAN::START.TMPWin3 = newwin(STARTSYSMAN::max_yr-2, STARTSYSMAN::max_xc, 2, 0); //-23
    wbkgd(STARTSYSMAN::START.TMPWin3,COLOR_PAIR(61));
    box(STARTSYSMAN::START.TMPWin3, 0, 0);
    mvwhline(STARTSYSMAN::START.TMPWin3, 4, 1, ACS_HLINE, STARTSYSMAN::max_xc-2);
    mvwvline(STARTSYSMAN::START.TMPWin3, 4, STARTSYSMAN::max_xc-1, ACS_RTEE,1);
    mvwvline(STARTSYSMAN::START.TMPWin3, 4, 0, ACS_LTEE,1);
    VARSYSMAN::NETZWERK.TMPWin1 = newwin(SYSNETZWERK::maxIface+1, STARTSYSMAN::max_xc-2, 3, 1);// SYSNETZWERK::maxIfaceL+1, 3, 1); //static_cast<int>
    wbkgd(VARSYSMAN::NETZWERK.TMPWin1, COLOR_PAIR(61));

    VARSYSMAN::NETZWERK.TMPWin2 = newpad(STARTSYSMAN::max_yr-8, STARTSYSMAN::max_xc-2); //-23
    wbkgd(VARSYSMAN::NETZWERK.TMPWin2, COLOR_PAIR(11));
    STARTSYSMAN::START.TMPWin3 = derwin(VARSYSMAN::NETZWERK.TMPWin2, STARTSYSMAN::max_yr-8, STARTSYSMAN::max_xc-2, 7, 1);
    wsetscrreg(VARSYSMAN::NETZWERK.TMPWin2, 0, STARTSYSMAN::max_yr -4);
    scrollok(VARSYSMAN::NETZWERK.TMPWin2, true);
    scroll(VARSYSMAN::NETZWERK.TMPWin2);
}

void SYSNETZWERK::IFACENAME(void)
{
    struct if_nameindex *if_ni, *i;
    if_ni = if_nameindex();
    int Y=0,X=0;
    if (if_ni == nullptr) {
        perror("if_nameindex");
        exit(EXIT_FAILURE);}

    for (i = if_ni; ! (i->if_index == 0 && i->if_name == nullptr); i++){
        SYSNETZWERK::NetIface[Y] = i->if_name;
        unsigned long TMPL = SYSNETZWERK::NetIface[Y].length();
        if ((SYSNETZWERK::maxIfaceL==0) || (SYSNETZWERK::maxIfaceL < static_cast<int>(TMPL))) {
            SYSNETZWERK::maxIfaceL = static_cast<int>(SYSNETZWERK::NetIface[Y].length());
        }
        Y++;
    }
    SYSNETZWERK::maxIface=Y-1;
    while (X!=(SYSNETZWERK::maxIface+1)){
        VARSYSMAN::NETZWERK_IF[X].IF_Name[0] = SYSNETZWERK::NetIface[X];
        VARSYSMAN::NETZWERK_IF[X].IF_ID = X;
        X++;
    }
    if_freenameindex(if_ni);
    SYSNETZWERK::Netz_Info();
}

void SYSNETZWERK::VendorDevice()
{
    string path = "/sys/class/net/";
    string Device = "/device/device";
    string Vendor = "/device/vendor";
    string Device2 = "/device/idProduct";
    string Vendor2 = "/device/idVendor";
    string Driver = "/device/uevent";
    string tmppath1;
    string tmppath2;
    string tmppath3;
    string tmppath4;
    string tmppath5;
    string tmppath6;
    string tmppath7;
    int IF_ID;

    string lesen;
    string delim = "x";
    string delim2 = "DRIVER=";
    string delim3 = "MODALIAS=";
    size_t strchk;

    for (int i = 0;i <= SYSNETZWERK::maxIface;i++)
    {
        IF_ID = i;
        tmppath1 = path;
        tmppath1.append(VARSYSMAN::NETZWERK_IF[i].IF_Name[0].c_str());
        if (VARSYSMAN::DirectoryExists(tmppath1.c_str()))
        {
            tmppath1.append(Vendor);
            tmppath2 = path;
            tmppath2.append(VARSYSMAN::NETZWERK_IF[i].IF_Name[0].c_str());
            tmppath2.append(Device);
            tmppath3 = path;
            tmppath3.append(VARSYSMAN::NETZWERK_IF[i].IF_Name[0].c_str());
            tmppath3.append(Driver);
            tmppath4 = path;
            tmppath4.append(VARSYSMAN::NETZWERK_IF[i].IF_Name[0].c_str());
            tmppath4.append(Driver);
            tmppath5 = path;
            tmppath5.append(VARSYSMAN::NETZWERK_IF[i].IF_Name[0].c_str());
            tmppath5.append(Driver);
            tmppath6 = path;
            tmppath6.append(VARSYSMAN::NETZWERK_IF[i].IF_Name[0].c_str());
            tmppath6.append(Vendor2);
            tmppath7 = path;
            tmppath7.append(VARSYSMAN::NETZWERK_IF[i].IF_Name[0].c_str());
            tmppath7.append(Device2);

            ifstream filestream1(tmppath1.c_str());
            ifstream filestream2(tmppath2.c_str());
            ifstream filestream3(tmppath3.c_str());
            ifstream filestream4(tmppath4.c_str());
            ifstream filestream5(tmppath5.c_str());
            ifstream filestream6(tmppath6.c_str());
            ifstream filestream7(tmppath7.c_str());

            if (filestream1.is_open() && filestream2.is_open()
                    && filestream3.is_open() && !filestream6.is_open()
                    && !filestream7.is_open())
            {
                while (getline(filestream1,lesen)) //(d<=54)
                {
                    streampos oldpos = filestream1.tellg();
                    strchk = size_t(lesen.find(delim));
                    if(strchk != std::string::npos){
                        filestream1.seekg (oldpos);
                        std::string token = lesen.substr(lesen.find(delim)+1,lesen.length()-1);
                        VARSYSMAN::NETZWERK_IF[i].IF_VendorID = token;
                    }else{
                        filestream1.seekg (oldpos);
                    }
                }
                strchk = 0;
                lesen = "";
                while (getline(filestream2,lesen))
                {
                    streampos oldpos = filestream2.tellg();
                    strchk = size_t(lesen.find(delim));
                    if(strchk != std::string::npos){
                        filestream2.seekg (oldpos);
                        std::string token = lesen.substr(lesen.find(delim)+1,lesen.length()-1);
                        VARSYSMAN::NETZWERK_IF[i].IF_DeviceID = token;
                    }else{
                        filestream2.seekg (oldpos);
                    }
                }
                unsigned long lenge;
                lesen = "";
                while (getline(filestream3,lesen))
                {
                    if(lesen.substr(0,7).compare(delim2.c_str()) == 0)// && lesen.at(7) == '=' )
                    {
                        lenge = lesen.length();
                        VARSYSMAN::NETZWERK_IF[i].IF_DRIVER = lesen.substr(7,lenge);
                    }
                }
                filestream1.close();
                filestream2.close();
                filestream3.close();

                SYSNETZWERK::NAMENsuche(IF_ID,1);
            }else if (!filestream1.is_open() && !filestream2.is_open()
                      && filestream3.is_open() && filestream6.is_open()
                      && filestream7.is_open()){
                while (getline(filestream6,lesen)) //(d<=54)
                {
                    unsigned long lenge = lesen.length();
                    VARSYSMAN::NETZWERK_IF[i].IF_VendorID = lesen.substr(0,lenge);
                }
                lesen = "";
                while (getline(filestream7,lesen))
                {
                    unsigned long lenge = lesen.length();
                    VARSYSMAN::NETZWERK_IF[i].IF_DeviceID = lesen.substr(0,lenge);
                }
                unsigned long lenge;
                lesen = "";
                while (getline(filestream3,lesen))
                {
                    if(lesen.substr(0,7).compare(delim2.c_str()) == 0)// && lesen.at(7) == '=' )
                    {
                        lenge = lesen.length();
                        VARSYSMAN::NETZWERK_IF[i].IF_DRIVER = lesen.substr(7,lenge);
                    }
                }
                filestream6.close();
                filestream7.close();

                SYSNETZWERK::NAMENsuche(IF_ID,2);
            }else if (!filestream1.is_open() && !filestream2.is_open()
                      && filestream3.is_open()){
                unsigned long lenge;
                lesen = "";
                if (filestream4.is_open()){
                    while (getline(filestream4, lesen))
                    {
                        if(lesen.substr(0,7).compare(delim2.c_str()) == 0) // && lesen.at(6) == '=' )
                        {
                            lenge = lesen.length();
                            VARSYSMAN::NETZWERK_IF[i].IF_DRIVER = lesen.substr(7,lenge);
                        }
                    }
                }
                lenge = 0;
                lesen = "";
                if (filestream5.is_open()){
                    lesen = "";
                    while (getline(filestream5, lesen))
                    {
                        if(lesen.substr(0,9).compare(delim3.c_str()) == 0)// && lesen.at(13) == 'v' )
                        {
                            lenge = lesen.length();
                            string Ve = lesen.substr(14,4).c_str();
                            string De = lesen.substr(19,4).c_str();
                            std::transform(Ve.begin(),Ve.end(),Ve.begin(),static_cast<int(*)(int)>(std::tolower));
                            std::transform(De.begin(),De.end(),De.begin(),static_cast<int(*)(int)>(std::tolower));
                            VARSYSMAN::NETZWERK_IF[i].IF_VendorID = Ve; //lesen.substr(14,4);
                            VARSYSMAN::NETZWERK_IF[i].IF_DeviceID = De; //lesen.substr(19,4);
                        }
                    }
                }
                SYSNETZWERK::NAMENsuche(IF_ID,2);
            }
            filestream4.close();
            filestream5.close();
        }
    }
}

void SYSNETZWERK::NAMENsuche(int ifid,int appid)
{
    string PCI_ID = "/usr/share/misc/pci.ids";
    string USB_ID = "/var/lib/usbutils/usb.ids";

    if (appid==1){
        ifstream filestream_pci(PCI_ID.c_str());
        string line_pci;
        string Kontrolle;

        if (strcmp(VARSYSMAN::NETZWERK_IF[ifid].IF_VendorID.c_str(),"")!=0)
        {
            while(std::getline(filestream_pci, line_pci))
            {
                if (strcmp(VARSYSMAN::NETZWERK_IF[ifid].IF_VendorName.c_str(),"")==0
                        && strcmp(VARSYSMAN::NETZWERK_IF[ifid].IF_DeviceName.c_str(),"")==0)
                {
                    if(line_pci.substr(0,4).compare(VARSYSMAN::NETZWERK_IF[ifid].IF_VendorID.c_str()) == 0
                            && line_pci.at(5) == ' ' )
                    {
                        unsigned long lenge = line_pci.length();
                        VARSYSMAN::NETZWERK_IF[ifid].IF_VendorName = line_pci.substr(6,lenge);
                        Kontrolle = line_pci.substr(6,lenge);
                    }
                }else if (strcmp(VARSYSMAN::NETZWERK_IF[ifid].IF_VendorName.c_str(),Kontrolle.c_str())==0
                          && strcmp(VARSYSMAN::NETZWERK_IF[ifid].IF_DeviceName.c_str(),"") == 0){
                    string puffer = "\t";
                    puffer.append(VARSYSMAN::NETZWERK_IF[ifid].IF_DeviceID.c_str());

                    if(line_pci.substr(0,5).compare(puffer.c_str()) == 0
                            && line_pci.at(6) == ' ' )
                    {
                        unsigned long lenge2 = line_pci.length();
                        VARSYSMAN::NETZWERK_IF[ifid].IF_DeviceName = line_pci.substr(7,lenge2);
                        break;
                    }
                }
            }
        }
        filestream_pci.close();

    }else if(appid==2){
        ifstream filestream_usb(USB_ID.c_str());
        string line_usb;
        string Kontrolle;

        if (strcmp(VARSYSMAN::NETZWERK_IF[ifid].IF_VendorID.c_str(),"")!=0)
        {
            while(std::getline(filestream_usb, line_usb))
            {
                if (strcmp(VARSYSMAN::NETZWERK_IF[ifid].IF_VendorName.c_str(),"")==0
                        && strcmp(VARSYSMAN::NETZWERK_IF[ifid].IF_DeviceName.c_str(),"")==0)
                {
                    if(line_usb.substr(0,4).compare(VARSYSMAN::NETZWERK_IF[ifid].IF_VendorID.c_str()) == 0
                            && line_usb.at(5) == ' ' )
                    {
                        unsigned long lenge = line_usb.length();
                        VARSYSMAN::NETZWERK_IF[ifid].IF_VendorName = line_usb.substr(6,lenge);
                        Kontrolle = line_usb.substr(6,lenge);
                    }
                }else if (strcmp(VARSYSMAN::NETZWERK_IF[ifid].IF_VendorName.c_str(),Kontrolle.c_str())==0
                          && strcmp(VARSYSMAN::NETZWERK_IF[ifid].IF_DeviceName.c_str(),"") == 0){
                    string puffer = "\t";
                    puffer.append(VARSYSMAN::NETZWERK_IF[ifid].IF_DeviceID.c_str());
                    if(line_usb.substr(0,5).compare(puffer.c_str()) == 0
                            && line_usb.at(6) == ' ' )
                    {
                        unsigned long lenge2 = line_usb.length();
                        VARSYSMAN::NETZWERK_IF[ifid].IF_DeviceName = line_usb.substr(7,lenge2);
                        break;
                    }
                }
            }
        }
        filestream_usb.close();
    }
}

void SYSNETZWERK::menu_ifaces(void)
{
    int X=0;
    VARSYSMAN::NETZWERK.TMPItem1 = static_cast<ITEM **>(calloc(static_cast<unsigned long>(SYSNETZWERK::maxIface), sizeof(ITEM *)));
    while (X!=(SYSNETZWERK::maxIface+1)){
        VARSYSMAN::NETZWERK.TMPItem1[X] = new_item(VARSYSMAN::NETZWERK_IF[X].IF_Name[0].c_str(),"");
        X++;
    }
    VARSYSMAN::NETZWERK.TMPItem1[SYSNETZWERK::maxIface+1] = nullptr;
    VARSYSMAN::NETZWERK.TMPMenu1 = new_menu(VARSYSMAN::NETZWERK.TMPItem1);
    set_menu_win(VARSYSMAN::NETZWERK.TMPMenu1, VARSYSMAN::NETZWERK.TMPWin1);
    set_menu_sub (VARSYSMAN::NETZWERK.TMPMenu1, derwin(VARSYSMAN::NETZWERK.TMPWin1, 3, 6, 3, 1));
    set_menu_spacing(VARSYSMAN::NETZWERK.TMPMenu1, 0, 0, 0);
    set_menu_format(VARSYSMAN::NETZWERK.TMPMenu1, 3, 1);
    set_menu_mark(VARSYSMAN::NETZWERK.TMPMenu1, ">");
    //set_menu_pad(VARSYSMAN::NETZWERK.TMPMenu1, 1);
    menu_opts_on(VARSYSMAN::NETZWERK.TMPMenu1, O_NONCYCLIC);
    menu_opts_off(VARSYSMAN::NETZWERK.TMPMenu1, O_SHOWDESC);
    set_menu_fore(VARSYSMAN::NETZWERK.TMPMenu1, COLOR_PAIR(61)|A_BOLD|A_REVERSE);
    set_menu_back(VARSYSMAN::NETZWERK.TMPMenu1, COLOR_PAIR(61)|A_BOLD);
    post_menu(VARSYSMAN::NETZWERK.TMPMenu1);
}

int SYSNETZWERK::NLsockLesen(int sockFd, char *bufPtr, int seqNum, int pId)
{
    struct nlmsghdr *nlHdr;
    int readLen = 0, msgLen = 0;
    do {
        /* Receive response from the kernel */
        if((readLen = recv(sockFd, bufPtr, BUFSIZE - msgLen, 0)) < 0)
        {
            perror("SOCK READ: ");
            return -1;
        }
        nlHdr = reinterpret_cast<nlmsghdr *>(bufPtr);
        /* Check if the header is valid */
        if((0 == NLMSG_OK(nlHdr, readLen)) || (NLMSG_ERROR == nlHdr->nlmsg_type))
        {
            perror("Error in received packet");
            return -1;
        }
        /* Check if it is the last message */
        if (NLMSG_DONE == nlHdr->nlmsg_type)
        {
            break;
        }
        /* Else move the pointer to buffer appropriately */
        bufPtr += readLen;
        msgLen += readLen;
        /* Check if its a multi part message; return if it is not. */
        if (0 == (nlHdr->nlmsg_flags & NLM_F_MULTI)) {
            break;
        }
    } while((nlHdr->nlmsg_seq != static_cast<unsigned int>(seqNum))
            || (nlHdr->nlmsg_pid != static_cast<unsigned int>(pId)));
    return msgLen;
}

void SYSNETZWERK::RoutingTable(struct route_info *rtInfo){
    mvwprintw(VARSYSMAN::NETZWERK.TMPWin2,1+SYSNETZWERK::M,0,
              "%s \n",string(rtInfo->dstAddr ? VARSYSMAN::IP_Uint_to_IP_String(static_cast<unsigned long>(rtInfo->dstAddr))
                                             : "0.0.0.0").c_str(),-1);
    mvwprintw(VARSYSMAN::NETZWERK.TMPWin2,1+SYSNETZWERK::M,15,
              "%s \n",string(rtInfo->gateWay ? VARSYSMAN::IP_Uint_to_IP_String(static_cast<unsigned long>(rtInfo->gateWay))
                                             : "0.0.0.0").c_str(),-1);
    mvwprintw(VARSYSMAN::NETZWERK.TMPWin2,1+SYSNETZWERK::M,30,
              "%s \n",string(rtInfo->ifName).c_str(),-1);
    mvwprintw(VARSYSMAN::NETZWERK.TMPWin2,1+SYSNETZWERK::M,40,
              "%s \n",string(rtInfo->srcAddr ? VARSYSMAN::IP_Uint_to_IP_String(static_cast<unsigned long>(rtInfo->srcAddr))
                                             : "0.0.0.0").c_str(),-1);
    SYSNETZWERK::M++;
}

void SYSNETZWERK::GatewayLesen(struct nlmsghdr *nlHdr, struct route_info *rtInfo)
{
    struct rtmsg *rtMsg;
    struct rtattr *rtAttr;
    int rtLen;
    char *tempBuf = nullptr;
    tempBuf = static_cast<char *>(malloc(100));
    rtMsg = reinterpret_cast<rtmsg *>(NLMSG_DATA(nlHdr));
    /* If the route is not for AF_INET or does not belong to main routing table then return. */
    if((rtMsg->rtm_family != AF_INET) || (rtMsg->rtm_table != RT_TABLE_MAIN))
        return;
    /* get the rtattr field */
    rtAttr = reinterpret_cast<rtattr *>(RTM_RTA(rtMsg));
    rtLen = static_cast<int>(RTM_PAYLOAD(nlHdr));
    int A = 0;
    for (; RTA_OK(rtAttr,rtLen); rtAttr = RTA_NEXT(rtAttr,rtLen)) {
        switch(rtAttr->rta_type) {
        case RTA_OIF:
            if_indextoname(*static_cast<unsigned int *>(RTA_DATA(rtAttr)), rtInfo->ifName);
            VARSYSMAN::GATEWAY_IF[A].IF_NAME = string(rtInfo->ifName);
            //wprintw(VARSYSMAN::NETZWERK.TMPWin2,"%s\n", VARSYSMAN::GATEWAY_IF[A].IF_NAME.c_str());
            VARSYSMAN::GATEWAY_IF[A].GW_ID=A;
            A++;
            break;
        case RTA_GATEWAY:
            rtInfo->gateWay = *static_cast<u_int *>(RTA_DATA(rtAttr));
            char tmp1[255];
            sprintf(tmp1,"%s",rtInfo->gateWay ? VARSYSMAN::IP_Uint_to_IP_String(
                             static_cast<unsigned long>(rtInfo->gateWay)).c_str()
                             : "0.0.0.0");
            VARSYSMAN::GATEWAY_IF[A].GW_IPv4 = string(tmp1);
            break;
        case RTA_PREFSRC:
            rtInfo->srcAddr = *static_cast<u_int *>(RTA_DATA(rtAttr));
            break;
        case RTA_DST:
            rtInfo->dstAddr = *static_cast<u_int *>(RTA_DATA(rtAttr));
            break;
        }
    }
    SYSNETZWERK::RoutingTable(rtInfo);
    free(tempBuf);
}

int SYSNETZWERK::Start_Route(){
    struct nlmsghdr *nlMsg;
    struct route_info *rtInfo;
    char msgBuf[BUFSIZE];
    int sock, msgSeq = 0;
    unsigned int len;
    /* Create Socket */
    if((sock = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_ROUTE)) < 0){}
    /* Initialize the buffer */
    memset(msgBuf, 0, BUFSIZE);
    /* point the header and the msg structure pointers into the buffer */
    //nlMsg = (struct nlmsghdr *)msgBuf;
    nlMsg = reinterpret_cast<nlmsghdr *>(msgBuf);
    /* Fill in the nlmsg header*/
    nlMsg->nlmsg_len = NLMSG_LENGTH(sizeof(struct rtmsg)); // Length of message.
    nlMsg->nlmsg_type = RTM_GETROUTE; // Get the routes from kernel routing table .
    nlMsg->nlmsg_flags = NLM_F_DUMP | NLM_F_REQUEST; // The message is a request for dump.
    nlMsg->nlmsg_seq = static_cast<unsigned int>(msgSeq++); // Sequence of the message packet.
    nlMsg->nlmsg_pid = static_cast<unsigned int>(getpid()); // PID of process sending the request.
    /* Send the request */

    if(send(sock, nlMsg, nlMsg->nlmsg_len, 0) < 0){
        wprintw(VARSYSMAN::NETZWERK.TMPWin2,"Write To Socket Failed...\n");
        return -1;
    }
    /* Read the response */
    if((len = NLsockLesen(sock, msgBuf, msgSeq, getpid())) < 0) {
        wprintw(VARSYSMAN::NETZWERK.TMPWin2,"Read From Socket Failed...\n");
        return -1;
    }
    /* Parse and print the response */
    rtInfo = reinterpret_cast<route_info *>(malloc(sizeof(struct route_info)));
    // ADDED BY BOB
    /* THIS IS THE NETTSTAT -RL code I commented out the printing here and in parse routes */
    mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,0,0,"Destination    Gateway        Interface Source\n",-1);
    for(;NLMSG_OK(nlMsg, len);nlMsg = NLMSG_NEXT(nlMsg,len)) {
        memset(rtInfo, 0, sizeof(struct route_info));
        GatewayLesen(nlMsg, rtInfo);
    }
    free(rtInfo);
    close(sock);
    return 0;
}

int SYSNETZWERK::check_wireless(const char* ifname, char* protocol) {
    int sock = -1;
    struct iwreq pwrq;
    memset(&pwrq, 0, sizeof(pwrq));
    strncpy(pwrq.ifr_name, ifname, IFNAMSIZ);
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return 0;}
    if (ioctl(sock, SIOCGIWNAME, &pwrq) != -1) {
        if (protocol) strncpy(protocol, pwrq.u.name, IFNAMSIZ);
        close(sock);
        return 1;}
    close(sock);
    return 0;
}

void SYSNETZWERK::Netz_Info_v6(int S){
    void *tmp6;
    struct ifaddrs *ifaddr=nullptr, *ifa=nullptr;
    getifaddrs(&ifaddr);
    for (ifa = ifaddr; ifa != nullptr; ifa = ifa->ifa_next){
        if(strcmp(ifa->ifa_name,VARSYSMAN::NETZWERK_IF[S].IF_Name[0].c_str())==0){
            if (!ifa->ifa_addr){continue;}
            if(ifa->ifa_addr->sa_family == AF_INET6){
                tmp6 = &(reinterpret_cast<sockaddr_in6 *>(ifa->ifa_addr))->sin6_addr;
                char addBuf6[INET6_ADDRSTRLEN];
                inet_ntop(AF_INET6, tmp6, addBuf6, INET6_ADDRSTRLEN);
                VARSYSMAN::NETZWERK_IF[S].IF_IPv6[0] = addBuf6;
            }
        }
    }
    if (ifaddr!=nullptr) freeifaddrs(ifaddr);
}

void SYSNETZWERK::Netz_Info()
{
    for (int X = 0;X<SYSNETZWERK::maxIface+1;X++){
        const char *ifname= VARSYSMAN::NETZWERK_IF[X].IF_Name[0].c_str();
        int sock;
        struct ifreq ifr;
        struct sockaddr_in *ipaddr;
        char address[INET_ADDRSTRLEN];
        size_t ifnamelen;
        /* -------------------copy ifname to ifr object */
        ifnamelen = strlen(ifname);
        if (ifnamelen >= sizeof(ifr.ifr_name)) {
        }
        memcpy(ifr.ifr_name, ifname, ifnamelen);
        ifr.ifr_name[ifnamelen] = '\0';
        /* -------------------open socket */
        sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_IP);
        if (sock < 0) {
        }
        /* -------------------process mac */
        if (ioctl(sock, SIOCGIFHWADDR, &ifr) != -1) {
            char cache_MAC [50];
            sprintf(cache_MAC,"%02X:%02X:%02X:%02X:%02X:%02X",
                    static_cast<unsigned char>(ifr.ifr_hwaddr.sa_data[0]),static_cast<unsigned char>(ifr.ifr_hwaddr.sa_data[1]),
                    static_cast<unsigned char>(ifr.ifr_hwaddr.sa_data[2]),static_cast<unsigned char>(ifr.ifr_hwaddr.sa_data[3]),
                    static_cast<unsigned char>(ifr.ifr_hwaddr.sa_data[4]),static_cast<unsigned char>(ifr.ifr_hwaddr.sa_data[5]));
            // string MAC_Formatiert = string(cache_MAC);
            VARSYSMAN::NETZWERK_IF[X].IF_MAC=string(cache_MAC);}
        /* ------------------process mtu */
        if (ioctl(sock, SIOCGIFMTU, &ifr) != -1) {
            stringstream convert;
            convert<<ifr.ifr_mtu;
            VARSYSMAN::NETZWERK_IF[X].IF_MTU = convert.str();}
        /* ------------------die if cannot get address */
        if (ioctl(sock, SIOCGIFADDR, &ifr) == -1) {
            close(sock);
        }
        /* ------------------process ip */
        ipaddr = reinterpret_cast<sockaddr_in *>(&ifr.ifr_addr);
        if (inet_ntop(AF_INET, &ipaddr->sin_addr, address, sizeof(address)) != nullptr) {
            VARSYSMAN::NETZWERK_IF[X].IF_IPv4[2] = address;
            char protocol[IFNAMSIZ] = {0};
            if (check_wireless(VARSYSMAN::NETZWERK_IF[X].IF_Name[0].c_str(), protocol)){
                VARSYSMAN::NETZWERK_IF[X].IF_Typ = "wireless";
            }else{
                VARSYSMAN::NETZWERK_IF[X].IF_Typ = "ethernet";}
        }
        /* ----------------try to get broadcast */
        if (ioctl(sock, SIOCGIFBRDADDR, &ifr) != -1) {
            ipaddr = reinterpret_cast<sockaddr_in *>(&ifr.ifr_broadaddr);
            if (inet_ntop(AF_INET, &ipaddr->sin_addr, address, sizeof(address)) != nullptr) {
                VARSYSMAN::NETZWERK_IF[X].IF_BROADCAST[2] = address;
            }
        }
        /* ----------------try to get mask */
        if (ioctl(sock, SIOCGIFNETMASK, &ifr) != -1) {
            ipaddr = reinterpret_cast<sockaddr_in *>(&ifr.ifr_netmask);
            if (inet_ntop(AF_INET, &ipaddr->sin_addr, address, sizeof(address)) != nullptr) {
                VARSYSMAN::NETZWERK_IF[X].IF_NETMASK[2] = address;}
        }
        /* -----------------Hostname ausgeben */
        char hostname[128];
        gethostname(hostname, sizeof hostname);
        HST_NA[0].HOST_NAME=string(hostname);
        HST_NA[0].HOST_ID=1;
        //wprintw(WinPadN2,"My hostname: %s\n", hostname);
        close(sock);
        Netz_Info_v6(X);
        for (int Q = 0; Q < 4; Q++){
            if (strcmp(VARSYSMAN::NETZWERK_IF[X].IF_Name[0].c_str(), VARSYSMAN::GATEWAY_IF[Q].IF_NAME.c_str())==0){
                VARSYSMAN::NETZWERK_IF[X].GW_IPv4[2] = VARSYSMAN::GATEWAY_IF[Q].GW_IPv4.c_str();
            }
        }
    }
    SYSNETZWERK::VendorDevice();
}

void SYSNETZWERK::Netz_Conf_Anzeigen(string ifname){
    werase(VARSYSMAN::NETZWERK.TMPWin2);
    for (int X=0;X<(SYSNETZWERK::maxIface+1);X++){
        if (VARSYSMAN::NETZWERK_IF[X].IF_Name[0]==ifname){
            wattrset(VARSYSMAN::NETZWERK.TMPWin2,A_BOLD | COLOR_PAIR(11));
            wprintw(VARSYSMAN::NETZWERK.TMPWin2,"ID: %d", VARSYSMAN::NETZWERK_IF[X].IF_ID);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,0,8,"Name:",-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,0,14,VARSYSMAN::NETZWERK_IF[X].IF_Name[0].c_str(),-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,0,20,"Typ:",-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,0,26,VARSYSMAN::NETZWERK_IF[X].IF_Typ.c_str(),-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,3,0,"IP v 4: ",-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,4,0,"Netzmaske: ",-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,5,0,"Gateway: ",-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,6,0,"Broadcast: ",-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,7,0,"NETWORK: ",-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,8,0,"Nameserver: ",-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,9,0,"DNS-Search: ",-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,10,0,"IP v 6: ",-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,11,0,"MAC Adresse: ",-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,12,0,"Treiber Name: ",-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,13,0,"Geraet: ",-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,14,0,"WPA-Config: ",-1);

            wattrset(VARSYSMAN::NETZWERK.TMPWin2,A_BOLD | COLOR_PAIR(12));
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,1,15,"Aktuell:",-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,3,15,VARSYSMAN::NETZWERK_IF[X].IF_IPv4[2].c_str(),-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,4,15,VARSYSMAN::NETZWERK_IF[X].IF_NETMASK[2].c_str(),-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,5,15,VARSYSMAN::NETZWERK_IF[X].GW_IPv4[2].c_str(),-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,6,15,VARSYSMAN::NETZWERK_IF[X].IF_BROADCAST[2].c_str(),-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,7,15,VARSYSMAN::NETZWERK_IF[X].IF_NETWORK[2].c_str(),-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,8,15,VARSYSMAN::NETZWERK_IF[X].DNS_NAMESERVERS[2].c_str(),-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,9,15,VARSYSMAN::NETZWERK_IF[X].DNS_SEARCH[2].c_str(),-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,10,15,VARSYSMAN::NETZWERK_IF[X].IF_IPv6[2].c_str(),-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,11,15,VARSYSMAN::NETZWERK_IF[X].IF_MAC.c_str(),-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,12,15,VARSYSMAN::NETZWERK_IF[X].IF_DRIVER.c_str(),-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,13,15,VARSYSMAN::NETZWERK_IF[X].IF_DeviceName.c_str(),-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,14,15,VARSYSMAN::NETZWERK_IF[X].IF_WPA_CONF[2].c_str(),-1);

            wattrset(VARSYSMAN::NETZWERK.TMPWin2,A_BOLD | COLOR_PAIR(14));
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,1,33,"IFace Datei:",-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,3,33,VARSYSMAN::NETZWERK_IF[X].IF_IPv4[0].c_str(),-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,4,33,VARSYSMAN::NETZWERK_IF[X].IF_NETMASK[0].c_str(),-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,5,33,VARSYSMAN::NETZWERK_IF[X].GW_IPv4[0].c_str(),-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,6,33,VARSYSMAN::NETZWERK_IF[X].IF_BROADCAST[0].c_str(),-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,7,33,VARSYSMAN::NETZWERK_IF[X].IF_NETWORK[0].c_str(),-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,8,33,VARSYSMAN::NETZWERK_IF[X].DNS_NAMESERVERS[0].c_str(),-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,9,33,VARSYSMAN::NETZWERK_IF[X].DNS_SEARCH[0].c_str(),-1);
            mvwaddnstr(VARSYSMAN::NETZWERK.TMPWin2,10,33,VARSYSMAN::NETZWERK_IF[X].IF_IPv6[0].c_str(),-1);
        }
    }
}

void SYSNETZWERK::NetzMain(void)
{
    SYSNETZWERK::sys_netz1_fenster();
    SYSNETZWERK::menu_ifaces();
    SYSNETZWERK::Start_Route();
    //SYSNETZWERK::Netz_Info();

    int c;

    refresh();
    touchwin(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
    wrefresh(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
    wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::NETZWERK.TMPWin1));
    prefresh(VARSYSMAN::clearwindow(VARSYSMAN::NETZWERK.TMPWin2), 0, 0, 7, 1, STARTSYSMAN::max_yr -1, STARTSYSMAN::max_xc -1);


    keypad(STARTSYSMAN::START.TMPWin3,true);
    while ((c = getch()) != KEY_F(10)){
        switch (c) {
        case KEY_DOWN:
            menu_driver(VARSYSMAN::NETZWERK.TMPMenu1, REQ_NEXT_ITEM);
            break;
        case KEY_UP:
            menu_driver(VARSYSMAN::NETZWERK.TMPMenu1, REQ_PREV_ITEM);
            break;
        case 0x0A:
            SYSNETZWERK::NETNMeWaNe = string(item_name(current_item(VARSYSMAN::NETZWERK.TMPMenu1)));
            SYSNETZWERK::Netz_Conf_Anzeigen(item_name(current_item(VARSYSMAN::NETZWERK.TMPMenu1)));
            break;
        }
        refresh();
        wrefresh(STARTSYSMAN::START.TMPWin3);
        wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::NETZWERK.TMPWin1));
        prefresh(VARSYSMAN::clearwindow(VARSYSMAN::NETZWERK.TMPWin2), 0, 0, 7, 1, STARTSYSMAN::max_yr -1, STARTSYSMAN::max_xc -1);
    }
}

//SYSNETZWERK::SYS_NETZ(){}
//SYSNETZWERK::~SYS_NETZ(){}
