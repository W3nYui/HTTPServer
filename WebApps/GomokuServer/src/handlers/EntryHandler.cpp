#include "../include/handlers/EntryHandler.h"

void EntryHandler::handle(const http::HttpRequest& req, http::HttpResponse* resp)
{
    // 因为是get请求，请求的url也拿到了，我们就可以直接返回响应了
    std::string reqFile;
    reqFile.append("../WebApps/GomokuServer/resource/entry.html");
    FileUtil fileOperater(reqFile); // 转换成FileUtil类 并打开文件
    if (!fileOperater.isValid())
    {
        LOG_WARN << reqFile << " not exist";
        fileOperater.resetDefaultFile(); // 404 NOT FOUND
    }

    std::vector<char> buffer(fileOperater.size()); // 定义文件大小的缓冲区
    fileOperater.readFile(buffer); // 读出文件数据放入buffer
    std::string bufStr = std::string(buffer.data(), buffer.size()); // 将缓冲区数据转换为字符串 因为FileUtil是二进制模式读取的
    
    resp->setStatusLine(req.getVersion(), http::HttpResponse::k200Ok, "OK");
    resp->setCloseConnection(false);
    resp->setContentType("text/html");
    resp->setContentLength(bufStr.size());
    resp->setBody(bufStr);
}
