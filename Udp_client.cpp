#include <iostream>
#include <string>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
WSADATA wsa;
SOCKET clientSocket;
sockaddr_in server;
int serverSize = sizeof(server);
char buffer[1024];

WSAStartup(MAKEWORD(2, 2), &wsa);

clientSocket = socket(AF_INET, SOCK_DGRAM, 0);

server.sin_family = AF_INET;
server.sin_addr.s_addr = inet_addr("127.0.0.1");
server.sin_port = htons(8080);

string message;

cout << "Enter message: ";
getline(cin, message);

sendto(clientSocket, message.c_str(),
       (int)message.length(), 0,
       (sockaddr*)&server, sizeof(server));

int bytes = recvfrom(clientSocket, buffer, sizeof(buffer) - 1, 0,
                     (sockaddr*)&server, &serverSize);

if (bytes == SOCKET_ERROR) {
    cout << "Receive failed." << endl;
    closesocket(clientSocket);
    WSACleanup();
    return 1;
}

buffer[bytes] = '\0';

cout << "Reply from server: " << buffer << endl;

closesocket(clientSocket);
WSACleanup();

return 0;

}