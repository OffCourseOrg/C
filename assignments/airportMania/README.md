# Airport Mania

Welcome to the e.t.s.v. Thor Programming & Engineering Challenge practice exam! In this exercise you will develop a flight management system (FMS) that provides information about flights, passengers, and destinations. You will need to combine all the knowledge that you gained throughout the last two quartiles to complete the practice exam. We get you started by providing some parameters beforehand:

```c

#define MAX_FLIGHTS 16
#define MAX_PASSENGERS 440

struct flight_t {
  char *code;
  char *start;
  char *destination;
  int passengers;
};

```

This means that every flight has a flight number, a start location, a destination, and an amount of passengers assigned to it. These CLI (command-line-interface) programs were mostly used back in the day, hence the 8 flight limit. 
If you get stuck with any of the functions, you can decide to use some of the predefined functions provided.

### Task 1
A management system without any UI would be difficult to use, the employees need to know what they're working on at all times. The program should start with sending the following welcome message to the terminal:
```
** Flight Management System **
```
*You should not pass any tests yet.*

### Task 2
The employees use one letter commands to communicate with the FMS, the first command we will implement is the quit-command using the letter 'q'. Please refer to the example output below:
```
** Flight Managment System **
Command? q
* System Closed *
```
*You should pass Test Case 0.*

### Task 3
The next step is to implement the print-command which uses the letter 'p'. This command prints all the flight numbers together with their details, those of course being: the starting location, the destination, and the number of passengers onboard. The program checks against specific output formatting, so strictly follow what is provided in the later tasks (task 5 specifically). Create the function `void printFlights(struct flight_t *flights[])` that implements this command. Since the FMS is still empty for now, we expect the following output:
```
** Flight Managment System **
Command? p
FMS is empty, no flights to be printed.
Command? q
* System Closed *
```
*You should pass Test Cases 0-1.*
### Task 4
Though it seems counterintuitive, it is most sound to implement a find-command before we move over to the add-command. Because we want to avoid adding duplicate flights to the FMS, as a duplicate flight in the system would risk in a plane getting overbooked. The find-command uses the letter 'f' to find flights by their 6 character flight code, implement the command using the function `bool findFlight(struct flight_t *flights[], char* name)` that returns a Boolean value to indicate a flight is present or not.
```
** Flight Managment System **
Command? f
Enter flight code: 68V42
Error: flight not found.
* System Closed *
```
*You should pass Test Cases 0-2.*
### Task 5

Now it is time to start adding the first flights to our FMS. The `struct flight_t` has already been defined, you have to add an array with size `MAX_FLIGHTS` to store these flights inside of your main function. At the start of the program this array should be empty, and thus filled with `NULL` pointers.
The add-command uses the letter 'a' to add flights to the FMS, duplicate flights should never be added for reasons stated earlier in task 4. When trying to add a flight that already exists an error should be thrown. Implement the command by adding the function `void addFlight(struct flight_t *flights[], char* name, char* start, char* destination, int passengers)` to your code. Note that you should not be able to add negative passengers to flight, the following error message should be displayed: *"Error: cannot have negative passengers."*

A lot of the earlier tasks are coming together here, make sure to check if everything works as you expected it to before continuing to the next tasks. You can find an example below:
```
** Flight Managment System **
Command? p
FMS is empty, no flights to be printed.
Command? a
Enter flight code: 42B69
Enter starting location: Syndey
Enter destination: Bangkok
Enter passenger count: 309
Command? a
Enter flight code: YY67L
Enter starting location: Eindhoven
Enter destination: Oslo
Enter passenger count: 137
Command? a
Enter flight code: 42B69
Error: flight already exists.
Command? f
Enter flight code: 43P21
Error: flight not found.
Command? f
Enter flight code: 42B69
Flight found.
Command? p
Flight 42B69 - Syndey -> Bangkok - 309 passengers
Flight YY67L - Eindhoven -> Oslo - 137 passengers
Command? q
* System Closed *
```
*You should pass Test Cases 0-5.*

### Task 6
Great! We are now able to populate the FMS with flights, but this does not mean that our works over. New passengers are still able to buy tickets after the flights have been indexed, and these have to be added to their appropriate flights, whilst at the same time staying within the limits of the aircraft. At the same time, the airline that we are developing this system for is a bit shady, and does not allow for refunds, so we need to account for that too. The employees will use the letter 'b' in the CLI to execute our new buy-command.
Create a function `void buyTicket(struct flight_t *flights[], char* name, int passengers)` to add the newly bought tickets to the flights. An example of the new command can be found below:
```
** Flight Managment System **
Command? a
Enter flight code: 42B69
Enter starting location: Syndey
Enter destination: Bangkok
Enter passenger count: 309
Command? b
Enter additional tickets: -4
Error: the system does not allow refunds.
Command? b
Enter additional tickets: 6
Enter flight code: 42B69
Added 6 tickets to 42B69.
Command? p
Flight 42B69 - Syndey -> Bangkok - 315 passengers
Command? b
Enter additional tickets: 212
Enter flight code: 42B69
Error: flight overbooked, command declined.
Command? p
Flight 42B69 - Syndey -> Bangkok - 315 passengers
Command? q
* System Closed *
```
*You should pass Test Cases 0-8*


