/*
 * PersistenceServiceImpl.hpp
 *
 *  Created on: Apr 6, 2016
 *      Author: mateusz
 */

#ifndef PERSISTENCESERVICEIMPL_HPP_
#define PERSISTENCESERVICEIMPL_HPP_

#include <map>
#include <string>
#include <CommonAPI/CommonAPI.hpp>
#include "v1/com/mateuszmidor/CalcStubDefault.hpp"

using std::map;
using std::string;
using std::shared_ptr;

class CalcImpl: public v1::com::mateuszmidor::CalcStubDefault {
private:
    map<string, string> dictionary;

public:
    CalcImpl();
    virtual ~CalcImpl();

    virtual void add(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _a, int32_t _b, addReply_t _reply);
};

#endif /* PERSISTENCESERVICEIMPL_HPP_ */
