#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#define GRID_SIZE 16
#define BOX_SIZE 32
#define WINDOW_WIDTH (GRID_SIZE * BOX_SIZE)
#define WINDOW_HEIGHT (GRID_SIZE * BOX_SIZE)


int main(){

    //SDL pointers
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO); //initalizes SDl
    SDL_CreateWindowAndRenderer(WINDOW_WIDTH,WINDOW_HEIGHT,0,&window, &renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer); //renders the window to white
    
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); //switches to black for outline

    SDL_Event event; //defines the event 
    bool running = true, grid[GRID_SIZE][GRID_SIZE] = {false};

    //coordinates of the each pixel location is stored here
    int coords[16][16]= {0};

    //allows for a defined closing of the window
    while (running){
        while(SDL_PollEvent(&event)){
            if(event.type == SDL_QUIT){
                running = false;
            }
             
            //checks to see if the event is a mouse click
            if(event.type == SDL_MOUSEBUTTONDOWN){
                
                //collect its (x,y) coords and find out which box it was hovering over
                int x = event.button.x, y = event.button.y;

                //determines what 16x16 block the button click was in
                int col = x/BOX_SIZE, row = (WINDOW_HEIGHT - y)/BOX_SIZE;
                grid[col][row] = !grid[col][row]; //inverts the color of the selected box
                printf("A box has been marked at (%d,%d)\n",col, row);

                //stores the (x,y) coord to 1 if its filled in, or 0 if it isnt
                if(grid[col][row] == true){
                coords[col][row] = 1;
                }else{
                    coords[col][row] = 0;
                    }
                } 
        }
        //clears the screen before drawing new boxes
        SDL_RenderClear(renderer);  
        //nested for loop for drawing the grid
        for (int i = 0; i < GRID_SIZE; ++i) {
            int draw_row = GRID_SIZE - 1 - i;
            for (int j = 0; j < GRID_SIZE; ++j) {
                SDL_Rect box = {
                    .x = j * BOX_SIZE,
                    .y = draw_row * BOX_SIZE, 
                    .w = BOX_SIZE,
                    .h = BOX_SIZE
                };
                //if the (x,y) coord is 1 then the box is filled in
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
    //quits the rendering and window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();


    //binary address compiler
    int num = 0, bin_coord = 0, binary[16] ={0};
    //goes through each block on the grid
    for(int i = 0;i<16;i++){
        for(int j = 0;j<16;j++){
            //if the block is marked
            if(coords[j][i] == 1){
                //coversion from cardigan plane to the display's binary address system
                num = i * 16 + j; 
                for (int e = 7; e >= 0; e--) {
                    binary[e] = num % 2;
                    num /= 2;
                }

            //prints out the 16-bit long instruction. AAAAAAAA MMMM XXXX
                for (int e = 0; e < 16; e++) {
                    if(e == 8||e == 10|| e==11){ //The 4 bits in the middle(M) will always be 1011
                        printf("1");
                        continue;
                    }
                    //prints out the newly transformed binary values
                    printf("%d", binary[e]);
                }
                printf("\n");
            }
            
        }
    }
    return 0;
}
