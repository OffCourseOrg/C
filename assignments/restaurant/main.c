#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SEATS 16
#define MAX_BOOKINGS 10

struct Booking_t {
  int hour;
  char *name;
  int people;
};

int free_seats_available(struct Booking_t *restaurant[], int hour) {
  int free_seats = MAX_SEATS;
  for (size_t i = 0; i < MAX_BOOKINGS; ++i) {
    if (restaurant[i] != NULL && restaurant[i]->hour == hour) {
      free_seats -= restaurant[i]->people;
    }
  }
  return free_seats;
}

void add_booking(struct Booking_t *restaurant[], int hour, char *name, int people) {
  int free_index = -1;

  for (size_t i = 0; i < MAX_BOOKINGS; ++i) {
    if (restaurant[i] == NULL) {
      free_index = i;
      break;
    }
  }

  if (free_seats_available(restaurant, hour) >= people && free_index > -1) {
    restaurant[free_index] = malloc(sizeof(*restaurant[free_index]));
    if (restaurant[free_index] == NULL) {
      fprintf(stderr, "Buy more RAM\n");
      return;
    }
    restaurant[free_index]->name = malloc((strlen(name) + 1) * sizeof(*restaurant[free_index]->name));
    if (restaurant[free_index]->name == NULL) {
      fprintf(stderr, "Buy more RAM\n");
      return;
    }

    restaurant[free_index]->hour = hour;
    strcpy(restaurant[free_index]->name, name);
    restaurant[free_index]->people = people;
    return;
  }

  printf("Could not add reservation\n");
}

void print_restaurant(struct Booking_t *restaurant[]) {
  for (size_t i = 0; i < MAX_BOOKINGS; ++i) {
    if (restaurant[i] != NULL) {
      printf("Name: %s\n", restaurant[i]->name);
      printf(" Hour: %d\n", restaurant[i]->hour);
      printf(" Number of people: %d\n", restaurant[i]->people);
    }
  }
}

int find_booking(struct Booking_t *restaurant[], char *name) {
  for (size_t i = 0; i < MAX_BOOKINGS; ++i) {
    if (restaurant[i] != NULL && strcmp(name, restaurant[i]->name) == 0) {
      return i;
    }
  }
  return -1;
}

void change_booking_hour(struct Booking_t *restaurant[], char *name, int new_hour) {
  int index = find_booking(restaurant, name);
  if (index < 0 || new_hour == restaurant[index]->hour) {
    return;
  }
  if (free_seats_available(restaurant, new_hour) >= restaurant[index]->people) {
    printf("Reseated %s from %d to %d\n", restaurant[index]->name, restaurant[index]->hour, new_hour);
    restaurant[index]->hour = new_hour;
    return;
  }
  printf("Could not resit %s, because at %d there are not enough seats\n", restaurant[index]->name, new_hour);
}

// remove_booking
void remove_booking(struct Booking_t *restaurant[], char *name) {
  int index = find_booking(restaurant, name);
  if (index < 0) {
    return;
  }
  free(restaurant[index]->name);
  restaurant[index]->name = NULL;

  free(restaurant[index]);
  restaurant[index] = NULL;
}
// sort_bookings

void sort_bookings(struct Booking_t *restaurant[]) {
  struct Booking_t *temp;
  for (size_t i = 0; i < MAX_BOOKINGS; ++i) {
    for (size_t j = i; j < MAX_BOOKINGS; ++j) {
      //swap if left one is lower on time or is not NULL
      if (restaurant[j] == NULL) {
        continue;
      }
      if (restaurant[i] == NULL || restaurant[i]->hour > restaurant[j]->hour) {
        temp = restaurant[i];
        restaurant[i] = restaurant[j];
        restaurant[j] = temp;
      }
    }
  }
}

int main(void) {
  char c;
  int quit, hour, people;
  char name[1024];

  struct Booking_t *restaurant[MAX_BOOKINGS] = {NULL};

  printf("Welcome to restaurants booking system\n");

  quit = 0;
  do {
    printf("Command? ");
    scanf(" %c", &c);

    switch (c) {
      case 'q':
        quit = 1;
        break;

      case 'a':
        printf("Hour? ");
        scanf(" %d", &hour);
        printf("Name? ");
        scanf(" %[^\n]", name);
        printf("Number of people? ");
        scanf(" %d", &people);
        add_booking(restaurant, hour, name, people);
        break;

      case 'p':
        print_restaurant(restaurant);
        break;

      case 's':
        printf("Name? ");
        scanf(" %[^\n]", name);
        printf("New hour? ");
        scanf(" %d", &hour);
        change_booking_hour(restaurant, name, hour);
        break;

      case 'r':
        printf("Name? ");
        scanf(" %[^\n]", name);
        remove_booking(restaurant, name);
        break;

      case 'o':
        sort_bookings(restaurant);
        break;

      default:
        printf("Unknown command\n");
    }

  } while (!quit);

  return 0;
}
