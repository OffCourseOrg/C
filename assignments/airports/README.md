## Airport assignment
*This task was created by one of TA's just for fun*
In this assigment you will develope airport connection infrastructure.


### Task 1
Create `int main(void)` function that prints `** Airports **`, asks for command and on `q` quits, and prints `Bye`
```
** Airports **
Command? q
Bye
```

### Task 2
Create an array of pointers to `struct Airport_t` of size `MAX_DESTINATIONS`
Then create a function `void add_airport(struct Airport_t *airports[], char *name)` that adds and airport to the array with supplied name.
```
** Airports **
Command? a
Name? schiphol
Command? q
Bye
```

### Task 3
Create `void print_airports(struct Airport_t *airports[])` that prints out all airports added and their destinations, if they exist.
```
** Airports **
Command? a
Name? schiphol
Command? p
Airports:
schiphol
Command? a
Name? Riga
Command? p
Airports:
schiphol
Riga
Command? q
Bye
```

### Task 4
Create a function `int find_airport(struct Airport_t *airports[], char *name)`
which searches by name and returns index where the airport is stored and `-1` if it does not exist. There are no test cases for this, but this function might be useful later.

### Task 5
Create a function `void add_destination(struct Airport_t *airports[], char* destination1, char* destination2, float time)` that accepts airports array, both destinations by name and time how long the flight takes.
Add `d` command, that connects destinations.
```
** Airports **
Command? a
Name? Schiphol
Command? a
Name? Riga
Command? d
Destination1? Riga
Destination2? Schiphol
Time? 3
Command? p
Airports:
Schiphol
 -Riga: 3.00
Riga
 -Schiphol: 3.00
Command? a
Name? Paris
Command? p
Airports:
Schiphol
 -Riga: 3.00
Riga
 -Schiphol: 3.00
Paris
Command? d
Destination1? Riga
Destination2? Rome
Time? 3.5
One of destionations does not exist
Command? q
Bye
```

### Task 6
Create `void remove_airport(struct Airport_t *airports[], char *name)` which finds airport by name and removes it.
Add `r` command to ask for name.
```
** Airports **
Command? a
Name? Riga
Command? a
Name? Schiphol
Command? p
Airports:
Riga
Schiphol
Command? r
Name? Riga
Command? p
Airports:
Schiphol
Command? q
Bye
```

### Task 7
Create function `float is_connected(struct Airport_t *airports[], char *name1, char *name2, int hops)` that accepts airports array, names of both destinations and number of hops. Then it should *recursively* searches if two airports are conneted and if they are you should print out the total flight time.
```
** Airports **
Command? a
Name? Paris
Command? a
Name? Schiphol
Command? a
Name? Rome
Command? c
Destination1? Paris
Destination2? Schiphol
Not connected
Command? d
Destination1? Schiphol
Destination2? Paris
Time? 1.5
Command? d
Destination1? Paris
Destination2? Rome
Time? 2
Command? c
Destination1? Schiphol
Destination2? Rome
Flight time is 3.50
Command? q
Bye
```
#### Hint
Will be added later

