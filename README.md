SimpleRpcServer
==================
SimpleRpcServer is a multi-threaded C++ messaging example which is based on [RabbitMQ](https://www.rabbitmq.com/) project. It combines an [RPC application](https://www.rabbitmq.com/tutorials/tutorial-six-python.html) with [work queues (threads)](https://www.rabbitmq.com/tutorials/tutorial-two-python.html). The application builds a consumer queue with multiple channels, consumes the queue with multiple threads (single channel for each thread) and sends a response with each thread. This project heavily depends on [SimpleAmqpClient](https://github.com/alanxz/SimpleAmqpClient).

Installing
----------------
Tested and known to work in Linux (Ubuntu 16.04, 64 bit) with [Eclipse Nsight IDE](https://developer.nvidia.com/nsight-eclipse-edition). Please refer to [Pre-requisites](https://github.com/alanxz/SimpleAmqpClient#pre-requisites) for a proper installation.
