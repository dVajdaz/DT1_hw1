//
// Created by roro1 on 20/05/2023.
//

#ifndef DS1_HW1_NODE_H
#define DS1_HW1_NODE_H

#endif //DS1_HW1_NODE_H


#include "User.h"

class User;

struct userNode {
    User *user;
    userNode *prev;
    userNode *next;

    userNode(User *user, userNode *prev, userNode *next) : user(user), prev(prev), next(next) {}

    userNode() : user(nullptr), prev(nullptr), next(nullptr) {}
};