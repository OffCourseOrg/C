#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FLIGHTS 16
#define MAX_PASSENGERS 440

struct flight_t {
  char *code;
  char *start;
  char *destination;
  int passengers;
};

void printFlights(struct flight_t *flights[]) {
  size_t j = 0;
  for (size_t i = 0; i < MAX_FLIGHTS; ++i) {
    if (flights[i] != NULL) {
      struct flight_t *f = flights[i];
      printf("Flight %s - %s -> %s - %d passengers\n", f->code, f->start, f->destination, f->passengers);
      j++;
      continue;
    }
  }
  if (j == 0) {
    printf("FMS is empty, no flights to be printed.\n");
  }
}

bool findFlight(struct flight_t *flights[], char *code) {
  // Not sorted so no optimisations, so O(n)
  for (size_t i = 0; i < MAX_FLIGHTS; ++i) {
    if (flights[i] != NULL && 0 == strcmp(flights[i]->code, code)) {
      return true;
    }
  }
  return false;
}

void addFlight(struct flight_t **flights, char *code, char *start, char *destination, int passengers) {
  for (size_t i = 0; i < MAX_FLIGHTS; ++i) {
    if (flights[i] == NULL) {
      flights[i] = malloc(sizeof(*flights[i]));
      if (flights[i] == NULL) {
        printf("Error: Buy more RAM\n");
        return;
      }

      flights[i]->code = malloc(sizeof(*(flights[i]->code)) * (strlen(code) + 1));
      if (flights[i]->code == NULL) {
        printf("Error: Buy more RAM\n");
        return;
      }
      strcpy(flights[i]->code, code);

      flights[i]->start = malloc(sizeof(*(flights[i]->start)) * (strlen(start) + 1));
      if (flights[i]->start == NULL) {
        printf("Error: Buy more RAM.\n");
        return;
      }
      strcpy(flights[i]->start, start);

      flights[i]->destination = malloc(sizeof(*(flights[i]->destination)) * (strlen(destination) + 1));
      if (flights[i]->destination == NULL) {
        printf("Error: Buy more RAM.\n");
        return;
      }
      strcpy(flights[i]->destination, destination);

      flights[i]->passengers = passengers;
      return;
    }
  }
}

void buyTickets(struct flight_t **flights, char *code, int passengers) {
  struct flight_t *f;

  for (size_t i = 0; i < MAX_FLIGHTS; ++i) {
    if (flights[i] != NULL && 0 == strcmp(flights[i]->code, code)) {
      f = flights[i];

      if (MAX_PASSENGERS < passengers + f->passengers) {
        printf("Error: flight overbooked, command declined.\n");
        return;
      }
      f->passengers += passengers;
      printf("Added %d tickets to %s.\n", passengers, f->code);
      return;
    }
  }
  printf("Error: flight not found.\n");
}

void removeFlight(struct flight_t *flights[], char *code) {
  for (size_t i = 0; i < MAX_FLIGHTS; ++i) {
    if (flights[i] != NULL && 0 == strcmp(flights[i]->code, code)) {
      free(flights[i]->code);
      free(flights[i]->start);
      free(flights[i]->destination);
      flights[i] = NULL;
      return;
    }
  }
  printf("Error: flight does not exist.\n");
}

void sortFlights(struct flight_t **flights) {
  struct flight_t *f;
  for (size_t i = 0; i < MAX_FLIGHTS; ++i) {
    for (size_t j = i; j < MAX_FLIGHTS; ++j) {
      if (flights[j] == NULL) {
        continue;
      }
      if (flights[i] == NULL) {
        flights[i] = flights[j];
        continue;
      }
      if (flights[i]->passengers > flights[j]->passengers) {
        f = flights[i];
        flights[i] = flights[j];
        flights[j] = f;
      }
    }
  }
}

bool flightTranser(struct flight_t *flights[], char *currentLoc, char *targetLoc, int depth, int maxDepth, int pathIndices[], int *pathLen) {
  int min_path = maxDepth;
  if (strcmp(currentLoc, targetLoc) == 0 && depth > 0) {
    *pathLen = depth;
    return true;
  }

  if (depth == maxDepth)
    return false;

  for (int i = 0; i < MAX_FLIGHTS; i++) {
    if (flights[i] != NULL && strcmp(flights[i]->start, currentLoc) == 0) {
      bool inPath = false;

      for (int k = 0; k < depth; k++) {
        if (pathIndices[k] == i) {
          inPath = true;
          break;
        }
      }
      if (inPath)
        continue;

      if (flightTranser(flights, flights[i]->destination, targetLoc, depth + 1, maxDepth, pathIndices, pathLen)) {
        if (*pathLen < min_path) {
          min_path = *pathLen;
          pathIndices[depth] = i;
        }
      }
    }
  }
  return min_path != maxDepth;
}

int main(void) {
  char c;
  char temp_code[7];
  char temp_start[64];
  char temp_dest[64];
  int temp_pas;
  int path_indeces[MAX_FLIGHTS];
  int path_len;
  bool found;
  struct flight_t *flights[MAX_FLIGHTS] = {0};

  printf("** Flight Managment System ** \n");
  do {
    printf("Command? ");

    scanf(" %c", &c);

    switch (c) {
      case 'p':
        printFlights(flights);
        break;
      case 'f':
        printf("Enter flight code: ");
        scanf(" %6s", temp_code);
        found = findFlight(flights, temp_code);
        if (!found) {
          printf("Error: flight not found.\n");
          break;
        } else {
          printf("Flight found.\n");
        }
        break;
      case 'a':
        printf("Enter flight code: ");
        scanf(" %6s", temp_code);
        if (findFlight(flights, temp_code)) {
          printf("Error: flight already exists.\n");
          break;
        }

        printf("Enter starting location: ");
        scanf(" %[^\n]", temp_start);
        printf("Enter destination: ");
        scanf(" %[^\n]", temp_dest);
        printf("Enter passenger count: ");
        scanf(" %d", &temp_pas);
        addFlight(flights, temp_code, temp_start, temp_dest, temp_pas);
        break;
      case 'b':
        printf("Enter additional tickets: ");
        scanf(" %d", &temp_pas);
        if (temp_pas < 1) {
          printf("Error: the system does not allow refunds.\n");
          break;
        }
        printf("Enter flight code: ");
        scanf(" %6s", temp_code);
        buyTickets(flights, temp_code, temp_pas);
        break;
      case 'r':
        printf("Enter flight code: ");
        scanf(" %6s", temp_code);
        removeFlight(flights, temp_code);
        break;
      case 's':
        sortFlights(flights);
        printf("Flights sorted.\n");
        break;
      case 't':
        printf("Enter starting location: ");
        scanf(" %[^\n]", temp_start);
        printf("Enter destination: ");
        scanf(" %[^\n]", temp_dest);
        found = flightTranser(flights, temp_start, temp_dest, 0, MAX_FLIGHTS, path_indeces, &path_len);
        if (found) {
          printf("%d flights needed: %s", path_len, flights[path_indeces[0]]->start);
          for (size_t i = 0; i < (unsigned int)path_len; ++i) {
            printf(" -> %s", flights[path_indeces[i]]->destination);
          } 
          putchar('\n');
        } else {
          printf("Error: Destination not found.\n");
        }

        break;
    }
  } while ('q' != c);

  for (size_t i = 0; i < MAX_FLIGHTS; ++i) {
    if (flights[i] != NULL) {
      removeFlight(flights, flights[i]->code);
    } 
  }

  printf("* System Closed *\n");

  return 0;
}
