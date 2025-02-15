#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;


struct Process {
    int pid;            
    int arrivalTime;    
    int burstTime;      
    int priority;       
    int completionTime; 
    int waitingTime;    
    int turnaroundTime; 
};


void printResults(const vector<Process>& processes) {

    vector<Process> proc = processes;
    sort(proc.begin(), proc.end(), [](const Process &a, const Process &b) {
        return a.pid < b.pid;
    });
    cout << "\nPID\tArrival\tBurst\tCompletion\tWaiting\tTurnaround\n";
    for (const auto& p : proc) {
        cout << p.pid << "\t" << p.arrivalTime << "\t" << p.burstTime << "\t" 
             << p.completionTime << "\t\t" << p.waitingTime << "\t" << p.turnaroundTime << "\n";
    }
    cout << endl;
}

// First Come First Serve (FCFS) Scheduling
void fcfsScheduling(const vector<Process>& processes) {
  
    vector<Process> proc = processes;
    // Sort by arrival time
    sort(proc.begin(), proc.end(), [](const Process &a, const Process &b) {
        return a.arrivalTime < b.arrivalTime;
    });
    
    int time = 0;
    for (auto &p : proc) {
        if (time < p.arrivalTime)
            time = p.arrivalTime;
        p.waitingTime = time - p.arrivalTime;
        time += p.burstTime;
        p.completionTime = time;
        p.turnaroundTime = p.completionTime - p.arrivalTime;
    }
    
    cout << "\n--- FCFS Scheduling ---\n";
    printResults(proc);
}

// Non-preemptive Shortest Job First (SJF) Scheduling
void sjfScheduling(const vector<Process>& processes) {
    vector<Process> proc = processes;
    int n = proc.size();
    vector<bool> completed(n, false);
    int completedCount = 0;
    int time = 0;
    
    while (completedCount < n) {
        int idx = -1;
        int minBurst = 1e9;
        for (int i = 0; i < n; i++) {
            if (!completed[i] && proc[i].arrivalTime <= time && proc[i].burstTime < minBurst) {
                minBurst = proc[i].burstTime;
                idx = i;
            }
        }
        if (idx == -1) { // No process has arrived yet
            time++;
        } else {
            proc[idx].waitingTime = time - proc[idx].arrivalTime;
            time += proc[idx].burstTime;
            proc[idx].completionTime = time;
            proc[idx].turnaroundTime = proc[idx].completionTime - proc[idx].arrivalTime;
            completed[idx] = true;
            completedCount++;
        }
    }
    
    cout << "\n--- Non-Preemptive SJF Scheduling ---\n";
    printResults(proc);
}

// Non-preemptive Priority Scheduling
void priorityScheduling(const vector<Process>& processes) {
    vector<Process> proc = processes;
    int n = proc.size();
    vector<bool> completed(n, false);
    int completedCount = 0;
    int time = 0;
    
    while (completedCount < n) {
        int idx = -1;
        int highestPriority = 1e9; // Assuming lower value means higher priority
        for (int i = 0; i < n; i++) {
            if (!completed[i] && proc[i].arrivalTime <= time && proc[i].priority < highestPriority) {
                highestPriority = proc[i].priority;
                idx = i;
            }
        }
        if (idx == -1) { // No process available to execute
            time++;
        } else {
            proc[idx].waitingTime = time - proc[idx].arrivalTime;
            time += proc[idx].burstTime;
            proc[idx].completionTime = time;
            proc[idx].turnaroundTime = proc[idx].completionTime - proc[idx].arrivalTime;
            completed[idx] = true;
            completedCount++;
        }
    }
    
    cout << "\n--- Non-Preemptive Priority Scheduling ---\n";
    printResults(proc);
}

