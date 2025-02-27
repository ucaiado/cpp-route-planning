#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    // TODO 2: Use the m_Model.FindClosestNode method to find the closest nodes to the starting and ending coordinates.
    // Store the nodes you find in the RoutePlanner's start_node and end_node attributes.
    // NOTE: start_node and end_node are private pointers attributed
    this->start_node = &m_Model.FindClosestNode(start_x, start_y);
    this->end_node = &m_Model.FindClosestNode(end_x, end_y);

}


// TODO 3: Implement the CalculateHValue method.
// Tips:
// - You can use the distance to the end_node for the h value.
// - Node objects have a distance method to determine the distance to another node.

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
    return node->distance(*end_node);
}


// TODO 4: Complete the AddNeighbors method to expand the current node by adding all unvisited neighbors to the open list.
// Tips:
// - Use the FindNeighbors() method of the current_node to populate current_node.neighbors vector with all the neighbors.
// - For each node in current_node.neighbors, set the parent, the h_value, the g_value. 
// - Use CalculateHValue below to implement the h-Value calculation.
// - For each node in current_node.neighbors, add the neighbor to open_list and set the node's visited attribute to true.

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {

    current_node->FindNeighbors();
    for (auto neighbor_node : current_node->neighbors){
        neighbor_node->parent = current_node;
        neighbor_node->h_value = CalculateHValue(neighbor_node);
        neighbor_node->g_value = current_node->g_value + current_node->distance(*neighbor_node);
        neighbor_node->visited = true;
        open_list.push_back(neighbor_node);
    }

}


// TODO 5: Complete the NextNode method to sort the open list and return the next node.
// Tips:
// - Sort the open_list according to the sum of the h value and g value.
// - Create a pointer to the node in the list with the lowest sum.
// - Remove that node from the open_list.
// - Return the pointer.

/**
 * Compare the F values of two nodes.
 */
bool Compare(const RouteModel::Node *a, const RouteModel::Node *b) {
  float f1 = a->g_value + a->h_value; // f1 = g1 + h1
  float f2 = b->g_value + b->h_value; // f2 = g2 + h2
  return f1 > f2;
}

RouteModel::Node *RoutePlanner::NextNode() {
    std::sort(open_list.begin(), open_list.end(), Compare);
    auto next_node = open_list.back();
    open_list.pop_back();
    return next_node;
}


// TODO 6: Complete the ConstructFinalPath method to return the final path found from your A* search.
// Tips:
// - This method should take the current (final) node as an argument and iteratively follow the 
//   chain of parents of nodes until the starting node is found.
// - For each node in the chain, add the distance from the node to its parent to the distance variable.
// - The returned vector should be in the correct order: the start node should be the first element
//   of the vector, the end node should be the last element.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    // TODO: Implement your solution here.

    // follow the chain of parents of nodes until the starting node is found (initialized with
    //  parent == nullptr in the route_model header)
    while (current_node->parent != nullptr){
        path_found.push_back(*current_node);
        // For each node in the chain, add the distance from the node to its parent to the distance
        //   variable
        distance += current_node->distance(*current_node->parent);
        current_node = current_node->parent;
    }
    // include the starting node to the list (which was not included in the while above)
    path_found.push_back(*current_node);

    // path_found the order of the returned vector
    // source: https://stackoverflow.com/questions/8877448/how-do-i-reverse-a-c-vector
    std::reverse(path_found.begin(), path_found.end());

    // Multiply the distance by the scale of the map to get meters.
    distance *= m_Model.MetricScale();
    return path_found;

}


// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath method to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;

    // TODO: Implement your solution here.

    // Include the starting node to the open_list
    start_node->visited=true;
    open_list.push_back(start_node);

    while (open_list.size() > 0) {
        // sort the open_list and get the next node
        auto current_node = NextNode();
        // Check if we're reached the end_node
        float dist = current_node->distance(*end_node);
        if (current_node->distance(*end_node) == 0){
            m_Model.path = ConstructFinalPath(current_node);
            break;
        }
        // If we're not done, expand search to current node's neighbors
        AddNeighbors(current_node);
    }

}