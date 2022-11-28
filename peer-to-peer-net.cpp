//
// Created by MikoG on 26.11.2022.
//
#include "peer-to-peer-h.h"

Peer::Peer(svector YourData, svector NodeData, uint16_t YourPort_c, uint16_t NodePort, int32_t DebugMode) {
    Addresses.resize(2);
    Nicknames.resize(2);

    Addresses.at(PeerAndNode::Peer) = YourData.at(ConstructorPeerOrNode::Address);
    Nicknames.at(PeerAndNode::Peer) = YourData.at(ConstructorPeerOrNode::Nickname);
    Addresses.at(PeerAndNode::Node) = NodeData.at(ConstructorPeerOrNode::Address);
    Nicknames.at(PeerAndNode::Node) = NodeData.at(ConstructorPeerOrNode::Nickname);

    AddressesNicknames.insert(smap::value_type(Addresses.at(PeerAndNode::Peer), Nicknames.at(PeerAndNode::Peer)));
    AddressesNicknames.insert(smap::value_type(Addresses.at(PeerAndNode::Node), Nicknames.at(PeerAndNode::Node)));
    NicknamesAddresses.insert(smap::value_type(Nicknames.at(PeerAndNode::Peer), Addresses.at(PeerAndNode::Peer)));
    NicknamesAddresses.insert(smap::value_type(Nicknames.at(PeerAndNode::Node), Addresses.at(PeerAndNode::Node)));

    AddressesPorts.insert(suintMap::value_type(Addresses.at(PeerAndNode::Peer), YourPort_c));
    AddressesPorts.insert(suintMap::value_type(Addresses.at(PeerAndNode::Node), NodePort));

    DebugMode_n = DebugMode;

    sizesock = sizeof(sockaddr_in);

    YourAddress = Addresses.at(PeerAndNode::Peer);
    YourNickname = Nicknames.at(PeerAndNode::Peer);
    YourPort = YourPort_c;

    {
        WSADATA wsa;

        if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
            if (DebugMode)
                fprintf(stdout, "[!]WSAInitError: %d\n", WSAGetLastError());

            exit(-1);
        }
    }
}

void Peer::initTCPPeer() {
    auto InitNodeConnection = ([&]() {
        node_sock.sin_addr.S_un.S_addr = inet_addr(Addresses.at(PeerAndNode::Node).c_str());
        node_sock.sin_port = htons(AddressesPorts.at(Addresses.at(PeerAndNode::Node)));
        node_sock.sin_family = AF_INET;

        NetUtils net;
        FD_NODE = net.Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        net.Connect(FD_NODE, (PSOCKADDR)&node_sock, sizesock);
        net.TCPSend(FD_NODE, (WINBUFFER)Nicknames.at(PeerAndNode::Peer).c_str(), Nicknames.at(PeerAndNode::Peer).size(), 0);

        while (loop::singularity) {
            net.TCPSend(FD_NODE, (WINBUFFER)"on", 2, 0);
            delay(1000);
        }
    });

    auto InitLoopConnection = ([&]() {
        loop_sock.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
        loop_sock.sin_port = htons(YourPort);
        loop_sock.sin_family = AF_INET;

        NetUtils net;
        SOCKET FD = net.Socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

        net.Bind(FD, (PSOCKADDR)&loop_sock, sizesock);

        sockaddr_in lsock;

        while (loop::singularity) {
            net.Listen(FD, 1024);
            FD_PEER_LOOP = net.Accept(FD, &lsock, &sizesock);
        }
    });

    std::thread(InitLoopConnection).detach();
    std::thread(InitNodeConnection).detach();
}