// Round Robin Scheduling
void roundRobinScheduling(const vector<Process>& processes, int quantum) {
    vector<Process> proc = processes;
    int n = proc.size();
    vector<int> remainingTime(n);
    for (int i = 0; i < n; i++) {
        remainingTime[i] = proc[i].burstTime;
    }
    
    int time = 0;
    queue<int> q;
    vector<bool> added(n, false);
    
    // Enqueue all processes that have arrived at time 0
    for (int i = 0; i < n; i++) {
        if (proc[i].arrivalTime <= time) {
            q.push(i);
            added[i] = true;
        }
    }
    // If no process has arrived at time 0, jump to the earliest arrival time
    if (q.empty()) {
        int earliest = 1e9, idx = -1;
        for (int i = 0; i < n; i++) {
            if (proc[i].arrivalTime < earliest) {
                earliest = proc[i].arrivalTime;
                idx = i;
            }
        }
        time = proc[idx].arrivalTime;
        q.push(idx);
        added[idx] = true;
    }

    vector<pair<int, int>> ganttChart; // pair<process id, start time>
    
    while (!q.empty()) {
        int idx = q.front();
        q.pop();
        
        // Record the start time for this process in the Gantt Chart
        ganttChart.push_back({proc[idx].pid, time});
        
        if (remainingTime[idx] > quantum) {
            remainingTime[idx] -= quantum;
            time += quantum;
        } else {
            time += remainingTime[idx];
            remainingTime[idx] = 0;
            proc[idx].completionTime = time;
            proc[idx].turnaroundTime = proc[idx].completionTime - proc[idx].arrivalTime;
            proc[idx].waitingTime = proc[idx].turnaroundTime - proc[idx].burstTime;
        }

        for (int i = 0; i < n; i++) {
            if (!added[i] && proc[i].arrivalTime <= time) {
                q.push(i);
                added[i] = true;
            }
        }
        // If the current process is not finished, push it back into the queue
        if (remainingTime[idx] > 0)
            q.push(idx);
        
        // If the queue is empty but there are still processes that haven't arrived, add the next process.
        if (q.empty()) {
            for (int i = 0; i < n; i++) {
                if (!added[i]) {
                    q.push(i);
                    added[i] = true;
                    if (time < proc[i].arrivalTime)
                        time = proc[i].arrivalTime;
                    break;
                }
            }
        }
    }
    
    cout << "\n--- Round Robin Scheduling (Quantum = " << quantum << ") ---\n";

    cout << "\nGantt Chart:\n";
    for (const auto &entry : ganttChart) {
        cout << "[P" << entry.first << " @ " << entry.second << "] ";
    }
    cout << "\n";
    
    printResults(proc);
}

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    
    vector<Process> processes(n);
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "\nEnter details for Process " << processes[i].pid << ":\n";
        cout << "Arrival Time: ";
        cin >> processes[i].arrivalTime;
        cout << "Burst Time: ";
        cin >> processes[i].burstTime;
        cout << "Priority (lower value => higher priority): ";
        cin >> processes[i].priority;
    }
    
    char choice;
    do {
        int option;
        cout << "\nSelect Scheduling Algorithm:\n";
        cout << "1. First Come First Serve (FCFS)\n";
        cout << "2. Shortest Job First (SJF)\n";
        cout << "3. Priority Scheduling\n";
        cout << "4. Round Robin\n";
        cout << "Enter choice (1-4): ";
        cin >> option;
    
        switch (option) {
            case 1:
                fcfsScheduling(processes);
                break;
            case 2:
                sjfScheduling(processes);
                break;
            case 3:
                priorityScheduling(processes);
                break;
            case 4: {
                int quantum;
                cout << "Enter Time Quantum: ";
                cin >> quantum;
                roundRobinScheduling(processes, quantum);
                break;
            }
            default:
                cout << "Invalid choice!" << endl;
        }
        
        cout << "Do you want to try another scheduling algorithm? (Y/N): ";
        cin >> choice;
    } while (choice == 'Y' || choice == 'y');
    
    return 0;
}
