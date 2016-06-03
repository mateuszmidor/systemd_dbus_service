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
#include "CalcImpl.h"

using namespace std;

int main() {

    auto log = [](const char s[]) { cout << "### " << s << endl; };
    // initialize CommonAPI runtime and register the Persistence service instance
    log("get runtime");
    shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();

    log("create service");
    shared_ptr<CalcImpl> myService = make_shared<CalcImpl>();

    log("register service");
    runtime->registerService("local", "main", myService, "CalcServerDbusConnection"); // CalcServerDbusConnection is used in Calc-stub.ini
    cout << "Successfully Registered Calc under CalcServerDbusConnection!" << endl;

    // keep the Persistence service alive
    while (true) {
        cout << "Waiting for calls... (Abort with CTRL+C)" << endl;
        this_thread::sleep_for(chrono::seconds(30));
    }

    return 0;
}
