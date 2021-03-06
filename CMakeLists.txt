cmake_minimum_required (VERSION 3.2)
project (systemd_dbus_service_demo)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11")


# setup directory paths for short
set(COMMONAPI_DIR "${PROJECT_SOURCE_DIR}/CommonAPI")
set(SRC-GEN_DIR "${PROJECT_SOURCE_DIR}/src-gen")


# the below files are generated by "generate_c++_from_franca.sh"
set(GENERATED_SOURCES
    ${SRC-GEN_DIR}/v1/com/mateuszmidor/calc/calcInterfaceStubDefault.cpp
    ${SRC-GEN_DIR}/v1/com/mateuszmidor/calc/calcInterfaceDBusProxy.cpp
    ${SRC-GEN_DIR}/v1/com/mateuszmidor/calc/calcInterfaceDBusDeployment.cpp
    ${SRC-GEN_DIR}/v1/com/mateuszmidor/calc/calcInterfaceDBusStubAdapter.cpp
)


# add c++ source-from-francaIDL generating step
add_custom_command(
    OUTPUT ${GENERATED_SOURCES}
    DEPENDS fidl/calc-dbus.fdepl fidl/calc.fidl
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMAND sh ${PROJECT_SOURCE_DIR}/generate_c++_from_franca.sh 
    COMMENT "Generating CommonAPI sources from FrancaIDL"
)
 

# make a library out of generated sources; client and service will both use that
add_library(src-gen STATIC ${GENERATED_SOURCES})

target_include_directories(src-gen
                            PUBLIC
                                ${SRC-GEN_DIR}
                                ${COMMONAPI_DIR}/dbus-1.8.20
                                ${COMMONAPI_DIR}/common-api-runtime/include
                                ${COMMONAPI_DIR}/common-api-dbus-runtime/include
)
  
link_directories(
    ${COMMONAPI_DIR}/common-api-runtime/build
    ${COMMONAPI_DIR}/common-api-dbus-runtime/build
    ${COMMONAPI_DIR}/dbus-1.8.20/dbus/.libs
)
 
target_link_libraries(src-gen
                         PUBLIC
                            dbus-1
                            CommonAPI
                            CommonAPI-DBus
)

# tell the linker to include whole archive not just the actually used code
# this is needed as commonapi uses ugly gcc trick __attribute__ ((constructor)) for autoinitialization
# and that would normally not be included in the binary
SET(src-gen-whole-archive -Wl,--whole-archive src-gen -Wl,--no-whole-archive)


# add Client target
add_executable(CalcClient
    src/Client.cpp   
)

target_link_libraries(CalcClient ${src-gen-whole-archive})


# add Service target
add_executable(CalcServer
    src/Server.cpp
    src/CalcImpl.cpp
)

target_link_libraries(CalcServer ${src-gen-whole-archive})


# install the systemd service and its dependencies
install(TARGETS CalcServer
        RUNTIME DESTINATION /usr/bin
        PERMISSIONS OWNER_EXECUTE GROUP_EXECUTE WORLD_EXECUTE
)

install(FILES ${COMMONAPI_DIR}/common-api-runtime/build/libCommonAPI.so
		${COMMONAPI_DIR}/common-api-runtime/build/libCommonAPI.so.3
		${COMMONAPI_DIR}/common-api-runtime/build/libCommonAPI.so.3.1.5
		${COMMONAPI_DIR}/common-api-dbus-runtime/build/libCommonAPI-DBus.so
		${COMMONAPI_DIR}/common-api-dbus-runtime/build/libCommonAPI-DBus.so.3
		${COMMONAPI_DIR}/common-api-dbus-runtime/build/libCommonAPI-DBus.so.3.1.5
		${COMMONAPI_DIR}/dbus-1.8.20/dbus/.libs/libdbus-1.so
		${COMMONAPI_DIR}/dbus-1.8.20/dbus/.libs/libdbus-1.so.3
		${COMMONAPI_DIR}/dbus-1.8.20/dbus/.libs/libdbus-1.so.3.8.13
        DESTINATION /lib
)

install(FILES systemd/Calc.service
        DESTINATION /etc/systemd/system
)

install(FILES "systemd/Calc-stub.ini" 
        DESTINATION "/etc/commonapi-dbus"
)

install(FILES "systemd/com.mateuszmidor.calc.calcInterface.conf" 
        DESTINATION "/etc/dbus-1/system.d"
)
