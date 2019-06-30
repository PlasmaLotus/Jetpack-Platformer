#include <SDL_net.h>
#include <string.h>
#include <vector>
//SDLNet_ResolveHost

//Handles all Net connections managed, maybe on another thread
class ClientNetworkManager;
class ServerNetworkManager;
class INetworkManager{
public:
	INetworkManager();
	~INetworkManager();
	virtual bool Init();
	virtual bool DeInit();
	virtual void HandleEvents();//handle send and recieve
	//list of different socket sets
	//Queue packet to send
	//Get all incoming packets
	SDLNet_SocketSet set;
	UDPsocket udpsock;
  TCPsocket tcpsock;
	SDLNet_GenericSocket genericsock;
	IPaddress ipAdress;
	std::vector<std::string> packetsRecieved;
};
INetworkManager::INetworkManager(){}
INetworkManager::~INetworkManager(){}
bool INetworkManager::Init(){
	if (SDLNet_Init() < 0) {
		printf("SDLNet_Init:  %s\n", SDLNet_GetError());
		return false;
	}
	else
		return true;
}
bool INetworkManager::DeInit(){
	SDLNet_Quit();

	return true;
}
void INetworkManager::HandleEvents(){
	udpsock = SDLNet_UDP_Open(42069);
	if(!udpsock){
		printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
	}
	else{
		printf("SDLNet_UDP_Open: Succesful on port %d \n", 42069);
	}

	if(SDLNet_ResolveHost(&ipAdress,"localhost",9999)==-1) {
		printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
		//SDLNET_MAX_UDPADDRESSES
		//exit(1);
		return;
	}
	/*
	ipAdress.host = INADDR_LOOPBACK;
	ipAdress.port = 42042;
	*/
	tcpsock = SDLNet_TCP_Open(&ipAdress);
	if(!tcpsock){
		printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
	}
	else
	{
		printf("SDLNet_TCP_Open: Succesful on \n");
	}



}


class ServerSocket;
class ClientSockset;
//IConnection;
class ISocket{
public:
	ISocket();
	~ISocket();
	SDLNet_SocketSet set; //a set of sockets. Used here only to check existing packets
	virtual void SetSocket();
	virtual bool Accept();
	virtual void onReady();
	

};