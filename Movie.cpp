//
// Created by Администратор on 07.05.2023.
//

#include "Movie.h"
Movie::Movie(int id, int views,  Genre genre, bool vip, bool sortById) : id(id), views(views), rating(0.0), genre(genre), vipOnly(vip),
sortById(sortById){}

//--------------------------Setters--------------------------
void Movie::addViews(const int toAdd) {
    views+=toAdd;
}

void Movie::Rate(const double toAdd) {
    rated++;
    rating = (rating+toAdd)/rated;
}

//--------------------------Getters--------------------------
int Movie::getId() const{
    return id;
}

int Movie::getViews() const {
    return views;
}

double Movie::getRating() const {
    return rating;
}

Genre Movie::getGenre() const {
    return genre;
}

bool Movie::isVipOnly() const {
    return vipOnly;
}
/*
bool Movie::isEqual(const Movie& m, bool sortedById) const {
    if(sortedById) {
        return *this == m;
    }
    return (m.getRating() == this->rating && m.getViews() == this->views && this->id == m.getId());
}

bool Movie::isLessThan(const Movie &m, bool sortedById) const {
    if(sortedById) {
        return *this < m;
    }
    return this->rating < m.getRating() || this->views < m.getViews() || this->id < m.getId();
}

bool Movie::isGreaterThan(const Movie &m, bool sortedById) const {
    if(sortedById) {
        return *this > m;
    }
    return this->rating > m.getRating() || this->views > m.getViews() || this->id > m.getId();
} */
//--------------------------Operators--------------------------
bool Movie::operator<(const Movie& m1) const{
    if(sortById)
        return id < m1.getId();

    return rating < m1.getRating() || views < m1.getViews() || id < m1.getId();
}

bool Movie::operator==(const Movie& m1) const{
    if(sortById)
        return id == m1.getId();

    return rating == m1.getRating() && views == m1.getViews() && id == m1.getId();
}

bool operator>(const Movie& m1, const Movie& m2){
    return m2 < m1;
}
