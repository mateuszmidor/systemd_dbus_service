#!/bin/bash

# Generate CommonAPI proxy-stub pairs and DBus backend for Franca .fdepl interface deployment description files
./CommonAPI/cgen/commonapi-generator/commonapi-generator-linux-x86_64 -sk ./fidl/*.fdepl
./CommonAPI/cgen/commonapi_dbus_generator/commonapi-dbus-generator-linux-x86_64 ./fidl/*.fdepl
