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
	
		while(i != 1000 ){
			i++;
			if(i == 1000)
				i=0;

			if(i == 99){
				client.Send(  client.GetSocket() ,client.GetBuf() );
				client.Receive( client.GetBuf(), sizeof(char)*_CONECT_SIZE_  );
			}
		}
		client.EndConnect();
	}
	else if(ctemp=='s')
	{
		Server server;
		server.Init();
		server.KeepListen();
		while(i != 1000 ){
			i++;
			if(i == 1000)
				i=0;
			if(i == 99){

				server.Receive( server.GetBuf(), sizeof(char)*_CONECT_SIZE_ );
				//server.Send(  server.GetConnectedSocket() ,server.GetBuf() );
			}
		
		}
		server.EndConnect();
	}
	while(1);
}