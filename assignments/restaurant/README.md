## Restaurant booking system
In this exercise you will have to develop a system that tracks table booking in a restaurant. The booking will have time, when the table is booked, persons who booked name and number of people coming in that booking.

### Task 1
Create function `int main(void)` that on start says `Welcome to restaurants booking system` asks for command and exists when `q` is entered

Example:
```
Welcome to restaurants booking system
Command? q
```
You should pass test *case 0*

### Task 2
Create structure `struct Booking_t` that contains: 

- `int hour` which stores the day when the booking is made
- `char *name` which stores name of the person who booked the table
- `int people` which stores number of people joining in this booking

Declare array called `bookings` in `main` function that has size of `MAX_BOOKINGS` contains pointers to `struct Booking_t`

Also create two defines:
```
#define MAX_SEATS 16
#define MAX_BOOKINGS 10
```
that show maximum available seats in the restaurant and maximum bookings that `bookings` array can hold

Create function `void print_bookings(struct Booking_t *bookings[])` that prints all non-NULL entrances in bookings.

Add command `p` to call `print_bookings` function.

Example:
```
Welcome to restaurants booking system
Command? p
Command? q
```
You should pass all previous tests and test *case 1*

### Task 3
Write function `void add_booking(struct Booking_t *bookings[], int hour, char *name, int people)` that add entrance to `bookings` array containing hour, name and number of people.

You are supposed to check if the restaurant can seat that many people, before adding entrance to the array. You may assume that all people who are booking a table have different name. 

Add command `a` to call `add_booking` function.

Example:
```
Welcome to restaurants booking system
Command? a
Hour? 15
Name? Frodo Baggins
Number of people? 4
Command? p
Name: Frodo Baggins
 Hour: 15
 Number of people: 4
Command? a
Hour? 15
Name? Thorin Oakenshield
Number of people? 13
Could not add reservation
Command? p
Name: Frodo Baggins
 Hour: 15
 Number of people: 4
Command? q
```
You should pass all previous tests and tests *case 2* and *case 3* and *case 4*

### Task 4
Write function `void change_booking_hour(struct Booking_t *bookings[], char *name, int new_hour)`  that allows person who made booking to change bookings hour.

If there is not enough space to sit all guests in the new time slot message `Could not resit <name>, because at <new time> there are not enough seats` should be printed.

Add command `s` that calls `change_booking_hour` function.

Example:
```
Welcome to restaurants booking system
Command? a
Hour? 8
Name? Hermione Granger
Number of people? 3
Command? p
Name: Hermione Granger
 Hour: 8
 Number of people: 3
Command? s
Name? Hermione Granger
New hour? 12
Reseated Hermione Granger from 8 to 12
Command? p
Name: Hermione Granger
 Hour: 12
 Number of people: 3
Command? q
```

You should pass all previous tests and tests *case 5* and *case 6*

### Task 5
Write function `void remove_booking(struct Booking_t *bookings[], char *name)` that removes booking from a list based on the persons who booked name.

Add command `r` that calls `remove_booking`

Example:
```
Welcome to restaurants booking system
Command? a
Hour? 6
Name? Aragorn
Number of people? 3
Command? a
Hour? 12
Name? Pipin
Number of people? 4
Command? p
Name: Aragorn
 Hour: 6
 Number of people: 3
Name: Pipin
 Hour: 12
 Number of people: 4
Command? r
Name? Pipin
Command? p
Name: Aragorn
 Hour: 6
 Number of people: 3
Command? q
```

You should pass all previous tests and test *case 7*

### Task 6
Wire function `void sort_bookings(struct Booking_t *bookings[])` that sorts all bookings in the array based on the time (the earliest ones come first). The empty slots of the array should be at the back.

Add command `o` that calls `sort_bookings`

Example:
```
Welcome to restaurants booking system
Command? a
Hour? 14
Name? Gendalf
Number of people? 1
Command? a
Hour? 7
Name? Radagast
Number of people? 1
Command? a
Hour? 12
Name? Saruman
Number of people? 1
Command? a
Hour? 11
Name? Alatar and Pallando
Number of people? 2
Command? p
Name: Gendalf
 Hour: 14
 Number of people: 1
Name: Radagast
 Hour: 7
 Number of people: 1
Name: Saruman
 Hour: 12
 Number of people: 1
Name: Alatar and Pallando
 Hour: 11
 Number of people: 2
Command? o
Command? p
Name: Radagast
 Hour: 7
 Number of people: 1
Name: Alatar and Pallando
 Hour: 11
 Number of people: 2
Name: Saruman
 Hour: 12
 Number of people: 1
Name: Gendalf
 Hour: 14
 Number of people: 1
Command? q
```
You should pass all previous tests and tests *case 8*, *case 9*, and *case 10*

