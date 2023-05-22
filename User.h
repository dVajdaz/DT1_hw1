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

    bool vip;
public:
    User(int id, bool vip = false);

    User(const User &toCopy) = default;

    ~User();

    void setGroup(Group *gr);

    void setOffset(int *offsets);

    void watchMovie(Genre genre);

    void addViews(int genre, int views);

    int getId() const;

    int getMoviesSeen(Genre genre) const;

    int getSoloSeen(Genre genre) const;

    int getOffset(Genre genre) const;

    //double setRating() const;
    bool isVip() const;

    userNode *self_pointer = nullptr;
    Group *group = nullptr;
    int group_offset[5] = {0};
};

#endif //DS1_HW1_USER_H
