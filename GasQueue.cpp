#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <vector>
#include <limits>
using namespace std;

const int MAX = 50;

// =========================
// CUSTOMER DATA
// =========================
struct Customer {
    int id;
    string name;
    int priority; 
    // 0 = Regular
    // 1 = Emergency
    // 2 = Authority
};

// =========================
// PRIORITY COMPARATOR
// Lower value = higher priority
// =========================
struct Compare {
    bool operator()(const Customer& a, const Customer& b) const {
        return a.priority > b.priority;
    }
};

// =========================
// GAS QUEUE SYSTEM (OOP)
// =========================
class GasQueueSystem {
private:
    queue<Customer> regularQueue;
    priority_queue<Customer, vector<Customer>, Compare> priorityQueue;
    stack<Customer> historyStack;

    int totalCustomers;
    int idCounter;

    // =========================
    // RECURSIVE DISPLAY HELPERS
    // =========================
    void displayPriorityRecursive(priority_queue<Customer, vector<Customer>, Compare> pq) {
        if (pq.empty()) return;

        Customer c = pq.top();
        pq.pop();

        cout << "ID: " << c.id << " | " << c.name;

        if (c.priority == 1) cout << " (Emergency)";
        else if (c.priority == 2) cout << " (Authority)";

        cout << endl;

        displayPriorityRecursive(pq);
    }

    void displayRegularRecursive(queue<Customer> q) {
        if (q.empty()) return;

        Customer c = q.front();
        q.pop();

        cout << "ID: " << c.id << " | " << c.name << endl;

        displayRegularRecursive(q);
    }

    bool searchRegularByName(queue<Customer> q, const string& name) {
        while (!q.empty()) {
            if (q.front().name == name) return true;
            q.pop();
        }
        return false;
    }

    bool searchPriorityByName(priority_queue<Customer, vector<Customer>, Compare> pq, const string& name) {
        while (!pq.empty()) {
            if (pq.top().name == name) return true;
            pq.pop();
        }
        return false;
    }

    bool searchRegularById(queue<Customer> q, int id) {
        while (!q.empty()) {
            if (q.front().id == id) return true;
            q.pop();
        }
        return false;
    }

    bool searchPriorityById(priority_queue<Customer, vector<Customer>, Compare> pq, int id) {
        while (!pq.empty()) {
            if (pq.top().id == id) return true;
            pq.pop();
        }
        return false;
    }

