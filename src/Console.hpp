/*
 * Console.hpp
 *
 *  Created on: Apr 6, 2016
 *      Author: mateusz
 */

#ifndef CONSOLE_HPP_
#define CONSOLE_HPP_


#include <iostream>
#include <string>
#include <sstream>
#include <tuple>
#include <vector>

// Console convenience class for getting user input
class Console {
public:

    // Get user input and split it into [command, params]
    static std::tuple<std::string, std::vector<std::string>> getInput() {

        // get entire line from console
        std::string line;
        getline(std::cin, line);
        std::stringstream ss { line };

        // first string is the command
        std::string command;
        getline(ss, command, ' ');

        // subsequent strings are params
        std::string param;
        std::vector<std::string> params;
        while (getline(ss, param, ' '))
            params.push_back(param);

        return make_tuple(command, params);
    }
};


#endif /* CONSOLE_HPP_ */
