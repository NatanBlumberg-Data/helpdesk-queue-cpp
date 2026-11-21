#ifndef HelpDesk_H
#define HelpDesk_H

#include <iostream>
#include <string>
#include "Ticket.h"
#include "TicketQueue.h"
#include "ActionStack.h"
using namespace std;

#define ADD_ACTION 1
#define SERVE_ACTION 2
#define CANCEL_ACTION 3

class HelpDesk {
private:
    TicketQueue queue;
    ActionStack actions;

public:
    void add(string student_name, string category, int minutes_needed) {
        int id = queue.getNextId();
        queue.add(student_name, category, minutes_needed);
        actions.push(ADD_ACTION, Ticket(id, student_name, category, minutes_needed), 0);
    }

    void serve() {
        if (queue.isEmpty()) {
            queue.serve();
            return;
        }
        Ticket ticket = queue.getTicketAt(1);
        queue.serve();
        actions.push(SERVE_ACTION, ticket, 1);
    }

    void print() {
        queue.print();
    }

    void searchId(int id) {
        queue.searchId(id);
    }

    void searchName(string student_name) {
        queue.searchName(student_name);
    }

    void cancel(int id) {
        int position = queue.findPosition(id);
        if (position == -1) {
            cout << "Ticket ID " << id << " not found." << endl;
            return;
        }
        Ticket ticket = queue.getTicketAt(position);
        queue.cancel(id);
        actions.push(CANCEL_ACTION, ticket, position);
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

        if (action == ADD_ACTION) {
            queue.cancel(ticket.getId());
            queue.setNextId(ticket.getId());
            cout << "Undo add - ID: " << ticket.getId() << " removed" << endl;
        } else if (action == SERVE_ACTION) {
            queue.insertAt(1, ticket);
            queue.setServedCount(queue.getServedCount() - 1);
            cout << "Undo serve - ID: " << ticket.getId() << " back at the front" << endl;
        } else if (action == CANCEL_ACTION) {
            queue.insertAt(position, ticket);
            cout << "Undo cancel - ID: " << ticket.getId() << " back at position " << position << endl;
        }
    }
};

#endif
