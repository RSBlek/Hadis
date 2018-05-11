#pragma once
#include "stdafx.h"

using namespace std;


typedef struct _ip_header_
{
	BYTE  ver_ihl;        // Version (4 bits) and Internet Header Length (4 bits)
	BYTE  type;           // Type of Service (8 bits)
	WORD  length;         // Total size of packet (header + data)(16 bits)
	WORD  packet_id;      // (16 bits)
	WORD  flags_foff;     // Flags (3 bits) and Fragment Offset (13 bits)
	BYTE  time_to_live;   // (8 bits)
	BYTE  protocol;       // (8 bits)
	WORD  hdr_chksum;     // Header check sum (16 bits)
	DWORD source_ip;      // Source Address (32 bits)
	DWORD destination_ip; // Destination Address (32 bits)
} IP_HEADER;


typedef struct _tcp_header
{
	unsigned short source_port;  // source port
	unsigned short dest_port;    // destination port
	unsigned int   sequence;     // sequence number - 32 bits
	unsigned int   acknowledge;  // acknowledgement number - 32 bits

	unsigned char  ns : 1;          //Nonce Sum Flag Added in RFC 3540.
	unsigned char  reserved_part1 : 3; //according to rfc
	unsigned char  data_offset : 4;    //number of dwords in the TCP header.

	unsigned char  fin : 1;      //Finish Flag
	unsigned char  syn : 1;      //Synchronise Flag
	unsigned char  rst : 1;      //Reset Flag
	unsigned char  psh : 1;      //Push Flag
	unsigned char  ack : 1;      //Acknowledgement Flag
	unsigned char  urg : 1;      //Urgent Flag

	unsigned char  ecn : 1;      //ECN-Echo Flag
	unsigned char  cwr : 1;      //Congestion Window Reduced Flag

	unsigned short window;          // window
	unsigned short checksum;        // checksum
	unsigned short urgent_pointer;  // urgent pointer
}   TCP_HEADER;



#define SIZE_ETHERNET 14
