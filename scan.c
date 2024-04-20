// scan.c
#include "scan.h"

int nombrePort = 0;
int *ports = NULL;
char * ip;
void demandeInfo()
{
    ip = (char *)malloc(20 * sizeof(char));
    int debut;
    int fin;
    printf("Quelle est l'adresse ip à scanner ?\n");
    if (scanf("%s", ip) != 1)
    {
        printf("Format incorrect\n");
        free(ip); // Libérer la mémoire allouée pour ip
        return;
    }
    if (is_valid_ipv4(ip))
    {
        printf("Quel est le premier port à scanner ?\n");
        if (scanf("%d", &debut) != 1)
        {
            printf("Format incorrect\n");
            free(ip); // Libérer la mémoire allouée pour ip
            return;
        }
        printf("Quel est le numéro du dernier port à scanner ?\n");
        if (scanf("%d", &fin) != 1)
        {
            printf("Format incorrect\n");
            free(ip); // Libérer la mémoire allouée pour ip
            return;
        }
        scan_ports(debut, fin);
    }
    else
    {
        printf("Le format de votre adresse ip est incorrect\n");
        return;
    }
}

void vmScan()
{
    printf("-----------------------------\n");
    printf("----------MODE SCAN----------\n");
    printf("-----------------------------\n");
    char *demande = (char *)malloc(20 * sizeof(char));

    while (1)
    {
        printf("[Scan] - ");
        if (scanf("%s", demande) != 1)
        {
            printf("La demande est incorrecte.\n");
        }
        else
        {
            if (strcmp(demande, "scan") == 0)
            {
                printf("Demande de scan\n");
                demandeInfo();
            }
            else if (strcmp(demande, "quit") == 0)
            {
                printf("Fermeture du programme.\n");
                break;
            }
            else if (strcmp(demande, "voirPort") == 0)
            {
                affichePort();
            }
            else if (strcmp(demande, "sendReponse") == 0)
            {
                sendReponse();
            }
            else
            {
                printf("Je n'ai pas compris votre demande.\n");
            }
        }
    }

    free(demande); // Libérer la mémoire allouée pour demande
}

