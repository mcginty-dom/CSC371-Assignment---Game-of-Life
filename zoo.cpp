/**
 * Implements a Zoo namespace with methods for constructing Grid objects containing various creatures in the Game of Life.
 *      - Creatures like gliders, light weight spaceships, and r-pentominos can be spawned.
 *          - These creatures are drawn on a Grid the size of their bounding box.
 *
 *      - Grids can be loaded from and saved to an ascii file format.
 *          - Ascii files are composed of:
 *              - A header line containing an integer width and height separated by a space.
 *              - followed by (height) number of lines, each containing (width) number of characters,
 *                terminated by a newline character.
 *              - (space) ' ' is Cell::DEAD, (hash) '#' is Cell::ALIVE.
 *
 *      - Grids can be loaded from and saved to an binary file format.
 *          - Binary files are composed of:
 *              - a 4 byte int representing the grid width
 *              - a 4 byte int representing the grid height
 *              - followed by (width * height) number of individual bits in C-style row/column format,
 *                padded with zero or more 0 bits.
 *              - a 0 bit should be considered Cell::DEAD, a 1 bit should be considered Cell::ALIVE.
 *
 * @author 951939
 * @date March, 2020
 */


// Include the minimal number of headers needed to support your implementation.
// #include ...
#include "grid.h"
#include "world.h"
#include "zoo.h"
#include <fstream>
#include <bitset>
#include <iostream>

/**
 * Zoo::glider()
 *
 * Construct a 3x3 grid containing a glider.
 * https://www.conwaylife.com/wiki/Glider
 *
 * @example
 *
 *      // Print a glider in a Grid the size of its bounding box.
 *      std::cout << Zoo::glider() << std::endl;
 *
 *      +---+
 *      | # |
 *      |  #|
 *      |###|
 *      +---+
 *
 * @return
 *      Returns a Grid containing a glider.
 */

Grid Zoo::glider() {
    Grid grid = Grid(3);
    grid.set(1,0,Cell::ALIVE);
    grid.set(2,1,Cell::ALIVE);
    for (unsigned int x=0; x<grid.get_width(); x++) {
        grid.set(x,2,Cell::ALIVE);
    }
    return grid;
}

/**
 * Zoo::r_pentomino()
 *
 * Construct a 3x3 grid containing an r-pentomino.
 * https://www.conwaylife.com/wiki/R-pentomino
 *
 * @example
 *
 *      // Print an r-pentomino in a Grid the size of its bounding box.
 *      std::cout << Zoo::r_pentomino() << std::endl;
 *
 *      +---+
 *      | ##|
 *      |## |
 *      | # |
 *      +---+
 *
 * @return
 *      Returns a Grid containing a r-pentomino.
 */

Grid Zoo::r_pentomino() {
    Grid grid = Grid(3);
    grid.set(0,1,Cell::ALIVE);
    grid.set(2,0,Cell::ALIVE);
    for (unsigned int y=0; y<grid.get_height(); y++) {
        grid.set(1,y,Cell::ALIVE);
    }
    return grid;
}

/**
 * Zoo::light_weight_spaceship()
 *
 * Construct a 5x4 grid containing a light weight spaceship.
 * https://www.conwaylife.com/wiki/Lightweight_spaceship
 *
 * @example
 *
 *      // Print a light weight spaceship in a Grid the size of its bounding box.
 *      std::cout << Zoo::light_weight_spaceship() << std::endl;
 *
 *      +-----+
 *      | #  #|
 *      |#    |
 *      |#   #|
 *      |#### |
 *      +-----+
 *
 * @return
 *      Returns a grid containing a light weight spaceship.
 */

Grid Zoo::light_weight_spaceship() {
    Grid grid = Grid(5,4);
    grid.set(4,0,Cell::ALIVE);
    grid.set(4,2,Cell::ALIVE);
    grid.set(1,0,Cell::ALIVE);
    for (unsigned int y=1; y<grid.get_height(); y++) {
        grid.set(0,y,Cell::ALIVE);
    }
    
    for (unsigned int x=1; x<grid.get_width()-1; x++) {
        grid.set(x,3,Cell::ALIVE);
    }
    return grid;
}

/**
 * Zoo::load_ascii(path)
 *
 * Load an ascii file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an ascii file from a directory
 *      Grid grid = Zoo::load_ascii("path/to/file.gol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The parsed width or height is not a positive integer.
 *          - Newline characters are not found when expected during parsing.
 *          - The character for a cell is not the ALIVE or DEAD character.
 */

