#pragma once

#include <graphx.h>
#include <stdlib.h>
#include <string.h>

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
    gfx_SetTextConfig(gfx_text_clip);
}
void gfxEnd() {
    gfx_End();
}

void gfxDrawTri(Tri tri) {
    const Vec2 windowSize = {GFX_LCD_WIDTH - 100, GFX_LCD_HEIGHT - 80};
    const Vec2 windowPos = {90, 30};
    
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
    
    gfx_SetTextFGColor(COL_BLACK);
    const int maxChars = 8;
    
    char* buffer = malloc(maxChars + 3); //2 for variable, 1 for \0
    memset(buffer, 0, maxChars + 3);
    
    char* num = malloc(maxChars + 1);
    memset(num, 0, maxChars + 1);
    
    float2str(tri.sA, num);
    strcpy(buffer, "a=");
    strcat(buffer, num);
    
    uint width = gfx_GetStringWidth(buffer);
    gfx_PrintStringXY(buffer, p1.x - width - 1, (p1.y + p2.y) / 2 - CHAR_HEIGHT / 2);
    
    memset(buffer, 0, maxChars + 3);
    memset(num, 0, maxChars + 1);
    float2str(tri.sB, num);
    strcpy(buffer, "b=");
    strcat(buffer, num);
    
    width = gfx_GetStringWidth(buffer);
    gfx_PrintStringXY(buffer, (p1.x + p3.x) / 2 - width / 2, p1.y + CHAR_HEIGHT + 1);
    
    memset(buffer, 0, maxChars + 3);
    memset(num, 0, maxChars + 1);
    float2str(tri.sC, num);
    strcpy(buffer, "c=");
    strcat(buffer, num);
    
    gfx_PrintStringXY(buffer, (p1.x + p3.x) / 2 + 1, (p1.y + p2.y) / 2 - CHAR_HEIGHT - 1);
    
    free(num);
    free(buffer);
    
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