void sendReponse()
{
    int p;
    printf("Quel est le port a scanner  ?\n");
    if (scanf("%d", &p) != 1)
    {
        printf("Format incorrect\n");
        return;
    }
    printf("ici\n");
    if (in_array(p))
    {
            struct sockaddr_in server; // struct qui se compose de l'adresse ip et du port

        printf("La?\n");
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1)
        {
            perror("Erreur lors de la création du socket");
            return ;
        }

        server.sin_addr.s_addr = inet_addr(ip);
        server.sin_family = AF_INET;
        server.sin_port = htons(p);

        if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
        {
            printf("Le port semble fermé\n");
           return;
        }
        
        if (sock == -1)
        {
            perror("Erreur lors de la création du socket");
            return ;
        }
        printf("Laett la?\n");

        char buffer[BUFFER_SIZE];

        if (p == 80 || p == 8080)
        { // Ports HTTP
            printf("Hein?\n");
            strcpy(buffer, "GET / HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n");
            printf("DEUX?\n");
        }
        else if (p == 22)
        {
            strcpy(buffer, "SSH-2.0-OpenSSH_8.2p1");
        }
        else if (p == 23)
        {
            strcpy(buffer, "GET / HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n");
        }
        else
        { // Autres ports
            strcpy(buffer, "Test de connexion");
        }
        printf("Avanc\n");
        if (send(sock, buffer, strlen(buffer), 0) < 0)
        {
            printf("Erreur lors de l'envoi de la requête");
        }
        else
        {
            printf("Requête envoyée sur le port %d\n", p);
        }
        printf("ICIII\n");

        int recv_size = recv(sock, buffer, BUFFER_SIZE, 0);
        if (recv_size < 0)
        {
            printf("Erreur lors de la réception de la réponse");
        }
        else if (recv_size > 0)
        {
            buffer[recv_size] = '\0';
            printf("Réponse reçue sur le port %d :\n%s\n", p, buffer);
        }
    }
    else
    {
        printf("Le format de votre adresse ip est incorrect\n");
        return;
    }
}
int in_array(int p)
{
    for (int i = 0; i < nombrePort; i++)
    {
        if (ports[i] == p)
        {
            return 1;
        }
    }
    return 0;
}
void scan_ports( int start_port, int end_port)
{
    struct sockaddr_in server; // struct qui se compose de l'adresse ip et du port

    for (int port = start_port; port <= end_port; ++port)
    {
        // AF_INET6 Pour ipv6
        // SOCK_STREAM pour indiquer qu'on veut se connecter
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock == -1)
        {
            perror("Erreur lors de la création du socket");
            return ;
        }

        server.sin_addr.s_addr = inet_addr(ip);
        server.sin_family = AF_INET;
        server.sin_port = htons(port);

        if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
        {
            // port fermé
            // printf("Port %d : Fermé\n", port);
        }
        else
        {
            printf("Port %d : Ouvert\n", port);
            ajoutPort(port);
            // if (port == 80 || port == 8080)
            // { // Ports HTTP
            //     strcpy(buffer, "GET / HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n");
            // }
            // else if (port == 22)
            // {
            //     strcpy(buffer, "SSH-2.0-OpenSSH_8.2p1");
            // }
            // else if (port == 23)
            // {
            //     strcpy(buffer, "GET / HTTP/1.1\r\nHost: localhost\r\nConnection: close\r\n\r\n");
            // }
            // else
            // { // Autres ports
            //     strcpy(buffer, "Test de connexion");
            // }

            // if (send(sock, buffer, strlen(buffer), 0) < 0)
            // {
            //     perror("Erreur lors de l'envoi de la requête");
            // }
            // else
            // {
            //     printf("Requête envoyée sur le port %d\n", port);
            // }

            // int recv_size = recv(sock, buffer, BUFFER_SIZE, 0);
            // if (recv_size < 0)
            // {
            //     perror("Erreur lors de la réception de la réponse");
            // }
            // else if (recv_size > 0)
            // {
            //     buffer[recv_size] = '\0';
            //     printf("Réponse reçue sur le port %d :\n%s\n", port, buffer);
            // }
        }

        close(sock);
    }
    printf("Vous pouvez maintenant verifier les ports ouverts.\n");
}

int is_valid_ipv4()
{
    int num, dots = 0;
    char *ptr;

    if (ip == NULL)
    {
        return 0;
    }
    if (strcmp(ip, "127.0.0.1") == 0)
    {
        return 1;
    }
    ptr = strtok((char *)ip, ".");

    while (ptr != NULL)
    {
        num = atoi(ptr);

        if (num < 0 || num > 255)
        {
            return 0;
        }
        if (++dots > 3)
        {
            return 0;
        }

        ptr = strtok(NULL, ".");
    }

    if (dots != 3)
    {
        return 0;
    }

    return 1;
}

void ajoutPort(int port)
{
    if (est_present(ports, port) == 0)
    {
        ajouter_valeur(&ports, &nombrePort, port);
    }
}

void ajouter_valeur(int **tableau, int *nombrePort, int valeur)
{
    int *nouveau_tableau = (int *)malloc((*nombrePort + 1) * sizeof(int));
    if (nouveau_tableau == NULL)
    {
        // En cas d'échec de l'allocation de mémoire
        printf("Erreur d'allocation de mémoire.\n");
        return ;
    }

    for (int i = 0; i < *nombrePort; i++)
    {
        nouveau_tableau[i] = (*tableau)[i];
    }

    // Ajouter la nouvelle valeur à la fin du nouveau tableau
    nouveau_tableau[*nombrePort] = valeur;

    // Libérer la mémoire du tableau existant
    free(*tableau);

    // Mettre à jour le pointeur pour qu'il pointe vers le nouveau tableau
    *tableau = nouveau_tableau;

    // Mettre à jour la taille du tableau
    (*nombrePort)++;
}

int est_present(int tableau[], int valeur)
{
    for (int i = 0; i < nombrePort; i++)
    {
        if (tableau[i] == valeur)
        {
            return 1;
        }
    }
    return 0;
}

void affichePort()
{
    for (int i = 0; i < nombrePort; i++)
    {
        printf("Port : %d\n", ports[i]);
    }
}