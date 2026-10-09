#include <algorithm>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct Process {
    int id, arrival, burst, completion, turnaround, waiting, response;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;
    vector<Process> p(n);

    for (int i = 0; i < n; ++i) {
        p[i].id = i + 1;
        cout << "Enter arrival time and burst time for P" << p[i].id << ": ";
        cin >> p[i].arrival >> p[i].burst;
    }

    stable_sort(p.begin(), p.end(), [](const Process& a, const Process& b) {
        return a.arrival < b.arrival;
    });

    int time = 0;
    double totalWaiting = 0, totalTurnaround = 0;
    for (auto& process : p) {
        time = max(time, process.arrival);
        process.response = time - process.arrival;
        time += process.burst;
        process.completion = time;
        process.turnaround = process.completion - process.arrival;
        process.waiting = process.turnaround - process.burst;
        totalWaiting += process.waiting;
        totalTurnaround += process.turnaround;
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
