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
    Movie(int id, int views = 0,  Genre genre = Genre::NONE, bool vip = false, bool sortById = true);
    Movie(const Movie& toCopy) = default;
    ~Movie() = default;

    bool operator<(const Movie& toCompare) const;
    bool operator==(const Movie& toCompare) const;
//    bool isEqual(const Movie& m, bool sortedById = true) const;
//    bool isGreaterThan(const Movie& m, bool sortedById = true) const;
//    bool isLessThan(const Movie& m, bool sortedById = true) const;
    int getId() const;
    int getViews() const;
    double getRating() const;
    bool isVipOnly() const;
    Genre getGenre() const;

    void addViews(const int toAdd);
    void Rate(const double toAdd);
};

bool operator>(const Movie& m1, const Movie& m2);

#endif //DS1_HW1_MOVIE_H
