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

VARSYSMAN::FENSTERDATEIRECHTE VARSYSMAN::DATEIRECHTE;

int SYSDATEIRECHTE::List_Max = 0;
std::vector<DateiListe> SYSDATEIRECHTE::DatenListe;
char SYSDATEIRECHTE::TMP_FileAccess[10] = {'-','-','-','-','-','-','-','-','-','-'};
std::string SYSDATEIRECHTE::path = "";
string SYSDATEIRECHTE::TMP_LinkPath = "";
string SYSDATEIRECHTE::tmptest22 = "";

void SYSDATEIRECHTE::FensterDesign()
{
    VARSYSMAN::DATEIRECHTE.FEID = 5;
    VARSYSMAN::DATEIRECHTE.FENAME = string("Dateirechte");
    delwin(STARTSYSMAN::START.TMPWin3);
    VARSYSMAN::DATEIRECHTE.TMPWinHigh = STARTSYSMAN::max_yr-3;
    STARTSYSMAN::START.TMPWin3 = newwin(STARTSYSMAN::max_yr-1,STARTSYSMAN::max_xc,1,0);
    wbkgd(STARTSYSMAN::START.TMPWin3,COLOR_PAIR(61));
    box(STARTSYSMAN::START.TMPWin3, 0, 0);
    mvwhline(STARTSYSMAN::START.TMPWin3, 8, 1, ACS_HLINE, STARTSYSMAN::max_xc-2);
    mvwhline(STARTSYSMAN::START.TMPWin3, 8, 0, ACS_LTEE,1);
    mvwhline(STARTSYSMAN::START.TMPWin3, 8, STARTSYSMAN::max_xc-1, ACS_RTEE,1);
    mvwvline(STARTSYSMAN::START.TMPWin3, 1, 44, ACS_VLINE, 7);
    mvwvline(STARTSYSMAN::START.TMPWin3, 0, 44, ACS_TTEE, 1);
    mvwvline(STARTSYSMAN::START.TMPWin3, 8, 44, ACS_BTEE, 1);

    refresh();
    touchwin(STARTSYSMAN::START.TMPWin3);
    wrefresh(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));

    VARSYSMAN::DATEIRECHTE.TMPWin1 = newwin(7, 34,2,45);
    //STARTSYSMAN::START.TMPWin3 = derwin(VARSYSMAN::DATEIRECHTE.TMPWin1, 7, 35, 2, STARTSYSMAN::max_xc-37);
    wbkgd(VARSYSMAN::DATEIRECHTE.TMPWin1,COLOR_PAIR(11));
    wsetscrreg(VARSYSMAN::DATEIRECHTE.TMPWin1, 1, STARTSYSMAN::max_yr-2);
    scrollok(VARSYSMAN::DATEIRECHTE.TMPWin1, true);
    scroll(VARSYSMAN::DATEIRECHTE.TMPWin1);
    idlok(VARSYSMAN::DATEIRECHTE.TMPWin1, true);

    VARSYSMAN::DATEIRECHTE.TMPWin2 = newwin(STARTSYSMAN::max_yr-10, STARTSYSMAN::max_xc-2, 10, 1);
    //STARTSYSMAN::START.TMPWin3 = derwin(VARSYSMAN::DATEIRECHTE.TMPWin2, STARTSYSMAN::max_yr-10, STARTSYSMAN::max_xc-2, 10, 1);
    wbkgd(VARSYSMAN::DATEIRECHTE.TMPWin2,COLOR_PAIR(11));
    wsetscrreg(VARSYSMAN::DATEIRECHTE.TMPWin2, 1, STARTSYSMAN::max_yr-2);
    scrollok(VARSYSMAN::DATEIRECHTE.TMPWin2, true);
    scroll(VARSYSMAN::DATEIRECHTE.TMPWin2);
    idlok(VARSYSMAN::DATEIRECHTE.TMPWin2, true);
}

