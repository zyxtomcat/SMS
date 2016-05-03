#include <Ice/Ice.h>
#include "SAS.h"
#include "PublicFunction.h"
#include <json/json.h>
#include <functions.h>

using namespace TIGWS;

std::string buildRequest() {
    std::string sim = "1064818830568";
    std::string content="你好你好你好";

    Json::Value request;
    
    request["sim"] = sim;
    request["content"] = content;

    Json::FastWriter writer;
    return writer.write(order);
}

int main(int argc, char **argv) {
    int status = 0;
    Ice::CommunicatorPtr ic;
    try {
       ic = Ice::initialize(argc, argv);
       Ice::ObjectPrx base = ic->stringToProxy("SASSession:tcp -p 10006 -h 127.0.0.1");
       TIGWSSessionPrx session = TIGWSSessionPrx::checkedCast(base);
       if (!session) {
           throw "Invalid proxy";
       }

       std::string request = buildRequest();
       std::string response;

       int res = session->SendSMS(request, response);

       cout<<"res = "<<res<<endl;
       cout<<"orderRequest = "<<request<<endl;
       cout<<"orderResponse = "<<response<<endl;

       status = 0;

    } catch (const Ice::Exception &e) {
        cerr<<e<<endl;
        status = 1;
    } catch (const char *msg) {
        cerr<<msg<<endl;
        status = 1;
    }

    if (ic) {
        ic->destroy();
    }

    return status;
}
