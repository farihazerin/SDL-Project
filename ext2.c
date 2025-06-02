#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Gesture names stored in an array
const char *gesture_names[] = {"Rock", "Fire", "Scissors", "Sponge", "Paper", "Air", "Water"};
const int NUM_GESTURES = sizeof(gesture_names)/sizeof(gesture_names[0]);
const int WIN_SCORE = (NUM_GESTURES + 1)/2; 

// Modular arithmetic winner determination using recursion
// Returns: 1 = player1 wins, -1 = player2 wins, 0 = tie
int winner_determine(int player1, int player2, int step) {
    if (player1 == player2) return 0; // tie
    if (step == NUM_GESTURES / 2) return -1; // halfway reached: player2 wins
    if ((player1 - player2 + NUM_GESTURES) % NUM_GESTURES == step) return 1; // player1 wins
    return winner_determine(player1, player2, step + 1);
}

// Get validated input from human player
int input_gesture(int player) {
    int gesture;
    printf("\nPlayer %d, choose your gesture (0–6):\n", player);
    for (int i = 0; i < NUM_GESTURES; i++) {
        printf("%d = %s\n", i, gesture_names[i]);
    }

    while (1) {
        if (scanf("%d", &gesture) == 1 && (gesture >= -1 && gesture < NUM_GESTURES)) {
            return gesture;
        } else {
            printf("Invalid input! Enter a number between 0 and 6: ");
            while (getchar() != '\n'); // clear input buffer
        }
    }
}

// Random gesture for computer
int get_rand_gesture() {
    return rand() % NUM_GESTURES;
}

int main() {
    int mode, g1, g2, winner;
    int score1 = 0, score2 = 0;
    srand(time(NULL));

    // Game mode prompt
    printf("Select game mode:\n");
    printf("1: Human vs Human\n2: Human vs Computer\n3: Computer vs Computer\nEnter your choice:");

    while (scanf("%d", &mode) != 1 || (mode < 1 || mode > 3)) {
        printf("Invalid choice! Enter 1, 2 or 3: ");
        while (getchar() != '\n');
    }

    // Game loop
    while (score1 < WIN_SCORE && score2 < WIN_SCORE) {
        printf("\n---------------- Round %d ----------------\n", score1 + score2 + 1);

        // Gesture input
        if (mode == 1) {
            g1 = input_gesture(1);
            if (g1 == -1) break;
            g2 = input_gesture(2);
            if (g2 == -1) break;
        } else if (mode == 2) {
            g1 = input_gesture(1);
            if (g1 == -1) break;
            g2 = get_rand_gesture();
            printf("Computer chose: %d (%s)\n", g2, gesture_names[g2]);
        } else {
            g1 = get_rand_gesture();
            g2 = get_rand_gesture();
            printf("Computer 1 chose: %d (%s)\n", g1, gesture_names[g1]);
            printf("Computer 2 chose: %d (%s)\n", g2, gesture_names[g2]);
        }

        // Result
        winner = winner_determine(g1, g2, 0);
        printf("\n%s vs %s\n", gesture_names[g1], gesture_names[g2]);

        if (winner == 1) {
            printf("%s wins this round!\n", 
                (mode == 3) ? "Computer 1" : (mode == 2) ? "You" : "Player 1");
            score1++;
        } else if (winner == -1) {
            printf("%s wins this round!\n", 
                (mode == 3) ? "Computer 2" : (mode == 2) ? "Computer" : "Player 2");
            score2++;
        } else {
            printf("It's a tie! Replay the round.\n");
            continue;
        }

        printf("Score: %s - %d | %s - %d\n",
            (mode == 3) ? "Computer 1" : (mode == 2) ? "You" : "Player 1", score1,
            (mode == 3) ? "Computer 2" : (mode == 2) ? "Computer" : "Player 2", score2);
    }

    // Final winner
    if (score1 == WIN_SCORE)
        printf("\n%s wins the game!\n", (mode == 3) ? "Computer 1" : (mode == 2) ? "You" : "Player 1");
    else if (score2 == WIN_SCORE)
        printf("\n%s wins the game!\n", (mode == 3) ? "Computer 2" : (mode == 2) ? "Computer" : "Player 2");

    return 0;
}