#include "StreamingDBa1.h"

streaming_database::streaming_database() : users(AVL<User, CompareById<User>>()),
                                           movies(AVL<Movie, CompareById<Movie>>()),
                                           groups(AVL<Group, CompareById<Group>>()) {
    for (int counter = 0; counter < 5; counter++) {
        movies_by_rating[counter] = *(new AVL<Movie, CompareByRating>());
    }
}

streaming_database::~streaming_database() = default;


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly) {
    if (movieId <= 0 || genre == Genre::NONE || views < 0)
        return StatusType::INVALID_INPUT;

    Movie *toAdd;
    try {
        toAdd = new Movie(movieId, views, genre, vipOnly);

        if (movies.find(toAdd)) {
            delete toAdd;
            return StatusType::FAILURE;
        }

        try {
            movies.insert(*toAdd);
            movies_by_rating[static_cast<int>(genre)].insert(*toAdd);
            movies_by_rating[static_cast<int>(Genre::NONE)].insert(*toAdd);
        } catch (const std::bad_alloc &) {
            movies.remove(*toAdd);
            movies_by_rating[static_cast<int>(genre)].remove(*toAdd);
            movies_by_rating[static_cast<int>(Genre::NONE)].remove(*toAdd);

            delete toAdd;
        }
    } catch (const std::bad_alloc &) {
        delete toAdd;
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId) {
    if (movieId <= 0)
        return StatusType::INVALID_INPUT;

    Movie *toRemoveDummy;
    Movie *toRemove;
    try {
        toRemoveDummy = new Movie(movieId);

        if (!movies.find(toRemoveDummy)) {
            delete toRemoveDummy;
            return StatusType::FAILURE;
        }

        toRemove = movies.find(toRemoveDummy);

        movies.remove(*toRemove);
        movies_by_rating[static_cast<int>(toRemove->getGenre())].remove(*toRemove);
        movies_by_rating[static_cast<int>(Genre::NONE)].remove(*toRemove);

    } catch (const std::exception e) {
        delete toRemoveDummy;
        delete toRemove;
        return StatusType::ALLOCATION_ERROR;
    }
    delete toRemoveDummy;
    delete toRemove;

    return StatusType::SUCCESS;
}

StatusType streaming_database::add_user(int userId, bool isVip) {
    if (userId <= 0)
        return StatusType::INVALID_INPUT;

    User *toAdd;

    try {
        toAdd = new User(userId, isVip);

        if (users.find(toAdd)) {
            delete toAdd;
            return StatusType::FAILURE;
        }

        users.insert(*toAdd);

    } catch (const std::bad_alloc &) {
        delete toAdd;
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId) {
    if (userId <= 0)
        return StatusType::INVALID_INPUT;

    User *toRemoveDummy;
    User *toRemove;
    try {                                        //Creating a tmp user in order to find the real one to remove
        toRemoveDummy = new User(userId);
        if (!users.find(toRemoveDummy)) {
            delete toRemoveDummy;
            return StatusType::FAILURE;
        }

        toRemove = users.find(toRemoveDummy);

        users.remove(*toRemove);

    } catch (const std::exception e) {
        delete toRemoveDummy;
        delete toRemove;
        return StatusType::ALLOCATION_ERROR;
    }

    delete toRemoveDummy;
    delete toRemove;
    return StatusType::SUCCESS;
}

StatusType streaming_database::add_group(int groupId) {
    if (groupId <= 0)
        return StatusType::INVALID_INPUT;

    Group *toAdd;
    try {
        toAdd = new Group(groupId);

        if (groups.find(toAdd)) {
            delete toAdd;
            return StatusType::FAILURE;
        }

        groups.insert(*toAdd);
    } catch (const std::bad_alloc &) {
        delete toAdd;
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_group(int groupId) {
    if (groupId <= 0)
        return StatusType::INVALID_INPUT;

    Group *toRemoveDummy;
    Group *toRemove;
    try {                                        //Creating a tmp group in order to find the real one to remove
        toRemoveDummy = new Group(groupId);

        if (!groups.find(toRemoveDummy)) {
            delete toRemoveDummy;
            return StatusType::FAILURE;
        }

        toRemove = groups.find(toRemoveDummy);

        groups.remove(*toRemove);

    } catch (const std::exception e) {
        delete toRemoveDummy;
        delete toRemove;
        return StatusType::ALLOCATION_ERROR;
    }

    delete toRemoveDummy;
    delete toRemove;
    return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId) {
    if (groupId <= 0 || userId <= 0)
        return StatusType::INVALID_INPUT;

    User *tmp_user;
    Group *tmp_group;

    try {
        tmp_user = new User(userId);
        tmp_group = new Group(groupId);

        User *found_user = users.find(tmp_user);
        Group *found_group = groups.find(tmp_group);

        if (!found_user || !found_group || (found_user->group !=
                                            nullptr)) { //In case found_user is already in found_group - is it success or failure??
            delete tmp_user;
            delete tmp_group;

            return StatusType::FAILURE;
        } else {
            found_user->setGroup(found_group);
            found_group->addUser(found_user);
            found_user->setOffset(found_group->moviesSeen);
        }

        delete tmp_user;
        delete tmp_group;
    } catch (const std::exception e) {
        delete tmp_user;
        delete tmp_group;
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId) {
    if (movieId <= 0 || userId <= 0)
        return StatusType::INVALID_INPUT;

    User *tmp_user;
    Movie *tmp_movie;
    try {
        tmp_user = new User(userId);
        tmp_movie = new Movie(movieId);

        User *found_user = users.find(tmp_user);
        Movie *found_movie = movies.find(tmp_movie);


        if (!found_user || !found_movie || (!found_user->isVip() && found_movie->isVipOnly())) {
            delete tmp_user;
            delete tmp_movie;

            return StatusType::FAILURE;
        } else {
            movies_by_rating[static_cast<int>(found_movie->getGenre())].remove(*found_movie);
            movies_by_rating[static_cast<int>(Genre::NONE)].remove(*found_movie);

            found_user->watchMovie(found_movie->getGenre());

            found_movie->addViews(1);

            movies_by_rating[static_cast<int>(found_movie->getGenre())].insert(*found_movie);
            movies_by_rating[static_cast<int>(Genre::NONE)].insert(*found_movie);
        }

        delete tmp_user;
        delete tmp_movie;
    } catch (const std::exception e) {
        delete tmp_user;
        delete tmp_movie;
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId, int movieId) {
    if (groupId <= 0 || movieId <= 0)
        return StatusType::INVALID_INPUT;

    Group *tmp_group;
    Movie *tmp_movie;
    try {
        tmp_group = new Group(groupId);
        tmp_movie = new Movie(movieId);

        Group *found_group = groups.find(tmp_group);
        Movie *found_movie = movies.find(tmp_movie);

        if (!found_group || !found_movie || (!found_group->hasVip() && found_movie->isVipOnly()) ||
            found_group->getSize() == 0) {
            delete tmp_group;
            delete tmp_movie;

            return StatusType::FAILURE;
        } else {
            movies_by_rating[static_cast<int>(found_movie->getGenre())].remove(*found_movie);
            movies_by_rating[static_cast<int>(Genre::NONE)].remove(*found_movie);

            found_movie->addViews(found_group->getSize());

            movies_by_rating[static_cast<int>(found_movie->getGenre())].insert(*found_movie);
            movies_by_rating[static_cast<int>(Genre::NONE)].insert(*found_movie);


            found_group->watchMovie(found_movie->getGenre());
        }

        delete tmp_group;
        delete tmp_movie;
    } catch (const std::exception e) {
        delete tmp_group;
        delete tmp_movie;
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre) {
    int total = movies_by_rating[static_cast<int>(genre)].size;
    return output_t<int>(total);
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output) {
    if (!output) {
        return StatusType::INVALID_INPUT;
    }
    int *copy = output;
    if (movies_by_rating[static_cast<int>(genre)].size == 0) {
        return StatusType::FAILURE;
    }
    movies_by_rating[static_cast<int>(genre)].printPostOrder(movies_by_rating[static_cast<int>(genre)].root, copy);
    //output[0] = 4001;
    //output[1] = 4002;
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre) {
    if (userId <= 0)
        return output_t<int>(StatusType::INVALID_INPUT);

    User *tmp_user;
    try {
        tmp_user = new User(userId);
        User *found_user = users.find(tmp_user);


        if (!found_user)
            return output_t<int>(StatusType::FAILURE);
        else {
            int views = found_user->getMoviesSeen(genre);

            delete tmp_user;
            return output_t<int>(views);
        }

    } catch (const std::exception e) {
        delete tmp_user;
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }

    return 2008;
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating) {

    if (movieId <= 0 || userId <= 0 || rating < 0 || rating > 100)
        return StatusType::INVALID_INPUT;

    User *tmp_user;
    Movie *tmp_movie;
    try {
        tmp_user = new User(userId);
        tmp_movie = new Movie(movieId);

        User *found_user = users.find(tmp_user);
        Movie *found_movie = movies.find(tmp_movie);

        if (!found_movie || !found_user || (!found_user->isVip() && found_movie->isVipOnly()))
            return StatusType::FAILURE;

        movies_by_rating[static_cast<int>(found_movie->getGenre())].remove(*found_movie);
        movies_by_rating[static_cast<int>(Genre::NONE)].remove(*found_movie);

        found_movie->Rate(rating);

        movies_by_rating[static_cast<int>(found_movie->getGenre())].insert(*found_movie);
        movies_by_rating[static_cast<int>(Genre::NONE)].insert(*found_movie);

    } catch (const std::exception e) {
        delete tmp_user;
        delete tmp_movie;
        return StatusType::ALLOCATION_ERROR;
    }

    delete tmp_user;
    delete tmp_movie;
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_group_recommendation(int groupId) {
    /*Add to the group class an array.
     * Once the user is added to the group we add his views to the array. DONE
     * Once the user is removed from the system - we subtract his views from the array. DONE
     * Each time the user is watching a movie - we add the views to the array of his group. DONE
     * Each time the group is watching a movie together - we add the views to the array according to the current size of the group. DONE
     * Note that we also need to subtract the views added while group_watch in case a group member is deleted. We can do this using the offset array. DONE
    */
    if (groupId <= 0)
        return output_t<int>(StatusType::INVALID_INPUT);

    Group *tmp_group;
    try {
        tmp_group = new Group(groupId);
        Group *gr = groups.find(tmp_group);

        int genre = 0;
        int max_views = 0;

        if (!gr || gr->getSize() == 0)
            return output_t<int>(StatusType::FAILURE);

        for (int current = 0; current < 4; current++) {
            if (max_views < gr->totalViews[current]) {
                max_views = gr->totalViews[current];
                genre = current;
            } else if (max_views == gr->totalViews[current]) {
                genre = (genre < current) ? genre : current;
            }
        }
        delete tmp_group;

        if (movies_by_rating[genre].size == 0)
            return output_t<int>(StatusType::FAILURE);

        return output_t<int>(movies_by_rating[genre].max_node->obj->getId());

    } catch (const std::exception e) {
        delete tmp_group;
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }


    static int i = 0;
    return (i++ == 0) ? 11 : 2;
}
