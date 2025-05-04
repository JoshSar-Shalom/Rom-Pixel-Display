#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#define GRID_SIZE 16
#define BOX_SIZE 32
#define WINDOW_WIDTH (GRID_SIZE * BOX_SIZE)
#define WINDOW_HEIGHT (GRID_SIZE * BOX_SIZE)


int main(){

    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO); //initalizes SDl
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH,WINDOW_HEIGHT,0,&window, &renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer); //renders the window to white
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //switches to black

    SDL_Event event;
    bool running = true, grid[GRID_SIZE][GRID_SIZE] = {false};
    
    int coords[16][16]= {0};

    while (running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }
             
            //checks that if the event is a mouse click
            if(event.type == SDL_MOUSEBUTTONDOWN){
                //collect its (x,y) coords and find out which box it was hovering over
                int x = event.button.x, y = event.button.y;
                int col = x/BOX_SIZE, row = (WINDOW_HEIGHT - y)/BOX_SIZE;
                grid[col][row] = !grid[col][row]; //inverts the color of the selected box
                printf("A box has been marked at (%d,%d)\n",col, row);
                
                if(grid[col][row] == true){
                coords[col][row] = 1;
                }else{
                    coords[col][row] = 0;
                }

            } 
        }
        //clears the screen before drawing new boxes
        SDL_RenderClear(renderer);  
        for (int i = 0; i < GRID_SIZE; ++i) {
            int draw_row = GRID_SIZE - 1 - i;
            for (int j = 0; j < GRID_SIZE; ++j) {
                SDL_Rect box = {
                    .x = j * BOX_SIZE,
                    .y = draw_row * BOX_SIZE, 
                    .w = BOX_SIZE,
                    .h = BOX_SIZE
                };
                if (grid[j][i]) {
                    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // black
                } else {
                    // Otherwise, set the color to white
                    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // white
                }
                SDL_RenderFillRect(renderer, &box);

                // Draw the outline (black)
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderDrawRect(renderer, &box);
            }
        }
        SDL_RenderPresent(renderer);
    }
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    int num = 0, bin_coord = 0, binary[16] ={0};
    for(int i = 0;i<16;i++){
        for(int j = 0;j<16;j++){
            if(coords[j][i] == 1){
            num = i * 16 + j;    // I CHANEGD THISSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSS
            for (int e = 7; e >= 0; e--) {
                binary[e] = num % 2;
                num /= 2;
            }

            


            //printf("(%d,%d) is at ",i,j);
            for (int e = 0; e < 16; e++) {
                if(e == 8||e == 10|| e==11){
                    printf("1");
                    continue;
                }
                printf("%d", binary[e]);
            }
            printf("\n");
            }
        }
    }
    return 0;
}