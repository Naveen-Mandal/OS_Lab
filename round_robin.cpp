#include <algorithm>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Process {
    int id, arrival, burst, remaining = 0;
    int completion = 0, turnaround = 0, waiting = 0, response = -1;
};

int main() {
    int n, quantum;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> p(n);
    for (int i = 0; i < n; ++i) {
        p[i].id = i + 1;
        cout << "Enter arrival time and burst time for P" << p[i].id << ": ";
        cin >> p[i].arrival >> p[i].burst;
        p[i].remaining = p[i].burst;
    }
    cout << "Enter time quantum: ";
    cin >> quantum;

    vector<int> order(n);
    for (int i = 0; i < n; ++i) order[i] = i;
    sort(order.begin(), order.end(), [&](int a, int b) {
        return p[a].arrival < p[b].arrival;
    });

    queue<int> ready;
    int next = 0, completed = 0, time = 0;
    double totalWaiting = 0, totalTurnaround = 0;
    while (completed < n) {
        if (ready.empty() && next < n && time < p[order[next]].arrival) {
            time = p[order[next]].arrival;
        }
        while (next < n && p[order[next]].arrival <= time) {
            ready.push(order[next++]);
        }
        if (ready.empty()) continue;

        int i = ready.front();
        ready.pop();
        if (p[i].response == -1) p[i].response = time - p[i].arrival;
        int runTime = min(quantum, p[i].remaining);
        time += runTime;
        p[i].remaining -= runTime;

        while (next < n && p[order[next]].arrival <= time) {
            ready.push(order[next++]);
        }
        if (p[i].remaining > 0) {
            ready.push(i);
        } else {
            ++completed;
            p[i].completion = time;
            p[i].turnaround = time - p[i].arrival;
            p[i].waiting = p[i].turnaround - p[i].burst;
            totalWaiting += p[i].waiting;
            totalTurnaround += p[i].turnaround;
        }
    }

    cout << "\nProcess  AT  BT  CT  TAT  WT  RT\n";
    for (const auto& process : p) {
        cout << "P" << process.id << "       " << process.arrival << "   "
             << process.burst << "   " << process.completion << "   "
             << process.turnaround << "    " << process.waiting << "   "
             << process.response << '\n';
    }
    cout << fixed << setprecision(2);
    cout << "\nAverage waiting time: " << totalWaiting / n << '\n';
    cout << "Average turnaround time: " << totalTurnaround / n << '\n';
}
