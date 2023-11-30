# bank-operation-simulate
![Static Badge](https://img.shields.io/badge/c%2Fc%2B%2B-100%25-green)


Using linked list and queue data structure to simulate the operation in bank.

## Introduction
The Bank Simulation Program is a C-based application that utilizes linked lists and queue data structures to simulate the operation of a bank. It models customers arriving at the bank, joining queues, and conducting transactions with tellers. This documentation provides an overview of the code structure, functions, and usage of the program.

## Code Structure
The code is structured as follows:

- **Customer Structure**: Defines the structure for a customer, including customer ID, arrival time, service time, and a pointer to the next customer.

- **Queue Structure**: Defines the structure for a queue, representing a teller's queue, with attributes such as current served time, status (open, close), count of customers, front, and rear pointers.

- **Global Variables**: Includes a global clock to track the overall time progression.

- **Function Definitions**:

  - `initialize`: Initializes a queue.
  - `isempty`: Checks if a queue is empty.
  - `enqueue`: Adds a customer to a queue.
  - `dequeue`: Removes and returns a customer from a queue.
  - `display`: Displays the customers in a queue.
  - `GetShortestQueueId`: Finds the ID of the shortest queue.
  - `getCustomer`: Retrieves a customer from a specific queue.
  - `check_if_remain`: Checks if there are remaining customers in any queue.
  - `main`: The main function that reads input from a file, processes operations (join, open, close), and writes output to another file.

## Usage

The program reads input from a file named "inp.txt" and writes output to "output.txt". The input file specifies the number of tellers and operations, including customer arrivals, queue openings, and closures.

- **Customer Arrival:** Lines starting with a character other than '#' or '@' represent customer arrivals. The format is `customer_id arrival_time service_time`.

- **Queue Closure:** Lines starting with '#' represent queue closures. The format is `# close_teller_id`.

- **Queue Opening:** Lines starting with '@' represent queue openings. The format is `@ open_teller_id`.

## Examples

### Input.txt
```text
4
J3 3 8
J4 4 7
J5 5 6
J6 6 5
J7 7 20
J8 8 20
J9 9 20
J10 10 3
J11 11 20
# 12 2
# 13 3
J14 14 20
J15 15 20
J16 16 20
J17 17 20
J18 18 20
J19 19 20
J20 20 20
J21 21 20
J22 22 20
@ 23 2
# 24 1
J44 25 5
J45 26 5
@ 100 3
J46 101 5
J47 102 5
# 103 2
J27 200 3
# 201 3
J28 202 20
J29 203 20
J30 204 20
J31 205 20
J32 206 20
J33 207 20
J34 208 20
J35 209 20
J36 210 20
```

### Output.txt
```text
J3 11 0
J4 11 1
J5 11 2
J6 11 3
J10 14 3
J7 31 0
J8 31 1
J9 31 2
J11 51 0
J14 51 2
J15 71 0
J16 71 2
J17 91 0
J18 91 2
J46 106 3
J19 111 0
J20 111 2
J47 111 3
J21 131 0
J22 131 3
J44 136 0
J45 141 0
J27 203 0
J28 223 0
J29 243 0
J30 263 0
J31 283 0
J32 303 0
J33 323 0
J34 343 0
J35 363 0
J36 383 0
```

