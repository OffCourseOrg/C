#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

#define MAX_DESTINATIONS 5

struct Airport_t {
  char *name;
  char *destonations[MAX_DESTINATIONS];
  float flight_time[MAX_DESTINATIONS];
};

int find_airport(struct Airport_t *airports[], char *name) {
  for (size_t i = 0; i < MAX_DESTINATIONS; i++) {
    if (airports[i] != NULL && strcmp(airports[i]->name, name) == 0) {
      return i;
    }
  }
  return -1;
}

void add_airport(struct Airport_t *airports[], char *name) {
  if (find_airport(airports, name) > -1) {
    printf("Airport '%s' exists\n", name);
    return;
  }

  for (size_t i = 0; i < MAX_DESTINATIONS; ++i) {
    if (airports[i] == NULL) {
      airports[i] = malloc(sizeof(*airports[i]));
      if (airports[i] == NULL) {
        fprintf(stderr, "Buy more RAM\n");
        return;
      }
      airports[i]->name =
          malloc((strlen(name) + 1) * sizeof(*airports[i]->name));
      if (airports[i]->name == NULL) {
        fprintf(stderr, "Buy more RAM\n");
        return;
      }
      memset(airports[i]->name, 0,
             sizeof(*airports[i]->name) * (strlen(name) + 1));
      strcpy(airports[i]->name, name);
      return;
    }
  }
}

void print_airports(struct Airport_t *airports[]) {
  printf("Airports:\n");
  for (size_t i = 0; i < MAX_DESTINATIONS; ++i) {
    if (airports[i] != NULL) {
      printf("%s\n", airports[i]->name);
      for (size_t j = 0; j < MAX_DESTINATIONS; ++j) {
        if (airports[i]->destonations[j] != NULL) {
          printf(" -%s: %.2f\n", airports[i]->destonations[j],
                 airports[i]->flight_time[j]);
        }
      }
    }
  }
}

void add_destination(struct Airport_t *airports[], char* destination1, char* destination2, float time) {
  int index1 = find_airport(airports, destination1);
  int index2 = find_airport(airports, destination2);

  if (index1 < 0 || index2 < 0) {
    printf("One of destinations does not exist\n");
    return;
  }
  for (size_t i = 0; i < MAX_DESTINATIONS; ++i) {
    if (airports[index1]->destonations[i] == NULL) {
      airports[index1]->destonations[i] = malloc(sizeof(airports[index1]->destonations[i]) * (strlen(destination2) + 1));
      if (airports[index1]->destonations[i] == NULL) {
        fprintf(stderr, "Buy more RAM\n");
        return;
      }
      strcpy(airports[index1]->destonations[i], destination2);
      airports[index1]->flight_time[i] = time;
      break;
    }
  }
  for (size_t i = 0; i < MAX_DESTINATIONS; ++i) {
    if (airports[index2]->destonations[i] == NULL) {
      airports[index2]->destonations[i] = malloc(sizeof(airports[index2]->destonations[i]) * (strlen(destination2) + 1));
      if (airports[index2]->destonations[i] == NULL) {
        fprintf(stderr, "Buy more RAM\n");
        return;
      }
      strcpy(airports[index2]->destonations[i], destination1);
      airports[index2]->flight_time[i] = time;
      break;
    }
  }
}


void remove_airport(struct Airport_t *airports[], char *name) {
  int index = find_airport(airports, name);
  if (index < 0) {
    return;
  }
  for(size_t i = 0; i < MAX_DESTINATIONS; ++i) {
    if(airports[i] == NULL) {
      continue;
    }
    for (size_t j = 0; j < MAX_DESTINATIONS; ++j) {
      if (airports[i]->destonations[j] != NULL && 
          strcmp(airports[i]->destonations[j], name) == 0) {
          free(airports[i]->destonations[j]);
          airports[i]->destonations[j] = NULL;
          airports[i]->flight_time[j] = 0;
      }
    }
  }
  free(airports[index]);
  airports[index] = NULL;
}

float is_connected(struct Airport_t *airports[], char *name1, char *name2, int hops) {
  int index1 = find_airport(airports, name1);
  int index2 = find_airport(airports, name2);
  float time = 0;
  float smallest_time = FLT_MAX;
  size_t index = 0;
  if (index1 < 0 || index2 < 0 || hops < 0) {
    return -1;
  }
  // Both names are the same
  if (strcmp(airports[index1]->name, airports[index2]->name) == 0) {
    return 0;
  }
  // Both names are not the same
  for (size_t i = 0 ; i < MAX_DESTINATIONS; ++i) {
    if(airports[index1]->destonations[i] == NULL) {
      continue;
    }
    time = is_connected(airports, airports[index1]->destonations[i], name2, hops - 1);
    if (time >= 0) {
      if (time < smallest_time) {
        smallest_time = time;
        index = i;
      }
    }
  }
  if (smallest_time == FLT_MAX) {
    return -1;
  }
  return smallest_time + airports[index1]->flight_time[index];
}


int main(void) {
  char c;
  bool quit = 0;
  char name[1024] = {0};
  char dest1[1024] = {0};
  char dest2[1024] = {0};
  float time = 0.0f;

  struct Airport_t *airports[MAX_DESTINATIONS] = {NULL};

  printf("** Airports **\n"); // TASK 1: print "** Airports **"
                              // TASK 2: print "Bye" on quitting
  do {
    printf("Command? ");
    scanf(" %c", &c);

    switch (c) {
    case 'q':
      quit = 1;
      printf("Bye\n");
      break;
    case 'a':
      printf("Name? ");
      scanf(" %[^\n]", name);
      add_airport(airports, name);
      break;
    case 'p':
      print_airports(airports);
      break;
    case 'f':
      printf("Name?: ");
      scanf(" %[^\n]", name);
      find_airport(airports, name);
      break;
    case 'd':
      printf("Destination1? ");
      scanf(" %[^\n]", dest1);
      printf("Destination2? ");
      scanf(" %[^\n]", dest2);
      printf("Time? ");
      scanf(" %f", &time);
      add_destination(airports, dest1, dest2, time);
      break;
    case 'r':
      printf("Name? ");
      scanf(" %[^\n]", name);
      remove_airport(airports, name);
      break;
    case 'c':
      printf("Destination1? ");
      scanf(" %[^\n]", dest1);
      printf("Destination2? ");
      scanf(" %[^\n]", dest2);
      // if (strcmp(dest1, dest2) == 0)  {
      //   printf("Flight time is %2f\n", 0.0f);
      //   break;
      // }
      time = is_connected(airports, dest1, dest2, MAX_DESTINATIONS);
      if (time < 0) {
        printf("Not connected\n");
      } else {
        printf("Flight time is %.2f\n", time);
      }
      break;
    default:
      printf("Unknown command '%c'\n", c);
    }

  } while (!quit);

  for (size_t i = 0; i < MAX_DESTINATIONS; ++i) {
    if(airports[i] != NULL) {
      remove_airport(airports, airports[i]->name);
    }
  }

  return 0;
}
