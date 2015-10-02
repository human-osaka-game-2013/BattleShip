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
	
	int i=0; 

	if(ctemp=='c'){
		Client client;
		client.m_deststr = "localhost";
		client.Init();
		client.ConnectToServer();
	
		while(i != 100 ){
			i++;
			if(i == 100)
				i=0;

			if(i == 99){
				client.Send(  client.GetSocket() ,client.GetBuf() );
				client.Receive( client.GetBuf() );
			}
		}
		client.EndConnect();
	}
	else if(ctemp=='s')
	{
		Server server;
		server.Init();
		server.KeepListen();
		while(i != 100 ){
			i++;
			if(i == 100)
				i=0;
			if(i == 99){

		server.Receive( server.GetBuf() );
		server.Send(  server.GetConnectedSocket() ,server.GetBuf() );
		
		server.EndConnect();
	}
	while(1);
}