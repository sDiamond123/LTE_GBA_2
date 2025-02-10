#include "graphics.h"

volatile unsigned short* Scanline=(volatile unsigned short*)0x4000006;

void init_mode5(){
    *(unsigned short*)0x4000000 = 0x405;                                           //mode 5 background 2
    *(unsigned short*)0x400010A = 0x82;                                            //enable timer for fps
    *(unsigned short*)0x400010E = 0x84;                                            //cnt timer overflow
    REG_BG2PA=256/2;                                                    //256=normal 128=scale 
    REG_BG2PD=256/2;                                                    //256=normal 128=scale 
}

void wait_for_frame(){
    while(*Scanline<160){};
}

void swap_buffer() {
    if  ( DISPCNT&BACKB){
        DISPCNT &= ~BACKB;
        VRAM=(unsigned short*)VRAM_B;
    }      //back  buffer
    else {
        DISPCNT |=  BACKB; 
        VRAM=(unsigned short*)VRAM_F;
    }      //front buffer  
}

void update_frame(){
    wait_for_frame();
    swap_buffer();
}

void set_pixel(int x, int y,unsigned char r, unsigned char b, unsigned char g){
    VRAM[y*GBA_SW+x] = RGB(r,b,g);
}

void set_pixel_col(int x, int y,unsigned short col){
    //if (x<0 || y < 0 || x > 120 || y > 80) return;
    VRAM[y*GBA_SW+x] = col;
}


void clear_frame (unsigned char r, unsigned char b, unsigned char g){
    int x;
    int y;
    for (x = 0; x <SW; x++){
        for (y = 0 ; y < SH; y++){
            set_pixel(x,y,r,b,g);
        }
    }
}

void fps_clock(int FPS){
    VRAM[15]=0; 
    VRAM[FPS]=RGB(31,31,0); //draw fps 
}

void draw_image(int w,int h, int xo,int yo, const unsigned short* map, int to)
{int x,y,c;          //image w/h, position offset,  texture name, texture offset
 for(x=0;x<w;x++) 
 {                
  for(y=0;y<h;y++){ c=map[(y+to*h)*w+x]; if(c>0){ VRAM[(y+yo)*GBA_SW+x+xo]=c;}} 
 }
}

void draw_image_w_recolor (int w,int h, int xo,int yo, const unsigned short* map, int to, unsigned char r, unsigned char g, unsigned char b)
{int x,y,c;          //image w/h, position offset,  texture name, texture offset
 for(x=0;x<w;x++) 
 {                
  for(y=0;y<h;y++){ c=map[(y+to*h)*w+x]; if(c>0){ VRAM[(y+yo)*GBA_SW+x+xo]=RGB(r,g,b);}} 
 }
}

void project (struct Vector v, unsigned char r, unsigned char g, unsigned char b){
    set_pixel(v.x,v.y, r, g, b);
}

signed char abs_c (signed char a){
    if (a<0){
        a = -a;
    }
    return a;
}

void b_high (struct Vector v0, struct Vector v1, unsigned char r, unsigned char g, unsigned char b){
    short dx,dy,xi,x,y,D;
    dx = v1.x - v0.x;
    dy = v1.y - v0.y;
    xi = 1;
    if (dx < 0){
        xi = -1;
        dx = -dx;
    } 
    D = (2*dx) - dy;
    x = v0.x;
    for (y=v0.y;  y <=v1.y; y++){
        set_pixel(x,y,r,g,b);
        if (D>0){
            x +=xi;
            D+=2*(dx-dy);
        }
        else{
            D+=2*dx;
        }
    }
}

void b_low (struct Vector v0, struct Vector v1, unsigned char r, unsigned char g, unsigned char b){
    short dx,dy,yi,x,y,D;
    dx = v1.x - v0.x;
    dy = v1.y - v0.y;
    yi = 1;
    if (dy<0){
        yi = -1;
        dy = -dy;
    }
    D=(2*dy)-dx;
    y=v0.y;
    for (x=v0.x; x <= v1.x; x++){
        set_pixel(x,y,r,g,b);
        if (D>0){
            y+=yi;
            D+=2 * (dy-dx);
        }
        else{
            D+=2*dy;
        }
    }
}

void bresenham (struct Vector v0, struct Vector v1, unsigned char r, unsigned char g, unsigned char b){
    if (abs_c(v1.y-v0.y) < abs_c(v1.x-v0.x)){
        if (v0.x > v1.x){
            b_low(v1,v0,r,g,b);
        }
        else {
            b_low(v0,v1,r,g,b);
        }
    }
    else{
        if (v0.y > v1.y){
            b_high(v1,v0,r,g,b);
        }
        else {
            b_high(v0,v1,r,g,b);
        }
    }
}

void bresenham_2 (struct Vector v0, struct Vector v1, unsigned char r, unsigned char g, unsigned char b){
    short dx, sx, dy, sy, er, x0, x1, y0, y1, e2;
    x0 = v0.x;
    y0 = v0.y;
    x1 = v1.x;
    y1 = v1.y;
    dx = abs_c (x1-x0);
    sx =-1;
    if ( x0 < x1 ) sx = 1;
    dy = -1 *abs_c(y1-y0);
    sy = -1;
    if (y0 < y1)sy = 1;
    er = dx + dy;
    while (1) {
        set_pixel(x0,y0,r,g,b);
        if (x0 == x1 && y0 == y1)break;
        e2 = 2 * er;
        if (e2 > dy){
            if(x0 == x1)break;
            er += dy;
            x0+=sx;
        }
        if (e2 < dx){
            if (y0 == y1) break;
            er += dx;
            y0 +=sy;
        } 
    } 
}

void draw_rect (struct Vector pos, struct Vector dim, unsigned char r, unsigned char g, unsigned char b){
    short x,y;
    for (x = pos.x; x < dim.x; x++){
        for (y = pos.y; y < dim.y; y ++){
            set_pixel(x,y,r,g,b);
        }
    }
}

void draw_rect_coor (short x1, short y1, short x2, short y2, unsigned char r, unsigned char g, unsigned char b){
    short x,y;
    for (x = x1; x < x2; x++){
        for (y = y1; y < y2; y ++){
            set_pixel(x,y,r,g,b);
        }
    }
}

void draw_image_w_recolor_and_back (int w,int h, int xo,int yo, const unsigned short* map, int to, unsigned char r, unsigned char g, unsigned char b, unsigned char r1, unsigned char g1, unsigned char b1)
{int x,y,c;          //image w/h, position offset,  texture name, texture offset
 for(x=0;x<w;x++) 
 {                
  for(y=0;y<h;y++){ c=map[(y+to*h)*w+x]; if(c>0){ VRAM[(y+yo)*GBA_SW+x+xo]=RGB(r,g,b);} else {VRAM[(y+yo)*GBA_SW+x+xo]=RGB(r1,g1,b1);}} 
 }
}
// need:
// upscale
// downscale
// draw scale
// rotate
// draw rotate