### Task 7
Flights that have successfully landed at their destination need to be removed from the FMS. For this we will need to create the remove-command that can be called by the letter 'r' that ask for the flight code and removes it from the FMS. 

Create a function `void removeFlight(struct flight_t *flights[], char* name)` to remove the flight from the FMS. An example of what it should look like can be found below:
```
** Flight Managment System **
Command? p
FMS is empty, no flights to be printed.
Command? a
Enter flight code: 42B69
Enter starting location: Sydney
Enter destination: Bangkok
Enter passenger count: 309
Command? r
Enter flight code: YY67L
Error: flight does not exist.
Command? p
Flight 42B69 - Sydney -> Bangkok - 309 passengers
Command? r
Enter flight code: 42B69
Command? p
FMS is empty, no flights to be printed.
Command? q
* System Closed *
```

*You should pass Test Cases 0-12*

### Task 8
You can imagine that the FMS gets quite messy when it starts filling up. To combat this, the employees have asked to get some way of sorting the flights implemented, preferably by the amount of passengers that are on the flight, if the number of passengers is equal, the fallback option is then to sort by flight code. Your next task is to implement this sort-command that is called by the letter 's'.

Create a function `void sortFlights(struct flight_t *flights[])` to sort the flights in the FMS by the number of passengers assigned to it. An example of the new command can be found below:
```
** Flight Managment System **
Command? p
FMS is empty, no flights to be printed.
Command? a
Enter flight code: 42B69
Enter starting location: Sydney
Enter destination: Bangkok
Enter passenger count: 309
Command? a
Enter flight code: 23LP1
Enter starting location: New York
Enter destination: London
Enter passenger count: 89
Command? a
Enter flight code: 40DT7
Enter starting location: Bratislava
Enter destination: Riga
Enter passenger count: 220
Command? p
Flight 42B69 - Sydney -> Bangkok - 309 passengers
Flight 23LP1 - New York -> London - 89 passengers
Flight 40DT7 - Bratislava -> Riga - 220 passengers
Command? s
Flights sorted.
Command? p
Flight 23LP1 - New York -> London - 89 passengers
Flight 40DT7 - Bratislava -> Riga - 220 passengers
Flight 42B69 - Sydney -> Bangkok - 309 passengers
Command? q
* System Closed *
```
*You should pass Test Cases 0-14*

### Task 9
Finally, when this FMS was used, people could not go to a website to see what transfers they could take to go from one place to another.  Instead, the customers were able to call the to the flight agency to ask this kind of information. However, doing this by hand is a lot of work, especially when the number of transfers going from point A to point B grows. Therefore, the employees at the service desk have asked to have this implemented as the transfer-command that uses the letter 't'. 

Create a function `bool flightTranser(struct flight_t *flights[], char *currentLoc, char *targetLoc, int depth, int maxDepth, int pathIndices[], int *pathLen)` to implement this new command. When a route is possible, the function should return `true` and print how many transfers are necessary, otherwise the function returns `false` and print an appropriate error message is printed and always choose the shortest possible route (in amount of transfers). 
An example of the final command can be found below:
```
** Flight Management System **
Command? p
FMS is empty, no flights to be printed.
Command? a
Enter flight code: 18GB2
Enter starting location: Sydney
Enter destination: Bangkok
Enter passengers: 309
Command? a
Enter flight code: 09PP5
Enter starting location: Bangkok
Enter destination: Istanbul
Enter passengers: 177
Command? a
Enter flight code: 67XD0
Enter starting location: Istanbul
Enter destination: Eindhoven
Enter passengers: 89
Command? t
Enter starting location: Sydney
Enter destination: Stockholm
Error: no possible transfer found.
Command? t 
Enter starting location: Sydney
Enter destination: Eindhoven
3 flights needed: Sydney -> Bangkok -> Istanbul -> Eindhoven.
Command? q
* System Closed *
```

*You should pass all 19 Test Cases*

That's it, you're now done with the practice exam, hopefully you learned something new along the way, and good luck at your exam tomorrow! A possible solution to the exam can be found [here](https://github.com/OffCourseOrg/C/blob/master/assignments/airportMania/main.c)

*The copyright for this practice paper belongs to e.t.s.v. Thor and Gijs Jongenelen.*
