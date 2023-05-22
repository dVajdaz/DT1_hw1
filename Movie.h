//
// Created by Администратор on 07.05.2023.
//

#ifndef DS1_HW1_MOVIE_H
#define DS1_HW1_MOVIE_H

#include "User.h"
#include "Group.h"

#include "wet1util.h"

//#include "AVL.h"

class Movie {
private:
    int id;
    int views;
    int rated = 0;

    double rating;
    bool sortById;
    bool vipOnly;
    Genre genre;

public:
    Movie(int id, int views = 0, Genre genre = Genre::NONE, bool vip = false, bool sortById = true);

    Movie(const Movie &toCopy) = default;

    ~Movie() = default;

    int getId() const;

    int getViews() const;

    double getRating() const;

    bool isVipOnly() const;

    Genre getGenre() const;

    void addViews(const int toAdd);

    void Rate(const double toAdd);

    void setSortingType(const bool sortingType);
};

#endif //DS1_HW1_MOVIE_H
