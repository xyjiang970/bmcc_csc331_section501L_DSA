/******************************************************
Xin Yu (Jason) Jiang
CSC331 | Section: 501L
Program Assignment 4: Priority Queue
Due Date: Nov. 21st, 2025 at 11:59PM

Program Name: csc331_501L_prog4_jiang.cpp

Program Purpose:
This program implements an interactive ticket scheduling application using an array-based heap to implement a priority queue data structure in C++ (utilizing a user-defined Heap class).
******************************************************/

#include <iostream>
#include <string>
#include <cmath>
#include <cstddef> // provides the definition for NULL

#include "heap331_f25.h"

// Global sequence counter to maintain FIFO order (within same priority level)
int globalSequence = 0;

/*
Determines priority level based on age.

Parameters:
- age: the age of the ticket requester.

Returns: priority value (1 = highest, 3 = lowest).

Priority Rules:
- Children (age < 16): Priority 1 (highest)
- Seniors (age > 64): Priority 2 (middle)
- Others (16 <= age <= 64): Priority 3 (lowest)
*/
int calculatePriority(int age)
{
    if (age < 16)
    {
        return 1; // Children have highest priority
    }
    else if (age > 64)
    {
        return 2; // Seniors have second priority
    }
    else
    {
        return 3; // Others have lowest priority
    }
}

/*
Pads a number with leading zeros to create a fixed-width string.
Crucial for lexicographic (string) comparison to work correctly.
The heap uses string comparison (lexicographic), not numeric comparison:

When compared as strings:
Sequence 1:  "1_1_Alice"
Sequence 2:  "1_2_Bob"
Sequence 10: "1_10_Charlie"
"1_1_Alice" < "1_10_Charlie" < "1_2_Bob" -->  WRONG ORDER!

String comparison is character-by-character:
"1" vs "10" vs "2": The second character matters!
'1' < '2', so "10" comes before "2" lexicographically

Solution with Padding:
Sequence 1:  "1_00001_Alice"
Sequence 2:  "1_00002_Bob"
Sequence 10: "1_00010_Charlie"
"1_00001_Alice" < "1_00002_Bob" < "1_00010_Charlie" --> CORRECT!

Parameters:
- num: number to pad.
- width: desired width of the string.

Returns: string padded with leading zeros.
Example: padWithZeros(42, 5) returns "00042".
*/
std::string padWithZeros(int num, int width)
{
    std::string result = std::to_string(num);
    // Add leading zeros until we reach desired width
    while (result.length() < width)
    {
        result = "0" + result;
    }
    return result;
}

/*
Creates a formatted string for the heap that encodes priority,
sequence, and name in a way that sorts correctly lexicographically.

Parameters:
- priority: priority level (1-3).
- sequence: global sequence number for FCFS ordering.
- name: customer name.

Returns: formatted string in format "P_SSSSS_Name".

Example: "1_00042_Oumy" (Priority 1, sequence 42, name Oumy).
The sequence is padded with zeros to ensure proper lexicographic sorting.
*/
std::string createHeapString(int priority, int sequence, const std::string &name)
{
    // Format: "Priority_SequenceNumber(5digits)_Name"
    std::string result = std::to_string(priority) + "_" + padWithZeros(sequence, 5) + "_" + name;
    return result;
}

/*
Extracts the customer name from the encoded heap string. Parses strings in format "P_SSSSS_Name" and returns "Name".

Parameters:
- heapString: the encoded string from the heap.

Returns: the customer name.
 */
std::string extractNameFromHeapString(const std::string &heapString)
{
    // Find the second underscore (after priority and sequence)
    /*
    Note: size_t is for unsigned integer types used to represent:
    - objects
    - array indices
    - string positions

    Guaranteed to be large enough to hold the size of any object in memory!
    */
    size_t firstUnderscore = heapString.find('_');
    if (firstUnderscore == std::string::npos)
    {
        return heapString; // Fallback if format is unexpected
    }

    size_t secondUnderscore = heapString.find('_', firstUnderscore + 1);
    if (secondUnderscore == std::string::npos)
    {
        return heapString; // Fallback if format is unexpected
    }

    // Extract everything after the second underscore (the name)
    return heapString.substr(secondUnderscore + 1);
}

/*
Parses a ticket request string to extract name and age.

Parameters:
- input: Input string in format "name,age".
- name: Output parameter for parsed name.
- age: Output parameter for parsed age.

Returns: true if parsing successful, false otherwise.
*/
bool parseTicketRequest(const std::string &input, std::string &name, int &age)
{
    // Find the comma separator
    /*
    find() method returns a "size_t" which represents the position/ index
    where the comma was found (0,1,2,...)
    */
    size_t commaPos = input.find(',');

    // If no comma found, invalid format
    if (commaPos == std::string::npos)
    {
        return false;
    }

    // Extract name (everything before comma)
    name = input.substr(0, commaPos);

    // Extract age string (everything after comma)
    std::string ageStr = input.substr(commaPos + 1);

    // Convert age string to integer
    try
    {
        age = std::stoi(ageStr); // string to int
        return true;
    }
    catch (...)
    {
        // If conversion fails
        return false;
    }
}

int main()
{
    // Create the priority queue using the heapType class
    heapType ticketQueue;

    // Variable to store user input
    std::string input;

    // Main loop - continues until "end-of-file" is entered
    while (true)
    {
        // Prompt for transaction
        std::cout << "Enter transaction: ";

        // Read entire line of input
        if (!std::getline(std::cin, input))
        {
            // EOF detected (Ctrl+D on Unix/Linux, Ctrl+Z on Windows)
            break;
        }

        // Skip empty lines
        if (input.empty())
        {
            continue;
        }

        // Check for end-of-file
        if (input == "end-of-file" || input == "end of file" || input == "endoffile" || input == "\"end-of-file\"" || input == "\"end of file\"" || input == "\"endoffile\"")
        {
            break;
        }

        // Process service transaction
        if (input == "service")
        {
            // Check if queue is empty
            if (ticketQueue.empty())
            {
                std::cout << "error: empty" << std::endl;
            }
            else
            {
                // Get the front ticket from the queue
                std::string heapString = ticketQueue.front();

                // Extract the customer name from the encoded string
                std::string name = extractNameFromHeapString(heapString);

                // Remove ticket from queue
                ticketQueue.pop();

                // Display serviced ticket name
                std::cout << name << std::endl;
            }
        }
        // Process new ticket request
        else
        {
            std::string name; // Variable to store parsed name
            int age;          // Variable to store parsed age

            // Parse the ticket request (format: "name,age")
            if (parseTicketRequest(input, name, age))
            {
                // Check if queue is full (maximum 10 tickets)
                if (ticketQueue.full())
                {
                    std::cout << "error: full" << std::endl;
                }
                else
                {
                    // Calculate priority level based on age
                    int priority = calculatePriority(age);

                    // Create the encoded heap string with priority, sequence, and name
                    std::string heapString = createHeapString(priority, globalSequence, name);

                    // Increment global sequence counter for next ticket
                    globalSequence++;

                    // Add ticket to priority queue
                    ticketQueue.push(heapString);

                    // Confirm ticket was queued
                    std::cout << "queued" << std::endl;
                }
            }
        }
    }

    // Get number of tickets remaining in queue
    int remaining = ticketQueue.elementsinheap();

    // Display appropriate message with correct grammar
    if (remaining == 1)
    {
        std::cout << remaining << " ticket remaining" << std::endl;
    }
    else
    {
        std::cout << remaining << " tickets remaining" << std::endl;
    }

    return 0;
}