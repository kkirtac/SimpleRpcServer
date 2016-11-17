//============================================================================
// Name        : ProducerConsumer.cpp
// Author      : kadir.kirtac
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "SimpleProducerConsumer.h"

#include "gflags/gflags.h"
#include "glog/logging.h"

using namespace std;


DEFINE_string(iniFileName, "config.ini",
              "ini file which contains various parameters needed for messaging");

int main(int argc, char* argv[]) {

	::google::InitGoogleLogging(argv[0]);

	gflags::ParseCommandLineFlags(&argc, &argv, true);

	SimpleProducerConsumer simple;

	simple.startConnection(FLAGS_iniFileName);

	return 0;
}
