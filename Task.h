#ifndef TASK_H
#define TASK_H

#include <string>

struct Task {
    int id;
    std::string description, status, createdAt, updatedAt;
};

#endif