string SYSDATEIRECHTE::rechte(string datei)
{
    //string rights;
    //char rightsFF[10];
    const char *rwx = "rwxrwxrwx";
    struct stat attribut;
    unsigned int bits[9] = { S_IRUSR,S_IWUSR,S_IXUSR,/*Zugriffsrechte User*/
                             S_IRGRP,S_IWGRP,S_IXGRP,/*Zugriffsrechte Gruppe*/
                             S_IROTH,S_IWOTH,S_IXOTH /*Zugriffsrechte der Rest*/
                           };

    unsigned int EXC_BITS[3] = {S_ISUID,S_ISGID,S_ISVTX};

    //stat(datei.c_str(), &attribut);
    if(stat(datei.c_str(), &attribut) == -1) {
        fprintf(stderr,"Fehler bei stat: %s\n",
                strerror(errno));
        cout << datei.c_str() << "Fehler" << endl;
        //return "fehler";
    }
    /* Dateiart erfragen */
    mode_t perm; //typ,

/*    typ = attribut.st_mode >> 12;
    switch (typ) {
    case 001: TMP_FileAccess[0] = 'p'; break;
    case 002: TMP_FileAccess[0] = 'c'; break;
    case 004: TMP_FileAccess[0] = 'd'; break;
    case 006: TMP_FileAccess[0] = 'b'; break;
    case 010: TMP_FileAccess[0] = '-'; break;
    case 012: TMP_FileAccess[0] = 'l'; break;
    case 014: TMP_FileAccess[0] = 's'; break;
    default:  TMP_FileAccess[0] = '-';
    }
    if( S_ISLNK(attribut.st_mode) ){
        TMP_FileAccess[0] = 'l';
    }else if( S_ISDIR(attribut.st_mode) ){
        TMP_FileAccess[0] = 'd';
    }else if( S_ISCHR(attribut.st_mode) ){
        TMP_FileAccess[0] = 'c';
    }else if( S_ISBLK(attribut.st_mode) ){
        TMP_FileAccess[0] = 'b';
    }else if( S_ISFIFO(attribut.st_mode) ){
        TMP_FileAccess[0] = 'p';
    }else if( S_ISREG(attribut.st_mode) ){
        TMP_FileAccess[0] = '-';
    }else if( S_ISSOCK(attribut.st_mode) ){
        TMP_FileAccess[0] = 's';
    }else{
        TMP_FileAccess[0] = '-';
    }*/

    char tmptest[32];
    perm = attribut.st_mode & 0777;   /* Nur die unteren 12 Bits ausgeben */
    sprintf(tmptest, "0%o", perm); /* Rechte als Oktalzahl ausgeben */

    tmptest22 = string(tmptest);

    for(int i=1; i<=9; i++) { /*Wenn nicht 0, dann gesetzt*/
        TMP_FileAccess[i]=(attribut.st_mode & bits[i-1]) ? rwx[i-1] : '-';
    }

    for (int i=0; i<3; i++){
        if(i==0 && TMP_FileAccess[3]=='x'){
            TMP_FileAccess[3] = (attribut.st_mode & EXC_BITS[0]) ? 's' : 'x';
        }else if(i==0 && TMP_FileAccess[3]=='-'){
            TMP_FileAccess[3] = (attribut.st_mode & EXC_BITS[0]) ? 's' : '-';
        }else if (i==1 && TMP_FileAccess[6]=='x'){
            TMP_FileAccess[6] = (attribut.st_mode & EXC_BITS[1]) ? 's' : 'x';
        }else if (i==1 && TMP_FileAccess[6]=='-'){
            TMP_FileAccess[6] = (attribut.st_mode & EXC_BITS[1]) ? 's' : '-';
        }else if (i==2 && TMP_FileAccess[9]=='x'){
            TMP_FileAccess[9] = (attribut.st_mode & EXC_BITS[2]) ? 't' : 'x';
        }else if (i==2 && TMP_FileAccess[9]=='-'){
            TMP_FileAccess[9] = (attribut.st_mode & EXC_BITS[2]) ? 't' : '-';
        }
    }

    string rights(TMP_FileAccess);
    rights.erase(10,4);
    return rights;
}

string SYSDATEIRECHTE::user_group(string datei,int id)
{
    string tmpbuff = "";
    struct stat attribut;
    stat(datei.c_str(), &attribut);  // Error check omitted
    struct passwd *pw = getpwuid(attribut.st_uid);
    struct group *gr = getgrgid(attribut.st_gid);

    switch (id)
    {
    case 0:
        if (pw){
            tmpbuff = string(pw->pw_name);
        }
        break;
    case 1:
        if (gr){
            tmpbuff = string(gr->gr_name);
        }
        break;
    }
    //    tmpstr = "";
    //    if (pw){
    //        tmpstr.append(string(pw->pw_name));
    //    }
    //    tmpstr.append(":");
    //    if (gr){
    //        tmpstr.append(string(gr->gr_name));
    //    }
    return tmpbuff;
}

