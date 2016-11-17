/*
 * SimpleProducerConsumer.cpp
 *
 *  Created on: Nov 14, 2016
 *      Author: kadir
 */

#include "SimpleProducerConsumer.h"
#include "glog/logging.h"
#include "rapidjson/document.h"     // rapidjson's DOM-style API
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "ImageProcessor.h"
#include "base64.h"
#include <iostream>

using namespace rapidjson;
using namespace std;

SimpleProducerConsumer::SimpleProducerConsumer() {
	// TODO Auto-generated constructor stub

}

SimpleProducerConsumer::~SimpleProducerConsumer() {
	// TODO Auto-generated destructor stub
}

void SimpleProducerConsumer::receiveSendRpc(AmqpClient::SimpleRpcServer::ptr_t simpleServer){

	while(true){

		AmqpClient::BasicMessage::ptr_t incoming = simpleServer->GetNextIncomingMessage();

		std::string resizeResponse;
		resizeOperation(incoming->Body(), resizeResponse);

		simpleServer->RespondToMessage(incoming, resizeResponse);

		LOG(ERROR) << "Thread " << std::this_thread::get_id() << " sent message: "<< incoming->CorrelationId() << " , " << incoming->ReplyTo();

	}

}

void SimpleProducerConsumer::initialize(int numThreads){

	for (int i = 0; i < numThreads; ++i) {

		AmqpClient::Channel::ptr_t channel = AmqpClient::Channel::Create(host, port, username, password);
		AmqpClient::SimpleRpcServer::ptr_t simpleServer = AmqpClient::SimpleRpcServer::Create(channel, rpc_queue);
		processorThreads.emplace_back(&SimpleProducerConsumer::receiveSendRpc, this, simpleServer);
	}

	for (int i = 0; i < numThreads; ++i) {
		if(processorThreads[i].joinable())
			processorThreads[i].join();
	}
}

bool SimpleProducerConsumer::resizeOperation(const std::string& messageIn, std::string& messageOut){

	// parse json
	Document document;  // Default template parameter uses UTF8 and MemoryPoolAllocator.

    if (document.Parse(messageIn.c_str()).HasParseError())
    	return false;

//    LOG(ERROR) << "Access values in document:";
    assert(document.IsObject());    // Document is a JSON value represents the root of DOM. Root can be either an object or array.

    assert(document.HasMember("base64Image"));
    assert(document["base64Image"].IsString());
//    LOG(ERROR) << "base64Image = " << document["base64Image"].GetString();
    std::string base64Image = document["base64Image"].GetString();

    assert(document.HasMember("resizeWidth"));
    assert(document["resizeWidth"].IsInt());
//    LOG(ERROR) << "resizeWidth = " << document["resizeWidth"].GetInt();
    int resizeWidth = document["resizeWidth"].GetInt();

    assert(document.HasMember("resizeHeight"));
    assert(document["resizeHeight"].IsInt());
//    LOG(ERROR) << "resizeHeight = " << document["resizeHeight"].GetInt();
    int resizeHeight = document["resizeHeight"].GetInt();

	// base64 decoding
    std::string decodedStr = base64_decode(base64Image);
    std::vector<uchar> data(decodedStr.begin(), decodedStr.end());
    Mat decodedImg = imdecode(data, CV_LOAD_IMAGE_UNCHANGED);

	// resize image
    ImageProcessor processor;
    Mat resizedImg;
    processor.resizeImage(decodedImg, resizeHeight, resizeWidth, resizedImg);

    // base64 encoding
    vector<uchar> buf;
    imencode(".jpg", resizedImg, buf);
    uchar *enc_msg = new uchar[buf.size()];
    for(int i=0; i < buf.size(); i++)
    	enc_msg[i] = buf[i];
    std::string encodedImg = base64_encode(enc_msg, buf.size());

	// build json
    StringBuffer s;
    Writer<StringBuffer> writer(s);
    writer.StartObject();               // Between StartObject()/EndObject(),
    writer.Key("base64Image");
    writer.String(encodedImg.c_str());
    writer.Key("resizeWidth");
    writer.Int(resizeWidth);
    writer.Key("resizeHeight");
    writer.Int(resizeHeight);
    writer.EndObject();

    messageOut = s.GetString();

    return true;
}
