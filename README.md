*This project has been created as part of the 42 curriculum by matmagal.*

# Philosophers

## Description

Philosophers is a concurrency project inspired by the classic Dining Philosophers problem.
The goal is to simulate a group of philosophers who alternate between thinking, eating,
and sleeping while sharing a limited number of forks.

This project focuses on thread synchronization, mutex usage, timing, and deadlock avoidance.
It also includes monitoring logic to detect philosopher death and to stop the simulation when
all philosophers have eaten the required number of times.

## Instructions

### Compilation

Build the project with:

```bash
make
```

Useful Makefile targets:

```bash
make clean
make fclean
make re
```

### Execution

Run the program with:

```bash
./philosophers number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

Arguments:

- `number_of_philosophers`: number of philosophers and forks.
- `time_to_die`: time in milliseconds before a philosopher dies without eating.
- `time_to_eat`: time in milliseconds spent eating.
- `time_to_sleep`: time in milliseconds spent sleeping.
- `number_of_times_each_philosopher_must_eat` (optional): if provided, the simulation stops when every philosopher has eaten this many times.

Examples:

```bash
./philosophers 5 800 200 200
./philosophers 5 800 200 200 7
./philosophers 1 800 200 200
```

## Resources

Classic references used while working on the project:

- The 42 Philosophers subject.
- POSIX Threads documentation: https://pubs.opengroup.org/onlinepubs/9699919799/basedefs/pthread.h.html
- `pthread_mutex_lock(3)` manual page.
- `gettimeofday(2)` manual page.
- Dining Philosophers problem overview: https://en.wikipedia.org/wiki/Dining_philosophers_problem

### AI Usage

AI was used to help with code review, debugging guidance, test planning, and drafting this README.
It was also used to summarize behavior observed during runtime tests and to identify timing-sensitive
issues related to thread scheduling and mutex contention.
The project logic, implementation decisions, and final code changes were still made and validated manually.
