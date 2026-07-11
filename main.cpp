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
#include <utility>
#include "Task.h"

using json = nlohmann::json;


static const std::pair<std::string, int> commands[] = {{"add", 3}, {"update", 4}, {"delete", 3}, {"mark-in-progress", 3}, {"mark-done", 3}, {"list", 3}};

bool error_checking(int argc, char *argv[]) {
    bool valid_action = false;
    bool valid_specifier;
    int threshold = -1;
    try {

        if (argc < 2) { // didn't specify any command
            throw "Error, unspecified arg. \n";
        }

        if (argc >= 2) {

            // check if action is valid
            std::string action = std::string(argv[1]);
            for (const auto& cmd : commands) {
                if (action == cmd.first) {
                    valid_action = true;
                    threshold = cmd.second;

                }
            }
            if (valid_action == false) {
                throw "Error, illegal arg. \n";
            }

            // check if argc isn't above the allowed amount of specifiers
            if (threshold != -1 && argc > threshold) {
                throw "Error, too many args. \n";
            }

            // check if specifiers is valid

        }
    } catch (const char* msg) {
        std::cout << msg;
    }
    return false;
}

void print_info(int argc, char *argv[]) {
    std::cout << "[DEBUGGING INFORMATION]" << std::endl;
    std::cout << "[ARG COUNT]: " << argc << std::endl;
    for (int i = 0; i < argc; i++) {
        std::cout << "[ARG (" << i << ")]: " << argv[i] << std::endl;
    }
}


int main(int argc, char *argv[]) {

    print_info(argc, argv);

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
