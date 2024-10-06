# Operating System Assignments

This repository contains assignments related to operating system concepts. Each assignment addresses specific problems involving concurrency, process synchronization, and system calls. Below is a description of each problem and the corresponding file.

## Assignment 1:

**File**: `bakery_lock.cpp`

### Problem Statement:
Implement your own lock and unlock mechanism (methods) using the Bakery algorithm to prevent race conditions and ensure mutual exclusion. The solution must be efficient, fault-tolerant, and scalable to handle multiple concurrent requests while minimizing the risk of starvation.

Instructions:
- Use C/C++, and do not rely on OS-based locks (e.g., mutexes/semaphores).
- Ensure compatibility with Ubuntu as the demo environment.

---

**File**: `bridge_traffic.cpp`

### Problem Statement:
A small island has a one-lane historic bridge that can hold up to four cars or a combination of one bus and two cars at a time. Two buses cannot be on the bridge at the same time. Implement a mutex synchronization mechanism in a multi-threaded program to control traffic flow and prevent overload on the bridge.

Instructions:
- Use C++ and the pthread library to implement the solution.
- Ensure compatibility with Ubuntu as the demo environment.


## Assignment 2
**File**: `multiplayer_game.cpp`

### Problem Statement:
You are tasked with implementing a multiplayer game where players move around a two-dimensional grid and collect items. The game must support multiple players concurrently, and each player thread handles its movement and item collection. Use a message-passing system between threads to manage movement and score updates. No mutexes or semaphores are allowed, and thread priority may be set based on player performance.

Instructions:
- Use C++ and threads to implement the solution.
- Ensure compatibility with Ubuntu as the demo environment.

---

## Assignment 3

### Problem 1: Process Creation and Matrix Multiplication

**File**: `matrix_multiplication.cpp`

### Problem Statement:
Write a program that creates "n" processes based on a randomly generated number and your roll number. Populate an "n x n" matrix and perform matrix multiplication where each process calculates one row. Save the results in text files and display the final matrix.

---

### Problem 2: Chat Program with Shared Memory

**File**: `chat_system`

### Problem Statement:
Develop a chat program that uses shared memory, fork(), and exec() for communication between clients. Messages will be stored in shared memory, and synchronization issues need to be discussed within the code. You are not allowed to use pipes for communication.

---

### Problem 3: Bash Script for System Administration

**File**: `script.sh`

### Problem Statement:
Implement a bash script to create a user, list installed applications, install Dropbox, set IP configurations, and display system information. The script should use functions, allow input through command-line switches, and verify configurations upon execution.

---
