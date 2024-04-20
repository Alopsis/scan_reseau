// scan.h
#ifndef SCAN_H
#define SCAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

void demandeInfo();
void vmScan();
void ajoutPort(int port);
void scan_ports( int start_port, int end_port);
int is_valid_ipv4();
void sendReponse();
void affichePort();

void ajouter_valeur(int **tableau, int *nombrePort, int valeur) ;
int est_present(int tableau[], int valeur) ;

extern int nombrePort;
extern int *ports;
extern char * ip;

#endif // SCAN_H
