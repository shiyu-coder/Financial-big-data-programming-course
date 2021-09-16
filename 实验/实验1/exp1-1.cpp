#include<iostream>
#include<mpi.h>
#include<cmath>
using namespace std;

int main(int argc, char** argv){
    int id, source, N, numprocs;
    double sqrtSum = 0.0, res = 0.0;
    MPI_Status status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &id);
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    --numprocs;
    if(id == 0){
        cout <<"Input N: ";
        cin >>N;
    }
    MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    if(id != 0){
        for(int i=id-1; i<N; i+=numprocs){
            sqrtSum += sqrt(i*(i+1));
        }
    }
    MPI_Reduce(&sqrtSum, &res, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if(id == 0){
        cout <<"I am process "<<id<<". The final value is "<<res<<endl;
    }else{
        cout <<"I am process "<<id<<". My SqrtSum is "<<sqrtSum<<endl;
    }
    
    MPI_Finalize();
}