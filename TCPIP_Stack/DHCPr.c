#define __DHCPR_C
#define __18F97J60
#define __SDCC__
#include <pic18f97j60.h> //ML

#include "../Include/TCPIPConfig.h"

#if defined(STACK_USE_DHCP_RELAY)

#include "../Include/TCPIP_Stack/TCPIP.h"

#include "../DHCPRelayConfig.h"

static UDP_SOCKET			RelaySocket;

static UDP_SOCKET_INFO      ServerInfo;
static UDP_SOCKET_INFO      BroadcastInfo;
static UDP_SOCKET_INFO      ClientInfo;
static UDP_SOCKET_INFO      *CurrentInfo;

static IP_ADDR              RelayIP;

static BYTE                 buff[240], buff2[256];

// tmp variables
static BYTE                 *cur, byteLength, optionCode;
static WORD                 length, totalLength;
static BOOL                 retry;
static BOOTP_HEADER         *header;

static enum {
    DHCPr_RECEIVE = 0,
    DHCPr_SEND,
} RelayState;

static BOOL isAlreadyInit;

static void DHCPr_Read();
static void DHCPr_Forward();

void DHCPRelayInit(BYTE vInterface) {
    // set ServerInfo.remoteNode.MACAddr
    {
        int i;
        BYTE routerMac[] = _DHCP_ROUTER_MAC;
        for (i = 0; i < 6; i++)
            ServerInfo.remoteNode.MACAddr.v[i] = routerMac[i];
    }
    // set ServerInfo.remoteNode.IPAddr
    {
        int i;
        unsigned long ip[] = _DHCP_SERVER_IP;
        for (i = 0; i < 4; i++)
            ServerInfo.remoteNode.IPAddr.v[i] = ip[i];
    }
    // set RelayIP
    {
        int i;
        unsigned long ip[] = _DHCP_RELAY_IP;
        for (i = 0; i < 4; i++)
            RelayIP.v[i] = ip[i];
    }
    // set BroadcastInfo to broadcast address
    {
        memset((void*)&(BroadcastInfo.remoteNode), 0xFF, sizeof(BroadcastInfo.remoteNode));
    }
    
    ServerInfo.localPort = BroadcastInfo.localPort = ClientInfo.localPort = DHCP_SERVER_PORT;
    ServerInfo.remotePort = DHCP_SERVER_PORT;
    BroadcastInfo.remotePort = ClientInfo.remotePort = DHCP_CLIENT_PORT;
    
    if (isAlreadyInit) {
        UDPClose(RelaySocket);
        RelaySocket = INVALID_UDP_SOCKET;
    }
    
	RelaySocket = UDPOpen(DHCP_SERVER_PORT, NULL, DHCP_CLIENT_PORT);
    if (RelaySocket == INVALID_UDP_SOCKET) {
        return;
    }

    isAlreadyInit = TRUE;
    RelayState = DHCPr_RECEIVE;
}

void DHCPRelayTask(void) {
    if (!isAlreadyInit) return;
    
    switch(RelayState) {
    case DHCPr_RECEIVE:
        if (UDPIsGetReady(RelaySocket) < 240u) break;
        DHCPr_Read();
        //no break
    case DHCPr_SEND:
        if (UDPIsPutReady(RelaySocket) < 300u) break;
        DHCPr_Forward();
    }
}

static
void DHCPr_Read() {
    LED0_IO ^= 1;
    if (UDPIsPutReady(RelaySocket) < 300u) return;
    LED1_IO ^= 1;
    if (UDPIsGetReady(RelaySocket) < 240u) return;
    LED2_IO ^= 1; 
        
    // header
    UDPGetArray(buff, 240);
    header = (BOOTP_HEADER *)buff;
    
    // set the GIADDR
    memcpy(&(header->RelayAgentIP), &RelayIP, sizeof(RelayIP));
         
    length = UDPIsGetReady(RelaySocket);
    if (length > sizeof(buff2)) length = sizeof(buff2);
    UDPGetArray(buff2, length);
    
    // drop the rest of the packet
    UDPDiscard();
    
    switch (header->MessageType) {
        case BOOT_REQUEST:
            CurrentInfo = &ServerInfo;
            RelayState = DHCPr_SEND;
            break;
            
        case BOOT_REPLY:
            memcpy(&ClientInfo.remoteNode.IPAddr, &header->ClientIP, sizeof(header->ClientIP));
            memcpy(&ClientInfo.remoteNode.MACAddr, &header->ClientMAC, sizeof(header->ClientMAC));
            CurrentInfo = &ClientInfo;
            RelayState = DHCPr_SEND;
            break;
        
        default:
            return;
    }
}

static
void DHCPr_Forward() {
    if (240 + length < 300) {
        totalLength = 300;
    } else {
        totalLength = 240 + length;
    }

    if (UDPIsPutReady(RelaySocket) >= totalLength) {
        UDPPutArray(buff, 240);
        UDPPutArray(buff2, length);
        
        while (UDPTxCount < 300u) {
            UDPPut(0);
        }
        UDPFlushTo(CurrentInfo);
        
        RelayState = DHCPr_RECEIVE;
    }
}

#endif // defined(STACK_USE_DHCP_RELAY)
