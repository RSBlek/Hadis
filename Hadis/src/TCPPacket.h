#pragma once

class TCPPacket {
public:
	char* data;
	bool clientpacket;
	unsigned short ip_header_size;
	unsigned short ip_packet_id;
	unsigned char ip_time_to_live;
	unsigned int ip_src;
	unsigned int ip_dst;
	unsigned short tcp_port_src;
	unsigned short tcp_port_dst;
	unsigned int tcp_sequence;
	unsigned int tcp_acknowledge;
	unsigned char tcp_header_size;
	unsigned char tcp_fin;
	unsigned char tcp_ack;
	unsigned char tcp_rst;
	unsigned char tcp_syn;
	unsigned char tcp_psh;
	unsigned short data_size;
	unsigned long long timestamp; //Unix Timestamp in milliseconds
public:
	~TCPPacket() {
		free(data);
	}
};