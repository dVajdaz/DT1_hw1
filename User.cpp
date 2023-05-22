//
// Created by Администратор on 08.05.2023.
//

#include "User.h"

User::User(int id, bool vip) : id(id), vip(vip) {}

User::~User() {
    if (self_pointer && group)
        group->deleteUserNode(self_pointer);

    self_pointer = nullptr;
    group = nullptr;
}

//--------------------------Setters--------------------------
void User::setGroup(Group *gr) {
    if (gr) {
        this->group = gr;
    }
}

void User::setOffset(int *offsets) {
    for (int current = 0; current < 5; current++) {
        this->group_offset[current] = offsets[current];
    }
}

void User::watchMovie(Genre genre) {
    this->moviesSeen[static_cast<int>(genre)]++;
    this->moviesSeen[4]++;

    if (group) {
        this->group->totalViews[static_cast<int>(genre)]++;
        this->group->totalViews[4]++;
    }
}

void User::addViews(int genre, int views) {
    moviesSeen[genre] += views;
}

//--------------------------Getters--------------------------
int User::getId() const {
    return id;
}

/*
bool User::isEqual(const User &m, bool sortedById) const {
    return *this == m;
}
bool User::isGreaterThan(const User &m, bool sortedById) const {
    return *this > m;
}
bool User::isLessThan(const User &m, bool sortedById) const {
    return *this < m;
} */
int User::getMoviesSeen(Genre genre) const {
    int views = moviesSeen[static_cast<int>(genre)];
    int group_views = 0;

    if (group)
        group_views = group->getMoviesSeen(genre) - group_offset[static_cast<int>(genre)];

    return views + group_views;
}

int User::getSoloSeen(Genre genre) const {
    return moviesSeen[static_cast<int>(genre)];
}

int User::getOffset(Genre genre) const {
    return group_offset[static_cast<int>(genre)];
}

bool User::isVip() const {
    return vip;
}