std::string SYSDATEIRECHTE::do_readlink(std::string const& path) {
    char buff[PATH_MAX];
    ssize_t len = ::readlink(path.c_str(), buff, sizeof(buff)-1);
    if (len != -1) {
        buff[len] = '\0';

    }
    return std::string(buff);
    /* handle error condition */
}

void SYSDATEIRECHTE::sort(std::vector<DateiListe>& DatenListe)
{
    static const auto name_pair = [] ( const DateiListe& dl ) { return std::make_pair( dl.DateiPath, dl.DateiLink ); };
    static const auto cmp = [] ( const DateiListe& dl_a, const DateiListe& dl_b ) { return name_pair(dl_a) < name_pair(dl_b) ; } ;
    std::sort( std::begin(DatenListe), std::end(DatenListe), cmp ) ;
}

void SYSDATEIRECHTE::ProcessDirectory(std::string directory)
{
    std::string dirToOpen = path + directory;
    auto dir = opendir(dirToOpen.c_str());

    //set the new path for the content of the directory
    if (dirToOpen.compare("/")==0){
        path = dirToOpen;
    }else{
        path = dirToOpen + "/";
    }

//    string tmp = rechte(dirToOpen);
//    string tmp2 = user_group(dirToOpen,0);
//    string tmp3 = user_group(dirToOpen,1);
    //std::cout << tmp << "\t" << user_group(dirToOpen) << "\t" << dirToOpen.c_str() << std::endl;
    //DatenListe.push_back(tmp + "\t" + tmp2 + "\t" + dirToOpen.c_str());
    //DatenListe.push_back(dirToOpen.c_str());
//    DatenListe.push_back({List_Max++,tmp,tmp2,tmp3,dirToOpen.c_str(),TMP_LinkPath.c_str()});
    DatenListe.push_back({List_Max++, rechte(dirToOpen), tmptest22, user_group(dirToOpen,0),
                          user_group(dirToOpen,1), dirToOpen, TMP_LinkPath});

    //    if(nullptr == dir)
    //    {
    //        //std::cout << "could not open directory: " << dirToOpen.c_str() << std::endl;
    //        //string fehler = "could not oen directory -> ";
    //        //DatenListe.push_back(fehler + dirToOpen.c_str());
    //        //DatenListe.push_back(dirToOpen.c_str());
    //        DatenListe2.push_back({count++,tmp,tmp2,tmp3,dirToOpen.c_str(),dirToOpen.c_str()});
    //        return;
    //    }

    auto entity = readdir(dir);

    while(entity != nullptr)
    {
        ProcessEntity(entity);
        entity = readdir(dir);
    }

    //we finished with the directory so remove it from the path
    path.resize(path.length() - 1 - directory.length());
    closedir(dir);
}

void SYSDATEIRECHTE::ProcessFile(std::string file)
{
    string tmp = rechte(file);
    string tmp2 = user_group(file,0);
    string tmp3 = user_group(file,1);
    //std::cout << tmp << "\t" << user_group(file) << "\t" << file.c_str() << std::endl;
    //DatenListe.push_back(tmp + "\t" + tmp2 + "\t" + file.c_str());
    //DatenListe.push_back(file.c_str());
    DatenListe.push_back({List_Max++, rechte(file), tmptest22, user_group(file,0), user_group(file,1), file, TMP_LinkPath});
}

