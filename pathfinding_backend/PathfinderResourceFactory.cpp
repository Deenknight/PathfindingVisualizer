#include "PathfinderResourceFactory.h"

#include <random>
#include <iostream>

#include <sstream>
#include <iomanip>

#include "json.hpp"

PathfinderResourceFactory::PathfinderResourceFactory(){
    _resource = make_shared<Resource>();
    _resource->set_path(
        "/{start: [0-9]+}"
        "/{end: [0-9]+}"
        "/{rows: [0-9]+}"
        "/{columns: [0-9]+}"
    );

    _resource->set_method_handler("GET", [&](const shared_ptr<Session> session){
        get_handler(session);
    });
}

bool* PathfinderResourceFactory::generate_maze(int start, int end, const int* dimensions){
    std::random_device rd;     // Only used once to initialise (seed) engine
    std::mt19937 rng(rd());    // Random-number engine used (Mersenne-Twister in this case)
    std::uniform_int_distribution<int> uni(0,2); // Guaranteed unbiased

    
    const int ROWS = dimensions[0];
    const int COLUMNS = dimensions[1];

    const int TOTAL_NODES = ROWS*COLUMNS;
    bool* walls = new bool[TOTAL_NODES] { false };

    // the perimeter should be walled off

    for (int i = 0; i < ROWS; i++){
        walls[i*COLUMNS] = true;
        walls[(i+1)*COLUMNS - 1] = true;
    }

    for (int j = 0; j < COLUMNS; j++){
        walls[j] = true;
        walls[(ROWS-1)*COLUMNS + j] = true;
    }

    for (int row = 0; row < ROWS; row++){
        for (int col = 0; col < COLUMNS; col++){

            const int ONE_DIMENSIONAL_INDEX = (row)*COLUMNS + col;

            if (!walls[ONE_DIMENSIONAL_INDEX]){
                std::cout << " ";
            } else {
                std::cout << "+";
            }
        }
        std::cout << std::endl;
    }

    std::cout << '\n' << std::endl;

    // sidewinder maze generation
    
    for (int i = 1; i < int((ROWS)/2); i++){
        int runStart = 2*COLUMNS*i + 1;

        for (int j = 1; j < COLUMNS-1; j++){
            const int ONE_DIMENSIONAL_INDEX = (i*2)*COLUMNS + j;

            const int END_RUN = uni(rng);
            if (END_RUN == 1){
                std::uniform_int_distribution<int> run_distribution(
                    runStart,ONE_DIMENSIONAL_INDEX);

                const int GAP_NODE = run_distribution(rng);
                walls[GAP_NODE - COLUMNS] = false;
                if (ONE_DIMENSIONAL_INDEX + 1 != start && ONE_DIMENSIONAL_INDEX +1 != end){
                    walls[ONE_DIMENSIONAL_INDEX] = true;
                }
                
                runStart = ONE_DIMENSIONAL_INDEX + 1;
                
            } else if (ONE_DIMENSIONAL_INDEX - COLUMNS != start 
                && ONE_DIMENSIONAL_INDEX - COLUMNS != end){

                    walls[ONE_DIMENSIONAL_INDEX - COLUMNS] = true;
            }
        }

        // if there is still a run once we reach the end of the row, run the algorithm
        const int ROW_END_INDEX = (i*2+1)*COLUMNS-2;

        if (runStart < ROW_END_INDEX){
            
    
            std::uniform_int_distribution<int> run_distribution(
                    runStart,ROW_END_INDEX);

            const int GAP_NODE = run_distribution(rng);
            walls[GAP_NODE - COLUMNS] = false;
        }

    }

    for (int row = 0; row < ROWS; row++){
        for (int col = 0; col < COLUMNS; col++){
            const int ONE_DIMENSIONAL_INDEX = (row)*COLUMNS + col;
            if (walls[ONE_DIMENSIONAL_INDEX] == 0){
                std::cout << " ";
            } else {
                std::cout << "+";
            }
        }
        std::cout << std::endl;
    }


    return walls;
}

tuple<int, int, int*> PathfinderResourceFactory::get_path_parameters(
    const shared_ptr<Session> session){
    
    const auto& request = session->get_request();
    int start = stoi(request->get_path_parameter("start"));
    int end = stoi(request->get_path_parameter("end"));
    int rows = stoi(request->get_path_parameter("rows"));
    int columns = stoi(request->get_path_parameter("columns"));
    
    return make_tuple(start, end, new int[2] {rows, columns});
}

string PathfinderResourceFactory::to_json(const bool* walls, const int* dimensions){
    const int NODES = dimensions[0]*dimensions[1];
    
    ostringstream str_stream;
    
    str_stream << '[';
    for (int i = 0; i < NODES-1; i++){
        str_stream << walls[i] << ", ";
    }
    str_stream << walls[NODES-1] << ']';

    nlohmann::json jsonWalls = {
        {"walls", str_stream.str()}
    };

    return jsonWalls.dump();
}

shared_ptr<Resource> PathfinderResourceFactory::get_resource() const {
    return _resource;
}

void PathfinderResourceFactory::get_handler(const shared_ptr<Session> session){
    const auto [start, end, dimensions] = get_path_parameters(session);
    const bool* walls = generate_maze(start, end, dimensions);

    auto content = to_json(walls, dimensions);

    delete[] dimensions;
    delete[] walls;

    session->close(OK, content, {{"Content-Length", to_string(content.size())}});


}