1. 知识点
 * webSocket, protobuf, Thrift, _gRPC, JavaNIO, Reactor模式， 线程池。

* 针对各种传输类型实现统一API
* 高度定制化线程模型，seda。 把一个请求的若干个过程分成一个一个stage，每个stage可以定制
用于处理stage的线程数目。

* Protobuf：通过Url的RESTFul实现RPC。 RPC：调用序列化，网络传输，调用反序列化。
* RPC客户端代码叫stub，RPC服务端代码叫skeleton
*  如果有一种方式能让我们像调用本地服务一样调用远程服务，而让调用者对网络通信这些细节透明，那么将大大提高生产力，比如服务消费方在执行helloWorldService.sayHello("test")时，实质上调用的是远端的服务。这种方式其实就是RPC（Remote Procedure Call Protocol），在各大互联网公司中被广泛使用，如阿里巴巴的hsf、dubbo（开源）、Facebook的thrift（开源）、Google grpc（开源）、Twitter的finagle（开源）等。
