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
static IP_ADDR              RelayIP;

static BYTE                 buff[256];

// tmp variables
static BYTE                 *cur, byteLength, optionCode;
static WORD                 length;
static BOOL                 done;
static BOOTP_HEADER         *header;

static BOOL isAlreadyInit;

static void ForwardToClient();
static void ForwardToServer();

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
    }{
        int i;
        unsigned long ip[] = _DHCP_RELAY_IP;
        for (i = 0; i < 4; i++)
            RelayIP.v[i] = ip[i];
    }
    
    if (isAlreadyInit) {
        UDPClose(SocketToClient);
        UDPClose(SocketToServer);
    }
    
	SocketToClient = UDPOpen(DHCP_SERVER_PORT, NULL, DHCP_CLIENT_PORT);
    if (SocketToClient == INVALID_UDP_SOCKET) {
        return;
    }
    SocketToServer = UDPOpen(DHCP_CLIENT_PORT, /*&ServerInfo*/ NULL, DHCP_SERVER_PORT);
    if (SocketToServer == INVALID_UDP_SOCKET) {
        UDPClose(SocketToClient);
        return;
    }

    isAlreadyInit = TRUE;
}

void DHCPRelayTask(void) {
    if (!isAlreadyInit) return;
    
    if (UDPIsGetReady(SocketToServer) > 0) {
        ForwardToClient();
    }
    if (UDPIsGetReady(SocketToClient) > 0) {
        ForwardToServer();
    }
}

static
void ForwardToClient() {
    LED0_IO ^= 1;
    if (UDPIsPutReady(SocketToClient) < 300u) return;
    LED1_IO ^= 1;
    if (UDPIsGetReady(SocketToServer) < 250u) return;
    LED2_IO ^= 1;
    
    cur = (BYTE *)buff;
    length = 0;
    
    // Skip the header etc. until GIADDR
    UDPGetArray(cur, 240);
    cur += 240;
    
    done = FALSE;
    while (!done) {
        if (!UDPGet(&optionCode)) {
            done = TRUE;
        }
        *cur = optionCode;
        cur++;
        
        switch (optionCode) {
            case DHCP_MESSAGE_TYPE:
                UDPGetArray(cur, 2);
                cur += 2;
                break;
            case DHCP_SUBNET_MASK:
            case DHCP_SERVER_IDENTIFIER:
            case DHCP_IP_LEASE_TIME:
                UDPGetArray(cur, 5);
                cur += 5;
                break;
            case DHCP_END_OPTION:
                done = TRUE;
                break;
            case DHCP_ROUTER:
#if defined(STACK_USE_DNS)
            case DHCP_DNS:
#endif
            default:
                UDPGet(&byteLength);
                *cur = byteLength;
                cur++;
                UDPGetArray(cur, byteLength);
                cur += byteLength;
                break;
        }
    }
    
    // drop the rest of the packet
    UDPDiscard();
    
    length = (cur - buff);
    if (UDPIsPutReady(SocketToClient) >= length) {
        UDPPutArray(buff, length);
        
        while (UDPTxCount < 300u) {
            UDPPut(0);
        }
        UDPFlush();
    }
}

static
void ForwardToServer() {
    LED0_IO ^= 1;
    if (UDPIsPutReady(SocketToServer) < 300u) return;
    LED1_IO ^= 1;
    if (UDPIsGetReady(SocketToClient) < 240u) return;
    LED2_IO ^= 1;
    
    cur = (BYTE *)buff;
    length = 0;
    
    // header
	/*UDPGetArray((BYTE *)&header, sizeof(header));
    memcpy(cur, &header, sizeof(header));
    cur += sizeof(header);
    
    // legacy BOOTP junk
	UDPGetArray(cur, 192);
    cur += 192;
    
    // magic word
    UDPGetArray(cur, sizeof(DWORD));
    cur += sizeof(DWORD);*/
    
    UDPGetArray(cur, 240);
    header = (BOOTP_HEADER *)cur;
    cur += 240;
    
    // set the GIADDR
    memcpy(&(header->RelayAgentIP), &RelayIP, sizeof(RelayIP));
    
    // read the rest
    while ((length = UDPIsGetReady(SocketToClient)) > 0) {
        UDPGetArray(cur, length);
        cur += length;
    }
	// options
	/*while(1)
	{
		// Get option type
		if(!UDPGet(&optionCode))
			break;
        *cur = optionCode;
        cur++;
            
		if(optionCode == DHCP_END_OPTION)
			break;

		// Get option length
		UDPGet(&length);
        *cur = length;
        cur ++;
        
        // read the option
        UDPGetArray(cur, length);
        cur += length;
    }*/
    
    // discard the package
    UDPDiscard(); 
    
    length = (cur - buff);
    if (UDPIsPutReady(SocketToServer) >= length) {
        UDPPutArray(buff, length);
        
        // pad to 300 if needed
        while (UDPTxCount < 300u) {
            UDPPut(0);
        }
        UDPFlush();
    }
}

#endif // defined(STACK_USE_DHCP_RELAY)