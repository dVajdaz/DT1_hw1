//
// Created by Администратор on 07.05.2023.
//

#ifndef DS1_HW1_MOVIE_H
#define DS1_HW1_MOVIE_H

#include "wet1util.h"

class Movie {
private:
    const int id;
    int views;

    double rating;

    const bool vipOnly;

    Genre genre;

public:
    Movie(int id, Genre genre, bool vip = false);
    Movie(const Movie& toCopy) = default;
    ~Movie() = default;

    bool operator<(const Movie& toCompare) const;
    bool operator==(const Movie& toCompare) const;

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
