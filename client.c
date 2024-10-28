#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib") // Link with Winsock library

#define SIZE 1024

//To send file to server
void send_file(FILE *fp, SOCKET sockfd) {
    char data[SIZE] = {0};

    while (fgets(data, SIZE, fp) != NULL) {
        if (send(sockfd, data, sizeof(data), 0) == SOCKET_ERROR) {
            perror("[-]Error in sending file.");
            exit(1);
        }
        memset(data, 0, SIZE); // Using memset instead of bzero
    }
}
void print_file_content(FILE *fp) {
    char line[1024];
    while (fgets(line, sizeof(line), fp) != NULL) {
        printf("%s", line);
    }
}

int main() {
    WSADATA wsaData;
    char *ip = "127.0.0.1";
    int port = 8080;
    int e;

    SOCKET sockfd;
    struct sockaddr_in server_addr;
    FILE *fp;
    char *filename = "send.txt";

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        fprintf(stderr, "Failed to initialize Winsock. Error Code : %d", WSAGetLastError());
        return 1;
    }

    // Create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == INVALID_SOCKET) {
        perror("[-]Error in socket creation");
        WSACleanup();
        return 1;
    }
    printf("[+]Client socket created successfully.\n");

    // Set up server address structure
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip);

    // Connect to the server
    e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
    if (e == SOCKET_ERROR) {
        perror("[-]Error in connection");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }
    printf("[+]Connected to Server.\n");

    // Open file for reading
    fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("[-]Error in reading file.");
        closesocket(sockfd);
        WSACleanup();
        return 1;
    }
    printf("[+] Printing file content:\n");
    print_file_content(fp);
    printf("\n");

    // Send file to server
    send_file(fp, sockfd);
    printf("[+]File data sent successfully.\n");


    // Close file and socket
    fclose(fp);
    printf("[+]Closing the connection.\n");
    closesocket(sockfd);

    WSACleanup(); // Cleanup Winsock
    return 0;
}