void SYSDATEIRECHTE::ProcessEntity(struct dirent* entity)
{
    if(entity->d_type == DT_DIR)
    {
        if (strcmp(entity->d_name,"..")==0 || strcmp(entity->d_name,".")==0)
        {
            return;
        }
        TMP_FileAccess[0] = 'd';
        TMP_LinkPath = "";
        ProcessDirectory(std::string(entity->d_name));
        return;
    }
    if(entity->d_type == DT_REG)
    {
        TMP_FileAccess[0] = '-';
        TMP_LinkPath = "";
        ProcessFile(std::string(path) + std::string(entity->d_name));
        return;
    }else if(entity->d_type == DT_BLK)
    {
        TMP_FileAccess[0] = 'b';
        TMP_LinkPath = "";
        ProcessFile(std::string(path) + std::string(entity->d_name));
        return;
    }else if(entity->d_type == DT_CHR)
    {
        TMP_FileAccess[0] = 'c';
        TMP_LinkPath = "";
        ProcessFile(std::string(path) + std::string(entity->d_name));
        return;
    }else if(entity->d_type == DT_FIFO)
    {
        TMP_FileAccess[0] = 'p';
        TMP_LinkPath = "";
        ProcessFile(std::string(path) + std::string(entity->d_name));
        return;
    }else if(entity->d_type == DT_LNK)
    {
        TMP_FileAccess[0] = 'l';
        TMP_LinkPath = do_readlink(std::string(path) + std::string(entity->d_name));
        ProcessFile(std::string(path) + std::string(entity->d_name));
        return;
    }else if(entity->d_type == DT_SOCK)
    {
        TMP_FileAccess[0] = 's';
        TMP_LinkPath = "";
        ProcessFile(std::string(path) + std::string(entity->d_name));
        return;
    }else if(entity->d_type == DT_UNKNOWN)
    {
        TMP_FileAccess[0] = '-';
        TMP_LinkPath = "";
        ProcessFile(std::string(path) + std::string(entity->d_name));
        return;
    }
    //std::cout << "Not a file or directory: " << entity->d_name << std::endl;
    //string fehler = "Not a file or directory -> ";
    //DatenListe.push_back(fehler + entity->d_name);
    //DatenListe.push_back(entity->d_name);
}

void SYSDATEIRECHTE::DateiMenu()
{
    VARSYSMAN::DATEIRECHTE.TMPItem1 = static_cast<ITEM **>(calloc(5,sizeof(ITEM *)));
    VARSYSMAN::DATEIRECHTE.TMPItem1[0] = new_item("Installiert", "");
    VARSYSMAN::DATEIRECHTE.TMPItem1[1] = new_item("Software-Center", "");//15
    VARSYSMAN::DATEIRECHTE.TMPItem1[2] = new_item("AK-UB-conf", "");
    VARSYSMAN::DATEIRECHTE.TMPItem1[3] = new_item("Starten", "");
    VARSYSMAN::DATEIRECHTE.TMPItem1[4] = nullptr;
    VARSYSMAN::DATEIRECHTE.TMPMenu1 = new_menu(VARSYSMAN::DATEIRECHTE.TMPItem1);
    set_menu_win (VARSYSMAN::DATEIRECHTE.TMPMenu1, VARSYSMAN::DATEIRECHTE.TMPWin1);
    set_menu_sub (VARSYSMAN::DATEIRECHTE.TMPMenu1, derwin(VARSYSMAN::DATEIRECHTE.TMPWin1, 0, 0, 1, 1));
    set_menu_spacing(VARSYSMAN::DATEIRECHTE.TMPMenu1, 0, 0, 0);
    set_menu_format(VARSYSMAN::DATEIRECHTE.TMPMenu1, 5, 0);
    menu_opts_off(VARSYSMAN::DATEIRECHTE.TMPMenu1, O_SHOWDESC);
    menu_opts_off(VARSYSMAN::DATEIRECHTE.TMPMenu1, O_NONCYCLIC);
    //set_menu_fore(VARSYSMAN::DATEIRECHTE.TMPMenu, COLOR_PAIR(12)|A_REVERSE|A_BOLD);
    set_menu_fore(VARSYSMAN::DATEIRECHTE.TMPMenu1, COLOR_PAIR(VARSYSMAN::HaMe_FG)|A_BOLD);
    set_menu_back(VARSYSMAN::DATEIRECHTE.TMPMenu1, COLOR_PAIR(VARSYSMAN::HaMe_HG));//|A_BOLD);
    set_menu_grey(VARSYSMAN::DATEIRECHTE.TMPMenu1, COLOR_PAIR(VARSYSMAN::HaMe_grey)|A_BOLD);
    set_menu_mark(VARSYSMAN::DATEIRECHTE.TMPMenu1,"");
    set_current_item(VARSYSMAN::DATEIRECHTE.TMPMenu1, VARSYSMAN::DATEIRECHTE.TMPItem1[0]);
    post_menu(VARSYSMAN::DATEIRECHTE.TMPMenu1);

}

