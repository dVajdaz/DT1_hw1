//
// 234218 Data Structures 1.
// Semester: 2023B (spring).
// Wet Exercise #1.
//
// Recommended TAB size to view this file: 8.
//
// The following main file is necessary to link and run your code.
// This file is READ ONLY: even if you submit something else, the compiler ..
// .. WILL use our file.
//

#include "StreamingDBa1.h"
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

void print(string cmd, StatusType res);

void print(string cmd, output_t<int> res);

void query_get_all_movies(string cmd, streaming_database *obj, Genre genre);

int main() {
    /*
    streaming_database s;
    int *a = new int[10]();
    s.get_all_movies_count(Genre(3));
    s.add_group(4601);
    s.user_watch(5899, 9441);
    s.add_user(2494, false);
    s.remove_user(2494);
    s.add_group(1973);
    s.add_movie(9198, Genre(2), 97, true);
    s.group_watch(4601 ,9198);
    s.get_group_recommendation(4601);
    s.remove_user(8573);
    s.add_movie(1163, Genre(4), 26, false);
    s.get_all_movies(Genre(1), a);
    s.rate_movie(1294, 1163, 149);
    s.remove_movie(9198);
    s.add_group(7226);
    s.get_all_movies(Genre(4), a);
    s.user_watch(6760, 1163);
    s.add_user(1001 , false);
    s.get_group_recommendation(7226);
    s.add_user(5369, false);
    s.group_watch(1973, 1163);
    s.group_watch(7226, 1163);
    s.get_num_views(5369, Genre(4));
    s.add_group(656);
    s.add_user(5813, false);
    s.add_user(1706, false);
    s.get_group_recommendation(656);
    s.get_group_recommendation(7226);
    s.remove_movie(1163);
    s.group_watch(4601, 9506);
    s.remove_user(5813);
    s.get_all_movies(static_cast<Genre>(1), a);
    s.user_watch(5369, 6756);
    s.get_all_movies (static_cast<Genre>(2),a);
    s.get_all_movies (static_cast<Genre>(4),a);
    s.add_movie (463, Genre(2) ,62, true);
    s.add_group (8865);
    s.get_num_views (1001, static_cast<Genre>(2));
    s.get_group_recommendation (1973);
    s.add_user (2673, false);
    s.get_num_views (1001, Genre(1));
    s. add_user (1912, false);
    s.user_watch (5369, 463);
    s.get_num_views (1001, static_cast<Genre>(2));
    s.add_movie (6049, Genre(2), 69, false);
    s.add_user (6667, false);
    s.add_movie (4957, Genre(4), 14, false);
    s.add_user (7624 ,false);
    s.add_user (1001, false);
    s.rate_movie (1001, 4957 ,83);
    s.rate_movie (5813 ,6049, 36);
    s.remove_user (6667);
    s.remove_movie (6049);
    s.group_watch (7226, 463);
    s.rate_movie (1706, 463, 110);
    s.add_group (437);
    s.get_num_views (2673, Genre(2));
    s.add_user_to_group (1706 ,4601);
    s.add_movie (6931 ,Genre(1), 31 ,true);
    s.remove_group (9983);
    s.add_group (1784);
    s.get_num_views (7624 ,static_cast<Genre>(2));
    */

    /*
    streaming_database s;
    int *a = new int[10]();
    s.add_group(6567);
    s.get_all_movies((Genre)1,a);
    s.get_all_movies((Genre)3, a);
    s.get_all_movies ((Genre)0, a);
    s.get_num_views (9854, (Genre)2);
    s.get_num_views (1472, (Genre)2);
    s.add_user_to_group (3347, 8466);
    s.add_group (7703);
    s.add_user (9744, false);
    s.add_user_to_group (9744, 6567);
    s.add_group (6727);
    s.get_all_movies ((Genre)3,a);
    s.rate_movie (9744, 5173,2);
    s.group_watch (7703, 6945);
    s.group_watch (6727 ,264);
    s.remove_user (9744);
    s.get_all_movies_count ((Genre)2);
    s.rate_movie (6756 ,4670 ,116);
    s.get_all_movies_count ((Genre)4);
    s.add_user (8287, false);
    s.get_num_views (8287, (Genre)3);
    s.group_watch (7703, 7932);
    s.add_group (9143);
    s.remove_movie (1422);
    s.get_num_views (8287 ,(Genre)0);
    s.add_movie (7427, (Genre)3 ,90, true);
    s.add_user_to_group (8287, 7703);
    s.add_user (8857, true);
    s.get_all_movies_count ((Genre)1);
    s.rate_movie (8287 ,7427 ,136);
    s.add_movie (1138, (Genre)2, 4, false);
    s.remove_group(9143);
    s.remove_movie (7427);
    s.get_num_views (8287, (Genre) 3);
    s.add_movie (5174, (Genre)1, 12, false);
    s.remove_movie (5174);
    s.add_user_to_group (8287, 6727);
    s.get_all_movies ((Genre)4, a);
    s.add_movie(1085, (Genre)0, 80, false);
    s.get_all_movies((Genre)2, a);
    s.add_user_to_group( 8857, 7703);
    s.add_group (4884);
    s.get_all_movies( (Genre)0, a);
    s.group_watch( 6727, 1085);
    s.get_all_movies( (Genre)3, a);
    s.get_num_views (2050, (Genre)3);
    s.remove_movie (1138);
    s.user_watch (8287, 7928);
    s.add_group (8237);
    s.get_all_movies( (Genre)2, a);
    s.remove_user (8287);
    s.add_movie (147, (Genre)2, 58, false);
    s.add_group (3761);
    s.add_user (635, false);
    s.get_all_movies_count( (Genre)3);
    s.get_all_movies ((Genre)2, a);
    s.get_all_movies ((Genre)0, a);
    s.add_group( 2125);
    s.add_movie(9750, (Genre)2, 6, true);
    s.add_user_to_group(8857, 6727);

    delete [] a;
    */

    /*streaming_database s;
     int *a = new int[10]();
     s.group_watch( 3177, 4086);
     s.add_movie (7026, (Genre)1, 98, false);
     s.add_group (4373);
     s.add_group (8506);
     s.add_movie( 2189,(Genre) 1, 11, false);
     s.user_watch (9575, 2189);
     s.get_num_views (7691, (Genre)2);
     s.add_user( 4485, false);
     s.user_watch (4485, 7026);
     s.add_user (2357, true);
     s.get_all_movies_count ((Genre)1);
     s.rate_movie (2357, 2189, 5);
     s.add_user_to_group (2357, 8506);
     s.user_watch (4485, 7026);
     s.get_all_movies((Genre)4, a);
     s.add_group (3038);
     s.get_group_recommendation (8506);
     s.group_watch (3038, 2189);
     s.get_group_recommendation (8506);
     s.get_all_movies ((Genre)4, a);
     s.group_watch (8506, 2189);
     s.remove_movie (7026);
     s.group_watch (4373, 2189);
     s.rate_movie (4485, 8357, 65);
     s.add_user_to_group (2357, 4373);
     s.remove_user (4485);
     s.add_user_to_group( 2357, 8506);
     s.get_all_movies_count ((Genre)0);
     s.get_group_recommendation (3038);
     s.get_num_views( 2357,(Genre) 3);
     s.add_group (7231);
     s.rate_movie (2357 ,2189, 118);
     s.get_group_recommendation (3038);
     s.get_group_recommendation (8506);
     s.add_movie (2189, (Genre)3, 43, false);
     s.remove_movie (2189);
     s.get_all_movies_count ((Genre)3);
     s.add_user (4623, false);
     s.user_watch (2357, 8771);
     s.add_user (4623, true);
     s.remove_user (4623);
     s.get_num_views (2357, (Genre)4);
     s.add_group (9699);
     s.get_all_movies ((Genre)0, a);
     s.get_num_views (9984, (Genre)2);
     s.add_movie (7981, (Genre) 3, 86, false);
     s.add_group (3219);
     s.get_num_views (2357, (Genre)4);
     s.remove_group( 8506);
     s.remove_movie( 7981);
     s.get_all_movies ((Genre)2, a);
     s.get_num_views (2357, (Genre)2);
     s.add_user (7295, false);
     s.remove_movie( 7181);
     s.remove_movie (9763);
     s.group_watch( 3219, 9123);
     s.rate_movie (2357, 7386, 119);
     s.get_num_views (7295, (Genre)3);
     s.add_movie (1115, (Genre)2, 78, false);
     s.add_user_to_group (7295, 7231);
     s.get_num_views (2357, (Genre)3);
     s.add_user_to_group( 3913, 3219);
     s.group_watch( 3038, 1115);
     s.add_movie (9281,(Genre) 3, 16, true);
     s.get_all_movies_count ((Genre)1);
     s.group_watch (4373, 8754);
     s.get_all_movies ((Genre)3, a);
     s.add_movie (1382, (Genre)3 ,32 ,true);
     s.remove_user (7295);
     s.get_num_views (2357, (Genre)2);
     s.remove_group (3038);
     s.remove_movie (9281);
     s.get_all_movies ((Genre)2, a);
     s.add_group (7343);
     s.rate_movie (2357, 1382, 104);
     s.get_all_movies((Genre) 2, a);
     s.remove_user (2357);
     s.add_user (7142, true);
     s.get_num_views (7142, (Genre)0);
     s.add_group (1521);
     s.add_movie (9319, (Genre)3, 9 ,false);
     s.get_all_movies_count((Genre) 2);
     s.get_all_movies ((Genre)1, a);
     s.rate_movie (7142, 1382, 0);
     s.get_all_movies ((Genre)1, a);
     s.remove_user (7142);
     s.get_all_movies ((Genre)4, a);
 */

//    streaming_database s;
//    int *a = new int[10]();
//    s.add_group(3906);
//    s.add_group(3182);
//    s.add_user_to_group(6174, 3906);
//    s.get_all_movies(Genre(1), a);
//    s.add_user(5740, false);
//    s.get_all_movies_count(Genre(2));
//    s.add_user_to_group(5740, 3906);
//    s.rate_movie(5740, 3637, 47);
//    s.add_user(5046, true);
//    s.user_watch(5046, 7603);
//    s.group_watch(3182, 5069);
//    s.get_num_views(5740, Genre(2));
//    s.remove_movie(4323);
//    s.get_all_movies(Genre(4), a);
//    s.remove_user(5740);
//    s.user_watch(5046, 4834);
//    s.remove_movie(4637);
//    s.add_user(5450, true);
//    s.add_user(3655, true);
//    s.get_all_movies_count(Genre(1));
//    s.add_user(6007, true);
//    s.user_watch(3655, 7517);
//    s.get_all_movies_count(Genre(0));
//    s.get_all_movies(Genre(1), a);
//    s.add_user(5973, false);
//    s.get_all_movies(Genre(2), a);
//    s.get_all_movies(Genre(3), a);
//    s.add_movie(1771, Genre(0), 77, true);
//    s.add_user(1211, false);
//    s.user_watch(5740, 1771);
//    s.add_movie(4008, Genre(2), 8, true);
//    s.get_all_movies(Genre(4), a);
//    s.get_all_movies_count(Genre(0));
//    s.get_all_movies_count(Genre(2));
//    s.user_watch(3655, 4008);
//    s.user_watch(5740, 4008);
//    s.add_group(8180);
//    s.add_user_to_group(5973, 8180);
//    s.remove_user(8643);
//    s.add_group(2254);
//    s.remove_user(5046);
//    s.remove_group(2254);
//    s.remove_group(3182);
//    s.remove_movie(4008);
//    s.remove_movie(1771);
//    s.add_movie(1376, Genre(3), 8, false);
//    s.add_user_to_group(1211, 3906);
//    s.add_user_to_group(3655, 8180);
//    s.group_watch(3182, 1376);
//    s.get_all_movies_count(Genre(2));
//    s.user_watch(1211, 1376);
//    s.add_user_to_group(1211, 3906);
//    s.add_movie(6549, Genre(2), 58, false);
//    s.remove_movie(2038);
//    s.get_all_movies(Genre(4), a);
//    s.get_group_recommendation(3906);
//    s.rate_movie(1211, 6549, 14);
//    s.rate_movie(5450, 6549, 48);
//    s.add_user(3931, true);
//    s.get_all_movies(Genre(0), a);
//    s.get_all_movies(Genre(1), a);
//    s.get_num_views(1211, Genre(1));
//    s.get_all_movies(Genre(2), a);
//    s.remove_movie(1376);
//    s.get_all_movies(Genre(1), a);
//    s.user_watch(6007, 6549);
//    s.add_user(188, false);
//    s.add_user(2103, true);
//    s.add_user_to_group(2103, 3182);
//    s.remove_group(3182);
//    s.rate_movie(3655, 6549, 78);
//    s.add_group(6737);
//    s.get_all_movies(Genre(4), a);
//    s.get_all_movies(Genre(4), a);
//    s.add_user(7092, true);
//    s.add_group(8818);
//    s.remove_movie(6549);
//    s.rate_movie(1744, 6549, 17);
//    s.get_group_recommendation(8180);
//    s.remove_user(2103);

    int d1, d2, d3, g1;
    string b1;
    bool b;
    // Init
    streaming_database *obj = new streaming_database();

    // Execute all commands in file
	string op;
	while (cin >> op)
    {
        if (!op.compare("break")) {
            int i = 3;
        } else if (!op.compare("add_movie")) {
            cin >> d1 >> g1 >> d2 >> b1;
            if (!b1.compare("True")) {
                b = true;
            }
            else if (!b1.compare("False")) {
                b = false;
            }
            else {
                cout << "Invalid input format" << endl;
                return -1;
            }
            print(op, obj->add_movie(d1, (Genre) g1, d2, b));
        } else if (!op.compare("remove_movie")) {
            cin >> d1;
            print(op, obj->remove_movie(d1));
        } else if (!op.compare("add_user")) {
            cin >> d1 >> b1;
            if (!b1.compare("True")) {
                b = true;
            }
            else if (!b1.compare("False")) {
                b = false;
            }
            else {
                cout << "Invalid input format" << endl;
                return -1;
            }
            print(op, obj->add_user(d1, b));
        } else if (!op.compare("remove_user")) {
            cin >> d1;
            print(op, obj->remove_user(d1));
        } else if (!op.compare("add_group")) {
            cin >> d1;
            print(op, obj->add_group(d1));
        } else if (!op.compare("remove_group")) {
            cin >> d1;
            print(op, obj->remove_group(d1));
        } else if (!op.compare("add_user_to_group")) {
            cin >> d1 >> d2;
            print(op, obj->add_user_to_group(d1, d2));
        } else if (!op.compare("get_all_movies_count")) {
            cin >> g1;
            print(op, obj->get_all_movies_count((Genre) g1));
        } else if (!op.compare("get_all_movies")) {
            cin >> g1;
            query_get_all_movies(op, obj, (Genre) g1);
        } else if (!op.compare("user_watch")) {
            cin >> d1 >> d2;
            print(op, obj->user_watch(d1, d2));
        } else if (!op.compare("group_watch")) {
            cin >> d1 >> d2;
            print(op, obj->group_watch(d1, d2));
        } else if (!op.compare("get_num_views")) {
            cin >> d1 >> g1;
            print(op, obj->get_num_views(d1, (Genre) g1));
        } else if (!op.compare("rate_movie")) {
            cin >> d1 >> d2 >> d3;
            print(op, obj->rate_movie(d1, d2, d3));
        } else if (!op.compare("get_group_recommendation")) {
            cin >> d1;
            print(op, obj->get_group_recommendation(d1));
        } else {
            cout << "Unknown command: " << op << endl;
            return -1;
        }
        // Verify no faults
        if (cin.fail()){
            cout << "Invalid input format" << endl;
            return -1;
        }
    }

    // Quit
	delete obj;

    return 0;
}

