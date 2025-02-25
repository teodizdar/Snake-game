#define MAX_SNAKE_SIZE 10

typedef struct player_position {
  int x;
  int y;
  int size;
  int body[MAX_SNAKE_SIZE][2]; 

} player_position;


void get_bigger();

void print_screen();

int check_coallision(player_position *player_coordinates);

void move_snake(char user_input,player_position *player_coordinates);

int update_map(char user_input,player_position *player_coordinates);


