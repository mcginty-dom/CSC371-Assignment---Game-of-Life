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
#include "zoo.h"

// Include the minimal number of headers needed to support your implementation.
// #include ...
#include "grid.h"
#include <fstream>

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
    //Creates a grid and sets certain values to be alive for the grid to contain a glider
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
    //Creates a grid and sets certain values to be alive for the grid to contain a r-pentomino
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
    //Creates a grid and sets certain values to be alive for the grid to contain a light weight
    //spaceship
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

Grid Zoo::load_ascii(const std::string path) {
    //opens file and if file exists then
    std::ifstream in(path);
    if (in.is_open()) {
        //gets the first line to set width and height of the grid
        std::string line;
        std::getline(in,line);
        unsigned int width, height;
        //-48 for ASCII code (char to int conversion)
        width = line[0]-48;
        height = line[2]-48;
        //if width or height are negative then throw exception
        if (width<0 || height<0) {
            throw std::domain_error("Zoo::load_ascii negative width/height.");
        }
        //creates grid and loops through x,y on said grid
        Grid grid = Grid(width,height);
        char cell;
        for (unsigned int y = 0; y < grid.get_height(); y++) {
            //for every y increment, get a new line from ifstream
            std::getline(in,line);
            //if the length of the line does not equal the width of the grid then throw exception
            if (line.length()!=grid.get_width()) {
                throw std::length_error("Zoo::load_ascii line too short/too long.");
            } else {
                //for every x increment, get a char from the line string
                for (unsigned int x = 0; x < grid.get_width(); x++) {
                    cell = line[x];
                    //if char is a hash then set x,y on grid to be alive
                    if (cell == '#') {
                        grid.set(x,y,Cell::ALIVE);
                    //else if char is a space then set x,y on grive to be dead
                    } else if (cell == ' ') {
                        grid.set(x,y,Cell::DEAD);
                    //else throw exception
                    } else {
                        throw std::domain_error("Zoo::load_ascii unrecognized character.");
                    }
                }
            }
        }
        //close ifstream to prevent memory leaks and return grid
        in.close();
        return grid;
    //else throw exception
    } else {
        throw std::invalid_argument("Zoo::load_ascii file does not exist.");
    }
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

void Zoo::save_ascii(const std::string path, const Grid grid) {
    //opens file and if file exists then
    std::ofstream out(path);
    if (out.is_open()) {
        //outputs width and height of grid parameter into first line of the file
        out << grid.get_width() << ' ' << grid.get_height() << '\n';
        //loops through x,y of grid parameter
        for (unsigned int y = 0; y < grid.get_height(); y++) {
            for (unsigned int x = 0; x < grid.get_width(); x++) {
                //if x,y on grid is alive then output a hash
                if (grid.get(x,y)==Cell::ALIVE) {
                out << '#';
                //else output a space
                } else {
                out << ' ';
                }
            }
            //places a new line character whenever the x loop is finished (a row has been made)
            out << '\n';
        }
        //closes file to prevent memory leaks
        out.close();
    //else throw exception
    } else {
        throw std::invalid_argument("Zoo::save_ascii file does not exist.");
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

Grid Zoo::load_binary(const std::string path) {
    //opens file and if exists then
    std::ifstream in (path);
    if (in.is_open()) {
        //sets width and height of grid (4 byte char* -> 4 byte unsigned ints) and creates grid
        unsigned int width, height;
        in.read((char*) &width, 4);
        in.read((char*) &height, 4);
        Grid grid = Grid(width,height);
        //idx increments only during the for loop that loops through 0 to 7 bits of char byte
        unsigned int idx = 0;
        char byte;
        //calculates number of bits to load
        unsigned int num_bits = grid.get_width()*grid.get_height();
        //while the number of bits has not been reached
        while (idx<num_bits) {
            //reads in 8 bits into the char byte
            in.read(&byte, 1);
            //loops through 0 to 7 bits of the char byte
            for (unsigned int i=0; i<8; i++) {
                //if no (error) state flags set then
                if (in.good()) {
                    //if the number of bits has not been reached yet then
                    if (idx<num_bits) {
                        //calculates from idx to x,y
                        unsigned int x = idx % grid.get_width();
                        unsigned int y = (idx-x) / grid.get_width();
                        //performs a right shift and use a bitwise AND to get value of a bit
                        if ((byte >> i) & 1U) {
                            grid.set(x,y,Cell::ALIVE);
                        } else {
                            grid.set(x,y,Cell::DEAD);
                        }
                        //increments number of bits reached
                        idx++;
                    }
                //else throw exception
                } else {
                    throw std::runtime_error("Zoo::load_binary EOF reached too early.");
                }
            }
        }
        //closes ifstream to prevent memory leaks and returns filled grid
        in.close();
        return grid;
    //else throw exception
    } else {
        throw std::invalid_argument("Zoo::load_binary file does not exist.");
    }
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

void Zoo::save_binary(const std::string path, const Grid grid) {
    //opens file and if exists then
    std::ofstream out(path);
    if (out.is_open()) {
        unsigned int width = grid.get_width();
        unsigned int height = grid.get_height();
        //outputs width and height of grid parameter both as 4 byte ints
        out.write((char*) &width, 4);
        out.write((char*) &height, 4);
        //initialize number of bits reached and byte storage in char byte
        unsigned int idx = 0;
        char byte;
        //calculates number of bits to load
        unsigned int num_bits = grid.get_width()*grid.get_height();
        //while the number of bits has not been reached
        while (idx<num_bits) {
            //loops through number of bits in char byte (0 to 7)
            for (unsigned int i=0; i<8; i++) {
                //calculates from idx to x,y
                unsigned int x = idx % grid.get_width();
                unsigned int y = (idx-x) / grid.get_width();
                //if number of bits has not yet been reached then
                if (idx<num_bits) {
                    //if x,y in grid is alive then set bit by using a bitwise OR with 1 (true)
                    if (grid.get(x,y)==Cell::ALIVE) {
                        byte |= 1U << i;
                    //else clear bit by using a bitwise AND on itself and NOT itself
                    } else {
                        byte &= ~(1U << i);
                    }
                }
                //increment number of bits reached
                idx++;
            }
            //outputs 8 cell values within the grid to file (8 bit = 1 byte)
            out.write(&byte, 1);
        }
        //closes ofstream to prevent memory leaks
        out.close();
    //else throw exception
    } else {
        throw std::invalid_argument("Zoo::save_binary file does not exist.");
    }
}