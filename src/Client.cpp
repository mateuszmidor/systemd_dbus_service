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

    // CalcServiceDbusConnection is used in Calc-stub.ini
    // same must be used on server side
    shared_ptr<calcInterfaceProxy<>> myProxy = runtime->buildProxy<calcInterfaceProxy>("local", "main", "CalcServiceDbusConnection");

    // loop until the service is available
    cout << "Checking availability!" << endl;
    while (!myProxy->isAvailable())
        usleep(10);
    cout << "Available..." << endl;

    // subscribe to CalculationDone service event (broadcast in fild)
    auto event_calculation_listener = [](const string &s) { cout << s << endl; };
    auto event_terminate_listener = []() { cout << "CalcServer terminated!\n"; exit(0); };
    auto error_listener = [](CommonAPI::CallStatus s) { cout << "Broadcast Error" << endl; };
    myProxy->getCalculationDoneEvent().subscribe(event_calculation_listener, error_listener);
    myProxy->getTerminateEvent().subscribe(event_terminate_listener, error_listener);

    // some handy variables
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
