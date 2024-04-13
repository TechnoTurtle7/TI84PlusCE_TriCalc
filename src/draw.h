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
    gfx_palette[COL_GREEN] = gfx_RGBTo1555(0, 255, 0);
    gfx_palette[COL_RED] = gfx_RGBTo1555(255, 0, 0);
    
    gfx_SetTransparentColor(COL_WHITE);
    gfx_SetTextFGColor(COL_BLACK);
    gfx_SetColor(COL_BLACK);
}
void gfxEnd() {
    gfx_End();
}
void gfxRender() {
    gfx_FillScreen(COL_WHITE);
    
    gfx_SetTextFGColor(COL_BLACK);
    //version number
    uint width = gfx_GetStringWidth(VERSION);
    gfx_PrintStringXY(VERSION, GFX_LCD_WIDTH - width - 1, GFX_LCD_HEIGHT - CHAR_HEIGHT - 1);
    
    //controls
    gfx_PrintStringXY("[del] - Exit", 1, GFX_LCD_HEIGHT - CHAR_HEIGHT - 1);
    
    gfx_SwapDraw();
    
    needsRedraw = false;
}
