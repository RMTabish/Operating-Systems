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