void SYSDATEIRECHTE::Start_Rechte()
{
    SYSDATEIRECHTE::FensterDesign();

    refresh();
    touchwin(STARTSYSMAN::START.TMPWin3);
    wrefresh(VARSYSMAN::clearwindow(STARTSYSMAN::START.TMPWin3));
    wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::DATEIRECHTE.TMPWin1));
    wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::DATEIRECHTE.TMPWin2));
    //prefresh(VARSYSMAN::clearwindow(VARSYSMAN::DATEIRECHTE.TMPWin1), 0, 0, 7, 35, 2, 45);
    //prefresh(VARSYSMAN::clearwindow(VARSYSMAN::DATEIRECHTE.TMPWin2), 0, 0, STARTSYSMAN::max_yr-10, STARTSYSMAN::max_xc-2, 10, 1);

    List_Max = 0;
    std::string directory = "/usr/bin";
    SYSDATEIRECHTE::ProcessDirectory(directory);

    SYSDATEIRECHTE::sort(DatenListe);
    for( const DateiListe& dl : DatenListe )
    {
        if (dl.DateiLink.empty()==true)
        {
            waddnstr(VARSYSMAN::DATEIRECHTE.TMPWin2,dl.Octal.c_str(),-1);
            waddnstr(VARSYSMAN::DATEIRECHTE.TMPWin2," ",-1);
            waddnstr(VARSYSMAN::DATEIRECHTE.TMPWin2,dl.FileAccess.c_str(),-1);
            waddnstr(VARSYSMAN::DATEIRECHTE.TMPWin2," ",-1);
            waddnstr(VARSYSMAN::DATEIRECHTE.TMPWin2,dl.Benutzer.c_str(),-1);
            waddnstr(VARSYSMAN::DATEIRECHTE.TMPWin2," ",-1);
            waddnstr(VARSYSMAN::DATEIRECHTE.TMPWin2,dl.Gruppe.c_str(),-1);
            waddnstr(VARSYSMAN::DATEIRECHTE.TMPWin2," ",-1);
            waddnstr(VARSYSMAN::DATEIRECHTE.TMPWin2,dl.DateiPath.c_str(),-1);
            waddnstr(VARSYSMAN::DATEIRECHTE.TMPWin2,"\n",-1);
            /*waddnstr(VARSYSMAN::DATEIRECHTE.TMPWin2,dl.DateiLink.c_str(),-1);
            cout <<  dl.Octal.c_str() << "\t" << dl.FileAccess.c_str() << "\t" << dl.Benutzer.c_str() << ":"
                 << dl.Gruppe.c_str() << " " << dl.DateiPath.c_str() << "\n";*/
        }else{
            waddnstr(VARSYSMAN::DATEIRECHTE.TMPWin2,dl.Octal.c_str(),-1);
            waddnstr(VARSYSMAN::DATEIRECHTE.TMPWin2," ",-1);
            waddnstr(VARSYSMAN::DATEIRECHTE.TMPWin2,dl.FileAccess.c_str(),-1);
            waddnstr(VARSYSMAN::DATEIRECHTE.TMPWin2," ",-1);
            waddnstr(VARSYSMAN::DATEIRECHTE.TMPWin2,dl.Benutzer.c_str(),-1);
            waddnstr(VARSYSMAN::DATEIRECHTE.TMPWin2," ",-1);
            waddnstr(VARSYSMAN::DATEIRECHTE.TMPWin2,dl.Gruppe.c_str(),-1);
            waddnstr(VARSYSMAN::DATEIRECHTE.TMPWin2," ",-1);
            waddnstr(VARSYSMAN::DATEIRECHTE.TMPWin2,dl.DateiPath.c_str(),-1);
            waddnstr(VARSYSMAN::DATEIRECHTE.TMPWin2," ",-1);
            waddnstr(VARSYSMAN::DATEIRECHTE.TMPWin2,dl.DateiLink.c_str(),-1);
            waddnstr(VARSYSMAN::DATEIRECHTE.TMPWin2,"\n",-1);
            /*cout <<  dl.Octal.c_str() << "\t" << dl.FileAccess.c_str() << "\t" << dl.Benutzer.c_str() << ":"
                 << dl.Gruppe.c_str() << " " << dl.DateiPath.c_str() << " -> " << dl.DateiLink.c_str() << "\n";*/
        }
         wrefresh(VARSYSMAN::clearwindow(VARSYSMAN::DATEIRECHTE.TMPWin2));
        //prefresh(VARSYSMAN::clearwindow(VARSYSMAN::DATEIRECHTE.TMPWin2), 0, 0, STARTSYSMAN::max_yr-10, STARTSYSMAN::max_xc-2, 10, 1);
    }
    //return (0);
}

SYSDATEIRECHTE::SYSDATEIRECHTE()
{
}
