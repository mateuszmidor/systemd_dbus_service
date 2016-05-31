#!/bin/bash
docker run -t -i -w "/systemd_dbus_service" -v `pwd`/..:/systemd_dbus_service franca_ubuntu bash
