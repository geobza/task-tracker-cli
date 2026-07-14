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
#include <map>

using json = nlohmann::json;


enum class SpecifierType {
    NONE,
    FREE_TEXT,
    TASK_ID,
    STATUS
};

struct Command {
    std::string name;
    int argc_threshold;
    SpecifierType expected_specifier;
};

/*
static const Command commands[] = {
    {"add", 3, SpecifierType::FREE_TEXT}, // no specifier meaning
    {"update", 4, SpecifierType::TASK_ID}, //
    {"delete", 3, SpecifierType::TASK_ID},
    {"mark-in-progress", 3, SpecifierType::TASK_ID},
    {"mark-done", 3, SpecifierType::TASK_ID},
    {"list", 2, SpecifierType::STATUS}
};
*/

static const std::map<std::string, int> commands = {{"add", 3}, {"update", 4}, {"delete", 3}, {"mark-in-progress", 3}, {"mark-done", 3}, {"list", 2}};


bool validate_specifier(SpecifierType type, const std::string& specifier) {
    switch (type) {
        case SpecifierType::NONE:
            return true;

        case SpecifierType::FREE_TEXT:
            return !specifier.empty();

        case SpecifierType::TASK_ID:
            // would need: is this parseable as a number? does a task with this ID exist?
            return false; // placeholder

        case SpecifierType::STATUS:
            return (specifier == "done" || specifier == "todo" || specifier == "in-progress");
    }
    return false;
}

bool error_checking(int argc, char *argv[]) {
    bool valid_action = false;
    bool valid_specifier;
    int threshold = -1;
    try {

        if (argc == 1) { // didn't specify any command (doesn't work for list)
            std::cout << "Valid Commands: " << std::endl;
            for (const auto& cmd: commands) {
                std::cout << cmd.first << std::endl;
            }
            throw "Error, unspecified command. \n";
        }

        if (argc >=2) {

            std::string action = std::string(argv[1]);  // check if action is valid
            for (const auto& cmd : commands) {
                if (action == cmd.first) {
                    valid_action = true;
                    threshold = cmd.second;

                }
            }
            if (valid_action == false) { // invalid action
                throw "Error, illegal action. \n";
            }
            if (argc < threshold) { // check if specified
                throw "Error, unspecified sub-actions. \n";
            }
            if (threshold != -1 && argc > threshold) { // check if argc isn't above the allowed amount of specifiers
                throw "Error, too many args. \n";
            }
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
        std::string specifier = std::string(argv[2]);


        if (action == "add") {

            std::cout << "[SUCCESS]: Task added successfully (ID: " << ")" << std::endl;
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
            if (argc == 2) { // sub-specifier exists
                if (specifier == "done") {

                }
                if (specifier == "todo") {

                }
                if (specifier == "in-progress") {

                }
            } else { // no specifier, default behaviour == just list all

            }


        }
        }
    }

    return 0;
}
