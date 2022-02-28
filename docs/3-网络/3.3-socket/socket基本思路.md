[TOC]

# Socket编程基本思路

## TCP

### 服务端

   1、初始化Windows Socket库。
   2、创建Socket。
   3、绑定Socket。
   4、监听。
   5、Accept。
   6、接收、发送数据

### 客户端

   1、初始化Windows Socket库。
   2、创建Socket。
   3、连接Socket。
   4、接收、发送数据。

## UDP 

### 发送端
	1. 建立udpsocket服务
 	2. 提供数据，并且将数据封装到包中
 	3. 关闭Socket服务的发送功能，将数据包发送出去
 	4. 关闭资源

### 接收端

1. 建立udpsocket服务
2. 定义一个空数据包，用于存储接收到的字节数据。
3. 通过Socket服务的receive（）方法将受到的数据存储到已经定义好的空数据包中
4.  取出不同的数据
5.  关闭资源