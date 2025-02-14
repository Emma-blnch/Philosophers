<h1 align="center"> 💻 <strong>Philosophers</strong> </h1>

## 🏷️ **About the project**
> [!IMPORTANT]
> 8th project of the 42 cursus ➡️ Level 3

Solve the dining philosophers problem using threads and mutexes.

## 📥 **What I learned**
With this project, I learned:
- [ ] **Resilience** (mistakes are sometimes very subtle).
- [ ] **Analytical thinking** (anticipate conflicts and find solutions to competition problems).
- [ ] Have a **rigorous code**

## ⚙️ **Technical skills I acquired**
- [x] Using threads and synchronizing resources with mutexes
- [x] Preventing deadlocks and data races
- [x] Strict management of shared memory resources
- [x] Use of low-level timing functions (usleep, gettimeofday)

## 📁 **My files**
<ins>Main.c</ins> : My main function which manages the overall orchestration of the simulation. And a function to free everything to avoid thread leaks.

<ins>Init.c</ins> : Initializes the structures needed and prepare all the data to launch the simulation.

<ins>Threads.c</ins> : Implements the main simulation flow by distributing tasks to threads.

<ins>Death.c</ins> : Monitors simulation status to ensure smooth operation.

<ins>Forks.c</ins> : Handles the mutexes on the forks to avoid data race.

<ins>Utils.c</ins> : Centralizes utility functions.
