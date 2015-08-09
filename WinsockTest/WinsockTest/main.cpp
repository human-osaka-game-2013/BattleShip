#include "Client.h"
#include "Server.h"

void main()
{
	char ctemp;
	printf("Client_or_Server? <c/s>\n");
	scanf("%[cs]",&ctemp);

	if(ctemp=='c'){
		Client client;
		client.Init();
		client.ConnectToServer();
		client.Receive();
		client.EndConnect();
	}
	else if(ctemp=='s')
	{
		Server server;
		server.Init();
		server.KeepListen();
		server.Send();	
		server.EndConnect();
	}
	while(1);
}