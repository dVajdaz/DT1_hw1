//
// Created by Администратор on 07.05.2023.
//

#include "Movie.h"
Movie::Movie(int id,  Genre genre, bool vip = false) : id(id), views(0), rating(0.0), Genre(genre), vipOnly(vip){}

//--------------------------Setters--------------------------
void Movie::addViews(const int toAdd) {
    views+=toAdd;
}

void Movie::Rate(const double toAdd) {  //Should first addViews() and ONLY THEN compute the new rating !!!
    rating = (rating+toAdd)/views;
}

//--------------------------Getters--------------------------
int Movie::getId() const{
    return id;
}

int Movie::getViews() const {
    return views;
}

int Movie::getRating() const {
    return rating;
}

int Movie::getGenre() const {
    return genre;
}

bool Movie::isVipOnly() const {
    return vipOnly;
}
//--------------------------Operators--------------------------
bool Movie::operator<(const Movie& m1) const{
    return id < m1.getId();
}

bool Movie::operator==(const Movie& m1) const{
    return id == m1.getId();
}

bool operator>(const Movie& m1, const Movie& m2){
    return m2 < m1;
}
