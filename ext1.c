Ext1: 
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TOTAL_ROUNDS 8
#define NUM_GESTURES 7

const char *gesture_names[] = {
    "Rock", "Paper", "Scissors", "Fire", "Air", "Water", "Sponge"
};

// Returns 1 for player 1 win, -1 for player 2 win and 0 for tie
int winner_determine(int g1, int g2) {
    if (g1 == g2) return 0;

    if (g1 == 0) { // Rock
        if (g2 == 2 || g2 == 3 || g2 == 6) return 1; // Scissors, Fire, Sponge
        else return -1;
    }
    if (g1 == 1) { // Paper
        if (g2 == 0 || g2 == 4 || g2 == 5) return 1; // Rock, Air, Water
        else return -1;
    }
    if (g1 == 2) { // Scissors
        if (g2 == 1 || g2 == 4 || g2 == 6) return 1; // Paper, Air, Sponge
        else return -1;
    }
    if (g1 == 3) { // Fire
        if (g2 == 1 || g2 == 2 || g2 == 6) return 1; // Paper, Scissors, Sponge
        else return -1;
    }
    if (g1 == 4) { // Air
        if (g2 == 0 || g2 == 3 || g2 == 5) return 1; // Rock, Fire, Water
        else return -1;
    }
    if (g1 == 5) { // Water
        if (g2 == 0 || g2 == 2 || g2 == 3) return 1; // Rock, Scissors, Fire
        else return -1;
    }
    if (g1 == 6) { // Sponge
        if (g2 == 1 || g2 == 4 || g2 == 5) return 1; // Paper, Air, Water
        else return -1;
    }

    return -1; // fallback
}

int check_gesture(int g) {
    return (g >= 0 && g < NUM_GESTURES) ? 0 : 1;
}

int input_gesture(int player) {
    int gesture;
    while (1) {
        printf("Player %d, enter your gesture (0 = Rock, 1 = Paper, 2 = Scissors, 3 = Fire, 4 = Air, 5 = Water, 6 = Sponge): ", player);
        if (scanf("%d", &gesture) == 1 && check_gesture(gesture) == 0) {
            break;
        } else {
            printf("Invalid input. Please enter a number between 0 and 6.\n");
            while (getchar() != '\n'); // clear input buffer
        }
    }
    return gesture;
}

int get_rand_gesture() {
    return rand() % NUM_GESTURES;
}

void display_gesture(const char *who, int gesture) {
    printf("%s chose: %d (%s)\n", who, gesture, gesture_names[gesture]);
}

void play_game(int mode) {
    int score1 = 0, score2 = 0, round = 1;

    while (score1 + score2 < TOTAL_ROUNDS) {
        printf("\nRound %d\n", round);
        int g1, g2;

        if (mode == 1) { // Human vs Human
            g1 = input_gesture(1);
            g2 = input_gesture(2);
        } else if (mode == 2) { // Human vs Computer
            g1 = input_gesture(1);
            g2 = get_rand_gesture();
            display_gesture("Computer", g2);
        } else { // Computer vs Computer
            g1 = get_rand_gesture();
            g2 = get_rand_gesture();
            display_gesture("Computer 1", g1);
            display_gesture("Computer 2", g2);
        }

        int result = winner_determine(g1, g2);

        if (result == 1) {
            printf(mode == 2 ? "You win this round!\n" : "Player 1 wins this round!\n");
            score1++;
        } else if (result == -1) {
            printf(mode == 2 ? "Computer wins this round!\n" : "Player 2 wins this round!\n");
            score2++;
        } else {
            printf("It's a tie! Replay the round.\n");
            continue; // repeat this round
        }

        printf("Score: %d:%d\n", score1, score2);
        round++;
    }

    printf("\n--- Final Result ---\n");
    if (score1 > score2)
        printf((mode == 2) ? "You win the game! Final Score: %d:%d\n" : "Player 1 wins the game! Final Score: %d:%d\n", score1, score2);
    else if (score2 > score1)
        printf((mode == 2) ? "Computer wins the game! Final Score: %d:%d\n" : "Player 2 wins the game! Final Score: %d:%d\n", score1, score2);
    else
        printf("It's a tie! Final Score: %d:%d\n", score1, score2);
}

int main() {
    srand(time(NULL));

    int choice;
    printf("Choose game mode:\n1. Human vs Human\n2. Human vs Computer\n3. Computer vs Computer\nEnter Choice: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > 3) {
        printf("Invalid choice. Try again.\n");
        return 1;
    }

    play_game(choice);

    return 0;
}
