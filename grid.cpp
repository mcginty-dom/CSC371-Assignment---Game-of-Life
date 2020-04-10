/**
 * Implements a class representing a 2d grid of cells.
 *      - New cells are initialized to Cell::DEAD.
 *      - Grids can be resized while retaining their contents in the remaining area.
 *      - Grids can be rotated, cropped, and merged together.
 *      - Grids can return counts of the alive and dead cells.
 *      - Grids can be serialized directly to an ascii std::ostream.
 *
 * You are encouraged to use STL container types as an underlying storage mechanism for the grid cells.
 *
 * @author 951939
 * @date March, 2020
 */
#include "grid.h"

// Include the minimal number of headers needed to support your implementation.
// #include ...
#include <ostream>
/**
 * Grid::Grid()
 *
 * Construct an empty grid of size 0x0.
 * Can be implemented by calling Grid::Grid(square_size) constructor.
 *
 * @example
 *
 *      // Make a 0x0 empty grid
 *      Grid grid;
 *
 */

Grid::Grid(): Grid(0) {
}

/**
 * Grid::Grid(square_size)
 *
 * Construct a grid with the desired size filled with dead cells.
 * Single value constructors should be marked "explicit" to prevent them
 * being used to implicitly cast ints to grids on construction.
 *
 * Can be implemented by calling Grid::Grid(width, height) constructor.
 *
 * @example
 *
 *      // Make a 16x16 grid
 *      Grid x(16);
 *
 *      // Also make a 16x16 grid
 *      Grid y = Grid(16);
 *
 *      // This should be a compiler error! We want to prevent this from being allowed.
 *      Grid z = 16;
 *
 * @param square_size
 *      The edge size to use for the width and height of the grid.
 */

Grid::Grid(const unsigned int square_size): Grid(square_size,square_size) {    
}

/**
 * Grid::Grid(width, height)
 *
 * Construct a grid with the desired size filled with dead cells.
 *
 * @example
 *
 *      // Make a 16x9 grid
 *      Grid grid(16, 9);
 *
 * @param width
 *      The width of the grid.
 *
 * @param height
 *      The height of the grid.
 */

Grid::Grid(const unsigned int width, const unsigned int height): width(width), height(height) {
    //creates an std::vector of cells of size width*height full of dead cells
    cells.resize(width*height,Cell::DEAD);
}

Grid::~Grid() {
}

/**
 * Grid::get_width()
 *
 * Gets the current width of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the width of the grid to the console
 *      std::cout << grid.get_width() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the width of the grid to the console
 *      std::cout << read_only_grid.get_width() << std::endl;
 *
 * @return
 *      The width of the grid.
 */

unsigned int Grid::get_width() const {
    return width;
}

/**
 * Grid::get_height()
 *
 * Gets the current height of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the height of the grid to the console
 *      std::cout << grid.get_height() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the height of the grid to the console
 *      std::cout << read_only_grid.get_height() << std::endl;
 *
 * @return
 *      The height of the grid.
 */

unsigned int Grid::get_height() const {
    return height;
}

/**
 * Grid::get_total_cells()
 *
 * Gets the total number of cells in the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << grid.get_total_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << read_only_grid.get_total_cells() << std::endl;
 *
 * @return
 *      The number of total cells.
 */

unsigned int Grid::get_total_cells() const {
    return cells.size();
}

/**
 * Grid::get_alive_cells()
 *
 * Counts how many cells in the grid are alive.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of alive cells to the console
 *      std::cout << grid.get_alive_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of alive cells to the console
 *      std::cout << read_only_grid.get_alive_cells() << std::endl;
 *
 * @return
 *      The number of alive cells.
 */

unsigned int Grid::get_alive_cells() const{
    return get_total_cells()-get_dead_cells();
}

/**
 * Grid::get_dead_cells()
 *
 * Counts how many cells in the grid are dead.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of dead cells to the console
 *      std::cout << grid.get_dead_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of dead cells to the console
 *      std::cout << read_only_grid.get_dead_cells() << std::endl;
 *
 * @return
 *      The number of dead cells.
 */

unsigned int Grid::get_dead_cells() const{
    //From idx to x,y, iterates through std::vector of cells to calculate number of dead cells
    unsigned int x, y, dead_cells = 0;
    for (unsigned int idx=0; idx<get_total_cells(); idx++) {
        x = idx % get_width();
        y = (idx - x) / get_width();
        if (get(x,y)==Cell::DEAD) {
            dead_cells++;
        }
    }
    return dead_cells;
}

