#include <iostream>
#include <queue>
#include <stack>
#include <string>
using namespace std;

#define MAX 50  // Maximum number of customers allowed

// Customer structure
struct Customer {
    string name;
    int priority; // 0 = regular, 1 = highest, 2 = secondary
};

// Comparator for priority queue
struct Compare {
    bool operator()(Customer a, Customer b) {
        return a.priority > b.priority;
    }
};

// Recursive display for regular queue
void displayRegular(queue<Customer> q) {
    if (q.empty()) return;

    cout << q.front().name << endl;
    q.pop();
    displayRegular(q);
}

// Recursive display for priority queue
void displayPriority(priority_queue<Customer, vector<Customer>, Compare> pq) {
    if (pq.empty()) return;

    Customer c = pq.top();
    cout << c.name << " (Priority: " << c.priority << ")\n";
    pq.pop();
    displayPriority(pq);
}

int main() {

    queue<Customer> regularQueue;
    priority_queue<Customer, vector<Customer>, Compare> priorityQueue;
    stack<Customer> servedStack;

    int totalCustomers = 0; // Track total number of customers

    int choice;

    do {
        cout << "\n===== GASQUEUE SYSTEM =====\n";
        cout << "1. Add Customer\n";
        cout << "2. Distribute Fuel\n";
        cout << "3. Undo Last Serve\n";
        cout << "4. Display Waiting List\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch(choice) {

        case 1: {
            if (totalCustomers >= MAX) {
                cout << "Queue is FULL (Max 100 customers).\n";
                break;
            }

            string name;
            int type;

            cout << "Enter customer name: ";
            cin >> name;

            cout << "Select type:\n";
            cout << "1. Regular\n";
            cout << "2. Priority\n";
            cout << "Enter choice: ";
            cin >> type;

            if (type == 1) {
                regularQueue.push({name, 0});
                totalCustomers++;
                cout << name << " added to REGULAR queue.\n";

            } else if (type == 2) {
                int priority;

                cout << "Enter priority level:\n";
                cout << "1 - Ambulance / Fire Truck\n";
                cout << "2 - Other Authority Vehicles\n";
                cout << "Choice: ";
                cin >> priority;

                if (priority == 1 || priority == 2) {
                    priorityQueue.push({name, priority});
                    totalCustomers++;
                    cout << name << " added to PRIORITY queue.\n";
                } else {
                    cout << "Invalid priority level.\n";
                }

            } else {
                cout << "Invalid type.\n";
            }

            break;
        }

        case 2:
            if (!priorityQueue.empty()) {
                Customer served = priorityQueue.top();
                priorityQueue.pop();

                cout << "Serving PRIORITY: " << served.name << endl;
                servedStack.push(served);
                totalCustomers--;

            } else if (!regularQueue.empty()) {
                Customer served = regularQueue.front();
                regularQueue.pop();

                cout << "Serving REGULAR: " << served.name << endl;
                servedStack.push(served);
                totalCustomers--;

            } else {
                cout << "No customers available.\n";
            }
            break;

        case 3:
            if (!servedStack.empty()) {
                Customer last = servedStack.top();
                servedStack.pop();

                if (totalCustomers >= MAX) {
                    cout << "Cannot undo, queue is full.\n";
                    break;
                }

                if (last.priority == 0) {
                    regularQueue.push(last);
                    cout << last.name << " returned to REGULAR queue.\n";
                } else {
                    priorityQueue.push(last);
                    cout << last.name << " returned to PRIORITY queue.\n";
                }

                totalCustomers++;

            } else {
                cout << "Nothing to undo.\n";
            }
            break;

        case 4:
            cout << "\n--- PRIORITY QUEUE ---\n";
            if (priorityQueue.empty()) {
                cout << "No priority customers.\n";
            } else {
                displayPriority(priorityQueue);
            }

            cout << "\n--- REGULAR QUEUE ---\n";
            if (regularQueue.empty()) {
                cout << "No regular customers.\n";
            } else {
                displayRegular(regularQueue);
            }

            cout << "\nTotal Customers: " << totalCustomers << "/" << MAX << endl;
            break;

        }

    } while (choice != 0);

    cout << "System terminated.\n";
    return 0;
}
