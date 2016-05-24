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
    2. Then run "cmake .." inside ./build/
    3. Then run "make" inside ./build/
    4. Then run CalcService and CalcClient in separate terminal windows
    5. Issue "add 2 3" from CalcClient and see how it is handled by CalcService