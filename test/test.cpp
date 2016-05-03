#include <Ice/Ice.h>
#include "SAS.h"
#include <json/json.h>
#include <functions.h>
#include <iostream>

using namespace SAS;

std::string buildRequest() {
    std::string sim = "1064818830568";
    std::string content="你好你好你好";

    Json::Value request;
    
    request["sim"] = sim;
    request["content"] = content;

    Json::FastWriter writer;
    return writer.write(request);
}

int main(int argc, char **argv) {
    int status = 0;
    Ice::CommunicatorPtr ic;
    try {
       ic = Ice::initialize(argc, argv);
       Ice::ObjectPrx base = ic->stringToProxy("SASSession:tcp -p 10006 -h 127.0.0.1");
       SASSessionPrx session = SASSessionPrx::checkedCast(base);
       if (!session) {
           throw "Invalid proxy";
       }

       std::string request = buildRequest();
       std::string response;

       session->SendSMS(request, response);

       std::cout<<"orderRequest = "<<request<<std::endl;
       std::cout<<"orderResponse = "<<response<<std::endl;

       status = 0;

    } catch (const Ice::Exception &e) {
        std::cerr<<e<<std::endl;
        status = 1;
    } catch (const char *msg) {
        std::cerr<<msg<<std::endl;
        status = 1;
    }

    if (ic) {
        ic->destroy();
    }

    return status;
}
