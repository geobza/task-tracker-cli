/* Task Properties
 * id - a unique identifier for the task
 * description - a short description of the task
 * status - the status of the task (todo, in-progress, done)
 * createdAt - the date and time when the task was created
 * updatedAt - the date and time when the task was last updated
 */

/* Commands
 * Add
 * Update
 * Delete
 * Mark In Progress
 * Mark Finished
 * List All Tasks
 * List All Finished Tasks
 * List All Tasks Not Finsihed
 * List All Tasks In Progress
*/

// Main Function --> Handles Input
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <ctime>
#include <stdio.h>
#include "Task.h"

using json = nlohmann::json;


static const std::string commands[] = {"add", "update", "delete", "mark-in-progress", "mark-done", "list"};

bool error_checking(int argc, char *argv[]) {
    try {
        if (argc > 3) {
            throw "Error, too many args. \n";
        }
        if (argc < 2) { // didn't specify any command
            throw "Error, unspecified arg. \n";
        }
        if (argc >= 2) { // check if action + specifier can be used
            std::string action = std::string(argv[1]);
            for (int i = 0; i < sizeof(commands) / sizeof(commands[0]); i++) {
                if (action == commands[i]) {
                    return true;
                }
            }
            throw "Error, illegal arg. \n";
        }
    } catch (const char* msg) {
        std::cout << msg;
    }
    return false;
}


int main(int argc, char *argv[]) {

    if (error_checking(argc, argv)) {

        std::string action = std::string(argv[1]);

        if (action == "add") {

            std::cout << "Task added successfully (ID: " << ")" << std::endl;
            return 0;

        if (action == "update") {

        }
        if (action == "delete") {

        }
        if (action == "mark-in-progress") {

        }
        if (action == "mark-done") {

        }
        if (action == "list") {

        }
        }
    }

    return 0;
}

