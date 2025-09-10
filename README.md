
# DiningPhilosophers

Dining Philosophers is a classic concurrency problem and a project from the 42 school curriculum. It demonstrates thread synchronization and resource sharing in a multi-threaded environment.

Objective:
Simulate a group of philosophers sitting around a table. Each philosopher must alternate between thinking, eating, and sleeping, using forks (represented by mutexes) shared with their neighbors.

Key Concepts: Concurrency and race conditions
| Thread creation and management (pthread)
| Mutexes and synchronization
| Deadlock prevention
| Precise timing and state management



## Usage

Use the Makefile to compile:
```javascript
make
```

Run the program:
```javascript
./philo <number_of_philosophers> <time_to_die time_to_die> <time_to_die time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]

```
Example input:
```javascript
./philo 200 700 250 250 

```
```javascript
./philo 200 700 250 250 8

```



## Authors

- [@Joana Wardenga](https://www.github.com/YunShenMiao)

