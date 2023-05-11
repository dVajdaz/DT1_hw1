//
// Created by Администратор on 08.05.2023.
//

#include "Group.h"


Group::Group(int id) : id(id){}
Group::~Group(){
    //TODO: Implement group destructor
}

//--------------------------Setters--------------------------

void Group::addUser(User *toAdd) {
    //TODO: Implement addUser
}

void Group::watchMovie(Genre genre) {
    this->moviesSeen[static_cast<int>(genre)]++;
}

//--------------------------Getters--------------------------
int Group::getId() const{
    return id;
}

int Group::getMoviesSeen(Genre genre) const {
    return moviesSeen[static_cast<int>(genre)];
}

bool Group::hasVip() const {
    return vip;
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