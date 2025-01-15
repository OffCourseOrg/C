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

int free_seats_available(struct Booking_t *bookings[], int hour) {
  int free_seats = MAX_SEATS;
  for (size_t i = 0; i < MAX_BOOKINGS; ++i) {
    if (bookings[i] != NULL && bookings[i]->hour == hour) {
      free_seats -= bookings[i]->people;
    }
  }
  return free_seats;
}

void add_booking(struct Booking_t *bookings[], int hour, char *name, int people) {
  int free_index = -1;

  for (size_t i = 0; i < MAX_BOOKINGS; ++i) {
    if (bookings[i] == NULL) {
      free_index = i;
      break;
    }
  }

  if (free_seats_available(bookings, hour) >= people && free_index > -1) {
    bookings[free_index] = malloc(sizeof(*bookings[free_index]));
    if (bookings[free_index] == NULL) {
      fprintf(stderr, "Buy more RAM\n");
      return;
    }
    bookings[free_index]->name = malloc((strlen(name) + 1) * sizeof(*bookings[free_index]->name));
    if (bookings[free_index]->name == NULL) {
      fprintf(stderr, "Buy more RAM\n");
      return;
    }

    bookings[free_index]->hour = hour;
    strcpy(bookings[free_index]->name, name);
    bookings[free_index]->people = people;
    return;
  }

  printf("Could not add reservation\n");
}

void print_bookings(struct Booking_t *bookings[]) {
  for (size_t i = 0; i < MAX_BOOKINGS; ++i) {
    if (bookings[i] != NULL) {
      printf("Name: %s\n", bookings[i]->name);
      printf(" Hour: %d\n", bookings[i]->hour);
      printf(" Number of people: %d\n", bookings[i]->people);
    }
  }
}

int find_booking(struct Booking_t *bookings[], char *name) {
  for (size_t i = 0; i < MAX_BOOKINGS; ++i) {
    if (bookings[i] != NULL && strcmp(name, bookings[i]->name) == 0) {
      return i;
    }
  }
  return -1;
}

void change_booking_hour(struct Booking_t *bookings[], char *name, int new_hour) {
  int index = find_booking(bookings, name);
  if (index < 0 || new_hour == bookings[index]->hour) {
    return;
  }
  if (free_seats_available(bookings, new_hour) >= bookings[index]->people) {
    printf("Reseated %s from %d to %d\n", bookings[index]->name, bookings[index]->hour, new_hour);
    bookings[index]->hour = new_hour;
    return;
  }
  printf("Could not resit %s, because at %d there are not enough seats\n", bookings[index]->name, new_hour);
}

// remove_booking
void remove_booking(struct Booking_t *bookings[], char *name) {
  int index = find_booking(bookings, name);
  if (index < 0) {
    return;
  }
  free(bookings[index]->name);
  bookings[index]->name = NULL;

  free(bookings[index]);
  bookings[index] = NULL;
}
// sort_bookings

void sort_bookings(struct Booking_t *bookings[]) {
  struct Booking_t *temp;
  for (size_t i = 0; i < MAX_BOOKINGS; ++i) {
    for (size_t j = i; j < MAX_BOOKINGS; ++j) {
      //swap if left one is lower on time or is not NULL
      if (bookings[j] == NULL) {
        continue;
      }
      if (bookings[i] == NULL || bookings[i]->hour > bookings[j]->hour) {
        temp = bookings[i];
        bookings[i] = bookings[j];
        bookings[j] = temp;
      }
    }
  }
}

int main(void) {
  char c;
  int quit, hour, people;
  char name[1024];

  struct Booking_t *bookings[MAX_BOOKINGS] = {NULL};

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
        add_booking(bookings, hour, name, people);
        break;

      case 'p':
        print_bookings(bookings);
        break;

      case 's':
        printf("Name? ");
        scanf(" %[^\n]", name);
        printf("New hour? ");
        scanf(" %d", &hour);
        change_booking_hour(bookings, name, hour);
        break;

      case 'r':
        printf("Name? ");
        scanf(" %[^\n]", name);
        remove_booking(bookings, name);
        break;

      case 'o':
        sort_bookings(bookings);
        break;

      default:
        printf("Unknown command\n");
    }

  } while (!quit);

  for (size_t i = 0; i < MAX_BOOKINGS; ++i) {
    if (bookings[i] != NULL) {
      remove_booking(bookings, bookings[i]->name);
    }
  }

  return 0;
}
