/*
 * SimpleProducerConsumer.h
 *
 *  Created on: Nov 14, 2016
 *      Author: kadir
 */

#ifndef SIMPLEPRODUCERCONSUMER_H_
#define SIMPLEPRODUCERCONSUMER_H_

#include "ProducerConsumerBase.h"
#include <vector>
#include <thread>

class SimpleProducerConsumer: public ProducerConsumerBase {
public:
	SimpleProducerConsumer();
	virtual ~SimpleProducerConsumer();

	virtual void receiveSendRpc(AmqpClient::SimpleRpcServer::ptr_t) override;
	virtual void initialize(int numThreads) override;

	bool resizeOperation(const std::string& messageIn, std::string& messageOut);
	bool convertGrayScale(const std::string& messageIn, std::string& messageOut);

private:
	std::vector<std::thread> processorThreads;
};


#endif /* SIMPLEPRODUCERCONSUMER_H_ */
