#include "TCPClient.h"
#include "EventDriver.h"
#include "Singleton.h"

TCPClient::TCPClient()
:m_u16Port(0)
{
  
}

TCPClient::TCPClient(const char* szAddr, unsigned short usPort)
{
    SetAddrPort(szAddr, usPort);
}

TCPClient::~TCPClient()
{
    Close();
}

void TCPClient::Open()
{
    SINGLETON(EventDriver)->add(this);
}

void TCPClient::Close()
{
    SINGLETON(EventDriver)->del(this);
}

bool TCPClient::Actived() const
{
    return (NULL != m_context);
}

unsigned short TCPClient::GetPort() const
{
    return m_u16Port;
}

bool TCPClient::SetAddrPort(const char* szAddr, unsigned short u16Port)
{

    m_strAddr = szAddr;
    m_u16Port = u16Port;
    return true;
  
}

void TCPClient::SetCtx(void *ctx) {
    m_context = ctx;    
}

void *TCPClient::GetCtx() {
    return m_context;
}

const char* TCPClient::GetAddr() const
{
    return m_strAddr.c_str();
}

void TCPClient::DoSocketError(int nErrorCode)
{
    OnTCPError.Execute(this, nErrorCode);
}

void TCPClient::DoConnect()
{
    OnTCPConnect.Execute(this);
}

void TCPClient::DoDisconnect()
{
    OnTCPDisconnect.Execute(this);

}

void TCPClient::DoRecvData(char *buffer, size_t size)
{
    OnTCPRecvData.Execute(this, buffer, size);
}

bool TCPClient::SendData(const char* buffer, size_t size)
{
    return SINGLETON(EventDriver)->send(this, buffer, size);
}

