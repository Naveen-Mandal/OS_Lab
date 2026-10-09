#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct Process {
    int id, arrival, burst, priority, remaining = 0;
    int completion = 0, turnaround = 0, waiting = 0, response = -1;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> p(n);
    for (int i = 0; i < n; ++i) {
        p[i].id = i + 1;
        cout << "Enter arrival time, burst time and priority for P" << p[i].id
             << " (smaller number = higher priority): ";
        cin >> p[i].arrival >> p[i].burst >> p[i].priority;
        p[i].remaining = p[i].burst;
    }

    int completed = 0, time = 0;
    double totalWaiting = 0, totalTurnaround = 0;
    while (completed < n) {
        int selected = -1;
        for (int i = 0; i < n; ++i) {
            if (p[i].arrival <= time && p[i].remaining > 0 &&
                (selected == -1 || p[i].priority < p[selected].priority ||
                 (p[i].priority == p[selected].priority &&
                  p[i].arrival < p[selected].arrival))) {
                selected = i;
            }
        }
        if (selected == -1) {
            ++time;
            continue;
        }
        if (p[selected].response == -1) p[selected].response = time - p[selected].arrival;
        --p[selected].remaining;
        ++time;
        if (p[selected].remaining == 0) {
            ++completed;
            p[selected].completion = time;
            p[selected].turnaround = time - p[selected].arrival;
            p[selected].waiting = p[selected].turnaround - p[selected].burst;
            totalWaiting += p[selected].waiting;
            totalTurnaround += p[selected].turnaround;
        }
    }

    cout << "\nProcess  AT  BT  P  CT  TAT  WT  RT\n";
    for (const auto& process : p) {
        cout << "P" << process.id << "       " << process.arrival << "   "
             << process.burst << "   " << process.priority << "  "
             << process.completion << "   " << process.turnaround << "    "
             << process.waiting << "   " << process.response << '\n';
    }
    cout << fixed << setprecision(2);
    cout << "\nAverage waiting time: " << totalWaiting / n << '\n';
    cout << "Average turnaround time: " << totalTurnaround / n << '\n';
}
