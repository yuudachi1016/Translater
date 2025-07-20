#include "RequstAPI.h"
#include "requests.h"
std::string RequstAPI::Requst_GET(std::string url)
{
    requests::Request req(new HttpRequest);
    req->method  = HTTP_GET;
    req->url     = url;
    req->timeout = 5000;
    requests::Response resp;
    resp = requests::request(req);
    if (resp == NULL || resp->status_code != HTTP_STATUS_OK)
    {
        return std::string();
    }
    std::string response = std::string(resp->body.data(), resp->body.size());
    return response;
}
