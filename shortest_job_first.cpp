#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

struct Process {
    int id, arrival, burst;
    int completion = 0, turnaround = 0, waiting = 0, response = 0;
};

int main() {
    int n;
    cout << "Enter number of processes: ";
    cin >> n;

    vector<Process> processes(n);
    for (int i = 0; i < n; ++i) {
        processes[i].id = i + 1;
        cout << "Enter arrival time and burst time for P" << processes[i].id
             << ": ";
        cin >> processes[i].arrival >> processes[i].burst;
    }

    vector<bool> completed(n, false);
    int finished = 0;
    int time = 0;
    double totalWaiting = 0;
    double totalTurnaround = 0;

    while (finished < n) {
        int selected = -1;

        for (int i = 0; i < n; ++i) {
            if (!completed[i] && processes[i].arrival <= time &&
                (selected == -1 ||
                 processes[i].burst < processes[selected].burst ||
                 (processes[i].burst == processes[selected].burst &&
                  processes[i].arrival < processes[selected].arrival))) {
                selected = i;
            }
        }

        if (selected == -1) {
            ++time;
            continue;
        }

        processes[selected].response = time - processes[selected].arrival;
        time += processes[selected].burst;
        processes[selected].completion = time;
        processes[selected].turnaround =
            processes[selected].completion - processes[selected].arrival;
        processes[selected].waiting =
            processes[selected].turnaround - processes[selected].burst;

        completed[selected] = true;
        ++finished;
        totalWaiting += processes[selected].waiting;
        totalTurnaround += processes[selected].turnaround;
    }

    cout << "\nProcess  AT  BT  CT  TAT  WT  RT\n";
    for (const auto& process : processes) {
        cout << "P" << process.id << "       " << process.arrival << "   "
             << process.burst << "   " << process.completion << "   "
             << process.turnaround << "    " << process.waiting << "   "
             << process.response << '\n';
    }

    cout << fixed << setprecision(2);
    cout << "\nAverage waiting time: " << totalWaiting / n << '\n';
    cout << "Average turnaround time: " << totalTurnaround / n << '\n';
}
