#include "Client.h"
#include "Server.h"


void main(int argc, char *argv[])
{
	char ctemp;
	printf_s("Client_or_Server? <c/s>\n");
	scanf("%[cs]",&ctemp);
/**	if (argc != 2) {
		 DebugMsgBox("Usage : %s dest\n", argv[0]);
		 while(1);
	}*/
	if(ctemp=='c'){
		Client client;
		client.m_deststr = "www.google.co.jp";
		client.Init();
		client.ConnectToServer();
	//	client.Receive();
		client.EndConnect();
	}
	else if(ctemp=='s')
	{
		Server server;
		server.Init();
		server.KeepListen();
	//	server.Send();	
		server.EndConnect();
	}
	while(1);
}