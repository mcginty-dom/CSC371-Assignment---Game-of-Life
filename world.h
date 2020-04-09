/**
 * Declares a class representing a 2d grid world for simulating a cellular automaton.
 * Rich documentation for the api and behaviour the World class can be found in world.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author 951939
 * @date March, 2020
 */
#pragma once

// Add the minimal number of includes you need in order to declare the class.
// #include ...
#include "grid.h"
/**
 * Declare the structure of the World class for representing a 2d grid world.
 *
 * A World holds two equally sized Grid objects for the current state and next state.
 *      - These buffers should be swapped using std::swap after each update step.
 */
class World {
    private:
    Grid current_state;
    Grid next_state;
    unsigned int count_neighbours(int x, int y, bool toroidal);
    public:
    World();
    World(unsigned int square_size);
    World(unsigned int width, unsigned int height);
    World(Grid initial_state);
    ~World();
    const unsigned int get_width() const;
    const unsigned int get_height() const;
    const unsigned int get_total_cells() const;
    const unsigned int get_alive_cells() const;
    const unsigned int get_dead_cells() const;
    const Grid &get_state() const;
    void resize(unsigned int square_size);
    void resize(unsigned int new_width, unsigned int new_height);
    void step(bool toroidal = false);
    void advance(int steps, bool toroidal = false);
};