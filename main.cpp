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
//#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <stdio.h>
#include <utility>
#include "Task.h"
#include <unordered_map>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

json load_tasks(const std::string& filepath) {
    std::ifstream in(filepath);
    if (!in.is_open()) {
        json j;
        j["tasks"] = json::array();
        j["last_id"] = 0;
        return j;
    }
    json data;
    try {
        in >> data;
    } catch (const json::parse_error& e) {
        std::cerr << "Failed to parse " << filepath << ": " << e.what() << std::endl;
    }
    return data;
}

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

static const std::unordered_map<std::string, Command> commands = {
    {"add",               {"add", 3, SpecifierType::FREE_TEXT}},
    {"update",            {"update", 4, SpecifierType::TASK_ID}},
    {"delete",            {"delete", 3, SpecifierType::TASK_ID}},
    {"mark-in-progress",  {"mark-in-progress", 3, SpecifierType::TASK_ID}},
    {"mark-done",         {"mark-done", 3, SpecifierType::TASK_ID}},
    {"list",              {"list", 2, SpecifierType::STATUS}},
};


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

const Command* find_command(const std::string& name) {
    auto it = commands.find(name);
    if (it != commands.end()) {
        return &(it->second);
    }
    return nullptr;
}

bool error_checking(int argc, char *argv[]) {;
    int threshold = -1;
    try {

        if (argc == 1) { // didn't specify any command (doesn't work for list)
            std::cout << "Valid Commands: " << std::endl;
            for (const auto& cmd: commands) {
                std::cout << cmd.second.name << std::endl;
            }
            throw "Error, unspecified command. \n";
        }

        if (argc >=2) {

            std::string action = std::string(argv[1]);  // check if action is valid
            const Command* cmd = find_command(action);

            if (cmd == nullptr) {
                throw "Error, illegal action. \n";
            }
            threshold = cmd->argc_threshold;

            if (argc < threshold) {
                throw "Error, unspecified sub-actions. \n";
            }
            if (argc > threshold) {
                throw "Error, too many args. \n";
            }
            return true;
        }
    } catch (const char* msg) {
        std::cout << msg;
    }
    return false;
}



void print_info(int argc, char *argv[]) {
    std::cout << "[DEBUGGING INFORMATION]" << std::endl;
    std::cout << "[ARG COUNT]: " << argc << std::endl;
    std::string action;
    for (int i = 0; i < argc; i++) {
        std::cout << "[ARG (" << i << ")]: " << argv[i] << std::endl;
        if (i == 1) {
            action = std::string(argv[i]);
            auto it = commands.find(action);
            if (it != commands.end()) {
                const Command& cmd = it->second;
                std::cout << "[COMMAND NAME: " << cmd.name << "]" << std::endl;
                std::cout << "[COMMAND ARGC_THRESHOLD: " << cmd.argc_threshold << "]" << std::endl;
                //std::cout << "[COMMAND EXPECTED_SPECIFIER " << cmd.expected_specifier << "]" << std::endl; does not work for now
            }
        }
    }
}


int main(int argc, char *argv[]) {

    print_info(argc, argv);

    if (error_checking(argc, argv)) {

        std::string action = std::string(argv[1]);
        std::string specifier = (argc > 2) ? std::string(argv[2]) : std::string();


        if (action == "add") {

            std::cout << "[SUCCESS]: Task added successfully (ID: " << ")" << std::endl;
            return 0;
        }
        if (action == "update") {


        }
        if (action == "delete") {

        }
        if (action == "mark-in-progress") {

        }
        if (action == "mark-done") {

        }
        if (action == "list") {
            if (argc > 2) { // sub-specifier exists
                if (specifier == "done") {

                }
                if (specifier == "todo") {

                }
                if (specifier == "in-progress") {

                }
            } else { // no specifier, default behaviour == just list all
                json data = load_tasks("task-tracking.json");
                for (const auto& task: data.at("tasks")) {
                    std::cout << "[" << task.at("id") << "] "
                        << task.at("description")
                        << " (" << task.at("status") << ")"
                        << std::endl;
                }
            }
        }
    }
    return 0;
}
