#include <iostream>
#include "TicketQueue.h"
#include "ActionStack.h"
using namespace std;

int passed = 0;
int failed = 0;

void check(string label, bool result) {
    if (result) {
        cout << "PASS: " << label << endl;
        passed = passed + 1;
    } else {
        cout << "FAIL: " << label << endl;
        failed = failed + 1;
    }
}

int main() {
    // Test 1: empty queue
    cout << "Test 1: empty queue" << endl;
    TicketQueue emptyQueue;
    check("isEmpty", emptyQueue.isEmpty());
    emptyQueue.serve();
    check("serve does nothing", emptyQueue.isEmpty() && emptyQueue.getServedCount() == 0);
    check("search finds nothing", emptyQueue.findPosition(1) == -1);
    check("delete finds nothing", emptyQueue.cancel(1) == false);
    emptyQueue.print();

    // Test 2: queue with one ticket
    cout << endl << "Test 2: queue with one ticket" << endl;
    TicketQueue oneQueue;
    oneQueue.add("Tom Hanks", "Password", 5);
    check("not empty", oneQueue.isEmpty() == false);
    check("ticket 1 at position 1", oneQueue.findPosition(1) == 1);
    check("next id is 2", oneQueue.getNextId() == 2);
    oneQueue.print();
    oneQueue.serve();
    check("empty after serve", oneQueue.isEmpty());
    check("served count is 1", oneQueue.getServedCount() == 1);
    oneQueue.add("Meryl Streep", "Wi-Fi", 15);
    check("add after emptying puts ticket 2 at position 1", oneQueue.findPosition(2) == 1);
    check("delete the only ticket", oneQueue.cancel(2) && oneQueue.isEmpty());

    // Test 3: full queue
    cout << endl << "Test 3: full queue (10 tickets)" << endl;
    TicketQueue fullQueue;
    for (int i = 1; i <= 10; i++) {
        fullQueue.add("Student " + to_string(i), "Wi-Fi", i);
    }
    bool inOrder = true;
    for (int i = 1; i <= 10; i++) {
        if (fullQueue.findPosition(i) != i) {
            inOrder = false;
        }
    }
    check("10 tickets in arrival order", inOrder);
    fullQueue.serve();
    check("serve removes the front ticket", fullQueue.findPosition(1) == -1 && fullQueue.findPosition(2) == 1);
    check("delete the rear ticket", fullQueue.cancel(10) && fullQueue.findPosition(10) == -1);
    fullQueue.add("Student 11", "Wi-Fi", 11);
    check("add after deleting the rear goes to the end", fullQueue.findPosition(11) == 9);

    // Test 4: empty stack
    cout << endl << "Test 4: empty stack" << endl;
    ActionStack emptyStack;
    check("isEmpty", emptyStack.isEmpty());
    check("pop returns -1", emptyStack.pop() == -1);
    check("peekPosition returns -1", emptyStack.peekPosition() == -1);
    check("search finds nothing", emptyStack.search(1) == -1);
    emptyStack.print();

    // Test 5: stack with one action
    cout << endl << "Test 5: stack with one action" << endl;
    ActionStack oneStack;
    oneStack.push(1, Ticket(1, "Tom Hanks", "Password", 5), 1);
    check("not empty", oneStack.isEmpty() == false);
    check("peekTicket gives ticket 1", oneStack.peekTicket().getId() == 1);
    check("peekPosition gives 1", oneStack.peekPosition() == 1);
    check("search finds ticket 1 at the top", oneStack.search(1) == 1);
    check("search finds nothing for ticket 2", oneStack.search(2) == -1);
    oneStack.print();
    check("pop gives action 1", oneStack.pop() == 1);
    check("empty after pop", oneStack.isEmpty());

    // Test 6: full stack
    cout << endl << "Test 6: full stack (1000 actions)" << endl;
    ActionStack fullStack;
    for (int i = 1; i <= 1000; i++) {
        fullStack.push(1, Ticket(i, "Student " + to_string(i), "Wi-Fi", 5), i);
    }
    check("search finds ticket 1000 at the top", fullStack.search(1000) == 1);
    check("search finds ticket 1 at the bottom", fullStack.search(1) == 1000);
    bool reversed = true;
    for (int i = 1000; i >= 1; i--) {
        if (fullStack.peekTicket().getId() != i) {
            reversed = false;
        }
        fullStack.pop();
    }
    check("1000 pops come back in reverse order", reversed);
    check("empty after 1000 pops", fullStack.isEmpty());

    cout << endl << "Passed: " << passed << "  Failed: " << failed << endl;

    return 0;
}