// Helpers
static const char *StatusTypeStr[] =
        {
                "SUCCESS",
                "ALLOCATION_ERROR",
                "INVALID_INPUT",
                "FAILURE"
        };

void print(string cmd, StatusType res) {
    cout << cmd << ": " << StatusTypeStr[(int) res] << endl;
}

void print(string cmd, output_t<int> res) {
    if (res.status() == StatusType::SUCCESS) {
        cout << cmd << ": " << StatusTypeStr[(int) res.status()] << ", " << res.ans() << endl;
    } else {
        cout << cmd << ": " << StatusTypeStr[(int) res.status()] << endl;
    }
}

void query_get_all_movies(string cmd, streaming_database *obj, Genre genre) {
    output_t<int> count = obj->get_all_movies_count(genre);
    int to_alloc = count.ans();
    if (to_alloc == 0) {
        //if there are no movies we will allocate 1 so that we will get failure instead of invalid input
        ++to_alloc;
    }
    // Allocate if okay
    int *out_mem = nullptr;
    if (count.status() == StatusType::SUCCESS) {
        out_mem = new int[to_alloc];
        for (int i = 0; i < to_alloc; ++i) out_mem[i] = -1;
    }
    // Call function
    StatusType status = obj->get_all_movies(genre, out_mem);
    print(cmd, status);
    if (status == StatusType::SUCCESS) {
        for (int i = 0; i < to_alloc; ++i) {
            cout << out_mem[i] << endl;
        }
    }
    delete[] out_mem;
}
