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
#include "v1/com/mateuszmidor/CalcProxy.hpp"
#include "Console.hpp"

using namespace std;
using namespace v1::com::mateuszmidor;

//Listener listener, ErrorListener errorListener

int main() {

    // initialize CommonAPI runtime and get service proxy instance
    shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    shared_ptr<CalcProxy<>> myProxy = runtime->buildProxy<CalcProxy>("local", "main");

    // loop until the service is available
    cout << "Checking availability!" << endl;
    while (!myProxy->isAvailable())
        usleep(10);
    cout << "Available..." << endl;

    // subscribe to CalculationDone service event (broadcast in fild)
    auto event_listener = [](const string &s) { cout << s << endl; };
    auto error_listener = [](CommonAPI::CallStatus s) { cout << "Broadcast Error" << endl; };
    myProxy->getCalculationDoneEvent().subscribe(event_listener, error_listener);

    // some handy variables
    CommonAPI::CallStatus callStatus;
    int64_t calculator_result;
    string command;
    vector<string> params;


    // interact with the user. forever
    while (true) {
        // get user input from console
        tie(command, params) = Console::getInput();

        // parse the input
        if ((command == "add") && (params.size() == 2)) {

            myProxy->add(stoi(params[0]), stoi(params[1]), callStatus, calculator_result);
            cout << " result: " << calculator_result << endl;
        }
        else {
            cout << "wrong command syntax! Try: add 2 3" << endl;
        }
        // loop and again...
    }

    return 0;
}
