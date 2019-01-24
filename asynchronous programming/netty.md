1. 知识点
 * webSocket, protobuf, Thrift, _gRPC, JavaNIO, Reactor模式， 线程池。

* 针对各种传输类型实现统一API
* 高度定制化线程模型，seda。 把一个请求的若干个过程分成一个一个stage，每个stage可以定制
用于处理stage的线程数目。

* Protobuf：通过Url的RESTFul实现RPC。 RPC：调用序列化，网络传输，调用反序列化。
* RPC客户端代码叫stub，RPC服务端代码叫skeleton
*  
