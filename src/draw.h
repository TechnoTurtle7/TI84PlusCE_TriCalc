#pragma once

#include <graphx.h>

#define COL_WHITE 0
#define COL_BLACK 1
#define COL_GREEN 2
#define COL_RED 3

#define CHAR_HEIGHT 8

bool needsRedraw = true;

void gfxInit() {
    gfx_Begin();
    
    gfx_SetDrawBuffer();
    
    gfx_palette[COL_WHITE] = gfx_RGBTo1555(255, 255, 255);
    gfx_palette[COL_BLACK] = gfx_RGBTo1555(0, 0, 0);
    gfx_palette[COL_GREEN] = gfx_RGBTo1555(0, 200, 0);
    gfx_palette[COL_RED] = gfx_RGBTo1555(200, 0, 0);
    
    gfx_SetTransparentColor(COL_WHITE);
    gfx_SetTextFGColor(COL_BLACK);
    gfx_SetColor(COL_BLACK);
}
void gfxEnd() {
    gfx_End();
}

void gfxDrawTri(Tri tri) {
    const Vec2 windowSize = {GFX_LCD_WIDTH - 40, GFX_LCD_HEIGHT - 60};
    const Vec2 windowPos = {20, 30};
    
    float scale = 30;
    if(tri.sA * scale > windowSize.y) scale = windowSize.y / tri.sA;
    if(tri.sB * scale > windowSize.x) scale = windowSize.x / tri.sB;
    
    Vec2 p1 = {(uint24_t) ((-tri.sB / 2.0f) * scale + windowSize.x / 2.0f + windowPos.x), (uint24_t) ((tri.sA / 2.0f) * scale + windowSize.y / 2.0f + windowPos.y)};
    Vec2 p2 = {(uint24_t) ((-tri.sB / 2.0f) * scale + windowSize.x / 2.0f + windowPos.x), (uint24_t) ((-tri.sA / 2.0f) * scale + windowSize.y / 2.0f + windowPos.y)};
    Vec2 p3 = {(uint24_t) ((tri.sB / 2.0f) * scale + windowSize.x / 2.0f + windowPos.x), (uint24_t) ((tri.sA / 2.0f) * scale + windowSize.y / 2.0f + windowPos.y)};
    
    gfx_SetColor(COL_BLACK);
    gfx_HorizLine_NoClip(p1.x, (uint24_t) (p1.y - 0.33 * scale), (uint24_t) (0.33 * scale));
    gfx_VertLine_NoClip((uint24_t) (p1.x + 0.33 * scale), (uint24_t) (p1.y - 0.33 * scale), (uint24_t) (0.33 * scale));
    
    gfx_SetColor(COL_GREEN);
    gfx_Line_NoClip(p1.x, p1.y, p2.x, p2.y);
    gfx_Line_NoClip(p1.x, p1.y, p3.x, p3.y);
    gfx_Line_NoClip(p2.x, p2.y, p3.x, p3.y);
    
    return;
}
void gfxRender(RenderInfo info) {
    gfx_FillScreen(COL_WHITE);
    
    gfx_SetTextFGColor(COL_BLACK);
    //version number
    uint width = gfx_GetStringWidth(VERSION);
    gfx_PrintStringXY(VERSION, GFX_LCD_WIDTH - width - 1, GFX_LCD_HEIGHT - CHAR_HEIGHT - 1);
    
    //controls
    gfx_PrintStringXY("[ARROWS] - Adjust", 1, GFX_LCD_HEIGHT - CHAR_HEIGHT * 2 - 2);
    gfx_PrintStringXY("[del] - Exit", 1, GFX_LCD_HEIGHT - CHAR_HEIGHT - 1);
    
    gfxDrawTri(info.tri);
    
    gfx_SwapDraw();
    needsRedraw = false;
}
