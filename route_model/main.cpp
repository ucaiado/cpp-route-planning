#include <optional>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <io2d.h>
#include "route_model.h"
#include "render.h"
#include "route_planner.h"

using namespace std::experimental;


// START HELP FUNCTIONS

/**
 * Capture user input if passed between 0 and 100
 *  or use the values passed as default
 */
void capture_and_bound_user_input(
    float* start_x,
    float* start_y,
    float* end_x,
    float* end_y) {
        std::vector<float> v_user_inputs{-1.0, -1.0, -1.0, -1.0};
        std::vector<std::string> v_text{"start X", "start Y", "end X", "end Y"};
        bool b_allright = true;
        for( int ii = 0; ii < 4; ++ii ){
            std::cout << "Enter the " << v_text[ii] << " coordinate (0~100): ";
            std::cin >> v_user_inputs[ii];
            if((v_user_inputs[ii] < 0) || (v_user_inputs[ii] > 100)){
                std::cout << "  >> !! You entered a coordinate outside the boundaries. Using default values instead.\n";
                b_allright = false;
                break;
            }
        }
        if(b_allright){
            *start_x=v_user_inputs[0];
            *start_y=v_user_inputs[1];
            *end_x=v_user_inputs[2];
            *end_y=v_user_inputs[3];
        }
}

// END HELP FUNCTIONS


static std::optional<std::vector<std::byte>> ReadFile(const std::string &path)
{   
    std::ifstream is{path, std::ios::binary | std::ios::ate};
    if( !is )
        return std::nullopt;
    
    auto size = is.tellg();
    std::vector<std::byte> contents(size);    
    
    is.seekg(0);
    is.read((char*)contents.data(), size);

    if( contents.empty() )
        return std::nullopt;
    return std::move(contents);
}

int main(int argc, const char **argv)
{    
    std::string osm_data_file = "";
    if( argc > 1 ) {
        for( int i = 1; i < argc; ++i )
            if( std::string_view{argv[i]} == "-f" && ++i < argc )
                osm_data_file = argv[i];
    }
    else {
        std::cout << "To specify a map file use the following format: " << std::endl;
        std::cout << "Usage: [executable] [-f filename.osm]" << std::endl;
        osm_data_file = "../map.osm";
    }
    
    std::vector<std::byte> osm_data;
 
    if( osm_data.empty() && !osm_data_file.empty() ) {
        std::cout << "Reading OpenStreetMap data from the following file: " <<  osm_data_file << std::endl;
        auto data = ReadFile(osm_data_file);
        if( !data )
            std::cout << "Failed to read." << std::endl;
        else
            osm_data = std::move(*data);
    }
    
    // TODO 1: Declare floats `start_x`, `start_y`, `end_x`, and `end_y` and get
    // user input for these values using std::cin. Pass the user input to the
    // RoutePlanner object below in place of 10, 10, 90, 90.
    float start_x = 10.0f;
    float start_y = 10.0f;
    float end_x = 90.0f;
    float end_y = 90.0f;
    capture_and_bound_user_input(&start_x, &start_y, &end_x, &end_y);
    std::cout << "  >> Using coordinates (" << start_x << ", " << start_y << ", " << end_x << ", " << end_y << ")\n";

    // Build Model.
    RouteModel model{osm_data};

    // Create RoutePlanner object and perform A* search.
    RoutePlanner route_planner{model, start_x, start_y, end_x, end_y};
    route_planner.AStarSearch();

    std::cout << "Distance: " << route_planner.GetDistance() << " meters. \n";

    // Render results of search.
    Render render{model};

    auto display = io2d::output_surface{400, 400, io2d::format::argb32, io2d::scaling::none, io2d::refresh_style::fixed, 30};
    display.size_change_callback([](io2d::output_surface& surface){
        surface.dimensions(surface.display_dimensions());
    });
    display.draw_callback([&](io2d::output_surface& surface){
        render.Display(surface);
    });
    display.begin_show();
}
