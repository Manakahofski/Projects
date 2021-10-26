#include <stdint.h>
#include <stdio.h>

typedef enum faciem { LEFT, RIGHT, CENTER, PASS } faces;
static faces die[] = {LEFT, RIGHT, CENTER, PASS, PASS, PASS};
static const char *names[] = {
    "Happy",  "Sleepy", "Sneezy",        "Dopey",      "Bashful",
    "Grumpy", "Doc",    "Mirror Mirror", "Snow White", "Wicked Queen"};
int main() {
  /* ------ Random Seed: Inputs a seed for the RNG ------ */

  int seed;
  printf("Random seed: ");
  scanf("%d", &seed);
  int srand();
  srand(seed);

  /* ------ User Number: Number of players selected by user ------*/
  int un;
grab:
  printf("How many players? ");
  scanf("%d", &un);
  if (un < 2 || un > 10) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
      ; // clear the stdin (this line made with help from stack overflow)
    goto grab;
  }

  /* ------ Initializes Money Amounts of Every Player ------- */
  int money[un];
  int i;
  for (i = 0; i < un; i++) {
    money[i] = 3;
  }

  /* ------ Defining Functions to be Used ------- */
  int checkPlayer(int un, int money[]);
  int rollDice();
  uint32_t left();
  uint32_t right();
  int checkPlayer();

  /* =========== MAIN LOOPING CODE =================================== */
  int pot = 0;
  int curPlay = 0;
  int rolls[3]; // Keeps track of dice roll results for Current Players turn
  int peepLeft;
  int check =
      0; // Variable used to check whether /n should be skipped at start of game
  peepLeft = 1;
  while (peepLeft) {
    peepLeft = checkPlayer(un, money);
    if (peepLeft ==
        0) { // Uses peepLeft for who has remaining money and declares winner
      for (i = 0; i < un; i++) {
        if (money[i] > 0) {
          printf("\n%s wins the $%d pot with $%d left in the bank!\n", names[i],
                 pot, money[i]);
        }
      }
      /* ------ If Player gets 3 rolls ------ */
    } else if (money[curPlay] >= 3) {

      /* ------ Only prints \n after first run ------ */
      if (check == 1) {
        printf("\n");
      }
      check = 1;

      /* ------ Declares who rolled and stores RNG rolled values ------ */
      printf("%s rolls...", names[curPlay]);
      for (i = 0; i < 3; i++) {
        rolls[i] = rollDice();

        /* ------ ROLL LOGIC ------ */
        if (rolls[i] == LEFT) {
          money[left(curPlay, un)] = money[left(curPlay, un)] + 1;
          money[curPlay] = money[curPlay] - 1;
          printf(" gives $1 to %s", names[left(curPlay, un)]);

        } else if (rolls[i] == RIGHT) {
          money[right(curPlay, un)] = money[right(curPlay, un)] + 1;
          money[curPlay] = money[curPlay] - 1;
          printf(" gives $1 to %s", names[right(curPlay, un)]);

        } else if (rolls[i] == CENTER) {
          pot = pot + 1;
          money[curPlay] = money[curPlay] - 1;
          printf(" puts $1 in the pot");

        } else if (rolls[i] == PASS) {
          printf(" gets a pass");
        }
      }
      curPlay = right(curPlay, un);
    }

    /* ------ If Player gets 2 rolls ------ */
    else if (money[curPlay] == 2) {

      /* ------ Declares who rolled and stores RNG rolled values ------ */
      printf("\n");
      printf("%s rolls...", names[curPlay]);
      for (i = 0; i < 2; i++) {
        rolls[i] = rollDice();

        /* ------ ROLL LOGIC ------ */
        if (rolls[i] == LEFT) {
          money[left(curPlay, un)] = money[left(curPlay, un)] + 1;
          money[curPlay] = money[curPlay] - 1;
          printf(" gives $1 to %s", names[left(curPlay, un)]);

        } else if (rolls[i] == RIGHT) {
          money[right(curPlay, un)] = money[right(curPlay, un)] + 1;
          money[curPlay] = money[curPlay] - 1;
          printf(" gives $1 to %s", names[right(curPlay, un)]);

        } else if (rolls[i] == CENTER) {
          pot = pot + 1;
          money[curPlay] = money[curPlay] - 1;
          printf(" puts $1 in the pot");

        } else if (rolls[i] == PASS) {
          printf(" gets a pass");
        }
      }

      curPlay = right(curPlay, un);

    }

    /* ------ If Player gets 1 rolls ------ */
    else if (money[curPlay] == 1) {

      /* ------ Declares who rolled and stores RNG rolled values ------ */
      printf("\n");
      printf("%s rolls...", names[curPlay]);
      for (i = 0; i < 1; i++) {
        rolls[i] = rollDice();

        /* ------ ROLL LOGIC ------ */
        if (rolls[i] == LEFT) {
          money[left(curPlay, un)] = money[left(curPlay, un)] + 1;
          money[curPlay] = money[curPlay] - 1;
          printf(" gives $1 to %s", names[left(curPlay, un)]);

        } else if (rolls[i] == RIGHT) {
          money[right(curPlay, un)] = money[right(curPlay, un)] + 1;
          money[curPlay] = money[curPlay] - 1;
          printf(" gives $1 to %s", names[right(curPlay, un)]);

        } else if (rolls[i] == CENTER) {
          pot = pot + 1;
          money[curPlay] = money[curPlay] - 1;
          printf(" puts $1 in the pot");

        } else if (rolls[i] == PASS) {
          printf(" gets a pass");
        }
      }

      curPlay = right(curPlay, un);

    }

    else if (money[curPlay] == 0) {
      curPlay = right(curPlay, un);
    }
  }

  /* =========== END MAIN LOOPING CODE =================== */

  return 0;
}

/* ===== Loops through array to check that at least 2 people have money ===== */
int checkPlayer(int un, int money[]) {
  int c;
  c = 0;
  int i;

  for (i = 0; i < un; i++) {
    if (money[i] > 0) {
      c++;
    }
  }

  if (c > 1) {
    return 1;
  } else {
    return 0;
  }
}

/* ====== Gives a random value between 0 and 5 ===== */
int rollDice() {
  int rand();
  int a = rand();
  a = a % 6;
  int x = die[a];
  return x;
}

uint32_t left(uint32_t pos, uint32_t players) {
  return ((pos + players - 1) % players);
}

uint32_t right(uint32_t pos, uint32_t players) { return ((pos + 1) % players); }
