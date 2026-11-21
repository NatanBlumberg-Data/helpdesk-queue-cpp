#include <iostream>
#include "HelpDesk.h"

using namespace std;

int main() {
    HelpDesk desk;

    cout << "Test 1: empty queue" << endl;
    desk.searchId(1);
    desk.searchName("Person 1");
    desk.cancel(1);
    desk.undo();

    cout << "\nTest 2: search id and search name" << endl;
    desk.add("Person 1", "Cat 1", 12);
    desk.add("Person 2", "Cat 2", 35);
    desk.add("Person 3", "Cat 3", 45);
    desk.add("Person 2", "Cat 4", 20);
    desk.add("Person 5", "Cat 5", 10);
    desk.searchId(3);
    desk.searchId(9);
    desk.searchName("Person 2");
    desk.searchName("Person 9");

    cout << "\nTest 3: cancel at the front, middle and rear" << endl;
    desk.cancel(1);
    desk.cancel(3);
    desk.cancel(5);
    desk.cancel(9);
    desk.print();

    cout << "\nTest 4: undo the three cancels" << endl;
    desk.undo();
    desk.undo();
    desk.undo();
    desk.print();

    cout << "\nTest 5: three undos in a row (add, serve, cancel)" << endl;
    desk.add("Person 6", "Cat 6", 15);
    desk.serve();
    desk.cancel(3);
    desk.undo();
    desk.undo();
    desk.undo();
    desk.print();

    return 0;
}
