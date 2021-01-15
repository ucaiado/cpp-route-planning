A* Route Planner using OpenStreetMap
================


This project is part of the [C++ Nanodegree](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213)
 program from Udacity. I used OpenStreetMap data and the IO2D visualization
 library to build a route planner using the A* search algorithm, implemented in C++,
 to find a path between two points on a real-world map. The Dockefile used here
 was based on this [repository](https://github.com/MrD504/cpp-route-docker).

<p align="center"><img src="map.png" alt="Example" width="50%" style="middle"></p>


### Install
To set up your environment to run the code in this repository, start by cloning
 this project using the `--recurse-submodules` flag. Afterward, install Docker
 in your machine and the appropriate Xserver. Then, start both and configure
 Xserver as explained [here](https://medium.com/@mreichelt/how-to-show-x11-windows-within-docker-on-mac-50759f4b65cb).
 You may need to restart your computer. Finally, run the following commands. You
 should see a blank map.
```shell
$ make docker-build
$ make blank-map
```


### Run
In a terminal or command window, navigate to the top-level project directory
 `cpp-route-planning/` (that contains this README) and run the following
 commands. This will run the project tests and then run the final code, opening
 a map with a path filled.

```shell
$ make tests
$ make route
```


### License
The contents of this repository are covered under the [MIT License](LICENSE).

