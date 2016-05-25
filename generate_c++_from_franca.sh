#!/bin/bash

# Generate CommonAPI proxy-stub pairs and DBus backend for Franca .fidl interface files
./CommonAPI/cgen/commonapi-generator/commonapi-generator-linux-x86_64 -sk ./fidl/*.fidl
./CommonAPI/cgen/commonapi_dbus_generator/commonapi-dbus-generator-linux-x86_64 ./fidl/*.fidl
