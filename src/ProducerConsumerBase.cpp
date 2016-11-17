/*
 * ProducerConsumer.cpp
 *
 *  Created on: Nov 11, 2016
 *      Author: kadir
 */

#include "ProducerConsumerBase.h"
#include "glog/logging.h"

ProducerConsumerBase::ProducerConsumerBase() {
	// TODO Auto-generated constructor stub

}

ProducerConsumerBase::~ProducerConsumerBase() {
	// TODO Auto-generated destructor stub
}

void ProducerConsumerBase::loadConnectionParams(const std::string& iniFileName){

}

void ProducerConsumerBase::startConnection(const std::string& iniFileName){

	loadConnectionParams(iniFileName);

	LOG(ERROR) << " [x] Awaiting RPC requests";

	// start receiving & sending messages
	initialize(numThreads);
}
