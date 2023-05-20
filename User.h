//
// Created by Администратор on 08.05.2023.
//

#ifndef DS1_HW1_USER_H
#define DS1_HW1_USER_H

//#include "Movie.h"
#include "Group.h"
#include  <memory>
#include "wet1util.h"

//#include "AVL.h"
#include "userNode.h"
//struct userNode;
class Group;
class User {
private:
    int id;
    int moviesSeen[5] = {0};

    int group_offset[5] = {0};

    bool vip;
public:
    User(int id, bool vip = false);
    User(const User& toCopy) = default;
    ~User() = default;
//    bool isEqual(const User& m, bool sortedById = true) const;
//    bool isGreaterThan(const User& m, bool sortedById = true) const;
//    bool isLessThan(const User& m, bool sortedById = true) const;
    void setGroup(Group* gr);
    void setOffset(int* offsets);
    void watchMovie(Genre genre);
    void addViews(int genre, int views);

    bool operator<(const User& toCompare) const;
    bool operator==(const User& toCompare) const;

    int getId() const;
    int getMoviesSeen(Genre genre) const;
    int getOffset(Genre genre) const;
    //double setRating() const;
    bool isVip() const;

    userNode* self_pointer = nullptr;
    std::shared_ptr<Group>  group = nullptr;
};

bool operator>(const User& u1, const User& u2);

#endif //DS1_HW1_USER_H
