#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "../include/main.h"

#define ROWS 10
#define COLUMNS 10

static int map[ROWS][COLUMNS]={
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,2,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,1,0,0},
  {0,0,0,0,0,0,0,0,0,0},
  {0,0,0,0,0,0,0,0,0,0}};

static int apple_coordinates[2]={2,5};

int main(){
  printf("press D to exit\n");

  player_position player_coordinates={7,7,1,{5,7}};
  time_t last_time=time(NULL);


  while(1){
    if(1){

      char user_input;
      user_input=getchar(); 
      if(user_input=='\n')continue;
      printf("\033[H\033[J");

      if(user_input=='D'){return 0;}
      else{
        if((update_map(user_input,&player_coordinates))==-1){
          printf("player has collided");
          return 0;
        }

        print_screen();
      }
    }
  }

  return 0;
}

int check_coallision(player_position *player_coordinates){
  if (player_coordinates->x< 0 || player_coordinates->x>= COLUMNS || player_coordinates->y< 0 || player_coordinates->y >= ROWS) {
      return 1;
  }

  // check if snake hits it self;
  else{
    for(int i=player_coordinates->size-1;i>0;i--){
      if((player_coordinates->x == player_coordinates->body[i][0])&&(player_coordinates->y == player_coordinates->body[i][1])){return 1;}
    }
  }

  return 0;
}


int update_map(char user_input,player_position *player_coordinates){
  move_snake(user_input,player_coordinates); 

  //clear map
  for(int i=0;i<ROWS;i++){
    for(int j=0;j<COLUMNS;j++){
      //if its not a apple
      if(map[i][j]!=2){map[i][j]=0;}
    }
  }
 
  if(check_coallision(player_coordinates)){
    return -1;
  }

  for(int i=0;i<(player_coordinates->size);i++){
    map[player_coordinates->body[i][0]][player_coordinates->body[i][1]]=1; 
  }

  return 0;
}


void move_snake(char user_input, player_position *player_coordinates) {
    // Check if the head is on the apple
    if (player_coordinates->body[0][0] == apple_coordinates[0] && player_coordinates->body[0][1] == apple_coordinates[1]) {
        // make the snake bigger
        player_coordinates->size++;

        // Add body part
        player_coordinates->body[player_coordinates->size - 1][0] = player_coordinates->body[player_coordinates->size - 2][0];
        player_coordinates->body[player_coordinates->size - 1][1] =player_coordinates->body[player_coordinates->size - 2][1];

        // make the apple when its eatren
        srand(time(NULL));
        apple_coordinates[0] = rand() % ROWS;
        apple_coordinates[1] = rand() % COLUMNS;
        map[apple_coordinates[0]][apple_coordinates[1]] = 2;
    }


    for (int i = player_coordinates->size - 1; i > 0; i--) {
        player_coordinates->body[i][0] = player_coordinates->body[i - 1][0];
        player_coordinates->body[i][1] = player_coordinates->body[i - 1][1];
    }

    // Update the head position based on input
    switch (user_input) {
        //  accidently swpaped x and y 
        case 'a': player_coordinates->y--; break; 
        case 'd': player_coordinates->y++; break;
        case 'w': player_coordinates->x--; break;
        case 's': player_coordinates->x++; break;
    }

    printf("this is x,y: %d %d\n", player_coordinates->x, player_coordinates->y);


    player_coordinates->body[0][0] = player_coordinates->x;
    player_coordinates->body[0][1] = player_coordinates->y;
}




void print_screen(){
  for(int i=0;i<1;i++){
    printf("|");
    for(int j=0;j<COLUMNS;j++){
      printf(" = ");
    }
  }
  printf("|");
  printf("\n");


  for(int i=0;i<ROWS;i++){
    printf("|");
    for(int j=0;j<COLUMNS;j++){
      if(map[i][j]==0){printf(" . ");}
      else if(map[i][j]==1){printf(" X ");}
      else{printf(" A ");}
    }
    printf("|");
    printf("\n");
  }

  for(int i=0;i<1;i++){
    printf("|");
    for(int j=0;j<COLUMNS;j++){
      printf(" = ");
    }
  }
  printf("|");
  printf("\n");
}

