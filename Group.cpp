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

    delete[] movies_seen;
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

    if(new_user->user->isVip())
        num_vip++;

}

void Group::watchMovie(Genre genre) {
    this->moviesSeen[static_cast<int>(genre)]++;
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

    try{
        delete toDelete; //TODO: DELETING THE NODE. NOT DELETING THE USER ITSELF YET. MIGHT CAUSE MEMORY LEAK !!!
    } catch(const std::exception e){
        throw e;
    }
}

//--------------------------Getters--------------------------
int Group::getId() const{
    return id;
}

int Group::getMoviesSeen(Genre genre) const {
    return moviesSeen[static_cast<int>(genre)];
}

bool Group::hasVip() const {
    return num_vip > 0;
}

//--------------------------Operators--------------------------
bool Group::operator<(const Group& g1) const{
    return id < g1.getId();
}

bool Group::operator==(const Group& g1) const{
    return id == g1.getId();
}

bool operator>(const Group& g1, Group& g2){
    return g2 < g1;
}