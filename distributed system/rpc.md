### RPC原理

#### 1.简介
* Protobuf：通过Url的RESTFul实现RPC。 RPC：调用序列化，网络传输，调用反序列化。
* RPC客户端代码叫stub，RPC服务端代码叫skeleton
*  如果有一种方式能让我们像调用本地服务一样调用远程服务，而让调用者对网络通信这些细节透明，那么将大大提高生产力，
比如服务消费方在执行helloWorldService.sayHello("test")时，实质上调用的是远端的服务。这种方式其实就是RPC（Remote Procedure Call Protocol）
，在各大互联网公司中被广泛使用，如阿里巴巴的hsf、dubbo（开源）、Facebook的thrift（开源）、Google grpc（开源）、Twitter的finagle（开源）等。

#### 2.rpc原理
1. 要让网络通信细节对使用者透明，我们需要对通信细节进行封装；其中rpc的通信细节包括了：
  * 服务消费方（client）调用以本地调用方式调用服务；
  * client stub接收到调用后负责将方法、参数等组装成能够进行网络传输的消息体；
  * client stub找到服务地址，并将消息发送到服务端；
  * server stub收到消息后进行解码；
  * server stub根据解码结果调用本地的服务；
  * 本地服务执行并将结果返回给server stub；
  * server stub将返回结果打包成消息并发送至消费方；
  * client stub接收到消息，并进行解码；
  * 服务消费方得到最终结果。
  
2. rpc通信的实现步骤
  * 1.确定调用消息的数据结构（包括 方法名，参数等等）
  * 2.序列化和反序列化调用消息，常见的有Json, Protobuf，thrift, Avro；rpc通信对于序列化协议的基础要求：
    * 通用性（能否支持编程语言中繁多的数据结构如数组，链表，图，树）
    * 序列化的性能，带宽的节约
    * 可扩展性，是否支持增加新的模块
  * 3.rpc客户端服务端之间的通信：常见网络IO通信模型包括阻塞io和无阻塞io
    * 常见的NIO框架 如 netty，python的gevent uvloop
  * 4.服务自动注册与发现zookeeper
    * zookeeper可以充当一个服务注册表（Service Registry），让多个服务提供者形成一个集群，让服务消费者通过服务注册表获取具体的服务访问地址（ip+端口）去访问具体的服务提供者。
    * 具体来说，zookeeper就是个分布式文件系统，每当一个服务提供者部署后都要将自己的服务注册到zookeeper的某一路径上: /{service}/{version}/{ip:port}, 比如我们的HelloWorldService部署到两台机器，那么zookeeper上就会创建两条目录：分别为/HelloWorldService/1.0.0/100.19.20.01:16888  /HelloWorldService/1.0.0/100.19.20.02:16888。
    * zookeeper提供了“心跳检测”功能，它会定时向各个服务提供者发送一个请求（实际上建立的是一个 Socket 长连接），如果长期没有响应，服务中心就认为该服务提供者已经“挂了”，并将其剔除，比如100.19.20.02这台机器如果宕机了，那么zookeeper上的路径就会只剩/HelloWorldService/1.0.0/100.19.20.01:16888。
    * 服务消费者会去监听相应路径（/HelloWorldService/1.0.0），一旦路径上的数据有任务变化（增加或减少），zookeeper都会通知服务消费方服务提供者地址列表已经发生改变，从而进行更新。


3. 客户端导入服务端的远程接口：
 * 大部分RPC框架采用IDL定义的方式生成服务端的stub代码。（跨语言的接口实现方式）
 * 非跨语言的可以采用共享接口，。。。
 
#### 3.protobuf原理
* message是protobuf的基础数据格式。
* 

