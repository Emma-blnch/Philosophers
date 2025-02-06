Reste à :


faire passer le test "./philo 4 310 200 100" ou un philo doit mourir
revoir quand temps de mort tres court et reste elevee car cense mourir mais personne meurt

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
<ins>Main.c</ins> : My main function which manages the overall orchestration of the simulation.

<ins>Data_init.c</ins> : Initialize the structures needed and prepare all the data to launch the simulation.

<ins>Dinner.c</ins> : Implements the main simulation flow by distributing tasks to threads.

<ins>Monitor.c</ins> : Monitors simulation status to ensure smooth operation.

<ins>Parsing.c</ins> : Prepares and validates parameters for correct simulation configuration.

<ins>Safe_handle.c</ins> : Ensures the security of concurrent operations by encapsulating thread and mutex manipulation.

<ins>Ft_atol.c</ins> : Converts a string in long.

<ins>Get_and_set.c</ins> : Facilitates synchronized access to data shared between threads using setters and getters.

<ins>Synchro_utils.c</ins> : Contains all the function I did to ensure smooth synchro and consistent output.

<ins>Utils.c</ins> : Centralizes utility functions.

<ins>Free_resources.c</ins> : Prevents leaks after simulation has ended.