/**
 * Grid::resize(square_size)
 *
 * Resize the current grid to a new width and height that are equal. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 8x8
 *      grid.resize(8);
 *
 * @param square_size
 *      The new edge size for both the width and height of the grid.
 */

void Grid::resize(const unsigned int square_size) {
    //Calls resize function below
    resize(square_size,square_size);
}

/**
 * Grid::resize(width, height)
 *
 * Resize the current grid to a new width and height. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 2x8
 *      grid.resize(2, 8);
 *
 * @param new_width
 *      The new width for the grid.
 *
 * @param new_height
 *      The new height for the grid.
 */

void Grid::resize(const unsigned int new_width, const unsigned int new_height) {
    //Create a new grid with updated width/height and loops through x,y
    Grid new_grid = Grid(new_width, new_height);
    for (unsigned int y = 0; y < new_height; y++) {
        for (unsigned int x = 0; x < new_width; x++) {
            //if within bounds of current grid then 
            if ((x<get_width()) && (y<get_height())) {
                //set value of same x,y position onto new grid
                new_grid.set(x,y,get(x,y));
            //else pad new area with dead cells
            } else {
                new_grid.set(x,y,Cell::DEAD);
            }
        }
    }
    //replace current grid with new grid
    (*this) = new_grid;
}

/**
 * Grid::get_index(x, y)
 *
 * Private helper function to determine the 1d index of a 2d coordinate.
 * Should not be visible from outside the Grid class.
 * The function should be callable from a constant context.
 *
 * @param x
 *      The x coordinate of the cell.
 *
 * @param y
 *      The y coordinate of the cell.
 *
 * @return
 *      The 1d offset from the start of the data array where the desired cell is located.
 */

unsigned int Grid::get_index(const unsigned int x, const unsigned int y) const{
    //from x,y to idx
    return (x+(y*get_width()));
}

/**
 * Grid::get(x, y)
 *
 * Returns the value of the cell at the desired coordinate.
 * Specifically this function should return a cell value, not a reference to a cell.
 * The function should be callable from a constant context.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Read the cell at coordinate (1, 2)
 *      Cell cell = grid.get(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @return
 *      The value of the desired cell. Should only be Grid::ALIVE or Grid::DEAD.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */

Cell Grid::get(const unsigned int x, const unsigned int y) const{
    //if within bounds then
    if (x>=0 && x<get_width() && y>=0 && y<get_height()) {
        //if cell is alive return alive
        if (operator()(x,y)==Cell::ALIVE) {
            return Cell::ALIVE;
        //else return dead
        } else {
            return Cell::DEAD;
        }
    //else throw exception
    } else {
        throw std::out_of_range("Grid::get out of bounds.");
    }
}

/**
 * Grid::set(x, y, value)
 *
 * Overwrites the value at the desired coordinate.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Assign to a cell at coordinate (1, 2)
 *      grid.set(1, 2, Cell::ALIVE);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @param value
 *      The value to be written to the selected cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */

void Grid::set(const unsigned int x, const unsigned int y, const Cell value){
    //if within bounds then
    if (x>=0 && x<get_width() && y>=0 && y<get_height()) {
        //replace value at modifiable reference
        operator()(x,y) = value;
    //else throw exception
    } else {
        throw std::out_of_range("Grid::set out of bounds.");
    }
}

/**
 * Grid::operator()(x, y)
 *
 * Gets a modifiable reference to the value at the desired coordinate.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = grid(1, 2);
 *
 *      // Directly assign to a cell at coordinate (1, 2)
 *      grid(1, 2) = Cell::ALIVE;
 *
 *      // Extract a reference to an individual cell to avoid calculating it's
 *      // 1d index multiple times if you need to access the cell more than once.
 *      Cell &cell_reference = grid(1, 2);
 *      cell_reference = Cell::DEAD;
 *      cell_reference = Cell::ALIVE;
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A modifiable reference to the desired cell.
 *
 * @throws
 *      std::runtime_error or sub-class if x,y is not a valid coordinate within the grid.
 */

Cell &Grid::operator()(const unsigned int x, const unsigned int y) {
    //if within bounds then
    if (x>=0 && x<get_width() && y>=0 && y<get_height()) {
        //gets a modifiable reference and returns it
        Cell &value = (cells[get_index(x, y)]); 
        return value;
    //else throw exception
    } else {
        throw std::runtime_error("Grid::operator() out of bounds.");
    }
}