    void clearInput() {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

public:
    GasQueueSystem() {
        totalCustomers = 0;
        idCounter = 1;
    }

    // =========================
    // ADD CUSTOMER
    // =========================
    void addCustomer() {
        if (totalCustomers >= MAX) {
            cout << "System FULL.\n";
            return;
        }

        Customer c;
        c.id = idCounter++;

        cout << "Enter customer name: ";
        getline(cin, c.name);

        int type;
        cout << "1. Regular\n";
        cout << "2. Priority\n";
        cout << "Choice: ";
        cin >> type;

        if (cin.fail()) {
            clearInput();
            cout << "Invalid input.\n";
            return;
        }

        if (type == 1) {
            c.priority = 0;
            regularQueue.push(c);
            cout << c.name << " added to REGULAR queue.\n";
        }
        else if (type == 2) {
            cout << "Priority Level:\n";
            cout << "1. Emergency\n";
            cout << "2. Authority\n";
            cout << "Choice: ";
            cin >> c.priority;

            if (cin.fail() || (c.priority != 1 && c.priority != 2)) {
                clearInput();
                cout << "Invalid priority level.\n";
                return;
            }

            priorityQueue.push(c);
            cout << c.name << " added to PRIORITY queue.\n";
        }
        else {
            cout << "Invalid type.\n";
            return;
        }

        totalCustomers++;
        clearInput();
    }

    // =========================
    // SERVE CUSTOMER
    // =========================
    void serveCustomer() {
        if (priorityQueue.empty() && regularQueue.empty()) {
            cout << "No customers available.\n";
            return;
        }

        Customer served;

        if (!priorityQueue.empty()) {
            served = priorityQueue.top();
            priorityQueue.pop();
            cout << "Serving PRIORITY customer: " << served.name << endl;
        }
        else {
            served = regularQueue.front();
            regularQueue.pop();
            cout << "Serving REGULAR customer: " << served.name << endl;
        }

        historyStack.push(served);
        totalCustomers--;
    }

    // =========================
    // UNDO LAST SERVE
    // =========================
    void undoLastServe() {
        if (historyStack.empty()) {
            cout << "Nothing to undo.\n";
            return;
        }

        if (totalCustomers >= MAX) {
            cout << "Cannot undo. System full.\n";
            return;
        }

        Customer last = historyStack.top();
        historyStack.pop();

        if (last.priority == 0) {
            regularQueue.push(last);
            cout << last.name << " returned to REGULAR queue.\n";
        } else {
            priorityQueue.push(last);
            cout << last.name << " returned to PRIORITY queue.\n";
        }

        totalCustomers++;
    }

    // =========================
    // DISPLAY QUEUES
    // =========================
    void displayQueues() {
        cout << "\n===== PRIORITY QUEUE =====\n";
        if (priorityQueue.empty()) cout << "Empty\n";
        else displayPriorityRecursive(priorityQueue);

        cout << "\n===== REGULAR QUEUE =====\n";
        if (regularQueue.empty()) cout << "Empty\n";
        else displayRegularRecursive(regularQueue);

        cout << "\nTotal Customers: " << totalCustomers << "/" << MAX << endl;
    }

    // =========================
    // SEARCH CUSTOMER
    // =========================
    void searchCustomer() {
        int option;
        cout << "Search by:\n";
        cout << "1. Name\n";
        cout << "2. ID\n";
        cout << "Choice: ";
        cin >> option;

        if (cin.fail()) {
            clearInput();
            cout << "Invalid input.\n";
            return;
        }

        clearInput();

        if (option == 1) {
            string name;
            cout << "Enter customer name: ";
            getline(cin, name);

            if (searchPriorityByName(priorityQueue, name)) {
                cout << name << " found in PRIORITY queue.\n";
            }
            else if (searchRegularByName(regularQueue, name)) {
                cout << name << " found in REGULAR queue.\n";
            }
            else {
                cout << name << " not found.\n";
            }
        }
        else if (option == 2) {
            int id;
            cout << "Enter customer ID: ";
            cin >> id;

            if (cin.fail()) {
                clearInput();
                cout << "Invalid input.\n";
                return;
            }

            if (searchPriorityById(priorityQueue, id)) {
                cout << "Customer ID " << id << " found in PRIORITY queue.\n";
            }
            else if (searchRegularById(regularQueue, id)) {
                cout << "Customer ID " << id << " found in REGULAR queue.\n";
            }
            else {
                cout << "Customer ID " << id << " not found.\n";
            }

            clearInput();
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    // =========================
    // MAIN MENU
    // =========================
    void run() {
        int choice;

        do {
            cout << "\n===== GASQUEUE SYSTEM =====\n";
            cout << "1. Add Customer\n";
            cout << "2. Serve Customer\n";
            cout << "3. Undo Last Serve\n";
            cout << "4. Display Queues\n";
            cout << "5. Search Customer\n";
            cout << "6. Exit\n";
            cout << "Enter choice: ";
            cin >> choice;

            if (cin.fail()) {
                clearInput();
                cout << "Invalid input.\n";
                continue;
            }

            clearInput();

            switch (choice) {
                case 1: addCustomer(); break;
                case 2: serveCustomer(); break;
                case 3: undoLastServe(); break;
                case 4: displayQueues(); break;
                case 5: searchCustomer(); break;
                case 6: cout << "System terminated.\n"; break;
                default: cout << "Invalid choice.\n";
            }

        } while (choice != 6);
    }
};

// =========================
// MAIN
// =========================
int main() {
    GasQueueSystem system;
    system.run();
    return 0;
}