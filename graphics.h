#include "gba.h"
#include "vector_3.h"

#define  GBA_SW 160                                        //actual gba screen width
#define  SW     120                                        //game screen width
#define  SH      80                                        //game screen height
#define RGB(r,g,b) ((r)+((g)<<5)+((b)<<10))                //15 bit, 0-31, 5bit=r, 5bit=g, 5bit=b 

void init_mode5();
void update_frame();
void clear_frame(unsigned char r, unsigned char b, unsigned char g);
void fps_clock(int frame);
void set_pixel(int x, int y,unsigned char r, unsigned char b, unsigned char g);
void draw_image(int w,int h, int xo,int yo, const unsigned short* map, int to);
void project (struct Vector v, unsigned char r, unsigned char b, unsigned char g);
void bresenham (struct Vector v0, struct Vector v1, unsigned char r, unsigned char b, unsigned char g);
void bresenham_2 (struct Vector v0, struct Vector v1, unsigned char r, unsigned char b, unsigned char g);
void draw_image_w_recolor (int w,int h, int xo,int yo, const unsigned short* map, int to, unsigned char r, unsigned char g, unsigned char b);
void draw_rect (struct Vector pos, struct Vector dim, unsigned char r, unsigned char g, unsigned char b);
void draw_rect_coor (short x1, short y1, short x2, short y2, unsigned char r, unsigned char g, unsigned char b);