/**
 * Grid::operator()(x, y)
 *
 * Gets a read-only reference to the value at the desired coordinate.
 * The operator should be callable from a constant context.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Constant reference to a grid (does not make a copy)
 *      const Grid &read_only_grid = grid;
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = read_only_grid(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A read-only reference to the desired cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */

const Cell &Grid::operator()(const unsigned int x, const unsigned int y) const {
    //if within bounds then
    if (x>=0 && x<get_width() && y>=0 && y<get_height()) {
        //gets a read-only reference and returns it
        const Cell &value = cells[get_index(x, y)]; 
        return value;
    //else throw exception
    } else {
        throw std::runtime_error("const Grid::operator() const out of bounds exception.");
    }
}

/**
 * Grid::crop(x0, y0, x1, y1)
 *
 * Extract a sub-grid from a Grid.
 * The cropped grid spans the range [x0, x1) by [y0, y1) in the original grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid y(4, 4);
 *
 *      // Crop the centre 2x2 in y, trimming a 1 cell border off all sides
 *      Grid x = y.crop(x, 1, 1, 3, 3);
 *
 * @param x0
 *      Left coordinate of the crop window on x-axis.
 *
 * @param y0
 *      Top coordinate of the crop window on y-axis.
 *
 * @param x1
 *      Right coordinate of the crop window on x-axis (1 greater than the largest index).
 *
 * @param y1
 *      Bottom coordinate of the crop window on y-axis (1 greater than the largest index).
 *
 * @return
 *      A new grid of the cropped size containing the values extracted from the original grid.
 *
 * @throws
 *      std::exception or sub-class if x0,y0 or x1,y1 are not valid coordinates within the grid
 *      or if the crop window has a negative size.
 */

Grid Grid::crop(const unsigned int x0,const unsigned int y0, const unsigned int x1, 
    const unsigned int y1) const{
    //if x1,y1 (right,bottom) > x0,y0 (left,top) and within bounds then
    if (x1>x0 && y1>y0 && x0>=0 && y0>=0 && x1<=get_width() && y1<=get_height()) {
        //Create a new grid and loop through x,y
        Grid new_grid = Grid(x1-x0,y1-y0);
        for (unsigned int y = y0; y < y1; y++) {
            for (unsigned int x = x0; x < x1; x++) {
                //gets value from x,y of current grid and sets it into x-x0,y-y0 of new grid
                new_grid.set(x-x0,y-y0,get(x,y));
            }
        }
        //returns new grid
        return new_grid;
    //else throw exception
    } else {
        if (x1<x0 || y1<y0) {
            throw std::runtime_error("Grid::crop invalid parameters.");
        } else {
            throw std::out_of_range("Grid::crop out of range.");
        }
    }
}

/**
 * Grid::merge(other, x0, y0, alive_only = false)
 *
 * Merge two grids together by overlaying the other on the current grid at the desired location.
 * By default merging overwrites all cells within the merge reason to be the value from the other grid.
 *
 * Conditionally if alive_only = true perform the merge such that only alive cells are updated.
 *      - If a cell is originally dead it can be updated to be alive from the merge.
 *      - If a cell is originally alive it cannot be updated to be dead from the merge.
 *
 * @example
 *
 *      // Make two grids
 *      Grid x(2, 2), y(4, 4);
 *
 *      // Overlay x as the upper left 2x2 in y
 *      y.merge(x, 0, 0);
 *
 *      // Overlay x as the bottom right 2x2 in y, reading only alive cells from x
 *      y.merge(x, 2, 2, true);
 *
 * @param other
 *      The other grid to merge into the current grid.
 *
 * @param x0
 *      The x coordinate of where to place the top left corner of the other grid.
 *
 * @param y0
 *      The y coordinate of where to place the top left corner of the other grid.
 *
 * @param alive_only
 *      Optional parameter. If true then merging only sets alive cells to alive but does not explicitly set
 *      dead cells, allowing whatever value was already there to persist. Defaults to false.
 *
 * @throws
 *      std::exception or sub-class if the other grid being placed does not fit within the bounds of the current grid.
 */

