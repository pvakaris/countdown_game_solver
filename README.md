# The Countdown Numbers Game

The Countdown numbers game is specified as follows:

- Players are given six integer numbers and a target integer number
- The six numbers should be combined using the mathematical operators + - * and / in a way that gets as close as possible to the target number.  Each number can only be used at most once, but it is okay not to use a number
- Getting the target number is worth 10 points, getting within 5 of the target is worth 7 points, getting within 10 is worth 5 points.

For instance if the numbers are (100,4,17,9,3,2) and the target is 37, then one way to do this is `(100 / (3 + 2)) + 17`, which would get the full 10 points.

***

# Solving countdown problems

The file `Countdown.h` contains a small class `CountdownSolution` for storing solutions to Countdown numbers problems: a string containg an RPN numeric expression, and an int containing the value that expression evaluates to.

In `Countdown.h`, `solveCountdownProblem` takes a `vector<int>` containing 6 numbers, and a target number; and returns a `CountdownSolution` object containing the solution to the problem that gets as close as possible to the target.

`TestCountdown.cpp` evaluates some Countdown numbers games problems, and check they give the right answer.

***

# How to compile and run

Open the terminal and cd to the directory containing countdown game files:

```
cd PATH_TO_THE_CLONED_DIRECTORY
```

Compile the test file:

```
g++ -std=c++11 -o test TestCountdown.cpp
```

Run tests

```
./test
```

Add more tests to the TestCountdown.cpp file to check other solutions

***

Vakaris Paulavičius

Version 1.0
