#ifndef PACKET_H
#define PACKET_H
#include <iostream>
#include<cstdio>
#include<string>
#include<string.h>
#include<cstring>
#include <byteswap.h>
#include<stdlib.h>
typedef unsigned short  int U_bit16 ;
typedef  int UINT32 ;
typedef unsigned short int UINT16 ;
typedef char* U_bit128 ;
typedef char UINT8;

#define SONU_ADDR "192.168.137.1"

#define ACK (0x06)
#define HEADER (0x8765)
#define FOOTER (0x4321)
#define MAX_SIZE 1024

using namespace std;
#define CONNECT_COMMAND 0xAA01
#define SPORT (0x1000)
#define RPORT (0x1001)
struct noor{
    char name[30];
    int a=12;
};
#endif // PACKET_H
