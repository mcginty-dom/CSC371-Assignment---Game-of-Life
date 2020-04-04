/**
 * Declares a class representing a 2d grid of cells.
 * Rich documentation for the api and behaviour the Grid class can be found in grid.cpp.
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
#include <vector>
#include <ostream>

/**
 * A Cell is a char limited to two named values for Cell::DEAD and Cell::ALIVE.
 */
enum Cell : char {
    DEAD  = ' ',
    ALIVE = '#'
};

/**
 * Declare the structure of the Grid class for representing a 2d grid of cells.
 */
class Grid {
    private:
        unsigned int width;
        unsigned int height;
        std::vector<Cell> cells;
        const unsigned int get_index(unsigned int x, unsigned int y) const;
    public:
        Grid();
        Grid(unsigned int square_size);
        Grid(unsigned int width, unsigned int height);
        ~Grid();

        const unsigned int get_width() const;
        const unsigned int get_height() const;
        const unsigned int get_total_cells() const;
        const unsigned int get_alive_cells() const;
        const unsigned int get_dead_cells() const;
        void resize(unsigned int square_size);
        void resize(unsigned int width, unsigned int height);
        const Cell get(unsigned int x, unsigned int y) const;
        void set(unsigned int x, unsigned int y, Cell value);
        Cell &operator()(unsigned int x,unsigned int y);
        const Cell &operator()(unsigned int x,unsigned int y) const;
        const Grid crop(unsigned int x0,unsigned int y0,unsigned int x1,unsigned int y1) const;
        void merge(Grid other, unsigned int x0, unsigned int y0, bool alive_only=false);
        const Grid rotate(int _rotation) const;
        friend std::ostream &operator<<(std::ostream &os, const Grid grid);
    // How to draw an owl:
    //      Step 1. Draw a circle.
    //      Step 2. Draw the rest of the owl.
};
