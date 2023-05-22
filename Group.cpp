//
// Created by Администратор on 08.05.2023.
//

#include "Group.h"


Group::Group(int id) : id(id) {}

Group::~Group() {
    while (first_user != nullptr) {
        first_user->user->self_pointer = nullptr;
        first_user->user->group = nullptr;

        for (int i = 0; i < 5; i++) {
            int toAdd = getMoviesSeen(static_cast<Genre>(i)) -
                        first_user->user->getOffset(static_cast<Genre>(i));
            first_user->user->addViews(i, toAdd);

            first_user->user->group_offset[i] = 0;
        }

        deleteUserNode(first_user);
    }
}

//--------------------------Setters--------------------------

void Group::addUser(User *toAdd) {
    userNode *new_user = new userNode();
    new_user->user = toAdd;
    new_user->next = nullptr;

    if (!first_user) {
        new_user->prev = nullptr;
        first_user = new_user;
    } else if (last_user) {
        last_user->next = new_user;
        new_user->prev = last_user;
    }

    last_user = new_user;
    toAdd->self_pointer = new_user;

    if (new_user->user->isVip())
        num_vip++;

    for (int current = 0; current < 5; current++)
        totalViews[current] += toAdd->getSoloSeen(static_cast<Genre>(current));

    size++;
}

void Group::watchMovie(Genre genre) {
    moviesSeen[static_cast<int>(genre)]++;
    totalViews[static_cast<int>(genre)] += size;
    moviesSeen[4]++;
}

void Group::deleteUserNode(userNode *toDelete) {
    if (!toDelete) {
        return;
    }
    if (toDelete == first_user) {
        if (!first_user->next) {
            first_user = nullptr;
        } else {
            first_user = toDelete->next;
            first_user->prev = nullptr;
        }

    }
    if (toDelete == last_user) {

        last_user = toDelete->prev;

        if (last_user)
            last_user->next = nullptr;
    }
    if (toDelete->prev != NULL) {
        toDelete->prev->next = toDelete->next;
    }
    if (toDelete->next != NULL) {
        toDelete->next->prev = toDelete->prev;
    }

    if (toDelete->user->isVip())
        num_vip--;

    size--;

    for (int current = 0; current < 5; current++) {
        totalViews[current] -= toDelete->user->getSoloSeen(static_cast<Genre>(current));
        totalViews[current] -= (moviesSeen[current] - toDelete->user->getOffset(static_cast<Genre>(current)));
    }

    toDelete->user = nullptr;
    delete toDelete;

}

//--------------------------Getters--------------------------
int Group::getId() const {
    return id;
}

int Group::getSize() const {
    return size;
}

userNode *Group::getFirstUser() {
    return first_user;
}

int Group::getMoviesSeen(Genre genre) const {
    return moviesSeen[static_cast<int>(genre)];
}

bool Group::hasVip() const {
    return num_vip > 0;
}

//--------------------------Operators--------------------------
/*
bool Group::isEqual(const Group &m, bool sortedById) const {
    return *this == m;
}
bool Group::isGreaterThan(const Group &m, bool sortedById) const {
    return *this > m;
}
bool Group::isLessThan(const Group &m, bool sortedById) const {
    return *this < m;
} */