Grid Zoo::load_ascii(std::string path) {
    //TODO: VALGRIND FIX
    std::ifstream in(path);
    std::string line;
    std::getline(in,line);
    unsigned int width, height;
    //-48 for ASCII code, casted to an unsigned int
    width = (unsigned int) (line[0]-48);
    height =  (unsigned int) (line[2]-48);
    Grid grid = Grid(width,height);
    char cell;
    for (unsigned int y = 0; y < grid.get_height(); y++) {
        std::getline(in,line);
        for (unsigned int x = 0; x < grid.get_width(); x++) {
            cell = line[x];
            if (cell == '#') {
                grid.set(x,y,Cell::ALIVE);
            } else if (cell == ' ') {
                grid.set(x,y,Cell::DEAD);
            } 
        }
    }
    in.close();
    return grid;
}

/**
 * Zoo::save_ascii(path, grid)
 *
 * Save a grid as an ascii .gol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an ascii file in a directory
 *      try {
 *          Zoo::save_ascii("path/to/file.gol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */

void Zoo::save_ascii(std::string path, Grid grid) {
    std::ofstream out(path);
    if (out.is_open()) {
        out << grid.get_width() << ' ' << grid.get_height() << '\n';
        for (unsigned int y = 0; y < grid.get_height(); y++) {
            for (unsigned int x = 0; x < grid.get_width(); x++) {
                if (grid.get(x,y)==Cell::ALIVE) {
                out << '#';
                } else {
                out << ' ';
                }
            }
            out << '\n';
        }
        out.close();
    } else {
        throw std::runtime_error("Zoo::save_ascii exception");
    }
}

/**
 * Zoo::load_binary(path)
 *
 * Load a binary file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an binary file from a directory
 *      Grid grid = Zoo::load_binary("path/to/file.bgol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The file ends unexpectedly.
 */

Grid Zoo::load_binary(std::string path) {
    std::ifstream in (path);
    int32_t width, height;
    in.read((char*) &width,4);
    in.read((char*) &height,4);
    //std::cout << width << " " << height;
    Grid grid = Grid(width,height);
    //std::bitset<8> buffer;
    int num_bytes = (width*height)/8;
    if (((width*height)/8) % 8 != 0) {
        num_bytes++;
    }
    //std::cout << num_bytes;
    std::vector<Cell> cells;
    for (int i=0; i<num_bytes; i++) {
        //std::cout << byte;
        std::bitset<8> buffer(in.get());
        for (int z=0; z<8; z++) {
            if (buffer.test(z)) {
                cells.push_back(Cell::ALIVE);
                //std::cout << "1";
            } else {
                cells.push_back(Cell::DEAD);
                //std::cout << "0";
            }
        }
    }
    //std::cout << std::endl << "vector size: " << cells.size() << std::endl;
    for (unsigned int y=0; y<grid.get_height(); y++) {
        for (unsigned int x=0; x<grid.get_width(); x++) {
            grid.set(x,y,cells[x+(y*grid.get_width())]);
        }
    }
    //std::cout << grid;
    in.close();
    return grid;
}

/**
 * Zoo::save_binary(path, grid)
 *
 * Save a grid as an binary .bgol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an binary file in a directory
 *      try {
 *          Zoo::save_binary("path/to/file.bgol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */

void Zoo::save_binary(std::string path, Grid grid) {
    std::ofstream out(path);
    if (out.is_open()) {
        int32_t width = (int32_t) grid.get_width();
        int32_t height = (int32_t) grid.get_height();
        out.write((char*) &width, 4);
        out.write((char*) &height, 4);
        //std::cout << byte;
        //create a counter to go to 8 everytime it accesses a new coordinate, at 8 write and reset
        std::bitset<8> buffer("        ", 8, '#', ' ');
        int counter = 0;
        for (unsigned int y=0; y<grid.get_height(); y++) {
            for (unsigned int x=0; x<grid.get_width(); x++) {
                if (grid.get(x,y)==Cell::ALIVE) {
                    buffer.set(counter,true);
                    //std::cout << "1";
                } else {
                    buffer.set(counter,false);
                    //std::cout << "0";
                }
                
                if (counter==7) {
                    //std::cout << "writing buffer: " << buffer;
                    out.write((char*) &buffer, 1);
                    counter=0;

                } else {
                    counter++;
                }
            }
        }
        if (counter!=0) {
            while (counter<=7) {
                //std::cout << "padding time";
                buffer.set(counter,false);
                counter++;
            }
            out.write((char*) &buffer, 1);
        }
        out.close();
    } else {
        throw std::runtime_error("Zoo::save_binary exception.");
    }
}