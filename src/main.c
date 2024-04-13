#include <ti/screen.h>
#include <ti/getcsc.h>

#define VERSION "v1.0 BETA"

int main() {
    os_ClrHome();
    
    os_PutStrFull("Hello, world!");
    
    while(!os_GetCSC());
    return 0;
}
