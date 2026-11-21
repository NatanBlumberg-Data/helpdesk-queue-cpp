#include <iostream>
#include "Ticket.h"
#include "TicketQueue.h"
#include "ActionStack.h"

using namespace std;

int main() {
    TicketQueue queue;
    ActionStack stack;

    queue.add("Person 1", "Cat 1", 12);
    queue.add("Person 2", "Cat 2", 35);
    queue.add("Person 3", "Cat 3", 45);

    cout << "\nWaiting tickets:" << endl;
    queue.print();

    cout << "\nServing front ticket..." << endl;
    queue.serve();

    cout << "\nUpdated tickets:" << endl;
    queue.print();

    cout << "\nTesting stack:" << endl;

    stack.push(1);
    stack.push(2);

    cout << "Pop: " << stack.pop() << endl;
    cout << "Pop: " << stack.pop() << endl;

    cout << "Is stack empty? " << boolalpha << stack.isEmpty() << endl;

    return 0;
}