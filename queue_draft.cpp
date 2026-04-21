#include <iostream>
#include <string>
using namespace std;

#define MAX 100

//  CUSTOMER 
struct Customer {
    string name;
};

//  QUEUE 
struct Queue {
    Customer data[MAX];
    int front, rear;
};

// Initialize
void initQueue(Queue &q) {
    q.front = -1;
    q.rear = -1;
}

// Check if empty
bool isEmpty(Queue q) {
    return (q.front == -1 || q.front > q.rear);
}

// Check if full
bool isFull(Queue q) {
    return (q.rear == MAX - 1);
}

// Enqueue
void enqueue(Queue &q, Customer c) {
    if (isFull(q)) {
        cout << "Queue is full!\n";
        return;
    }

    if (q.front == -1) q.front = 0;

    q.data[++q.rear] = c;
    cout << c.name << " added to queue.\n";
}

// Dequeue
void dequeue(Queue &q) {
    if (isEmpty(q)) {
        cout << "Queue is empty!\n";
        return;
    }

    cout << "Serving: " << q.data[q.front].name << endl;
    q.front++;
}

// Display
void display(Queue q) {
    if (isEmpty(q)) {
        cout << "Queue is empty!\n";
        return;
    }

    cout << "\nCurrent Queue:\n";
    for (int i = q.front; i <= q.rear; i++) {
        cout << i - q.front + 1 << ". " << q.data[i].name << endl;
    }
}

//  MAIN 
int main() {
    Queue q;
    initQueue(q);

    int choice;
    Customer c;

    do {
        cout << "\n=====  QUEUE  =====\n";
        cout << "1. Add Customer\n";
        cout << "2. Serve Customer\n";
        cout << "3. Display Queue\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore(); // fix input issue

        switch (choice) {

        case 1:
            cout << "Enter name: ";
            getline(cin, c.name);
            enqueue(q, c);
            break;

        case 2:
            dequeue(q);
            break;

        case 3:
            display(q);
            break;

        case 4:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice!\n";
        }

    } while (choice != 4);

    return 0;
}