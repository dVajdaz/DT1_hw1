//
// Created by Администратор on 08.05.2023.
//

#ifndef DS1_HW1_GROUP_H
#define DS1_HW1_GROUP_H

#include "User.h"
#include "Movie.h"

#include "wet1util.h"

//#include "AVL.h"
//#include "userNode.h"
class User;



struct userNode;
class Group {
private:

    userNode* first_user = nullptr;
    userNode* last_user = nullptr;

    int id;
    int num_vip = 0;

    int size = 0;

public:
    Group(int id);
    Group(const Group& toCopy) = default;
    ~Group();
//    bool isEqual(const Group& m, bool sortedById = true) const;
//    bool isGreaterThan(const Group& m, bool sortedById = true) const;
//    bool isLessThan(const Group& m, bool sortedById = true) const;
    void addUser(User *u);
    void deleteUserNode(userNode *toDelete);
    void watchMovie(Genre genre);


    bool operator<(const Group& toCompare) const;
    bool operator==(const Group& toCompare) const;

    int getId() const;
    int getMoviesSeen(Genre genre) const;
    int getSize() const;
    userNode* getFirstUser();
    bool hasVip() const;

    int moviesSeen[5] = {0};
    int totalViews[5] = {0};
};

bool operator>( Group const& g1, Group const& g2);

#endif //DS1_HW1_GROUP_H
