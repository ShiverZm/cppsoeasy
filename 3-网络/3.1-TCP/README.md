# TCP

传输控制协议（TCP，Transmission Control Protocol），工作在传输层。

以字节流为传输单位。

## 特点

### 1.面向连接的通信协议

通过三次握手建立连接，通讯完成时通过四次挥手拆除连接。

### 2.可靠的数据流服务

TCP 连接传送的数据，无差错、不丢失、不重复，并且按序到达。

采用"带重传的肯定确认"技术来实现传输的可靠性。

TCP还采用一种称为"滑动窗口"的方式进行流量控制，所谓窗口实际表示接收能力，用以限制发送方的发送速度

### 3.端对端传输

### 4.面向字节流传输

虽然应用程序和 TCP 的交互式一次一个数据块(大小不等)，但 TCP 把应用程序交下来的数据仅仅看成是一连串的`无结构的字节流。

### 5.全双工

两端可以同时传输数据、和接收数据







