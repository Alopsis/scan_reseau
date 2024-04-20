#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void scan_ports(const char *target_ip, int start_port, int end_port) {
    struct sockaddr_in server; // struct qui se compose de l'adresse ip et du port 
    char buffer[BUFFER_SIZE];

    for (int port = start_port; port <= end_port; ++port) {
        // AF_INET6 Pour ipv6
        // SOCK_STREAM pour indiquer qu'on veut se connecter 
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1) {
            perror("Erreur lors de la création du socket");
            exit(EXIT_FAILURE);
        }


        server.sin_addr.s_addr = inet_addr(target_ip);
        server.sin_family = AF_INET;
        server.sin_port = htons(port);

        if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
            printf("Port %d : Fermé\n", port);
        } else {
            printf("Port %d : Ouvert\n", port);
            
            // Envoi d'une requête pour identifier le service ou le protocole
            if (port == 80 || port == 8080) { // Ports HTTP
                strcpy(buffer, "GET / HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n");
            } else if (port == 22) { // Port SSH
                strcpy(buffer, "SSH-2.0-OpenSSH_8.2p1");
            } else if (port == 23) { // Port Telnet
                strcpy(buffer, "GET / HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n");
            } else { // Autres ports
                strcpy(buffer, "Test de connexion");
            }

            if (send(sock, buffer, strlen(buffer), 0) < 0) {
                perror("Erreur lors de l'envoi de la requête");
            } else {
                printf("Requête envoyée sur le port %d\n", port);
            }

            int recv_size = recv(sock, buffer, BUFFER_SIZE, 0);
            if (recv_size < 0) {
                perror("Erreur lors de la réception de la réponse");
            } else if (recv_size > 0) {
                buffer[recv_size] = '\0';
                printf("Réponse reçue sur le port %d :\n%s\n", port, buffer);
            }
        }

        close(sock);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <IP cible> <port de début> <port de fin>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *target_ip = argv[1];
    int start_port = atoi(argv[2]);
    int end_port = atoi(argv[3]);
    char * demande; 
    while(1){
        printf("Que voulez vous faire : (\"help\" si besoin)\n");
        printf("-");
        
        while(scanf("%s",demande) != 1){
            printf("La demande est incorrect...");
            printf("-");
        }
    }
    if (start_port < 1 || start_port > 65535 || end_port < 1 || end_port > 65535 || start_port > end_port) {
        printf("Ports invalides\n");
        return EXIT_FAILURE;
    }

    scan_ports(target_ip, start_port, end_port);

    return EXIT_SUCCESS;
}
