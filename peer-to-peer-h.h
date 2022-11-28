//
// Created by MikoG on 26.11.2022.
//

#ifndef UNTITLED_PEER_TO_PEER_H_H
#define UNTITLED_PEER_TO_PEER_H_H

#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
#include <map>
#include <winsock2.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <math.h>
#include <thread>
#include <time.h>

// socklen
typedef int32_t            socklen_t;
typedef long long           int128_t;
typedef unsigned long long uint128_t;

// ptr types
typedef FILE *               PFILE;
typedef char *           WINBUFFER;
typedef sockaddr *       PSOCKADDR;
typedef socklen_t *     PSOCKLEN_T;
typedef sockaddr_in * PSOCKADDR_IN;

// arrays types
typedef std::vector<std::string>         svector;
typedef std::map<std::string, std::string>  smap;
typedef std::map<std::string, uint16_t> suintMap;

uint8_t   size8_t     = pow(2, sizeof(int8_t)   * 8);
uint16_t  size16_t    = pow(2, sizeof(int16_t)  * 8);
uint32_t  size32_t    = pow(2, sizeof(int32_t)  * 8);
uint64_t  size64_t    = pow(2, sizeof(int64_t)  * 8);
uint128_t size128_t   = pow(2, sizeof(int128_t) * 8);

enum ConstructorPeerOrNode {
    Address = 0,
    Nickname
};

enum PeerAndNode {
    Peer = 0,
    Node
};

enum KernelEnumeration {
    DebugMode_off = 0,
    DebugMode_on
};

enum loop {
    singularity = 1
};

class NetUtils {
public:
    int32_t DebugMode_n;

    SOCKET Socket(int32_t, int32_t, int32_t);
    SOCKET Accept(SOCKET, PSOCKADDR_IN, PSOCKLEN_T);

    int64_t TCPRecv(SOCKET, WINBUFFER, size_t, int32_t);
    int64_t TCPSend(SOCKET, WINBUFFER, size_t, int32_t);
    int64_t UDPRecv(SOCKET, WINBUFFER, size_t, int32_t, PSOCKADDR_IN, PSOCKLEN_T);
    int64_t UDPSend(SOCKET, WINBUFFER, size_t, int32_t, PSOCKADDR, socklen_t);

    int32_t Bind(SOCKET, PSOCKADDR, socklen_t);
    int32_t Connect(SOCKET, PSOCKADDR, socklen_t);

    int32_t Listen(SOCKET, uint128_t);
};

class Utils {
public:
    svector Addresses;
    svector Nicknames;

    smap AddressesNicknames;
    smap NicknamesAddresses;

    suintMap AddressesPorts;

    void delay(uint128_t);
    void cmd(WINBUFFER);
    void cmdpopen(WINBUFFER);
};

class Peer : public NetUtils, Utils {
private:
    std::string YourAddress;
    std::string YourNickname;
    std::string YourPassword;

    uint16_t YourPort;

    sockaddr_in loop_sock;
    sockaddr_in node_sock;

    SOCKET FD_PEER;
    SOCKET FD_PEER_LOOP;
    SOCKET FD_NODE;
    SOCKET FD_NODE_LOOP;

    socklen_t sizesock;
public:
    Peer(svector, svector, uint16_t, uint16_t, int32_t); // svector YourData, svector NodeData, uint16_t YourPort, uint16_t NodePort, int32_t DebugMode;
    void initTCPPeer();
    void initUDPPeer();

    void ConnectToTCPPeer(std::string);
    void ConnectToUDPPeer(std::string);

    void ShareFileToTCPPeer(PFILE);
    void ShareFileToUDPPeer(PFILE);

    void SendDataToTCPPeer(std::string);
    void SendDataToUDPPeer(std::string);

    std::string GetMembers();
};

class Node : public NetUtils, Utils {

};

#endif //UNTITLED_PEER_TO_PEER_H_H
