#define VERSION "v1.0 BETA"
#define uint unsigned int

#include <keypadc.h>

#include "draw.h"

int main() {
    gfxInit();
    
    while(1) {
        kb_Scan();
        
        if(kb_IsDown(kb_KeyDel)) break;
        
        if(needsRedraw) gfxRender();
    }
    
    gfxEnd();
    return 0;
}
