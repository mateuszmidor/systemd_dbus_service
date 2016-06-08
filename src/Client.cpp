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
#include "v1/com/mateuszmidor/calc/calcInterfaceProxy.hpp"
#include "Console.hpp"

using namespace std;
using namespace v1::com::mateuszmidor::calc;

//Listener listener, ErrorListener errorListener

int main() {
    // initialize CommonAPI runtime and get service proxy instance
    shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();

	// build proxy to connect to the calc service instance
	// "local" is always used
	// "main" is chosen arbitrarily but must be same in Client, Server and commonapi config file (Calc-stub.ini)
	// "CalcServiceDbusConnection" is chosen arbitrarily but must be same in Client, Server and commonapi config file (Calc-stub.ini)
    shared_ptr<calcInterfaceProxy<>> calcProxy = runtime->buildProxy<calcInterfaceProxy>("local", "main", "CalcServiceDbusConnection");

    // loop until the service is available
    cout << "Checking calc service availability..." << endl;
    while (!calcProxy->isAvailable())
        usleep(10);
    cout << "Available! Try command: add 2 3" << endl;


    // subscribe to events ("broadcasts" in FrancaIDL terminology)
    auto event_calculationdone_listener = [](const string &s) { cout << "(" << s << ")" << "\n> " << flush; };
    auto event_serviceterminated_listener = []() { cout << "(Calc Service terminated!)\n"; exit(0); };
    auto event_error_listener = [](CommonAPI::CallStatus s) { cout << "(Broadcast Error)" << endl; };
    calcProxy->getCalculationDoneEvent().subscribe(event_calculationdone_listener, event_error_listener);
    calcProxy->getTerminateEvent().subscribe(event_serviceterminated_listener, event_error_listener);

    // some handy variables for command parsing and calculating
    CommonAPI::CallStatus callStatus;
    int64_t calculator_result;
    string command;
    vector<string> params;


    // interact with the user.
    while (true) {
        // get user input from console
        tie(command, params) = Console::getInput();

        // parse the input
        if ((command == "add") && (params.size() == 2)) {

            calcProxy->add(stoi(params[0]), stoi(params[1]), callStatus, calculator_result);
            cout << " result: " << calculator_result << endl;
        }
        else {
            cout << "wrong command syntax! Try: add 2 3" << endl;
        }
        // loop and again...
    }

    return 0;
}
