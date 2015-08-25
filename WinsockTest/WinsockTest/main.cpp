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
		client.m_deststr = "localhost";
		client.Init();
		client.ConnectToServer();
	
		while(1){
			//client.Receive( client.GetBuf() );
			client.Send(  client.GetSocket() ,client.GetBuf() );
		}
		client.EndConnect();
	}
	else if(ctemp=='s')
	{
		Server server;
		server.Init();
		server.KeepListen();
		while(1){
			//server.Send(  server.GetConnectedSocket() ,server.GetBuf() );
			server.Receive( server.GetBuf() );
		}
		server.EndConnect();
	}
	while(1);
}