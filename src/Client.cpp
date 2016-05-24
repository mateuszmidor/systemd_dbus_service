/*
 * Tuner.cpp
 *
 *  Created on: Apr 6, 2016
 *      Author: mateusz
 *
 *  Tuner is the client-side of IPC communication here
 */

#include <iostream>
#include <string>
#include <memory>
#include <unistd.h>
#include <CommonAPI/CommonAPI.hpp>
#include "v1_0/commonapi/CalcServiceProxy.hpp"
#include "Console.hpp"

using namespace std;
using namespace v1_0::commonapi;

int main() {

    // initialize CommonAPI runtime and get Persistence proxy instance
    shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    shared_ptr<CalcServiceProxy<>> myProxy = runtime->buildProxy<CalcServiceProxy>("local", "calculator");

    // loop until the persistence is available
    cout << "Checking availability!" << endl;
    while (!myProxy->isAvailable())
        usleep(10);
    cout << "Available..." << endl;


    CommonAPI::CallStatus callStatus;
    int64_t calculator_result;
    string command;
    vector<string> params;


    // interact with the user. forever
    while (true) {
        // get user input from console
        tie(command, params) = Console::getInput();

        // parse the input
        if (command == "add") {
            if (params.size() < 2) continue;

            myProxy->add(stoi(params[0]), stoi(params[1]), callStatus, calculator_result);
            cout << " result: " << calculator_result << endl;
//            myProxy->getCalculationDoneEvent();
        }
        else {
            cout << "wrong command! Try: add 2 3" << endl;
        }
        // loop and again...
    }

    return 0;
}
