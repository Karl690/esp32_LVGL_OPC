#include "main.h"
#include "server.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <pthread.h>

#include <map>



#define MAX_CLIENT_NUM 2
#define SOCKET_CLIENT_BUFFER_SIZE 1024
pthread_mutex_t mutex;
pthread_t threadAccept = 0;
int listenfd;
typedef struct client_socket {
	int socket_fd;
	struct sockaddr_in client_address;
	pthread_t thread;
	uint8_t buf[SOCKET_CLIENT_BUFFER_SIZE];
} client_socket;

client_socket clientList[MAX_CLIENT_NUM];
static void* server_client_handler(void* param)
{
	client_socket *clientsocket = (client_socket *)param;
	int socket_fd = clientsocket->socket_fd;
	struct sockaddr_in client_address = clientsocket->client_address;
	
	uint8_t* buffer = clientsocket->buf;
	int bytes_read;
	while ((bytes_read = recv(socket_fd, buffer, SOCKET_CLIENT_BUFFER_SIZE, 0)) > 0)
	{
		send(socket_fd, "OK", 2, 0);
	}
	clientsocket->socket_fd = 0;
	
	close(socket_fd);
	return NULL;
}

//find the free client buffer
client_socket* server_find_free_client()
{
	for (int i = 0; i < MAX_CLIENT_NUM; i++)
	{	
		if (clientList[i].socket_fd == 0) return &clientList[i];
	}
	return NULL;
}

//find the client buffer
client_socket* server_find_client(int socketid)
{
	for (int i = 0; i < MAX_CLIENT_NUM; i++)
	{	
		if (clientList[i].socket_fd == socketid) return &clientList[i];
	}
	return NULL;
}

int16_t server_send_buffer(int socketid, uint8_t* buf, uint16_t size)
{
	int16_t written = send(socketid, buf, size, 0);	
	return written;
}

static void* server_accept_handler(void* param)
{
	socklen_t client_address_len;	
	int socketid;
	client_socket* client;
	pthread_t pthread;
	while (1)
	{	
		client = server_find_free_client();
		
		struct sockaddr_in client_address;
		client_address_len = sizeof client_address;
		
		socketid = accept(listenfd, (struct sockaddr*)&client_address, &client_address_len);
		if (socketid == -1)
		{
			perror("accept");
			continue;
		}
		if (!client)
		{
			/*full clients*/
			char buf[] = "full clients, please try later";
			server_send_buffer(socketid, (uint8_t*)buf, strlen(buf));
			sleep(200);
			close(socketid);
			continue;
		}
		/* Create thread to serve connection to client. */
		client->client_address = client_address;
		client->socket_fd = socketid;
		if (pthread_create(&pthread, NULL, server_client_handler, (void *)client) != 0) {
			perror("pthread_create");
			continue;
		}
		client->thread = pthread;
	}
	return NULL;
}

bool server_start()
{
	struct sockaddr_in serv_addr; 
//	pthread_mutex_init(&mutex, NULL);
	threadAccept = 0;
	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if (listenfd <  0) 
	{
		perror("Error in socket creation");
		return false;
	}
	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(SERVER_PORT); 

	int yes = 1;
	if (setsockopt(listenfd, SOL_SOCKET,SO_REUSEADDR,(void*)&yes,sizeof(yes)) < 0) {
			return false;
	}
	int rv = bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); 

	if (rv <  0) 
	{
		perror("Error in binding");
		return false;
	}

	listen(listenfd, 10); 

	pthread_create(&threadAccept, NULL, server_accept_handler, (void *) NULL);
	return true;
}

void server_send_broadcast(uint8_t* buf, int size)
{
	for (uint8_t i = 0; i < MAX_CLIENT_NUM; i++)
	{
		if (clientList[i].socket_fd == 0) continue;
		send(clientList[i].socket_fd, buf, size, 0);
	}
}

void server_client_close(int socketid)
{
	client_socket* client = server_find_client(socketid);
	if (client && client->thread > 0)
	{
		pthread_cancel(client->thread);
		close(client->socket_fd);
		client->socket_fd = 0;	
	}
}
void server_stop()
{
	if (threadAccept == 0) return;
	for (int i = 0; i < MAX_CLIENT_NUM; i++)
	{
		if (clientList[i].socket_fd > 0) server_client_close(clientList[i].socket_fd);
	}
	close(listenfd);
	pthread_cancel(threadAccept);
	threadAccept = 0;
}

bool servier_is_status()
{
	return threadAccept == 0 ? false : true;
}