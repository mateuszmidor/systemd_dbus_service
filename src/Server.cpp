/*
 * Persistence.cpp
 *
 *  Created on: Apr 6, 2016
 *      Author: mateusz
 *
 *  Persistence is the server-side of IPC communication here
 */

#include <signal.h>
#include <iostream>
#include <thread>
#include <memory>
#include <CommonAPI/CommonAPI.hpp>
#include "CalcImpl.h"

using namespace std;

bool terminated = false;


void terminate(int)
{
	terminated = true;
}

int main() {
	// gracefully handle any attempts to stop the server
	signal(SIGKILL, terminate);
	signal(SIGTERM, terminate); // "systemctl stop" sends this signal


    // initialize CommonAPI runtime and create the calc service instance
    shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    shared_ptr<CalcImpl> calcService = make_shared<CalcImpl>();

    // register the calc service instance
    // "local" is always used
    // "main" is chosen arbitrarily but must be same in Client, Server and commonapi config file (Calc-stub.ini)
    // "CalcServiceDbusConnection" is chosen arbitrarily but must be same in Client, Server and commonapi config file (Calc-stub.ini)
    runtime->registerService("local", "main", calcService, "CalcServiceDbusConnection");
    cout << "Successfully Registered calc service under CalcServiceDbusConnection!" << endl;

    // keep the Persistence service alive
    while (!terminated) {
        cout << "Waiting for calls... (Abort with CTRL+C)" << endl;
        this_thread::sleep_for(chrono::seconds(30));
    }

    // broadcast terminate event to clients
    calcService->fireTerminateEvent();

    return 0;
}
