#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

/*
 * The status of a line.
 */
enum {
  NO = 0, /* No line */
  RED = 1,
  BLUE = 2
};

/*
 * The board records the colors of the lines.
 * board[0] = color of 12
 * board[1] = color of 13
 * ...
 * board[14] = color of 56
 */

int valid_edges[15] = {12, 13, 14, 15, 16, 23, 24, 25, 26, 34, 35, 36, 45, 46, 56};

typedef char board_t[15];
typedef char player_t; /* A player should be RED or BLUE. */

int random_range(int min, int max) {
    return min + rand() % (max - min + 1);
}

int search_maxid(int array[], int size) {
    if (size <= 0) {
        return -1; // Handle invalid size
    }

    int maxid = 0;

    for (int i = 1; i < size; i++) {
        if (array[i] > array[maxid]) {
            maxid = i; // Update maxid if a larger element is found
        }
    }

    return maxid;
}

int find_index(int array[], int size, int target) {
    for (int i = 0; i < size; i++) {
        if (array[i] == target) {
            return i;
        }
    }
    return -1;
}

int check_won(board_t board, player_t player) {
  // Check if the player has formed a triangle.

  int triangle[20][3] =
  {
    {0, 1, 5}, {0, 2, 6}, {0, 3, 7}, {0, 4, 8}, {1, 2, 9},
    {1, 3, 10}, {1, 4, 11}, {2, 3, 12}, {2, 4, 13}, {3, 4, 14},
    {5, 6, 9}, {5, 7, 10}, {5, 8, 11}, {6, 7, 12},
    {6, 8, 13}, {7, 8, 14}, {9, 10, 12}, {9, 11, 13}, {10, 11, 14}, {12, 13, 14}
  };

  for (int i=0; i < 20; i++){
    int a = triangle[i][0];
    int b = triangle[i][1];
    int c = triangle[i][2];

    player_t other_player = (player == RED) ? BLUE : RED;

    if (board[a] == other_player && board[b] == other_player && board[c] == other_player){
        return 1;
    }
  }

  // The player has not formed a triangle.
  return 0;
}

int check_board_full(board_t board) {
  for (int i = 0; i < 15; ++i) {
    if (board[i] == NO) {
      return 0;
    }
  }

  // The board is full.
  return 1;
}

typedef struct {
  int line; /* 0 for 12, 1 for 13, ..., 14 for 56. */
  int score; /* -1 for loss, 0 for draw, 1 for win. */
} move_t;

move_t best_move(board_t board, player_t player) {

  if (check_won(board, player)) {
    move_t bmv;
    bmv.line = -1;
    bmv.score = 1;
    return bmv;
  }

  if (check_board_full(board)) {
    move_t bmv;
    bmv.line = -1;
    bmv.score = 0;
    return bmv;
  }


  int bml = -1;
  int bms = -1;
  int lms[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  for (int i = 0; i < 15; i++) {
    if (board[i] == NO) {

      bml = i;

      board[i] = player;

      player_t opponent = (player_t) player == RED ? BLUE : RED;

      move_t move_op = best_move(board, opponent);
      int score = move_op.score;


      if (check_won(board, opponent)){
        lms[i] = -1;
      }
      else {
        lms[i] = 1;
      }

      board[i] = NO;

      if (score == -1) {
        bms = 1;
        break;
      }
    }
  }

  move_t bmv;
  bmv.line = bml;
  bmv.score = bms;

  if (bms == -1){
    bmv.line = search_maxid(lms, 15);
  }

  return bmv;
}


void print_board(board_t board) {
  for (int i = 0; i < 15; ++i) {
    switch (board[i]) {
      case RED: printf("R"); break;
      case BLUE: printf("B"); break;
      default: printf("_"); break;
    }
  }
  printf("\n");
}



int main() {
  board_t board;
  for (int i = 0; i < 15; i++) {
    board[i] = NO;
  }


  player_t player = NO;
  char player_choice;

  while (1){
      printf("Enter (R) to play first or to play second enter (B)? ");

      scanf("%c", &player_choice);

      while ((getchar()) != '\n');

      if (player_choice == 'r' || player_choice == 'R') {
          player = RED;
          break;
      }
      else if (player_choice == 'b' || player_choice == 'B'){
          player = BLUE;
          break;
      }
      else {
          printf("Enter R or B only.\n\n");
      }

  }

  player_t computer = (player == RED) ? BLUE : RED;

  player_t winner = NO;

  if (player == BLUE) {
    int line;
    line = random_range(0,14);
    board[line] = computer;

    // Print the board.
    printf("Computer's Move: %d\n", valid_edges[line]);
    print_board(board);
    printf("\n\n");
  }


  // Play the game until it is over.
  while (!check_board_full(board)){

    int x;
    int move;

    while (1){
        printf("Enter your move ([Example: 12, 23, 34]): ");
        scanf("%d", &x);
        move = find_index(valid_edges, 15, x);

        if (move == -1){
            printf("Invalid Input. Please enter a valid edge (the smaller vertex number first). [Example: 12, 23, 34]\n\n");
        }
        else if (board[move] != NO) {
            printf("Vertices already joined. Enter edge which is left to be joined.\n\n");
        }
        else {
            break;
        }

    }

    board[move] = player;

    if (check_won(board, player)) {
        print_board(board);
        winner = player;
        break;
    }

    if (check_won(board, computer)) {
        print_board(board);
        winner = computer;
        break;
    }


    move_t bmv = best_move(board, computer);


    // Make the move
    board[bmv.line] = computer;

    printf("Computer's Move: %d\n", valid_edges[bmv.line]);
    print_board(board);
    printf("\n\n");


    if (check_won(board, computer)) {
        winner = computer;
        break;
    }
    if (check_won(board, player)) {
        print_board(board);
        winner = player;
        break;
    }

  }

  printf("\n");

  // Print the winner
  switch (winner) {
    case RED:
        if (player == RED){
            printf("Congratulation! You win!");
        }
        if (player == BLUE){
            printf("Computer wins!");
        }
        break;
    case BLUE:
        if (player == BLUE){
            printf("Congratulation! You win!");
        }
        if (player == RED){
            printf("Computer wins!");
        }
        break;
    case NO: printf("It's a draw!\n"); break;
  }

  return 0;
}
