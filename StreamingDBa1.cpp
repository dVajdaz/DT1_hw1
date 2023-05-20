#include "StreamingDBa1.h"

streaming_database::streaming_database(): users(AVL<User>()), movies(AVL<Movie>()), groups(AVL<Group>())
{
    for(int counter = 0; counter<5; counter++){
        movies_by_rating[counter] = *(new AVL<Movie>());
    }
}

streaming_database::~streaming_database()
{
    users.destroy(users.root);
    movies.destroy(movies.root);
    for (AVL<Movie> genre_tree : movies_by_rating)
        genre_tree.destroy(genre_tree.root);
}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
    if(movieId<=0)
        return StatusType::INVALID_INPUT;

    Movie* toAdd;
    try {
        toAdd = new Movie(movieId,views, genre, vipOnly);
    } catch (const std::bad_alloc&) {
        delete toAdd;
        return StatusType::ALLOCATION_ERROR;
    }


    if(!movies.insert(*toAdd)){

        try {
            delete toAdd;
        } catch (const std::bad_alloc&) {
            return StatusType::ALLOCATION_ERROR;
        }

        return StatusType::FAILURE;
    }
    Movie* toAddByRating;
    try {
        toAddByRating = new Movie(movieId,views, genre, vipOnly, true);
    } catch (const std::bad_alloc&) {
        delete toAddByRating;
        try {
            movies.remove(*toAdd);
            delete toAdd;
        }
        catch (const std::exception&) {
            delete toAdd;
            return StatusType::ALLOCATION_ERROR;
        }

        return StatusType::ALLOCATION_ERROR;
    }
    if(!this->movies_by_rating[static_cast<int>(genre)].insert(*toAddByRating)) {
        try {
            movies.remove(*toAdd);
            delete toAdd;
            delete toAddByRating;
        }
        catch (const std::exception&) {
            delete toAdd;
            delete toAddByRating;
            return StatusType::ALLOCATION_ERROR;
        }

        return StatusType::FAILURE;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId)
{
    if(movieId<=0)
        return StatusType::INVALID_INPUT;

    try{                                        //Creating a tmp movie in order to find the real one to remove
        Movie* toRemove = new Movie(movieId);
        Movie* removed = movies.remove(*toRemove);   //Finding the real toRemove in the AVL tree and removing it
        try{                                        //Deleting the tmp user
            delete toRemove;
        }catch(const std::exception e){
            return StatusType::ALLOCATION_ERROR;
        }

        if(!removed){
            return StatusType::FAILURE;
        }


        this->movies_by_rating[static_cast<int>(removed->getGenre())].remove(*removed);

        try{
            delete removed;
        }catch(const std::exception e){
            return StatusType::ALLOCATION_ERROR;
        }

    }catch(const std::exception e){
        return StatusType::ALLOCATION_ERROR;
    }

	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user(int userId, bool isVip)
{
	if(userId<=0)
        return StatusType::INVALID_INPUT;


    try {
        User* toAdd = new User(userId, isVip);

        if(!users.insert(*toAdd)){        //not insert -> insert returned nullptr -> user already exists

            try {
                delete toAdd;
            } catch (const std::bad_alloc&) {
                return StatusType::ALLOCATION_ERROR;
            }

            return StatusType::FAILURE;
        }

    }catch(const std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    }

	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_user(int userId)
{
    if(userId<=0)
        return StatusType::INVALID_INPUT;

    try{                                        //Creating a tmp user in order to find the real one to remove
        User* toRemove = new User(userId);

        User* removed = users.remove(*toRemove);     //Finding the real toRemove in the AVL tree and removing it
        try{                                        //Deleting the tmp user
            delete toRemove;
        }catch(const std::exception e){
            return StatusType::ALLOCATION_ERROR;
        }

        if(!removed)
            return StatusType::FAILURE;

        try{                                        //Deleting the user from its group
            if(removed->self_pointer && removed->group)
                removed->group->deleteUserNode(removed->self_pointer);

        }catch(const std::exception e){
            return StatusType::ALLOCATION_ERROR;
        }

        try{                                        //Deleting the user's object
            delete removed;
        }catch(const std::exception e){
            return StatusType::ALLOCATION_ERROR;
        }

    }catch(const std::exception e){
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;

    //TODO: AVL remove method has to return the removed node so we could also remove the user from his group
}

StatusType streaming_database::add_group(int groupId)
{
    if(groupId<=0)
        return StatusType::INVALID_INPUT;

    try {
        Group* toAdd = new Group(groupId);

        if(!groups.insert(*toAdd)){        //not insert -> insert returned nullptr -> user already exists

            try {
                delete toAdd;
            } catch (const std::bad_alloc&) {
                return StatusType::ALLOCATION_ERROR;
            }

            return StatusType::FAILURE;
        }
    } catch (const std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    }

	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_group(int groupId)
{

    if(groupId<=0)
        return StatusType::INVALID_INPUT;

    try{                                        //Creating a tmp group in order to find the real one to remove
        Group* toRemove = new Group(groupId);

        Group* removed = groups.remove(*toRemove);     //Finding the real toRemove in the AVL tree and removing it
        try{                                        //Deleting the tmp group
            delete toRemove;
        }catch(const std::exception e){
            return StatusType::ALLOCATION_ERROR;
        }

        if(!removed)
            return StatusType::FAILURE;

        while(removed->getFirstUser() != nullptr){
            removed->getFirstUser()->user->self_pointer = nullptr;
            removed->getFirstUser()->user->group = nullptr;


            for(int i = 0; i<5; i++){
                int toAdd = removed->getMoviesSeen(static_cast<Genre>(i)) -  removed->getFirstUser()->user->getOffset(static_cast<Genre>(i));
                removed->getFirstUser()->user->addViews(i, toAdd);
            }
            //NOT SURE IF NEEDED !!!

            removed->getFirstUser()->user->setOffset(new int[5]());
            removed->deleteUserNode(removed->getFirstUser());
        }

        try{                                        //Deleting the group's object
            delete removed;
        }catch(const std::exception e){
            return StatusType::ALLOCATION_ERROR;
        }

    }catch(const std::exception e){
        return StatusType::ALLOCATION_ERROR;
    }



	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{
    if(groupId<=0 || userId <= 0)
        return StatusType::INVALID_INPUT;
    User* tmp_user;
    Group* tmp_group;
    try{
            tmp_user = new User(userId);
            tmp_group = new Group(groupId);

            User* found_user = users.find(tmp_user);
            Group* found_group = groups.find(tmp_group);

            if(!found_user || !found_group || (found_user->group != nullptr)){ //In case found_user is already in found_group - is it success or failure??
                delete tmp_user;
                delete tmp_group;

                return StatusType::FAILURE;
            }else{
                found_user->setGroup(found_group);
                found_user->setOffset(found_group->moviesSeen);
                found_group->addUser(found_user);
            }

        delete tmp_user;
        delete tmp_group;
    }catch(const std::exception e){
        delete tmp_user;
        delete tmp_group;
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
    if(movieId<=0 || userId <= 0)
        return StatusType::INVALID_INPUT;

    try{
        User* tmp_user = new User(userId);
        Movie* tmp_movie = new Movie(movieId);

        User* found_user = users.find(tmp_user);
        Movie* found_movie = movies.find(tmp_movie);

        if(!found_user || !found_movie || (!found_user->isVip()&&found_movie->isVipOnly())){
            delete tmp_user;
            delete tmp_movie;

            return StatusType::FAILURE;
        }else{
            found_user->watchMovie(found_movie->getGenre());
            found_movie->addViews(1);

            if(found_user->group)
                found_user->group->totalViews[static_cast<int>(found_movie->getGenre())]++;

        }

        delete tmp_user;
        delete tmp_movie;
    }catch(const std::exception e){
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
	if(groupId<=0 || movieId <= 0)
        return StatusType::INVALID_INPUT;

    try{
        Group* tmp_group = new Group(groupId);
        Movie* tmp_movie = new Movie(movieId);

        Group* found_group = groups.find(tmp_group);
        Movie* found_movie = movies.find(tmp_movie);

        if(!found_group || !found_movie || (!found_group->hasVip()&&found_movie->isVipOnly()) || found_group->getSize() == 0){
            delete tmp_group;
            delete tmp_movie;

            return StatusType::FAILURE;
        }else{
            found_movie->addViews(found_group->getSize());
            found_group->watchMovie(found_movie->getGenre());
        }

        delete tmp_group;
        delete tmp_movie;
    }catch(const std::exception e){
        return StatusType::ALLOCATION_ERROR;
    }

	return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    int total = movies_by_rating[static_cast<int>(genre)].size;
    return output_t<int>(total);

    static int i = 0;
    return (i++==0) ? 11 : 2;
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
    if(!output) {
        return StatusType::INVALID_INPUT;
    }
    int* copy = output;
    if(movies_by_rating[static_cast<int>(genre)].size == 0) {return StatusType::FAILURE;}
    movies_by_rating[static_cast<int>(genre)].printPostOrder(movies_by_rating[static_cast<int>(genre)].root,copy);
    output[0] = 4001;
    output[1] = 4002;
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
    if(userId <= 0)
        return output_t<int>(StatusType::FAILURE);
    try{
        User* tmp_user = new User(userId);
        User* found_user = users.find(tmp_user);

        delete tmp_user;

        if(!found_user)
            return output_t<int>(StatusType::FAILURE);
        else{
            int views = found_user->getMoviesSeen(genre) + (found_user->group)->getMoviesSeen(genre) - found_user->getOffset(genre);
            return output_t<int>(views);
        }

    }catch(const std::exception e){
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }
	return 2008;
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{

    if(movieId<=0 || userId <= 0 || rating < 0 || rating > 100)
        return StatusType::INVALID_INPUT;

    try{
        User* tmp_user = new User(userId);
        Movie* tmp_movie = new Movie(movieId);

        User* found_user = users.find(tmp_user);
        Movie* found_movie = movies.find(tmp_movie);

        delete tmp_user;
        delete tmp_movie;

        if(!found_movie || !found_user || (!found_user->isVip() && found_movie->isVipOnly()))
            return StatusType::FAILURE;

        found_movie->Rate(rating);
    }catch(const std::exception e){
        return StatusType::ALLOCATION_ERROR;
    }

    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
	/*Add to the group class an array.
	 * Once the user is added to the group we add his views to the array. DONE
	 * Once the user is removed from the system - we subtract his views from the array. DONE
	 * Each time the user is watching a movie - we add the views to the array of his group. DONE
	 * Each time the group is watching a movie together - we add the views to the array according to the current size of the group. DONE
	 * Note that we also need to subtract the views added while group_watch in case a group member is deleted. We can do this using the offset array. DONE
    */
    if(groupId<=0)
        return output_t<int>(StatusType::INVALID_INPUT);

    Group* tmp_group;
    try{
        tmp_group = new Group(groupId);
        Group* gr = groups.find(tmp_group);

        int genre = 0;
        int max_views = 0;

        if(!gr || gr->getSize() == 0)
            return output_t<int>(StatusType::FAILURE);

        for(int current = 0; current<0; current++){
            if(max_views < gr->totalViews[current]){
                max_views = gr->totalViews[current];
                genre = current;
            } else if (max_views == gr->totalViews[current]){
                genre = (genre>current) ? genre : current;
            }
        }
        delete tmp_group;
        //return id of the best rated movie of the computed genre

    }catch(const std::exception e){
        delete tmp_group;
        return output_t<int>(StatusType::ALLOCATION_ERROR);
    }


    static int i = 0;
    return (i++==0) ? 11 : 2;
}
