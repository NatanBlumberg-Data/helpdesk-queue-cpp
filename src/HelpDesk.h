#ifndef HelpDesk_H
#define HelpDesk_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "TicketQueue.h"
#include "ActionStack.h"
using namespace std;

bool isNumber(string text) {
    if (text.size() == 0 || text.size() > 9) {
        return false;
    }
    for (int i = 0; i < (int)text.size(); i++) {
        if (text[i] < '0' || text[i] > '9') {
            return false;
        }
    }
    return true;
}

class HelpDesk {
private:
    TicketQueue queue;
    TicketQueue served;
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
        served.addCSVTicket(ticket.getId(), ticket.getStudentName(), ticket.getCategory(), ticket.getMinutesNeeded());
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
            served.cancel(ticket.getId());
            cout << "Undo serve - ID: " << ticket.getId() << " back at the front" << endl;
        } else if (action == 3) {
            queue.insertAt(position, ticket);
            cout << "Undo cancel - ID: " << ticket.getId() << " back at position " << position << endl;
        }
    }

    void load(string fileName) {
        if (queue.isEmpty() == false) {
            cout << "Load only works when the queue is empty." << endl;
            return;
        }
        ifstream file(fileName);

        if (!file.is_open()) {
            cout << "Error opening file" << endl;
            return;
        }

        string line;

        getline(file, line);

        while (getline(file, line)) {
            stringstream ss(line);

            string idStr;
            string name;
            string category;
            string minutesStr;

            getline(ss, idStr, ',');
            getline(ss, name, ',');
            getline(ss, category, ',');
            getline(ss, minutesStr, ',');

            if (isNumber(idStr) == false || isNumber(minutesStr) == false) {
                continue;
            }

            int id = stoi(idStr);
            int minutes = stoi(minutesStr);

            queue.addCSVTicket(id, name, category, minutes);
        }

        file.close();

        while (actions.isEmpty() == false) {
            actions.pop();
        }

        cout << "Tickets loaded" << endl;
    }

    void save(string fileName) {
        ofstream file(fileName);
        if (!file.is_open()) {
            cout << "Error saving file!" << endl;
            return;
        }

        file << "ID,Student Name,Category,Minutes Needed" << endl;
        queue.saveToFile(file);
        file.close();

        cout << "Tickets saved successfully!" << endl;
    }
};

#endif
