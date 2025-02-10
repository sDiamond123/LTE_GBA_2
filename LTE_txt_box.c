#include "LTE_txt_box.h"

void get_page (unsigned int page_number, unsigned char * out, unsigned int * size, struct huff_branch * tree){
    unsigned int byte_number = TABLE_OF_CONTENTS[page_number];
    unsigned char byte_off = TABLE_OF_CONTENTS_OFFSET[page_number];
    //unsigned char byte_off = 3;
    //render_glyph (byte_off, 60, 40, 0, 0, 0, 0, 30, 30, 30);
    //render_glyph (TABLE_OF_CONTENTS_OFFSET[3], 20, 20, 0, 0, 0, 0, 30, 30, 30);
    unsigned int read_pos= byte_number;
    unsigned char current_block = CONTENTS[read_pos];
    unsigned int write_pos = 0;
    do{
        unsigned char current = HUFF_ROOT;
        while (current >= ALFA_SIZE){
            unsigned char choice = (current_block >> (7 - byte_off)) & 0x01;
            if (choice){
                current = tree[current].right;
            }
            else {
                current = tree[current].left;
            }
            byte_off++;
            if (byte_off > 7){
                read_pos++;
                current_block = CONTENTS[read_pos];
                byte_off = 0;
            }
        }
        out[write_pos] = current;
        write_pos++;
    }
    while (read_pos < TABLE_OF_CONTENTS[page_number + 1]);
    *size = write_pos;
}

void render_box(struct text_box box){
    unsigned short x, y, i, j;
    unsigned char line, segment, read, prev, start_draw;
    x = box.x_pos;
    y = box.y_pos;
    line = 0;
    segment = 0;
    read = 0;
    start_draw = FALSE;
    for (i = 0; i < box.text_length; i++){
        prev = read;
        read = box.text[i];
        if (read == EOF_GLYPH && prev == NEW_LINE_GLYPH){
                line++;
                if (line >= box.y_focus + box.height){
                    break;
                }
                if (start_draw){
                    for (j = segment; j < box.width - 1; j++){
                        x+=GLYPH_W + 1;
                        render_glyph(33, x, y, box.font_r, box.font_g, box.font_g, box.trans, box.back_r, box.back_b, box.back_g);
                    }
                    y+=GLYPH_H + 1;
                }
                segment = 0;
                x = box.x_pos;
        }
        else if (read < GLYPH_COUNT){
            segment++;
           
            if (line >= box.y_focus && line < box.y_focus + box.height && segment >= box.x_focus && segment < box.x_focus + box.width){
                 x+=GLYPH_W + 1;
                if (!start_draw){
                    start_draw = TRUE;
                }
                render_glyph(read, x, y, box.font_r, box.font_g, box.font_g, box.trans, box.back_r, box.back_b, box.back_g);
            }
        }
    }
}

struct text_box init_txt_box (unsigned char x0, unsigned char y0, unsigned char w, unsigned char h, unsigned int id, struct huff_branch * tree){
    struct text_box out;
    out.text = malloc(526);
    get_page(id, out.text, &out.text_length, tree);
    out.width  = w;
    out.height = h;
    out.font_r = 0;
    out.font_b = 0;
    out.font_g = 0;
    out.trans = FALSE;
    out.back_r = 31;
    out.back_g = 31;
    out.back_b = 31;
    out.x_focus = 0;
    out.y_focus = 0;
    out.x_pos = x0;
    out.y_pos = y0;
    return out;
}

void free_txt_box(struct text_box * free_me){
    free(free_me->text);
    free_me = NULL;
}


void LTE_test (){
    int x = 10;
    int y = 10;
    int i, x_1, y_1;/*
    for (i = 0; i < GLYPH_COUNT; i++){
       render_glyph (i, x, y, 20, 0, 0, i%2, 0, 0, 20);
       x+=GLYPH_W + 1;
       if (i%10 >= 9){
        x = 10;
        y+= GLYPH_H + 1;
       }
    }*/
    unsigned char* test_str = malloc(500);
    unsigned int  s=20;
    struct huff_branch * tree= make_huff_tree();
    get_page(2, test_str, &s, tree);
    y = 5;
    x=5;
    for (i = 0; i < s; i++){
        unsigned char c = test_str[i];
        render_glyph (c, x, y, 0, 0, 0, 0, 30, 30, 30);
        if (c < GLYPH_COUNT){
            x+=GLYPH_W + 1;
            if (x>115){
                x = 5;
                y+= GLYPH_H + 1;
            }
            if ( y > 75){
                break;
            }
       }
    }
    free(tree);
    free(test_str);
}
