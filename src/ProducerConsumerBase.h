/*
 * ProducerConsumer.h
 *
 *  Created on: Nov 11, 2016
 *      Author: kadir
 */

#ifndef ProducerConsumerBase_H_
#define ProducerConsumerBase_H_

#include <string>
#include <SimpleAmqpClient/SimpleAmqpClient.h>
#include "SimpleRpcServer.h"

class ProducerConsumerBase {
public:
	ProducerConsumerBase();
	virtual ~ProducerConsumerBase();

	virtual void receiveSendRpc(AmqpClient::SimpleRpcServer::ptr_t)=0;

	virtual void initialize(int numThreads)=0;

	void startConnection(const std::string& iniFileName);

	void loadConnectionParams(const std::string& iniFileName);

protected:
	std::string host = "127.0.0.1";
	int port = 5672;
	std::string username = "guest";
	std::string password = "guest";
	std::string rpc_queue = "rpc_queue";
	int numThreads = 8;

};

#endif /* PRODUCERCONSUMER_H_ */
