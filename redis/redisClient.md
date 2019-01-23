### redis客户端实现原理

####1. 基于TCP连接的RESP通信协议(REdis Serialization Protocol)
* RESP协议可以实现REdis客户端开发，实现REdis代理（分布式Redis解决方案，通过分片存储使得可用内存无限扩容）
* 实现哨兵机制
* 可以参考的开原方案包括：Jedis，Codis，sentinel

RESP通信协议的基本格式：
```cpp
*<参数数量> CR LF
$<参数 1 的字节数量> CR LF
<参数 1 的数据> CR LF
...
$<参数 N 的字节数量> CR LF
<参数 N 的数据> CR LF
```

比如客户端命令：SET key value
则会有如下格式
```cpp
*3
$3
SET
$3 //key是3字节
key
$5 //value是5字节
value
```
最后实际被解析成如下格式然后以流的形式在tcp连接中传输
```cpp
"*3\r\n$3\r\nSET\r\n$3\r\nkey\r\n$5\r\nvalue\r\n"
```

RESP通信协议的PIPELINE：
* 客户端可以通过 pipline ， 在一次写入操作中发送多个命令
* 多个命令的回复消息会在最后统一返回

