//
// Created by Администратор on 08.05.2023.
//

#ifndef DS1_HW1_GROUP_H
#define DS1_HW1_GROUP_H

#include "User.h"
#include "Movie.h"

#include "wet1util.h"

#include "AVL.h"

class User;

struct Node {
    User *user;
    Node* prev;
    Node* next;
    Node(User *user, Node* prev, Node* next) : user(user), prev(prev), next(next) {}
};


class Group {
private:

    Node* first_user = nullptr;
    Node* last_user = nullptr;

    int moviesSeen[5] = {0};

    const int id;
    int num_vip = 0;

    int size = 0;

public:
    Group(int id);
    Group(const Group& toCopy) = default;
    ~Group();

    void addUser(User *u);
    void deleteUserNode(Node *toDelete);
    void watchMovie(Genre genre);

    bool operator<(const Group& toCompare) const;
    bool operator==(const Group& toCompare) const;

    int getId() const;
    int getMoviesSeen(Genre genre) const;
    bool hasVip() const;
};

bool operator>(const Group& g1, const Group& g2);

#endif //DS1_HW1_GROUP_H
