#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "scan.h"



int main(int argc, char *argv[])
{
    printf("--------------------------------\n");
    printf("----------Mode General----------\n");
    printf("--------------------------------\n");
    char *demande = (char *)malloc(20 * sizeof(char));
    while (1)
    {
        printf("-");

        if (scanf("%s", demande) != 1)
        {
            printf("La demande est incorrect...");
            printf("-");
        }
        else
        {
            if (strcmp(demande, "scan") == 0)
            {

                vmScan();
            }else if (strcmp(demande, "quit") == 0){
                printf("Fermeture du programme.\n");
                break;
            }
            else
            {
                printf("Je n'ai pas compris votre demande.\n");
            }
        }

        strcpy(demande, "");
    }

    // fermeture propre du programme
    free(demande);
    // if (start_port < 1 || start_port > 65535 || end_port < 1 || end_port > 65535 || start_port > end_port) {
    //     printf("Ports invalides\n");
    //     return EXIT_FAILURE;
    // }

    // scan_ports(target_ip, start_port, end_port);

    return EXIT_SUCCESS;
}
