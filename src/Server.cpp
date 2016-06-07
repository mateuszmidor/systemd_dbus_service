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
	signal(SIGINT, terminate);
	signal(SIGKILL, terminate);
	signal(SIGTERM, terminate); // systemctl stop sends this signal


    // initialize CommonAPI runtime and register the Persistence service instance
    shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    shared_ptr<CalcImpl> myService = make_shared<CalcImpl>();

    // CalcServiceDbusConnection is used in Calc-stub.ini
    // same must be used on client side
    runtime->registerService("local", "main", myService, "CalcServiceDbusConnection");
    cout << "Successfully Registered Calc under CalcServiceDbusConnection!" << endl;

    // keep the Persistence service alive
    while (!terminated) {
        cout << "Waiting for calls... (Abort with CTRL+C)" << endl;
        this_thread::sleep_for(chrono::seconds(30));
    }
    myService->fireTerminateEvent();
    return 0;
}
