#include "sim.h"

sense_fb_bitmap_t *bm=NULL;
pi_framebuffer_t *fb=NULL;

cell_t (*g)[GRID_WIDTH][GRID_HEIGHT];	

int init_d(cell_t (*grid)[GRID_WIDTH][GRID_HEIGHT]){
    fb=getFrameBuffer();
    bm=fb->bitmap;
    clear_display();
    g=grid;
	
    

    if (fb)
        return 0;
    else
        return 1;
}

int close_d(){
    clear_display();
    bm=NULL;
    fb=NULL;
    return 0;
}   

int update_d(){
    return 0;
}

void clear_display(void){
        for(int i=0; i<8;i++){
                for(int j=0; j<8; j++){
                        bm->pixel[i][j]=0x00000;}}}
