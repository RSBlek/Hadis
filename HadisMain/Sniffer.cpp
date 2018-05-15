#include "stdafx.h"
#include "Sniffer.h"
#include "NetworkHeader.h"

using namespace std::chrono;

DWORD WINAPI Sniffer::sniffStart(void* data) {
	Sniffer* This = (Sniffer*)data;
	This->sniff();
	return 0;
}

void Sniffer::setIp(int ip) {
	this->devip = ip;
}

void Sniffer::sniff() {
	struct   sockaddr_in sock_sniff;
	SOCKET   sniff_socket = -1;
	WSAData  sa_data;
	WORD     ver;
	IP_HEADER *ip_header = NULL;
	int      optval = 1;
	DWORD    dwLen = 0;
	char     packet[LS_MAX_PACKET_SIZE];
	int      iRet = 0;
	int      ip_header_size = 0;
	// Init Windows sockets version 2.2   
	ver = MAKEWORD(2, 2);
	WSAStartup(ver, &sa_data);

	// Get a socket in RAW mode
	sniff_socket = socket(AF_INET, SOCK_RAW, IPPROTO_IP);
	if (sniff_socket == SOCKET_ERROR)
	{
		char errormsg[128];
		sprintf_s(errormsg, "Error Code: %d", WSAGetLastError());
		MessageBoxA(NULL, errormsg, "Hadis Error", 0);
		exit(-1);
	}


	sock_sniff.sin_family = AF_INET;
	sock_sniff.sin_port = htons(0);
	// If your machine has more than one IP you might put another one instead thisIP value
	sock_sniff.sin_addr.s_addr = this->devip;

	if (::bind(sniff_socket, (struct sockaddr *)&sock_sniff, sizeof(sock_sniff)) == SOCKET_ERROR)
	{
		char errormsg[128];
		sprintf_s(errormsg, "Error Code: %d \r\v Dev: %d", WSAGetLastError(),this->devip);
		MessageBoxA(NULL, errormsg, "Hadis Error", 0);
		exit(-2);
	}	
	

	// Set socket to sniffing mode
	if (WSAIoctl(sniff_socket,
		SIO_RCVALL,
		&optval,
		sizeof(optval),
		NULL,
		0,
		&dwLen,
		NULL,
		NULL) == SOCKET_ERROR)

	{
		printf("Error: ioctl  = %d\n", WSAGetLastError());
		exit(-3);
	}

	exited = false;
	while (!exited)
	{
		(void)memset(packet, 0x00, sizeof(packet));
		iRet = recv(sniff_socket, packet, LS_MAX_PACKET_SIZE, 0);
		if (iRet < (sizeof(IP_HEADER) + sizeof(TCP_HEADER))) //If the received byte count is smaller than the minimum header size
			continue;

		ip_header = (IP_HEADER *)packet;

		if (LS_HI_PART(ip_header->ver_ihl) != 4) //Only IPv4
			continue;

		ip_header_size = LS_LO_PART(ip_header->ver_ihl) * 4; //Get ip header size

		if (ip_header->protocol != 6) //Only TCP
			continue;
		
		TCP_HEADER *tcp_header = (TCP_HEADER*)&packet[ip_header_size];
		unsigned short srcport = htons(tcp_header->source_port);
		unsigned short dstport = htons(tcp_header->dest_port);
		unsigned int tcpsize = tcp_header->data_offset * 4;
		
		if (srcport != 7777 && dstport != 7777) continue;

		unsigned int datasize = iRet - ip_header_size - tcpsize;
		char* pdata = (char*)malloc(datasize);
		char* datastart = packet + ip_header_size + tcpsize;
		for (unsigned int i = 0; i < datasize; i++) {
			pdata[i] = datastart[i];
		}

		TCPPacket* tcppacket = new TCPPacket();

		tcppacket->data = packet;
		if (srcport == 7777) {
			tcppacket->clientpacket = false;
		}
		else {
			tcppacket->clientpacket = true;
		}
		tcppacket->data = pdata;
		tcppacket->ip_dst = ip_header->destination_ip;
		tcppacket->ip_src = ip_header->source_ip;
		tcppacket->ip_header_size = ip_header_size;
		tcppacket->ip_packet_id = ip_header->packet_id;
		tcppacket->ip_time_to_live = ip_header->time_to_live;
		tcppacket->tcp_port_dst = dstport;
		tcppacket->tcp_port_src = srcport;
		tcppacket->tcp_sequence = htonl(tcp_header->sequence);
		tcppacket->tcp_acknowledge = htonl(tcp_header->acknowledge);
		tcppacket->tcp_header_size = tcpsize;
		tcppacket->tcp_psh = tcp_header->psh;
		tcppacket->tcp_rst = tcp_header->rst;
		tcppacket->tcp_fin = tcp_header->fin;
		tcppacket->tcp_syn = tcp_header->syn;
		tcppacket->tcp_ack = tcp_header->ack;
		tcppacket->data_size = iRet - ip_header_size - tcpsize;
		tcppacket->timestamp = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
		PacketBuffer::packetmutex.lock();
		PacketBuffer::allpackets.push_back(tcppacket);
		cout << PacketBuffer::allpackets.size() << endl;
		PacketBuffer::packetmutex.unlock();
	}
	
}

