# philosophers

[![jaeskim's 42Project Score](https://badge42.herokuapp.com/api/project/cboutier/Philosophers)](https://github.com/JaeSeoKim/badge42)

Validated on November 21st, 2021

100/100 

Solving the Dining Philosophers problem by using multi-threading and mutexes.  
*X philosophers are seating around a circular table.  
There is one fork between each philosopher.  
A philosopher can only eat if he can pick up the two forks adjacent to him.  
*  
If a philosopher doesn't eat before the end of the `time_to_die` parameter, he dies and the programs stops.

Usage:  
`make`  
`./philo time_to_die time_to_eat time_to_sleep [nb_of_time_each_philo_must_eat]`  
last parameter is optional.

Examples:
* ```./philo 1 850 200 200```       ===> the philosopher cannot eat as there is only 1 fork, so he dies
* ```./philo 5 850 200 200```       ===> no philosopher should die
* ```./philo 4 450 200 200```       ===> no philosopher should die.
* * ```./philo 4 450 200 200 7```     ===> no philosopher should die, but the program should stop when each of                                          the 4 philosophers ate at least 7 times each
* ```./philo 4 300 200 300```       ===> a philosopher should die
