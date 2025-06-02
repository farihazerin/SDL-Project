#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_ROUNDS 8

const char *gesture_names[] = {"Rock", "Paper", "Scissors", "Spock", "Lizard"};

//Returns 1 for player 1 win, -1 for player 2 win and 0 for tie
int winner_determine( int gesture1, int gesture2) {
  if (gesture1 == gesture2) {
    return 0;
  }

  if ((gesture1 == 0 &&(gesture2 == 2|| gesture2 == 4)) || //Rock beats scissors and lizard
    (gesture1 == 1 && (gesture2 == 0 || gesture2 == 3)) ||  // Paper beats Rock and Spock
      (gesture1 == 2 && (gesture2 == 1 || gesture2 == 4)) ||  // Scissors beats Paper and Lizard
      (gesture1 == 3 && (gesture2 == 0 || gesture2 == 2)) ||  // Spock beats Rock and Scissors
      (gesture1 == 4 && (gesture2 == 1 || gesture2 == 3)))  // Lizard beats Paper and Spock
return 1; 
 else {
    return -1;
  }
}
//this function is used to show winner
void winner_display(winner) {
  if (winner ==1)
    printf("Player 1 wins!\n");
  else if (winner == 0)
    printf("The game is a tie. Play again\n");
  else if (winner == -1)
    printf("Player 2 wins!\n");
}

//this function is used to check if a function is valid: 0 for valid and 1 for invalid
int check_gesture (int g) {
  if (g<= 4 && g>= 0) {
    return 0;
  } else {
    return 1;
  }
}

//this function prompts for a gesture and checks if it is valid 
int input_gesture(int player) {
  int gesture;
  while (1) {
    printf("Player %d, enter your gesture (0 = Rock, 1 = Paper, 2 = Scissors, 3 = Spock, 4 = Lizard):", player);
    if(scanf("%d", &gesture) == 1 && check_gesture(gesture) == 0){//checking valid input
      break;
    } else {
     printf("Invalid input. Please enter a number between 0 and 4.\n");
     while (getchar() != '\n'); // clear the input buffer
  }
}
      return gesture; 
}

void test_check_gesture() {
  int test_cases[] = {-1, 0, 1, 2, 3, 4, 5};
  int expected_results[] = {1, 0, 0, 0, 0, 0, 1};

  for (int i =0; i<7; i++) {
    int result = check_gesture(test_cases[i]);
    printf("Test input %d: ", test_cases[i]);
    if (result == expected_results[i]) {
      printf("Passed\n");
    }else {
      printf("Failed (Expected %d but got %d)\n", expected_results[i], result);
    }
  }
}

//this function is used to generate a random gesture 
int get_rand_gesture() {
  return rand() % 5;
}

void display_gesture(const char* who, int gesture) {
  printf("%s chose: %d (%s)\n", who, gesture, gesture_names[gesture]);
}

void test_winner_determine() {
    for (int gesture1 = 0; gesture1 < 5; gesture1++) {
        for (int gesture2 = 0; gesture2 < 5; gesture2++) {
            int result = winner_determine(gesture1, gesture2);
            printf("Test: %s vs %s => ", gesture_names[gesture1], gesture_names[gesture2]);

            if (gesture1 == gesture2) {
                if (result == 0) {
                    printf("Passed (Tie)\n");
                } else {
                    printf("Failed (Tie expected)\n");
                }
            }
            else if (
                (gesture1 == 0 && (gesture2 == 2 || gesture2 == 4)) || // Rock beats Scissors, Lizard
                (gesture1 == 1 && (gesture2 == 0 || gesture2 == 3)) || // Paper beats Rock, Spock
                (gesture1 == 2 && (gesture2 == 1 || gesture2 == 4)) || // Scissors beats Paper, Lizard
                (gesture1 == 3 && (gesture2 == 0 || gesture2 == 2)) || // Spock beats Rock, Scissors
                (gesture1 == 4 && (gesture2 == 1 || gesture2 == 3))    // Lizard beats Paper, Spock
            ) {
                if (result == 1) {
                    printf("Passed (Player 1 wins)\n");
                } else {
                    printf("Failed (Player 1 should win)\n");
                }
            } else {
                if (result == -1) {
                    printf("Passed (Player 2 wins)\n");
                } else {
                    printf("Failed (Player 2 should win)\n");
                }
            }
        }
    }
}

    void play_game(int mode) {
      int score1 = 0, score2 = 0;
      int round = 1;

      while (score1 + score2 < 8) {
        int g1, g2;
        printf("\nRound %d\n", round);

        if (mode == 1) {//Human vs Human
          g1 = input_gesture(1);
          g2 = input_gesture(2);
        } else if (mode == 2) {//Human vs Computer
          g1 = input_gesture(1);
          g2 = get_rand_gesture();
          display_gesture("Computer", g2);
        } else {//Computer vs Computer
          g1 = get_rand_gesture();
          g2 = get_rand_gesture();
          display_gesture("Computer 1", g1);
          display_gesture("Computer 2", g2);
        }

        int result = winner_determine(g1, g2);

                if (result == 1) {
                    printf(mode == 2? "You win this round!\n": "Player 1 wins this round!\n");
                    score1++;
                } else if (result == -1) {
                    printf(mode == 2? "Computer wins this round!\n" : "Player 2 wins this round!\n");
                    score2++;
                } else {
                    printf("It's a tie! Replay the round.\n");
                    continue; // don't increment round if tie
                }

                printf("Score: %d:%d\n", score1, score2);
                round++;
            }

            printf("\n--- Final Result ---\n");
            if (score1 > score2)
                printf("Player 1 wins the game! Final Score: %d:%d\n", score1, score2);
            else if (score2 > score1)
                printf("Player 2 wins the game! Final Score: %d:%d\n", score1, score2);
            else
                printf("It's a tie! Final Score: %d:%d\n", score1, score2);
        }

int main() {
  srand(time(NULL));

  test_check_gesture();

  //Game logic 
  int choice;
  printf("Choose game mode:\n1. Human vs Human\n2. Human vs Computer\n3. Computer vs Computer.\nEnter Choice: ");
  scanf("%d", &choice);

  if (choice < 1 || choice > 3) {
    printf("Invalid choice. Try again.\n");
    return 1;
  }

  play_game(choice);

  return 0;
}
