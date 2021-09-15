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
        for(int i=1; i<=numprocs; i++){
            MPI_Send(&N, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        double *data =new double[N];
        for(int i=0; i<N; i++){
            data[i] = i * (i + 1) * 1.0;
        }
        for(int i=0; i<N; i++){
            MPI_Send(&data[i], 1, MPI_DOUBLE, i%numprocs+1, 1, MPI_COMM_WORLD);
        }
        // for(int i=1; i<=numprocs; i++){
        //     double d;
        //     MPI_Recv(&d, 1, MPI_DOUBLE, i, 2, MPI_COMM_WORLD, &status);
        //     sqrtSum += d;
        // }
    }else{
        MPI_Recv(&N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
        for(int i=id-1; i<N; i+=numprocs){
            double d;
            MPI_Recv(&d, 1, MPI_DOUBLE, 0, 1, MPI_COMM_WORLD, &status);
            sqrtSum += sqrt(d);
        }
        // MPI_Send(&sqrtSum, 1, MPI_DOUBLE, 0, 2, MPI_COMM_WORLD);
    }
    MPI_Reduce(&sqrtSum, &res, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    if(id == 0){
        cout <<"I am process "<<id<<". The final value is "<<res<<endl;
    }else{
        cout <<"I am process "<<id<<". My SqrtSum is "<<sqrtSum<<endl;
    }
    
    MPI_Finalize();
}