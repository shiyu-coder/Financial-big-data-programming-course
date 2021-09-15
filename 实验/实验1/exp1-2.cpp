#include<iostream>
#include<mpi.h>
#include<stdlib.h>
using namespace std;

int main(int argc, char **argv){
    int id, numprocs;
    int a = 10, b = 100;
    int N = 100000000;
    double part_sum = 0.0, dx = (double)(b-a)/N, x;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    --numprocs;
    if(id == 0){
        for(int i = 1; i <= numprocs; i++){
            MPI_Recv(&x, 1, MPI_DOUBLE, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            part_sum += x;
        }
    }else{
        for(int i=id-1; i<N; i+=numprocs) {
            x = a + i*dx + dx/2;
            part_sum += x*x*x*dx;
        }
        MPI_Send(&part_sum, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
    }
    if(id == 0){
        cout <<"I am process "<<id<<". The final value is "<<part_sum<<endl;
    }else{
        cout <<"I am process "<<id<<". My partSum is "<<part_sum<<endl;
    }
    
    MPI_Finalize();
}