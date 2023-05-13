#include "StreamingDBa1.h"

streaming_database::streaming_database(): users(AVL<User>()), movies(AVL<Movie>()), groups(AVL<Group>())
{
    for(int counter = 0; counter<5; counter++){
        movies_by_rating[counter] = new AVL<Movie>();
    }
}

streaming_database::~streaming_database()
{
	// TODO: Your code goes here
}


StatusType streaming_database::add_movie(int movieId, Genre genre, int views, bool vipOnly)
{
    if(movieId<=0)
        return StatusType::INVALID_INPUT;

    Movie* toAdd;
    try {
        toAdd = new Movie(movieId,views, genre, vipOnly);
    } catch (const std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    }

    if(!this->movies.insert(*toAdd)){

        try {
            delete toAdd;
        } catch (const std::bad_alloc&) {
            return StatusType::ALLOCATION_ERROR;
        }

        return StatusType::FAILURE;
    }

    this->movies_by_rating[static_cast<int>(genre)].insert(*toAdd);

    return StatusType::SUCCESS;
}

StatusType streaming_database::remove_movie(int movieId)
{
    if(movieId<=0)
        return StatusType::INVALID_INPUT;

    try{                                        //Creating a tmp movie in order to find the real one to remove
        Movie* toRemove = new Movie(movieId);
        Movie removed = movies.remove(*toRemove);   //Finding the real toRemove in the AVL tree and removing it
        try{                                        //Deleting the tmp user
            delete toRemove;
        }catch(const std::exception e){
            return StatusType::ALLOCATION_ERROR;
        }

        if(!removed)
            return StatusType::FAILURE;

        this->movies_by_rating[static_cast<int>(removed.getGenre())].remove(removed);

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

    User* toAdd;
    try {
        toAdd = new User(userId, isVip);
    } catch (const std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    }

    if(!this->users.insert(*toAdd)){        //not insert -> insert returned nullptr -> user already exists

        try {
            delete toAdd;
        } catch (const std::bad_alloc&) {
            return StatusType::ALLOCATION_ERROR;
        }

        return StatusType::FAILURE;
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
            if(removed->self_pointer && removed->group){
                removed->group->deleteUserNode(removed->self_pointer);
            }
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

    Group* toAdd;
    try {
        toAdd = new Group(groupId);
    } catch (const std::bad_alloc&) {
        return StatusType::ALLOCATION_ERROR;
    }

    if(!this->groups.insert(*toAdd)){        //not insert -> insert returned nullptr -> user already exists

        try {
            delete toAdd;
        } catch (const std::bad_alloc&) {
            return StatusType::ALLOCATION_ERROR;
        }

        return StatusType::FAILURE;
    }

	return StatusType::SUCCESS;
}

StatusType streaming_database::remove_group(int groupId)
{
	 
	return StatusType::SUCCESS;
}

StatusType streaming_database::add_user_to_group(int userId, int groupId)
{

    return StatusType::SUCCESS;
}

StatusType streaming_database::user_watch(int userId, int movieId)
{
	// TODO: Your code goes here
    return StatusType::SUCCESS;
}

StatusType streaming_database::group_watch(int groupId,int movieId)
{
	// TODO: Your code goes here
	return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_all_movies_count(Genre genre)
{
    // TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}

StatusType streaming_database::get_all_movies(Genre genre, int *const output)
{
    // TODO: Your code goes here
    output[0] = 4001;
    output[1] = 4002;
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_num_views(int userId, Genre genre)
{
	// TODO: Your code goes here
	return 2008;
}

StatusType streaming_database::rate_movie(int userId, int movieId, int rating)
{
    // TODO: Your code goes here
    return StatusType::SUCCESS;
}

output_t<int> streaming_database::get_group_recommendation(int groupId)
{
	// TODO: Your code goes here
    static int i = 0;
    return (i++==0) ? 11 : 2;
}