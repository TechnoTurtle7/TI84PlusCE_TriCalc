#define VERSION "v1.0 BETA"
#define BOOL unsigned int
#define TRUE 1
#define FALSE 0

#include <keypadc.h>

#include "draw.h"

int main() {
    gfxInit();
    
    gfxGreet();
    
    while(1) {
        kb_Scan();
        
        if(kb_IsDown(kb_KeyDel)) break;
        
        if(needsRedraw) gfxRender();
    }
    
    gfxEnd();
    return 0;
}
