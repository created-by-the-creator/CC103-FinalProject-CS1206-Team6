#include <iostream>
#include <string>
#include <queue>
#include <stack>
using namespace std;

#define MAX 50 

struct Customer {
    int id; 
    string name;
    int priority; // 0 = regular, 1 = highest, 2 = secondary
};

struct Compare {
    bool operator()(Customer a, Customer b) {
        return a.priority > b.priority;
    }
};
//
int main() {

    // stores costumer in FIFO order
    queue<Customer> regularQueue; 

    // stores priority costumers and uses the struct Compare rule
    priority_queue<Customer, vector<Customer>, Compare> priorityQueue;  
    
    // stores SERVED costumers and used for UNDO features
    stack<Customer> historyStack; 

    
    int totalCustomers = 0;
    int idCounter = 1;
    int choice;

    do {
        cout << "\n===== GASQUEUE SYSTEM =====\n";
        cout << "1. Add Customer\n";
        cout << "2. Serve Customer\n";
        cout << "3. Undo Last Serve\n";
        cout << "4. Display Queues\n";
        cout << "5. Exit\n";
        cout << "----------------------------\n";
        cout << "Enter choice: ";
        cin >> choice;
        cout << "----------------------------\n";
        cin.ignore();

        
        switch(choice) {

        case 1: {
            if (totalCustomers >= MAX) {
                cout << "System FULL.\n"; //if totalCustomers exceed or equal to MAX value which was initialized to 50 it will print "System FULL"
                break;
            }

            Customer c;
            c.id = idCounter++;

            cout << "----------------------------\n";
            cout << "Enter name: ";
            getline(cin, c.name);
            cout << "----------------------------\n";

            int type;
            cout << "1. Regular\n2. Priority\nChoice: ";
            cin >> type;
            

            if (type == 1) {
                c.priority = 0;
                regularQueue.push(c);
                cout << c.name << " added to REGULAR queue.\n";

            } else if (type == 2) {
                cout << "Priority level:\n";
                cout << "1 - Emergency\n2 - Authority\nChoice: ";
                cin >> c.priority;


                if (c.priority != 1 && c.priority != 2) {
                    cout << "Invalid priority.\n";
                    break;
                }

                priorityQueue.push(c);
                cout << c.name << " added to PRIORITY queue.\n";

            } else {
                cout << "Invalid type.\n";
                break;
            }

            totalCustomers++;
            break;
        }

        case 2: {
            Customer served;

            if (!priorityQueue.empty()) {
                served = priorityQueue.top();
                priorityQueue.pop();
                cout << "Serving PRIORITY: " << served.name << endl;

            } else if (!regularQueue.empty()) {
                served = regularQueue.front();
                regularQueue.pop();
                cout << "Serving REGULAR: " << served.name << endl;

            } else {
                cout << "No customers available.\n";
                break;
            }

            historyStack.push(served);
            totalCustomers--;
            break;
        }

        
        case 3: {
            if (historyStack.empty()) {
                cout << "Nothing to undo.\n";
                break;
            }

            if (totalCustomers >= MAX) {
                cout << "Cannot undo. System full.\n";
                break;
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
            break;
        }

        ///
        case 4: {
            cout << "\n--- PRIORITY QUEUE ---\n";
            priority_queue<Customer, vector<Customer>, Compare> tempPQ = priorityQueue;

            if (tempPQ.empty()) cout << "Empty\n";
            while (!tempPQ.empty()) {
                cout << tempPQ.top().name 
                << " (P" << tempPQ.top().priority << ")\n";
                tempPQ.pop();
            }

            cout << "\n--- REGULAR QUEUE ---\n";
            queue<Customer> tempQ = regularQueue;

            if (tempQ.empty()) cout << "Empty\n";
            while (!tempQ.empty()) {
                cout << tempQ.front().name << endl;
                tempQ.pop();
            }

            cout << "\nTotal: " << totalCustomers << "/" << MAX << endl;
            break;
        }
//💩
        }

    } while (choice != 5);

    cout << "System terminated.\n";
    return 0;
}