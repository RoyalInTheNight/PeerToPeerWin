//
// Created by MikoG on 26.11.2022.
//
#include "peer-to-peer-net.cpp"

SOCKET NetUtils::Socket(int32_t INET, int32_t STREAM, int32_t IPPROTO) {
    SOCKET return_s = socket(INET, STREAM, IPPROTO);

    switch (return_s) {
        case INVALID_SOCKET:
            if (DebugMode_n) {
                fprintf(stdout, "[!]SocketError: %d\n", WSAGetLastError());
                return return_s;
            }

            else
                return return_s;

        default:
            if (DebugMode_n) {
                fprintf(stdout, "[*]SocketSuccess\n");
                return return_s;
            }

            else
                return return_s;
    }
}

SOCKET NetUtils::Accept(SOCKET FD, PSOCKADDR_IN LSOCK, PSOCKLEN_T LSOCK_SIZE) {
    SOCKET return_s = accept(FD, (PSOCKADDR)LSOCK, LSOCK_SIZE);

    switch (return_s) {
        case INVALID_SOCKET:
            if (DebugMode_n) {
                fprintf(stdout, "[!]AcceptError: %d\n", WSAGetLastError());
                return return_s;
            }

            else
                return return_s;

        default:
            if (DebugMode_n) {
                fprintf(stdout, "[*]AcceptSuccess:\n\tAddressConnect: %s\t\nPortConnect: %d\n",
                        inet_ntoa(LSOCK->sin_addr),
                        htons(LSOCK->sin_port));

                return return_s;
            }

            else
                return return_s;
    }
}

int32_t NetUtils::Bind(SOCKET FD, PSOCKADDR SOCK, socklen_t SOCK_SIZE) {
    int32_t return_s = bind(FD, SOCK, SOCK_SIZE);

    switch (return_s) {
        case SOCKET_ERROR:
            if (DebugMode_n) {
                fprintf(stdout, "[!]BindError: %d\n", WSAGetLastError());
                return return_s;
            }

            else
                return return_s;

        default:
            if (DebugMode_n) {
                fprintf(stdout, "[*]BindSuccess\n");
                return return_s;
            }

            else
                return return_s;
    }
}

int32_t NetUtils::Connect(SOCKET FD, PSOCKADDR SOCK, socklen_t SOCK_SIZE) {
    int32_t return_s = connect(FD, SOCK, SOCK_SIZE);

    switch (return_s) {
        case SOCKET_ERROR:
            if (DebugMode_n) {
                fprintf(stdout, "[!]ConnectError: %d\n", WSAGetLastError());
                return return_s;
            }

            else
                return return_s;

        default:
            if (DebugMode_n) {
                fprintf(stdout, "[*]ConnectSuccess\n");
                return return_s;
            }

            else
                return return_s;
    }
}

int32_t NetUtils::Listen(SOCKET FD, uint128_t QUEUE) {
    int32_t return_s = listen(FD, QUEUE);

    switch (return_s) {
        case SOCKET_ERROR:
            if (DebugMode_n) {
                fprintf(stdout, "[!]ListenError: %d\n", WSAGetLastError());
                return return_s;
            }

            else
                return return_s;
        default:
            if (DebugMode_n) {
                fprintf(stdout, "[*]ListenSuccess\n");
                return return_s;
            }

            else
                return return_s;
    }
}

int64_t NetUtils::TCPRecv(SOCKET FD, WINBUFFER BUFFER, size_t BUFFER_SIZE, int32_t FLAGS) {
    int64_t return_s = recv(FD, BUFFER, BUFFER_SIZE, FLAGS);

    switch (return_s) {
        case SOCKET_ERROR:
            if (DebugMode_n) {
                fprintf(stdout, "[!]TCPRecvError: %d\n", WSAGetLastError());
                return return_s;
            }

            else
                return return_s;

        default:
            if (DebugMode_n) {
                fprintf(stdout, "[*]TCORecvSuccess\n");
                return return_s;
            }

            else
                return return_s;
    }
}

int64_t NetUtils::TCPSend(SOCKET FD, WINBUFFER MSG, size_t MSG_SIZE, int32_t FLAGS) {
    int64_t return_s = send(FD, MSG, MSG_SIZE, FLAGS);

    switch (return_s) {
        case SOCKET_ERROR:
            if (DebugMode_n) {
                fprintf(stdout, "[!]TCPSendError: %d\n", WSAGetLastError());
                return return_s;
            }

            else
                return return_s;

        default:
            if (DebugMode_n) {
                fprintf(stdout, "[*]TCPSendSuccess\n");
                return return_s;
            }

            else
                return return_s;
    }
}

int64_t NetUtils::UDPRecv(SOCKET FD,
                          WINBUFFER BUFFER,
                          size_t BUFFER_SIZE,
                          int32_t FLAGS,
                          PSOCKADDR_IN LSOCK,
                          PSOCKLEN_T LSOCK_SIZE) {
    int64_t return_s = recvfrom(FD,
                                BUFFER,
                                BUFFER_SIZE,
                                FLAGS,
                                (PSOCKADDR)LSOCK,
                                LSOCK_SIZE);

    switch (return_s) {
        case SOCKET_ERROR:
            if (DebugMode_n) {
                fprintf(stdout, "[!]UDPRecvError: %d\n", WSAGetLastError());
                return return_s;
            }

            else
                return return_s;
        default:
            if (DebugMode_n) {
                fprintf(stdout, "[*]UDPRecvSuccess:\n\tAddressConnect: %s\n\tPortConnect: %d\n",
                        inet_ntoa(LSOCK->sin_addr),
                        htons(LSOCK->sin_port));

                return return_s;
            }

            else
                return return_s;
    }
}

int64_t NetUtils::UDPSend(SOCKET FD,
                          WINBUFFER MSG,
                          size_t MSG_SIZE,
                          int32_t FLAGS,
                          PSOCKADDR SOCK,
                          socklen_t SOCK_SIZE) {
    int64_t return_s = sendto(FD,
                              MSG,
                              MSG_SIZE,
                              FLAGS,
                              SOCK,
                              SOCK_SIZE);

    switch (return_s) {
        case SOCKET_ERROR:
            if (DebugMode_n) {
                fprintf(stdout, "[!]UDPSendError: %d\n", WSAGetLastError());
                return return_s;
            }

            else
                return return_s;

        default:
            if (DebugMode_n) {
                fprintf(stdout, "[*[UDPSendSuccess\n");
                return return_s;
            }

            else
                return return_s;
    }
}