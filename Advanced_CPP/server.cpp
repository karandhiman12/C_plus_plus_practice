#include <iostream>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

#define PORT 8080

void handle_request(int client_socket) {
    char buffer[1024];
    int read_size = read(client_socket, buffer, sizeof(buffer) - 1);
    if (read_size < 0) {
        std::cerr << "Error reading from socket" << std::endl;
        return;
    }

    buffer[read_size] = '\0';  // Null-terminate the string

    std::cout << "Received request:\n" << buffer << std::endl;

    // Simple HTTP Response
    const char *http_response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html\r\n"
        "Connection: close\r\n"
        "\r\n"
        "<html><body><h1>Hello, World!</h1></body></html>\r\n";

    // Send the HTTP Response to the client
    send(client_socket, http_response, strlen(http_response), 0);
}

int main() {
    // Create socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

    std::cout << "Listening on port " << PORT << "..." << std::endl;

    // Accept incoming connections and handle them
    int client_socket;
    struct sockaddr_in client_address;
    socklen_t client_addr_len = sizeof(client_address);
    while ((client_socket = accept(server_fd, (struct sockaddr *)&client_address, &client_addr_len)) >= 0) {
        std::cout << "Connection accepted!" << std::endl;

        handle_request(client_socket);

        close(client_socket);  // Close the client connection
    }

    if (client_socket < 0) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    close(server_fd);  // Close the server socket
    return 0;
}
