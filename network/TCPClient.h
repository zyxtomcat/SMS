#ifndef _TCPCLIENT_H
#define _TCPCLIENT_H

#include "Event.h"
#include "DataTypeDef.h"
#include <string>

class TCPClient;

typedef EventDef<void(TCPClient* pClient, int nErrorCode)> EventOnTCPClientError;
typedef EventDef<void(TCPClient* pClient)> EventOnTCPClientConnect;
typedef EventDef<void(TCPClient* pClient)> EventOnTCPClientDisconnect;
typedef EventDef<void(TCPClient* pClient, char *buf, size_t size)> EventOnTCPClientRecvData;

class TCPClient : public Object
{
public:
    TCPClient();
    TCPClient(const char* szAddr, unsigned short usPort);
    virtual ~TCPClient();

    void Open();
    void Close();
    bool Actived() const;
    bool SendData(const char* buffer, size_t size);

    unsigned short GetPort() const;
    const char* GetAddr() const;
    bool SetAddrPort(const char* szAddr, unsigned short u16Port);
    void SetCtx(void *ctx);
    void *GetCtx();

    EventOnTCPClientError OnTCPError;
    EventOnTCPClientConnect OnTCPConnect;
    EventOnTCPClientDisconnect OnTCPDisconnect;
    EventOnTCPClientRecvData OnTCPRecvData;

    void DoSocketError(int nErrorCode);
    void DoConnect();
    void DoDisconnect();
    void DoRecvData(char *buffer, size_t size);

private:
    std::string m_strAddr;
    unsigned short m_u16Port;
    void *m_context;
};

#endif
