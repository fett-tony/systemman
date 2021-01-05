#ifndef SYSNETZWERK_H
#define SYSNETZWERK_H

#include <VarSysMan.h>

class SYSNETZWERK
{
public:
    static string NetIface[25];
    static stringstream IFsS;
    static int maxIfaceL;
    static int maxIface;
    static int M;
    static unsigned char IF_MAC_tmp[8];
    struct route_info;

    //struct NETZ_IF;
    struct GW_ROUTE;
    struct DNS_NASE;
    struct HOSTS_NAME;
    static string NETNMeWaNe;

    static void menu_ifaces(void);
    static int check_wireless(const char* ifname, char* protocol);
    static string umwandeln();
    static void Netz_Info_v6(int S);
    static void Netz_Info();
    static void Netz_Conf_Anzeigen(string ifname);
    static void IFACENAME(void);
    static void VendorDevice();
    static void NAMENsuche(int ifid,int appid);
    static void sys_netz1_fenster(void);

    static int NLsockLesen(int sockFd, char *bufPtr, int seqNum, int pId);
    static void SYSNETZWERK1_fenster(void);
    static void RoutingTable(struct route_info *rtInfo);
    static void GatewayLesen(struct nlmsghdr *nlHdr, struct route_info *rtInfo);
    static int Start_Route();
    static void NetzMain(void);

    SYSNETZWERK();
    ~SYSNETZWERK();

private:


protected:


};

#endif // SYSNETZWERK_H
