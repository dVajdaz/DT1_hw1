//
// Created by Администратор on 07.05.2023.
//

#include "Movie.h"

Movie::Movie(int id, int views, Genre genre, bool vip, bool sortById) : id(id), views(views), rating(0.0), genre(genre),
                                                                        vipOnly(vip),
                                                                        sortById(sortById) {}

//--------------------------Setters--------------------------
void Movie::addViews(const int toAdd) {
    views += toAdd;
}

void Movie::Rate(const double toAdd) {
    rated++;
    rating = (rating * (rated - 1) + toAdd) / rated;
}

void Movie::setSortingType(const bool sortingType) {
    sortById = sortingType;
}

//--------------------------Getters--------------------------
int Movie::getId() const {
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
