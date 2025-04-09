# Week 3: Algorithms

This session introduced the fundamentals of algorithms, with a focus on searching, sorting, and Big O notation. We explored how computers solve problems efficiently and how to compare algorithmic performance.

## Problem Set

### Sort  
Analyze and identify sorting algorithms (selection sort, bubble sort, and merge sort) based on the behavior of three compiled sorting programs.

- **Objective:** Examine the sorting programs, determine which algorithm each uses by observing how they operate, and explain your reasoning. Record your findings in `answers.txt` within the `sort` folder.

### Tideman
Implements Tideman's ranked pairs voting method to determine the winner of an election based on voters' preferences.

- **Objective:** Collect ranked votes, build a graph of candidate preferences, lock in pairs without creating cycles, and determine the election winner.

### Plurality
Simulates a simple plurality election where each voter votes for one candidate, and the candidate with the most votes wins.

- **Objective:** Tally votes and print the name(s) of the candidate(s) with the most votes.

### Runoff
Implements a runoff election where voters rank candidates in order of preference. The election continues in rounds until a winner is determined.

- **Objective:** Eliminate the candidate(s) with the fewest votes in each round and redistribute votes until one candidate has a majority.

## Files

- `/sort/`
- `tideman.c`
- `plurality.c`
- `runoff.c`
- `/submissions/` – Screenshots and links of CS50 check/submit result