void Grid::merge(const Grid other, const int x0, const int y0, const bool alive_only) {
    //set width, height in current x,y to end merging
    const unsigned int other_width = x0+other.get_width();
    const unsigned int other_height = y0+other.get_height();
    //if within bounds then
    if (x0>=0 && y0>=0 && other_width<=get_width() && other_height<=get_height()) {
        //loop through x0,y0 ending at other width, height
        Cell value;
        for (unsigned int y = y0; y < other_height; y++) {
            for (unsigned int x = x0; x < other_width; x++) {
                //get values from other grid
                value = other.get(x-x0,y-y0);
                //if alive_only set to true then 
                if (alive_only) {
                    //only set alive cells from other grid to current grid
                    if (value==Cell::ALIVE) {
                        set(x,y,Cell::ALIVE);
                    }
                //else set dead and alive cells from other grid to current grid
                } else {
                    set(x,y,value);
                }
            }
        }
    //else throw exception
    } else {
        throw std::out_of_range("Grid::merge out of range.");
    }
    }

/**
 * Grid::rotate(rotation)
 *
 * Create a copy of the grid that is rotated by a multiple of 90 degrees.
 * The rotation can be any integer, positive, negative, or 0.
 * The function should take the same amount of time to execute for any valid integer input.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a 1x3 grid
 *      Grid x(1,3);
 *
 *      // y is size 3x1
 *      Grid y = x.rotate(1);
 *
 * @param _rotation
 *      An positive or negative integer to rotate by in 90 intervals.
 *
 * @return
 *      Returns a copy of the grid that has been rotated.
 */

Grid Grid::rotate(int _rotation) const {
    //sets rotation to be only 0,1,2 or 3
    _rotation = ((_rotation % 4) +4) % 4;
    //creates new grid and swaps the width and height size if rotation is an odd number
    Grid new_grid = Grid(get_width(),get_height());
    if ((_rotation==1) || (_rotation==3)) {
        new_grid = Grid(get_height(),get_width());
    }
    //if rotation is 0 then do nothing
    if (_rotation==0) {
        new_grid = (*this);
    } else {
        Cell value;
        unsigned int minus_x, minus_y;
        //iterate through x,y in new grid
        for (unsigned int y=0; y < new_grid.get_height(); y++) {
            for (unsigned int x=0; x < new_grid.get_width(); x++) {
                //calculates -x,-y to place inside cartesian equations
                minus_x = new_grid.get_width()-(x+1);
                minus_y = new_grid.get_height()-(y+1);
                //if rotation is 1 gets value from current grid rotated 90 degrees clockwise
                if (_rotation==1) {
                    value = (*this).get(y, minus_x);
                //else if rotation is 2 gets value from current grid rotated 180 degrees clockwise
                } else if (_rotation==2) {
                    value = (*this).get(minus_x, minus_y);
                //else get value from current grid rotated 90 degrees counter-clockwise
                } else {
                    value = (*this).get(minus_y, x);
                }
                //set said value into new grid
                new_grid.set(x,y,value);
            }
        }
    }
    //return new grid
    return new_grid;
} 

/**
 * operator<<(output_stream, grid)
 *
 * Serializes a grid to an ascii output stream.
 * The grid is printed wrapped in a border of - (dash), | (pipe), and + (plus) characters.
 * Alive cells are shown as # (hash) characters, dead cells with ' ' (space) characters.
 *
 * The function should be callable on a constant Grid.
 *
 * @example
 *
 *      // Make a 3x3 grid with a single alive cell
 *      Grid grid(3);
 *      grid(1, 1) = Cell::ALIVE;
 *
 *      // Print the grid to the console
 *      std::cout << grid << std::endl;
 *
 *      // The grid is printed with a border of + - and |
 *
 *      +---+
 *      |   |
 *      | # |
 *      |   |
 *      +---+
 *
 * @param os
 *      An ascii mode output stream such as std::cout.
 *
 * @param grid
 *      A grid object containing cells to be printed.
 *
 * @return
 *      Returns a reference to the output stream to enable operator chaining.
 */

std::ostream &operator<<(std::ostream &os, const Grid grid) {
    //creates top wrapper
    os << '+' << std::string(grid.get_width(), '-') << '+' << std::endl;
    //iterates through x,y of grid parameter
    for (unsigned int y = 0; y < grid.get_height(); y++) {
        //creates left wrapper
        os << '|';
        for (unsigned int x = 0; x < grid.get_width(); x++) {
            //if value in current grid is alive then output a hash
            if (grid.get(x,y)==Cell::ALIVE) {
                os << '#';
            //else output a space
            } else {
                os << ' ';
            }
        }
        //creates right wrapper
        os << '|' << std::endl;
    }
    //creates bottom wrapper
    os << '+' << std::string(grid.get_width(), '-') << '+' << std::endl;
	return os;
}