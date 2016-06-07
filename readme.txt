What is this?
    A client - service demo of systemd/dbus/CommonAPI/FrancaIDL.
    Based on "CommonAPI C++ D-Bus in 10 minutes (from scratch)" at:
    https://genivi-oss.atlassian.net/wiki/pages/viewpage.action?pageId=5472316
    More detailed CommonAPI guide available at:
    http://docs.projects.genivi.org/ipc.common-api-tools/3.1.2/pdf/CommonAPICppUserGuide.pdf

What are the parties?
    "CalcClient" application - is a calculator client here.
    "CalcService" application - is a calculator service here.

Prerequisites?  
    java jre for c++ code generators (version 6 should suffice)

Steps to run the demo:
    0. Very first, run "install_linux_basetools.sh" to install CommonAPI installer tools.
    1. First run the installer script "install_common_api.sh" under CommonAPI/ 
    2. Under docker/: build_docker.sh, run_docker.sh, generate_c++_from_franca.sh, exit
    3. Then run "cmake .." inside ./build/
    4. Then run "make" inside ./build/
    5. Then run CalcService and CalcClient in separate terminal windows
    6. Issue "add 2 3" from CalcClient and see how it is handled by CalcService
    
For ambitious ones:    
	7. sudo make install, to install systemd service
	8. "xhost +", to allow X server connections from other than current user
	9. systemctl start CalcService to run the service,
	10. export COMMONAPI_DBUS_CONFIG=/etc/commonapi-dbus/Calc-stub.ini, then run CalcClient and play around