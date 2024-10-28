#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h> // Include Winsock
#include <windows.h>

#pragma comment(lib, "ws2_32.lib") // Link Winsock library

#define SIZE 1024

// Function to receive and write file data from client to a file
void write_file(SOCKET sockfd) {
    int n;
    FILE *fp;
    char *filename = "recv.txt";
    char buffer[SIZE];

    fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("[-]Error in opening file.");
        exit(1);
    }

    while (1) {
        memset(buffer, 0, SIZE); // Using memset instead of bzero
        n = recv(sockfd, buffer, SIZE, 0); // Read from socket
        if (n <= 0) {
            break;
        }
        fprintf(fp, "%s", buffer); // Write to file
    }

    fclose(fp); // Close file
    printf("[+]Data written to the file successfully.\n");
}

int main() {
    WSADATA wsaData;
    SOCKET sockfd, new_sock;
    struct sockaddr_in server_addr, new_addr;
    int addr_size;
    int port;

    // Initializing Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "Failed to initialize Winsock. Error Code : %d", WSAGetLastError());
        exit(1);
    }

    printf("Enter Port Number: ");
    scanf("%d", &port);

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
        fprintf(stderr, "[-]Socket creation error : %d\n", WSAGetLastError());
        WSACleanup();
        exit(1);
    }
    printf("[+]Server socket created successfully.\n");

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Bind socket
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        fprintf(stderr, "[-]Bind failed with error code : %d", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        exit(1);
    }
    printf("[+]Binding successful.\n");

    // Listen for connections
    if (listen(sockfd, 10) == SOCKET_ERROR) {
        fprintf(stderr, "[-]Listen failed with error code : %d", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        exit(1);
    }
    printf("[+]Listening...\n");

    addr_size = sizeof(new_addr);
    new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
    if (new_sock == INVALID_SOCKET) {
        fprintf(stderr, "[-]Accept failed with error code : %d", WSAGetLastError());
        closesocket(sockfd);
        WSACleanup();
        exit(1);
    }

    write_file(new_sock);
    
    closesocket(new_sock);
    closesocket(sockfd);
    WSACleanup();

    return 0;
}
