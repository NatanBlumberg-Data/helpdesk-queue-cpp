# helpdesk-queue-cpp

Stacks and Queues Mini Project: a help desk ticket system built in C++ on our own queue and stack classes.

## The Problem

A university IT help desk gets requests all day, such as password resets, broken printers and Wi-Fi problems. Tickets must be served in the order they arrive, agents must be able to undo their last action, and the manager wants to search, cancel and print tickets at any time.

## Class Design

| Class | File | What it is |
|---|---|---|
| `Ticket` | `src/Ticket.h` | id, student name, category, minutes needed |
| `TicketQueue` | `src/TicketQueue.h` | linked-list queue of waiting tickets; the front ticket is served next |
| `ActionStack` | `src/ActionStack.h` | linked-list stack of actions; the top is the last action |
| `HelpDesk` | `src/HelpDesk.h` | holds one queue and one stack, and records every add, serve and cancel on the stack |

No `std::queue` or `std::stack` is used.

| Command | Queue | Stack |
|---|---|---|
| `add` | enqueue the new ticket at the rear | push the add |
| `serve` | dequeue the front ticket | push the serve with the ticket |
| `print` | walk from the front to the rear and add up the minutes | |
| `search id`, `search name` | walk from the front, adding up the minutes in front of the ticket | |
| `cancel id` | unlink the ticket; the others keep their order | push the cancel with the ticket and its old position |
| `undo` | remove the added ticket, put a served ticket back at the front, or put a cancelled ticket back at its old position | pop the last action |
| `load file`, `save file` | read tickets into the queue, or write the waiting tickets out | |

## Sample Session

```
Help Desk Ticket System
Commands: add, serve, print, search id <id>, search name <name>, cancel <id>,
undo, load <file>, save <file>, simulate <file>, quit
> add
Student name: Tom Hanks
Category: Password
Minutes needed: 5
Ticket added - ID: 1
> add
Student name: Meryl Streep
Category: Wi-Fi
Minutes needed: 15
Ticket added - ID: 2
> add
Student name: Denzel Washington
Category: Printer
Minutes needed: 10
Ticket added - ID: 3
> add
Student name: Viola Davis
Category: Email
Minutes needed: 10
Ticket added - ID: 4
> print
Ticket ID: 1
Student: Tom Hanks
Category: Password
Minutes Needed: 5

Ticket ID: 2
Student: Meryl Streep
Category: Wi-Fi
Minutes Needed: 15

Ticket ID: 3
Student: Denzel Washington
Category: Printer
Minutes Needed: 10

Ticket ID: 4
Student: Viola Davis
Category: Email
Minutes Needed: 10

Total waiting minutes: 40
> search id 3
Ticket ID: 3
Student: Denzel Washington
Position: 3
Estimated wait: 20 minutes
> search name Viola Davis
Ticket ID: 4
Student: Viola Davis
Position: 4
Estimated wait: 30 minutes

> cancel 2
Ticket cancelled - ID: 2
> undo
Undo cancel - ID: 2 back at position 2
> serve
Serving ticket: 1
> undo
Undo serve - ID: 1 back at the front
> undo
Undo add - ID: 4 removed
> print
Ticket ID: 1
Student: Tom Hanks
Category: Password
Minutes Needed: 5

Ticket ID: 2
Student: Meryl Streep
Category: Wi-Fi
Minutes Needed: 15

Ticket ID: 3
Student: Denzel Washington
Category: Printer
Minutes Needed: 10

Total waiting minutes: 30
> simulate data/sample_day.csv
Tickets: 20

Agents: 1
Average wait: 126.75 minutes
Longest wait: 255 minutes

Agents: 2
Average wait: 59 minutes
Longest wait: 125 minutes
> quit
```

## Waiting-Time Results (M4)

`simulate data/sample_day.csv` serves the 20 tickets of the sample day, 270 minutes of work in total. All tickets are in line when the desk opens and are served in file order, each by the agent who is free first. A ticket's wait is the time until an agent starts on it.

| Agents | Average wait | Longest wait |
|---|---|---|
| 1 | 126.75 min | 255 min |
| 2 | 59 min | 125 min |
