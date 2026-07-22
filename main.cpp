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

/* Review Diff: data["tasks"] vs data.at("tasks") error handling
 *
 *
 */
#include <iostream>
#include <fstream>
#include <ostream>
#include <string>
#include <ctime>
#include <stdio.h>
#include <system_error>
#include <type_traits>
#include <utility>
#include <unordered_map>
#include <nlohmann/json.hpp>
#include <ctime>

using json = nlohmann::ordered_json;

json load_tasks(const std::string& filepath) { // load the json file
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

void save_tasks(const std::string& filepath, const json& data) {
    std::ofstream out(filepath);
    out << data.dump(4);
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


bool validate_specifier(SpecifierType type, const std::string& specifier) { // will be used to check if the sub-specifier is present or not (might not be needed?)
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

    // TODO:

    print_info(argc, argv); // debugging information
    if (error_checking(argc, argv)) { // if passes error checking, good to go

        std::string action = std::string(argv[1]);
        std::string specifier = (argc > 2) ? std::string(argv[2]) : std::string();
        int id_specifier = -1;
        json data = load_tasks("task-tracking.json");
        const Command* cmd = find_command(action);

        if (cmd->expected_specifier == SpecifierType::TASK_ID && argc > 2) {
            try {
                id_specifier = std::stoi(argv[2]);
            } catch (...) {
                std::cerr << "Error: task ID must be a number. \n";
                return 1;
            }
        }


        if (action == "add") { // expects string description

            std::cout << "[SUCCESS]: Task added successfully (ID: " << ")" << std::endl;
            return 0;
        }
        if (action == "update") { // expects id, and string description
            if (argc < 4) {
                std::cerr << "Error: update requires an ID and a description. \n";
            }
            std::string new_description = argv[3];

            time_t timestamp;
            time(&timestamp);
            bool found = false;
            for (auto& task: data["tasks"]) {
                if (task.at("id").is_null()) continue;
                if (task.at("id").get<int>() == id_specifier) {
                    task["description"] = new_description;
                    task["updatedAt"] = ctime(&timestamp);
                    found = true;
                    break;
                }
            }
            if (!found) {
                std::cerr << "Error: no task with ID " << id_specifier << "\n.";
                return 1;
            }
            save_tasks("task-tracking.json", data);
            std::cout << "[SUCCESS]: Task " << id_specifier << " updated.\n";
        }

        if (action == "mark-in-progress" || action == "mark-done") {
            time_t timestamp;
            time(&timestamp);
            for (auto& task: data["tasks"]) {
                if (task.at("id").is_null()) continue;
                if (task.at("id").get<int>() == id_specifier) {
                    task["status"] = action;
                    task["updatedAt"] = ctime(&timestamp);
                }
            }
            // TODO: add success checking
        }
        if  (action == "delete" && argc > 2) { // both expect id
            try {
                id_specifier = std::stoi(argv[2]);
            } catch (const std::invalid_argument&) {
                std::cerr << "Error: task ID must be a number. \n" << std::endl;
                return 1;
            } catch (const std::out_of_range&) {
                std::cerr << "Error: task ID out of range. \n" << std::endl;
                return 1;
            }
            auto& tasks = data["tasks"];
            bool found = false;
            for (auto it = tasks.begin(); it != tasks.end(); ++it) {
                if (it->at("id").is_null()) continue;  // skip bad entries to avoid err
                if (it->at("id").get<int>() == id_specifier) {
                    it = tasks.erase(it);
                    found = true;
                    break;
                }
            }
            if (!found) {
                std::cerr << "Error: no task with ID " << id_specifier << "\n.";
                return 1;
            }
            save_tasks("task-tracking.json", data);
            std::cout << "[SUCCESS]: Task " << id_specifier << " deleted. \n" << std::endl;
        }
        if (action == "list") {
            if (argc > 2) { // sub-specifier exists, match and loop
                for (const auto& task: data.at("tasks")) {
                    if (task.at("status").get<std::string>() != specifier) continue;
                    std::cout << "[" << task.at("id") << "] "
                    << task.at("description").get<std::string>() << std::endl;
                }
            } else { // no specifier, default behaviour == just list all
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
