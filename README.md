# Process Scheduling Algorithms in C++

This project demonstrates various process scheduling algorithms implemented in C++. The interactive console application allows users to input process details once and then experiment with different scheduling algorithms to understand their behavior and performance.

## Table of Contents

- [Features](#features)
- [Scheduling Algorithms](#scheduling-algorithms)
- [Requirements](#requirements)


## Features

- **Interactive Console Application:**  
  Input process details one time and test multiple scheduling algorithms.

- **Multiple Scheduling Algorithms:**
  - **FCFS (First Come First Serve):** Processes are scheduled in the order of arrival.
  - **SJF (Shortest Job First):** Non-preemptive scheduling that selects the process with the shortest burst time.
  - **Priority Scheduling:** Non-preemptive scheduling that prioritizes processes based on a defined priority (lower numeric value indicates higher priority).
  - **Round Robin (RR):** Processes are given a fixed time quantum; if a process isn’t finished, it cycles to the end of the queue. A simple Gantt chart is also provided.

- **Detailed Results:**  
  Displays a table with process details including PID, arrival time, burst time, completion time, waiting time, and turnaround time.

## Scheduling Algorithms

### First Come First Serve (FCFS)
- **Overview:**  
  Schedules processes in the order they arrive.
- **Metrics:**  
  - Waiting Time = Start Time - Arrival Time  
  - Turnaround Time = Completion Time - Arrival Time

### Shortest Job First (SJF)
- **Overview:**  
  Selects the process with the smallest burst time among those that have arrived.
- **Note:**  
  This implementation is non-preemptive.

### Priority Scheduling
- **Overview:**  
  Chooses the process with the highest priority (i.e., the lowest priority number) among available processes.
- **Note:**  
  This implementation is non-preemptive.

### Round Robin (RR)
- **Overview:**  
  Assigns a fixed time quantum to each process in a cyclic order. If a process isn’t completed within its time quantum, it is added back to the queue.
- **Additional Feature:**  
  Displays a simple Gantt chart for visualization.


