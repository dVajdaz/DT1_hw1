//
// Created by Администратор on 08.05.2023.
//

#include "Group.h"


Group::Group(int id) : id(id){}
Group::~Group() {
    Node *current = first_user;
    Node *next;
    while (current != nullptr) {
        next = current->next;
        delete current;
        current = next;
    }
}

//--------------------------Setters--------------------------

void Group::addUser(User *toAdd) {
    Node* new_user = new Node();
    new_user->user = toAdd;
    new_user->next = nullptr;

    if(!first_user){
        new_user->prev = nullptr;
        first_user = new_user;
        last_user = new_user;
    }

    if(last_user){
        last_user->next = new_user;
        new_user->prev = last_user;
    }

    last_user = new_user;
    toAdd->self_pointer = new_user;

    if(new_user->user->isVip())
        num_vip++;

    for(int current = 0; current <5; current++)
        totalViews[current]+=toAdd->getMoviesSeen(static_cast<Genre>(current));
}

void Group::watchMovie(Genre genre) {
    moviesSeen[static_cast<int>(genre)]++;
    totalViews[static_cast<int>(genre)]+=size;
}

void Group::deleteUserNode(Node *toDelete) {
    if (!toDelete) {
        return;
    }
    if (toDelete == first_user) {
        first_user = toDelete->next;
        first_user->prev = nullptr;
    }
    if (toDelete == last_user) {
        last_user = toDelete->prev;
        last_user->next = nullptr;
    }
    if (toDelete->prev != NULL) {
        toDelete->prev->next = toDelete->next;
    }
    if (toDelete->next != NULL) {
        toDelete->next->prev = toDelete->prev;
    }

    if(toDelete->user->isVip())
        num_vip--;

    size--;

    for(int current = 0; current<5; current++){
        totalViews[current]-=toDelete->user->getMoviesSeen(static_cast<Genre>(current));
        totalViews[current]-=(moviesSeen[current]-toDelete->user->getOffset(static_cast<Genre>(current)));
    }
    delete toDelete;

}

//--------------------------Getters--------------------------
int Group::getId() const{
    return id;
}

int Group::getSize() const {
    return size;
}

Node* Group::getFirstUser() {
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
bool Group::operator<(const Group& g1) const{
    return id < g1.getId();
}

bool Group::operator==(const Group& g1) const{
    return id == g1.getId();
}

bool operator>(const Group& g1, Group& g2){
    return g2 < g1;
}

