#include <iostream>
#include <string>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
WSADATA wsa;
SOCKET serverSocket;
sockaddr_in server, client;
int clientSize = sizeof(client);
char buffer[1024];

WSAStartup(MAKEWORD(2, 2), &wsa);

serverSocket = socket(AF_INET, SOCK_DGRAM, 0);

server.sin_family = AF_INET;
server.sin_addr.s_addr = INADDR_ANY;
server.sin_port = htons(8080);

bind(serverSocket, (sockaddr*)&server, sizeof(server));

cout << "UDP Server is waiting for message..." << endl;

int bytes = recvfrom(serverSocket, buffer, sizeof(buffer) - 1, 0,
                     (sockaddr*)&client, &clientSize);

if (bytes == SOCKET_ERROR) {
    cout << "Receive failed." << endl;
    closesocket(serverSocket);
    WSACleanup();
    return 1;
}

buffer[bytes] = '\0';
cout << "Message from client: " << buffer << endl;

string reply = "Hello from UDP Server!";

sendto(serverSocket, reply.c_str(), (int)reply.length(), 0,
       (sockaddr*)&client, clientSize);

cout << "Reply sent to client." << endl;

closesocket(serverSocket);
WSACleanup();

return 0;

}