//
// Created by MikoG on 12.12.2022.
//

#ifndef NATIVEPROJECT_NATIVEINTERFACE_H
#define NATIVEPROJECT_NATIVEINTERFACE_H

#include <cstdio>
#include <winsock2.h>
#include <cstdlib>
#include <cstring>

// int types
typedef signed char      int8_t;
typedef unsigned char   uint8_t;
typedef short           int16_t;
typedef unsigned short uint16_t;
typedef int             int32_t;
typedef unsigned int   uint32_t;
typedef long            int64_t;
typedef int32_t       socklen_t;


// pointer types
typedef FILE *            PFILE;
typedef socklen_t *  psocklen_t;

template<class __Key, class __tp> class npmap {
private:
    template<class __Alloc_key, class __Alloc_tn> struct __Allocator_memory {
        __Alloc_key declAllocKey;
        __Alloc_tn declAllocTn;
    };

    void np_memcpy(void *, const void *, size_t);
    void np_memset(void *, uint8_t, size_t);
public:
    typedef __Key     IndexType;
    typedef __tp      ArrayType;

    __Allocator_memory<IndexType, ArrayType> &value_types(IndexType &, ArrayType &);
    void __Allocator(__Allocator_memory<IndexType, ArrayType> *);
    template<class __tn, class __tn2> __tn2 &operator[](__tn &);
    template<class __tn> __tn &operator<<(__tn &);
    template<class __tn, class __tn2> __tn2 &at(__tn);
    __Allocator_memory<IndexType, ArrayType> &insert(__Allocator_memory<IndexType, ArrayType> &);

    void clean();
    void c_point();
};

class NetUtils {
protected:
    npmap<const char *, const char *> Addr2Nick;
    npmap<const char *, const char *> Nick2Addr;
    npmap<const char *, uint16_t>     Addr2Port;

    char **Addresses;
    char **Nicknames;

    SOCKET FD_PEER_LOOP;
    SOCKET FD_PEER_CONN;

    SOCKET FD_NODE_LOOP;
    SOCKET FD_NODE_CONN;

    socklen_t sizesock;
public:
    void SocketInitClient(SOCKET, int32_t, int32_t, int32_t, sockaddr *);
    void SocketInitServer(SOCKET, int32_t, int32_t, int32_t, sockaddr *);

    void TCPSend(SOCKET, const char *, size_t, int32_t);
    void TCPRecv(SOCKET, const char *, size_t, int32_t);

    void UDPSend(SOCKET, const char *, size_t, int32_t, sockaddr *, socklen_t);
    void UDPRecv(SOCKET, const char *, size_t, int32_t, sockaddr_in *, socklen_t *);
};

class Peer {
private:
};

#endif //NATIVEPROJECT_NATIVEINTERFACE_H
