#define VERSION "v1.0 BETA"
#define uint unsigned int

#include <keypadc.h>
#include <math.h>
#include <ti/real.h>

typedef struct Vec2 {
    int x, y;
} Vec2;
typedef struct Tri {
    float sA, sB, sC, a1, a2;
} Tri;
typedef struct RenderInfo {
    Tri tri;
} RenderInfo;

void float2str(float n, char* str) {
    real_t tmp_real = os_FloatToReal(n);
    os_RealToStr(str, &tmp_real, 8, 1, 2);
}
float pythag(float a, float b) {
    return sqrtf(a * a + b * b);
}

#include "draw.h"

int main() {
    gfxInit();
    
    Tri tri = {1, 1, sqrtf(2), 60, 60}; //default isos rt tri
    
    bool upLast = false;
    bool downLast = false;
    bool leftLast = false;
    bool rightLast = false;
    while(1) {
        kb_Scan();
        
        if(kb_IsDown(kb_KeyDel)) break;
        else if(kb_IsDown(kb_KeyUp) && !upLast) {
            tri.sA++;
            tri.sC = pythag(tri.sA, tri.sB);
            needsRedraw = true;
        }
        else if(kb_IsDown(kb_KeyDown) && !downLast && tri.sA > 1) {
            tri.sA--;
            tri.sC = pythag(tri.sA, tri.sB);
            needsRedraw = true;
        }
        else if(kb_IsDown(kb_KeyLeft) && !leftLast && tri.sB > 1) {
            tri.sB--;
            tri.sC = pythag(tri.sA, tri.sB);
            needsRedraw = true;
        }
        else if(kb_IsDown(kb_KeyRight) && !rightLast) {
            tri.sB++;
            tri.sC = pythag(tri.sA, tri.sB);
            needsRedraw = true;
        }
        
        if(needsRedraw) {
            RenderInfo info = {tri};
            gfxRender(info);
        }
        
        upLast = kb_IsDown(kb_KeyUp);
        downLast = kb_IsDown(kb_KeyDown);
        leftLast = kb_IsDown(kb_KeyLeft);
        rightLast = kb_IsDown(kb_KeyRight);
    }
    
    gfxEnd();
    return 0;
}
