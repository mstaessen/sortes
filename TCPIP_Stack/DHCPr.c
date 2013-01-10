#define __DHCPR_C
#define __18F97J60
#define __SDCC__
#include <pic18f97j60.h> //ML

#include "../Include/TCPIPConfig.h"

#if defined(STACK_USE_DHCP_RELAY)

#include "../Include/TCPIP_Stack/TCPIP.h"

#include "../DHCPRelayConfig.h"

static UDP_SOCKET			SocketToServer;
static UDP_SOCKET           SocketToClient;
static NODE_INFO            ServerInfo;

void DHCPRelayInit(BYTE vInterface) {
    
    {
        int i;
        BYTE routerMac[] = _DHCP_ROUTER_MAC;
        for (i = 0; i < 6; i++)
            ServerInfo.MACAddr.v[i] = routerMac[i];
    }{
        int i;
        unsigned long ip[] = _DHCP_SERVER_IP;
        for (i = 0; i < 4; i++)
            ServerInfo.IPAddr.v[i] = ip[i];
    }
    
	SocketToClient = UDPOpen(DHCP_SERVER_PORT, NULL, DHCP_CLIENT_PORT);
    SocketToServer = UDPOpen(DHCP_CLIENT_PORT, /*&ServerInfo*/ NULL, DHCP_SERVER_PORT);
}

void DHCPRelayTask(void) {
    if (UDPIsGetReady(SocketToServer) > 0) {
		UDPDiscard();
        LED1_IO ^= 1;
    }
    if (UDPIsGetReady(SocketToClient) > 0) {
        UDPDiscard();
        LED2_IO ^= 1;
    }
}

#endif // defined(STACK_USE_DHCP_RELAY)