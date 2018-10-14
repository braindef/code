#include "mpi.h"
#include <stdio.h>
#include <string.h>				

//ws2_32.lib mpichd.lib müssen dazu gelinkt werden
//ausserdem muss nach dem kompillieren das program aus guiMPIrun gestartet werden

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "mpichd.lib")

int main(int argc, char *argv[])
{
    char message[20];
    int myrank, tag=99;
    MPI_Status status;
 
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &myrank);
 
    if (myrank == 0) {
        strcpy(message, "Hello, there");
        MPI_Send(message, strlen(message)+1, MPI_CHAR, 1, tag, MPI_COMM_WORLD);
    }
    else {
        MPI_Recv(message, 20, MPI_CHAR, 0, tag, MPI_COMM_WORLD, &status);
        printf("received \"%s\"\n", message);
    }
 
    MPI_Finalize();
	
	

    return 0;
}
