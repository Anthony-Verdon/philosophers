# Philosophers 

## always sympathic to eat with friends around a table

This project is part of the third circle of projects of the 42 common core. The goal is to solve the dining philosophers problem (https://en.wikipedia.org/wiki/Dining_philosophers_problem).To summarize, there is X Philosophers around a table, and they can think, eat, sleep. When they think, they try to grab forks. When they got 2 forks, they eat, and after eating they sleep, and restart this cycle. The problem is if a philosopher don't eat during a certain time, he died. To simulate this situation, I use threads and mutex. You will find the subject of the project into the repository. My grade : 115/100.

## How to use it

1. Clone it `git clone git@github.com:AnthonyVerdon-42Projects/philosophers.git`.
2. Compile it `make`.
3. Run the program. It take 4 arguments and a fifth optional : 
- the number of philosophers around the table
- the time before they die
- the time they take to eat
- the time they take to sleep
- the number of times they must eat before the simulation end (this one is optional).

Time are in milliseconds

You can also compile with `make bonus`. The goal is the same but this time, each philo is a child process and forks are semaphore.

## Find a bug ?

If you find an undefined behaviour (crash, leaks, ...), please submit an issue or contact me
