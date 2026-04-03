#include <string>
#include <iostream>
#include <muduo/net/TcpServer.h>
#include <muduo/base/Logging.h>
#include <muduo/net/EventLoop.h>

#include "GomokuServer.h"

int main(int argc, char* argv[])
{
  // 利用muduo的日志输出当前pid
  LOG_INFO << "pid = " << getpid();

  std::string serverName = "HttpServer";
  int port = 80;
  
  // 参数解析
  int opt;
  const char* str = "p:";
  while ((opt = getopt(argc, argv, str)) != -1) // getopt函数会返回当前解析到的选项字符，如果没有更多选项可供解析，则返回-1
  {
    switch (opt)
    {
      case 'p':
      {
        port = atoi(optarg); // 如果命令行调用参数为 -p + 端口号，则optarg会指向该端口号字符串，atoi函数将其转换为整数并赋值给port变量
        break;
      }
      default:
        break;
    }
  }
  muduo::net::TcpServer::Option option = muduo::net::TcpServer::kReusePort; //option : reuse 允许多个进程绑定同一端口，适用于多线程服务器，提升性能
  muduo::Logger::setLogLevel(muduo::Logger::WARN); // 设定日志级别为WARN，减少日志输出量
  GomokuServer server(port, serverName, option); // 创建HTTP服务器实例 设定端口号与服务器名称
  server.setThreadNum(4); // 设置服务器线程数为4，允许服务器同时处理多个请求，提高性能
  server.start();
}
