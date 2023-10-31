#ifndef OOSTUBS_NW_PROTOCOLS_H
#define OOSTUBS_NW_PROTOCOLS_H
#include "machine/network.h"
#include "device/devices.h"

enum protocolNr{
    ICMP = 1,
    TCP = 6,
    UDP = 17

};

enum DHCP_Operation {
    REQ = 1,
    RPLY = 2
};

class UDPPacket: public IPv4Packet {
    uint16_t qport, dport, length, checksum;
    protected:
    UDPPacket(uint32_t source, uint32_t dest, uint16_t qport,
    uint16_t dport, uint16_t length):IPv4Packet(source, dest, length + sizeof(UDPPacket), 17),
    qport(qport), dport(dport), length(length), checksum(0){}
};

class DHCP_Packet: public UDPPacket {
    uint32_t op_htype_hlen_zero;
    uint32_t xid;
    uint32_t secs_flags;
    uint32_t ciaddr, yiaddr, siaddr, giaddr;
    uint64_t mac_1;
    uint64_t mac_2;
    public:
    DHCP_Packet(uint32_t source, uint32_t dest, uint8_t op,
    uint8_t htype, uint8_t hlen, uint32_t xid, uint16_t secs, uint16_t flags,
    uint32_t ciaddr, uint32_t yiaddr, uint32_t siaddr, uint32_t giaddr): UDPPacket(source, dest, 33245, 67,  sizeof(DHCP_Packet)){
        op_htype_hlen_zero = 0 | (uint32_t)op << 24 | htype << 16 | hlen << 8;
        secs_flags = (uint32_t)secs << 16 | flags;
        mac_1 = getDevice()->getMac_p1();
        mac_2 = getDevice()->getMac_p2();
    }
};

#endif