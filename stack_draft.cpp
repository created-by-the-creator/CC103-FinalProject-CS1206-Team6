#include <iostream>
using namespace std;

//Official file draft for GasQueue: Fuel Distribution System

#define MAX 50 //Until 50 ang max

//For Customer Identification
struct Customer 
{
    string name; //deets ng costumer
    string type; //whether they are regular or priority costumer
};

//manual implementation of a stack using an array
class Stack {

//mga infos na di pwedeng ma-access sa labas nitong Stack class
private:
    Customer arr[MAX]; //array na naglalaman ng customers at dito naka-store ang data
    int top; //pinakataas ng stack

//mga infos na pwedeng gamitin sa labas ng class
public:
    Stack() {
        top = -1; //empty
    }

    //check kung empty
    bool isEmpty() {
        return top == -1;
    }

    //check kung full
    bool isFull() {
        return top == MAX - 1; //kapag puno 
    }

    //addition of costumer
    void push(Customer person) {
        if (isFull()) { //pagfull na, di na pwede mag-add
            cout << "Designated Fuel Queues already full. Please try again later.";
            return;
        }

        top++; //move top up
        arr[top] = person; //store yung costumer sa new top position

        cout << "Costumer " << person.name << " added to queue" << endl;   
    }

    //removing the last added customer
    Customer pop () {
        if (isEmpty()) {
            cout << "There is no current queue!\n";
            return Customer{"", ""};
        }

        Customer person = arr[top];
        top--;
        return person;
    }


};



int main () {

    return 0;
}