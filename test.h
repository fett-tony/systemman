#ifndef TEST_H
#define TEST_H

#include <ncursesw/cursesapp.h>
#include <ncursesw/ncurses.h>
#include <ncursesw/menu.h>
#include <ncursesw/form.h>
#include <ncursesw/panel.h>
#include <ncursesw/unctrl.h>
#include <VarSysMan.h>

//#define AK_ENTER (define_key(AK_ENTER, 0015))
//#define AK_TAB_R (define_key(AK_TAB_R, 0541))
//#define AK_TAB_V (define_key(AK_TAB_V, 0011))
//#define AK_ESC (define_key(AK_ESC, 0027))
//#define MAX 8192

//#define M_ToCharPtr(p)        reinterpret_cast<char*>(p)                   // Cast to char*
//#define M_ToWCharPtr(p)       reinterpret_cast<wchar_t*>(p)                // Cast to wchar_t*
//#define M_ToConstCharPtr(p)   reinterpret_cast<const char*>(p)             // Cast to const char*
//#define M_ToConstWCharPtr(p)  reinterpret_cast<const wchar_t*>(p)          // Cast to const wchar_t*
//#define M_ToUCharPtr(p)       reinterpret_cast<unsigned char*>(p)          // Cast to unsigned char*
//#define M_ToConstUCharPtr(p)  reinterpret_cast<const unsigned char*>(p)    // Cast to const unsigned char*
//#define M_ToUCharPtr(n)       reinterpret_cast<unsigned char*>(n)          // Cast to unsigned char*
//#define M_ToVoidPtr(p)        reinterpret_cast<void*>(p)                   // Cast to void*
//#define M_ToConstVoidPtr(p)   reinterpret_cast<const void*>(p)             // Cast to const void*
//#define M_ToIntPtr(n)         reinterpret_cast<int*>(n)                    // Cast to int*
//#define M_ToConstIntPtr(p)    reinterpret_cast<const int*>(p)              // Cast to const int*
//#define M_ToDoublePtr(n)      reinterpret_cast<double*>(n)                 // Cast to double*
//#define M_ToConstDoublePtr(n) reinterpret_cast<const double*>(n)           // Cast to const double*
//#define M_ToBoolPtr(n)        reinterpret_cast<bool*>(n)                   // Cast to bool*
//#define M_ToConstBoolPtr(n)   reinterpret_cast<const bool*>(n)             // Cast to const bool*
//General Cast
//#define M_To(T, p)            reinterpret_cast<T>(p)     */                  // Cast to T

class TEST
{
public:
    static void FolderList(void);
    static void Anzeigen();
    static void Colortest();
    static const char *arrayshow(); //const char *option);
    static int kbhit(void);

    static void HWname();
    static bool DirectoryExists(const char* pzPath);
    static void VendorDevice(string Interface);
    static void NAMENsuche(int ifid);
    static char *ntoa(int addr);
    static void test();
    static void InterfacesDatei();

private:

protected:

};

#endif //TEST_H
