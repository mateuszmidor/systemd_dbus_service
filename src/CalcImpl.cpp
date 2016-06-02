/*
Console.hpp * PersistenceServiceImpl.cpp
 *
 *  Created on: Apr 6, 2016
 *      Author: mateusz
 */

#include "CalcImpl.h"

#include <string>

using namespace std;

CalcImpl::CalcImpl() {
}
CalcImpl::~CalcImpl() {
}


void CalcImpl::add(const std::shared_ptr<CommonAPI::ClientId> _client, int32_t _a, int32_t _b, addReply_t _reply) {
	_reply(_a + _b);
	fireCalculationDoneEvent("Service: added " + to_string(_a) + " and " + to_string(_b));
}
