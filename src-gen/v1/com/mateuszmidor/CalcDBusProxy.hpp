/*
* This file was generated by the CommonAPI Generators.
* Used org.genivi.commonapi.dbus 3.1.5.v201512091512.
* Used org.franca.core 0.9.1.201412191134.
*
* This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
* If a copy of the MPL was not distributed with this file, You can obtain one at
* http://mozilla.org/MPL/2.0/.
*/
#ifndef V1_COM_MATEUSZMIDOR_Calc_DBUS_PROXY_HPP_
#define V1_COM_MATEUSZMIDOR_Calc_DBUS_PROXY_HPP_

#include <v1/com/mateuszmidor/CalcProxyBase.hpp>
#include "v1/com/mateuszmidor/CalcDBusDeployment.hpp"

#if !defined (COMMONAPI_INTERNAL_COMPILATION)
#define COMMONAPI_INTERNAL_COMPILATION
#endif

#include <CommonAPI/DBus/DBusAddress.hpp>
#include <CommonAPI/DBus/DBusFactory.hpp>
#include <CommonAPI/DBus/DBusProxy.hpp>
#include <CommonAPI/DBus/DBusAddressTranslator.hpp>
#include <CommonAPI/DBus/DBusEvent.hpp>

#undef COMMONAPI_INTERNAL_COMPILATION

#include <string>

namespace v1 {
namespace com {
namespace mateuszmidor {

class CalcDBusProxy
    : virtual public CalcProxyBase, 
      virtual public CommonAPI::DBus::DBusProxy {
public:
    CalcDBusProxy(
        const CommonAPI::DBus::DBusAddress &_address,
        const std::shared_ptr<CommonAPI::DBus::DBusProxyConnection> &_connection);

    virtual ~CalcDBusProxy() { }


    virtual CalculationDoneEvent& getCalculationDoneEvent();

    virtual void add(const int32_t &_a, const int32_t &_b, CommonAPI::CallStatus &_internalCallStatus, int64_t &_result, const CommonAPI::CallInfo *_info);
    virtual std::future<CommonAPI::CallStatus> addAsync(const int32_t &_a, const int32_t &_b, AddAsyncCallback _callback, const CommonAPI::CallInfo *_info);


    virtual void getOwnVersion(uint16_t& ownVersionMajor, uint16_t& ownVersionMinor) const;

private:
   

    CommonAPI::DBus::DBusEvent<CalculationDoneEvent, CommonAPI::Deployable<std::string, CommonAPI::DBus::StringDeployment>> calculationDone_;

};

} // namespace mateuszmidor
} // namespace com
} // namespace v1

#endif // V1_COM_MATEUSZMIDOR_Calc_DBUS_PROXY_HPP_
