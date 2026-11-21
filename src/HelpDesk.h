#ifndef HelpDesk_H
#define HelpDesk_H

#include <iostream>
#include "TicketQueue.h"
#include "ActionStack.h"
using namespace std;

class HelpDesk {
private:
    TicketQueue queue;
    ActionStack actions;

public:
    void add(string studentName, string category, int minutesNeeded) {
        int id = queue.getNextId();
        queue.add(studentName, category, minutesNeeded);
        actions.push(1, Ticket(id, studentName, category, minutesNeeded), 0);
    }

    void serve() {
        if (queue.isEmpty()) {
            queue.serve();
            return;
        }
        Ticket ticket = queue.getTicketAt(1);
        queue.serve();
        actions.push(2, ticket, 1);
    }

    void print() {
        queue.print();
    }

    void searchId(int id) {
        queue.searchId(id);
    }

    void searchName(string studentName) {
        queue.searchName(studentName);
    }

    void cancel(int id) {
        int position = queue.findPosition(id);
        if (position == -1) {
            cout << "Ticket ID " << id << " not found." << endl;
            return;
        }
        Ticket ticket = queue.getTicketAt(position);
        queue.cancel(id);
        actions.push(3, ticket, position);
        cout << "Ticket cancelled - ID: " << id << endl;
    }

    void undo() {
        if (actions.isEmpty()) {
            cout << "Nothing to undo." << endl;
            return;
        }
        Ticket ticket = actions.peekTicket();
        int position = actions.peekPosition();
        int action = actions.pop();
        if (action == 1) {
            queue.cancel(ticket.getId());
            queue.setNextId(ticket.getId());
            cout << "Undo add - ID: " << ticket.getId() << " removed" << endl;
        } else if (action == 2) {
            queue.insertAt(1, ticket);
            queue.setServedCount(queue.getServedCount() - 1);
            cout << "Undo serve - ID: " << ticket.getId() << " back at the front" << endl;
        } else if (action == 3) {
            queue.insertAt(position, ticket);
            cout << "Undo cancel - ID: " << ticket.getId() << " back at position " << position << endl;
        }
    }

    void load(string fileName) {
        cout << "Cannot load " << fileName << ": load is not written yet (F7)." << endl;
    }

    void save(string fileName) {
        cout << "Cannot save " << fileName << ": save is not written yet (F7)." << endl;
    }
};

#endif
