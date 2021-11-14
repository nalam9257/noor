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
typedef short int UINT16 ;
typedef char* U_bit128 ;
typedef char UINT8;

using namespace std;
#define CONNECT_COMMAND (0xAA01)

struct packet
{
    char name[30];
    int a=12;
};
#endif // PACKET_H
