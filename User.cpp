//
// Created by Администратор on 08.05.2023.
//

#include "User.h"

User::User(int id,  bool vip) : id(id), vip(vip){}

//--------------------------Setters--------------------------
void User::setGroup(Group *gr) {
    if(gr){
        this->group = gr;
    }
}

void User::setOffset(int *offsets) {
    for(int current = 0; current<5; current++){
        this->group_offset[current] = offsets[current];
    }
}

void User::watchMovie(Genre genre) {
    this->moviesSeen[static_cast<int>(genre)]++;
}

void User::addViews(int genre, int views) {
    moviesSeen[genre] += views;
}

//--------------------------Getters--------------------------
int User::getId() const{
    return id;
}


int User::getMoviesSeen(Genre genre) const {
    int views = moviesSeen[static_cast<int>(genre)];
    int group_views = 0;

    if(group)
        group_views = *group->getMoviesSeen(genre) - group_offset[static_cast<int>(genre)];

    return views+group_views;
}

int User::getOffset(Genre genre) const {
    return group_offset[static_cast<int>(genre)];
}

bool User::isVip() const {
    return vip;
}

//--------------------------Operators--------------------------
bool User::operator<(const User& m1) const{
    return id < m1.getId();
}

bool User::operator==(const User& m1) const{
    return id == m1.getId();
}

bool operator>(const User& m1, const User& m2){
    return m2 < m1;
}