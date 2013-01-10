#ifndef _DHCP_RELAY_CONFIG_
#define _DHCP_RELAY_CONFIG_

#define _DHCP_RELAY_IP      { 192ul, 168ul,  97ul,  60ul }
#define _DHCP_SERVER_IP     { 192ul, 168ul,  97ul,   1ul }

#define _DHCP_NETMASK       { 255ul, 255ul, 255ul,   0ul }
#define _DHCP_GATEWAY       { 192ul, 168ul,  97ul,   1ul }
#define _DHCP_PRIMARY_DNS   { 192ul, 168ul,  97ul,   1ul }
#define _DHCP_SECONDARY_DNS {   0ul,   0ul,   0ul,   0ul }

#define _DHCP_MAC           { 0x00, 0x04, 0xA3, 0x00, 0x00, 0x00 }

// the duration of the lease, defaults to 60 seconds
#define DHCP_LEASE_DURATION 60ul

#endif