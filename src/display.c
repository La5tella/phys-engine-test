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

	clear_display();
   	//loops through grid, checks if there is any particles in there, adjust colors accordingly based on capacity.
	 
	for(int i=0; i<GRID_WIDTH;i++){
		for (int j=0; j<GRID_HEIGHT;j++){
			if((*g)[i][j].count>0){
				int count = (*g)[i][j].count;
				int capacity = (*g)[i][j].capacity;
				float t = count / capacity;

				int R = (int)(255 * (1-t));
				int G = (int)(255 * (1-t));
				int B = 255;

				uint32_t hex_color = (R << 16) | (G << 8) | B;
				
				bm->pixel[i][j]= hex_color;
			
			}
		}
	}

	return 0;
}

void clear_display(void){
        for(int i=0; i<8;i++){
                for(int j=0; j<8; j++){
                        bm->pixel[i][j]=0x000000;}}}
