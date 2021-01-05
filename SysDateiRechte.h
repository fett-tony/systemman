#ifndef SYSDATEIRECHTE_H
#define SYSDATEIRECHTE_H

#include <VarSysMan.h>
#include <StartSysMan.h>

struct DateiListe {
    int ID;
    string FileAccess;
    string Octal;
    string Benutzer;
    string Gruppe;
    string DateiPath;
    string DateiLink;
};

class SYSDATEIRECHTE
{
public:
    static int List_Max;
    static std::vector<DateiListe> DatenListe;
    static char TMP_FileAccess[10];
    static std::string path;
    static string TMP_LinkPath;
    static string tmptest22;
    //static MENU *DateiBrowser;
    //static ITEM **DateiItem;

    static void FensterDesign();
    static string rechte(string datei);
    static string user_group(string datei, int id);
    static std::string do_readlink(std::string const& path);
    static void sort(std::vector<DateiListe>& DatenListe);
    static void ProcessDirectory(std::string directory);
    static void ProcessFile(std::string file);
    static void ProcessEntity(struct dirent* entity);
    static void DateiMenu();
    static void Start_Rechte();

    SYSDATEIRECHTE();
private:


protected:

};

#endif // SYSDATEIRECHTE_H
