#include "game_manager.h"

void buttons();
int any_button(){
    return KEY_STATE != 0x03FF;
}

struct text_box main_box;
struct huff_branch * h_tree;

void init(){
    // init graphics
    init_mode5();
    h_tree= make_huff_tree();
    main_box = init_txt_box(10, 5, 20, 10, 2, h_tree);
}


int run(){
    int frame = 0;
    int cont = 1;
    int lastFr = 0;
    while(cont){
        if(REG_TM2D>>12!=lastFr)
        {
            // update game
            buttons();
            // draw screen
            clear_frame(20, 20, 20);
            fps_clock(frame);

            render_box(main_box);
            //LTE_test();

            update_frame();
            // update frame counter/rate
            frame++;
            if(lastFr>REG_TM2D>>12){
                frame = 0;
            }
            lastFr=REG_TM2D>>12;
        }
    }
    // free objects
    free(h_tree);
    free_txt_box(&main_box);

    // send out op code
    return 0;
}

void buttons()
{
    if(KEY_R ){main_box.x_focus ++;}
    if(KEY_L ){main_box.x_focus--;}
    if(KEY_U ){main_box.y_focus--;}
    if(KEY_D ){main_box.y_focus++;}
    if(KEY_A ){}  
    if(KEY_B ){} 
    if(KEY_LS){} 
    if(KEY_RS){} 
    if(KEY_ST){} 
    if(KEY_SL){ } 
}
