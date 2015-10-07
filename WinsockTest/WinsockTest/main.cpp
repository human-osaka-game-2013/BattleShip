#include "Client.h"
#include "Server.h"


void main(int argc, char *argv[])
{
	char ctemp;
	printf_s("Client_or_Server? <c/s>\n");
	scanf("%[cs]",&ctemp);

	
	int i=0; 

	if(ctemp=='c'){
		Client client;
		client.m_deststr = "localhost";
		client.Init();
		client.ConnectToServer();
	
		while(1){
			client.Send(  client.GetSocket() , client.GetBuf() );
	//		client.Receive( client.m_inbuf, sizeof(char)*_CONECT_SIZE_  );
		
		}
		client.EndConnect();
	}
	else if(ctemp=='s')
	{
		Server server;
		server.Init();
		server.KeepListen();
		while(1){
			
			server.Receive( server.m_inbuf, sizeof(char)*_CONECT_SIZE_ );
//			server.Send(  server.GetConnectedSocket() ,server.GetBuf() );
				
		}
		server.EndConnect();
	}
	while(1);
}