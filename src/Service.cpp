/*
 * Persistence.cpp
 *
 *  Created on: Apr 6, 2016
 *      Author: mateusz
 *
 *  Persistence is the server-side of IPC communication here
 */

#include <iostream>
#include <thread>
#include <memory>
#include <CommonAPI/CommonAPI.hpp>
#include "CalcServiceImpl.h"

using namespace std;

int main() {

    // initialize CommonAPI runtime and register the Persistence service instance
    shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();
    shared_ptr<CalServiceImpl> myService = make_shared<CalServiceImpl>();
    runtime->registerService("local", "calculator", myService);
    cout << "Successfully Registered PersistenceService!" << endl;

    // keep the Persistence service alive
    while (true) {
        cout << "Waiting for calls... (Abort with CTRL+C)" << endl;
        this_thread::sleep_for(chrono::seconds(30));
    }

    return 0;
}
