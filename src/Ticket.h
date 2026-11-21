#ifndef Ticket_H
#define Ticket_H

#include <string>
using namespace std;

class Ticket {
private:
    int id;
    string student_name;
    string category;
    int minutes_needed;

public:
    Ticket(int id, string student_name, string category, int minutes_needed) {
        this->id = id;
        this->student_name = student_name;
        this->category = category;
        this->minutes_needed = minutes_needed;
    }
    int getId() const {
        return id;
    }
    string getStudentName() const {
        return student_name;
    }
    string getCategory() const {
        return category;
    }
    int getMinutesNeeded() const {
        return minutes_needed;
    }
};

#endif
