# include <stdio.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
#define EPS 0.001



/*This function Checks the entered inputs. Prints out an error and exists if the input is invalid*/
void Checking(int K, int N, int d, int iter) {
    if (K <= 1 || K >= N) {
        printf("Error: Invalid number of clusters!\n");
        exit(1);
    }
    if (N <= 1) {
        printf("Error: Invalid number of points!\n");
        exit(1);
    }
    if (d < 0) {
        printf("Error: Invalid dimensions of points!\n");
        exit(1);
    }
    if (iter <= 1 || iter >= 1000) {
        printf("Error: Invalid number of iteration!\n");
        exit(1);
    }
}

/*helper function for update centroids*/
void calc_new_centroid(double **Vectors,double **Centroids, int *Cluster,int N,int D, int Cluster_Index){
    int h,i =0;
    double sum = 0.0;
    double cnt = 0;
    for(h=0 ; h<D; h++){
        for(i=0; i<N; i++){
            if (Cluster[i]==-1){
                break;
            }
            sum += Vectors[Cluster[i]][h];
            cnt += 1;
        }
        Centroids[Cluster_Index][h] = sum/cnt;
        sum = 0;
        cnt = 0;
    }
}

/*calculates the Euclidean distance between  two vectors*/
double Euclidean_Distance(double *Vec1, double *Vec2, int D){
    int i =0;
    double res=0;
    double delta=0;
    for(i=0; i<D;i++){
        delta = pow(Vec1[i] - Vec2[i], 2);
        res += delta;
    }
    return sqrt(res);
}

/*updating the centroid*/
int update_Centroid(double **Vectors,double **Centroids, int **Clusters, int K,int N,int D){
    int cnt=0;
    int i = 0;
    for(i=0; i<K; i++){
        double *Old_Centroid = (double *)malloc(D * sizeof(double));
        memcpy(Old_Centroid, Centroids[i], D * sizeof(double));
        calc_new_centroid(Vectors, Centroids,Clusters[i],N,D,i);
        if(Euclidean_Distance(Old_Centroid, Centroids[i], D) < EPS){
            cnt ++;
        }
        free(Old_Centroid);
    }
    return cnt;
}

/*assign vectors to clusters according to the centroid*/
void Assign_Clusters(double *Vector,double **Centroids, int **Clusters ,int K, int D, int N, int Vec_Index){
    int i=0;
    double min = Euclidean_Distance(Vector, Centroids[0], D);
    double distance = 0;
    int min_index=-1;
    for (i=0; i<K; i++){
        distance = Euclidean_Distance(Vector, Centroids[i], D);
        if(distance==0){
            min_index=i;
            break;
        }
        if(min>=distance){
            min = distance;
            min_index=i;
        }
    }
    for (i = 0 ; i<N;i++){
        if (Clusters[min_index][i] == -1){
            Clusters[min_index][i] = Vec_Index;
            break;
        }
    }
}

/*prints the Centroids*/
void printCentroids(double **Centroids, int K ,int D){
    int i, j =0;
    for (i = 0; i < K; i++) {
        for (j = 0; j < D-1; j++) {
            printf("%.4f,", Centroids[i][j]);
        }
        printf("%.4f", Centroids[i][D-1]);

        printf("\n");
    }
}

int main(int argc, char const **argv){
  /*Declaring vars*/
    int iteration;
    int K = atoi(argv[1]);
    int N = atoi(argv[2]);
    int D = atoi(argv[3]);
    char c;
    int cnt=0;
    int iter=0;
    int i, j =0;
    /*Creating the matrices Vectors, Centroids, Clusters*/
    double  **Vectors = (double **)malloc(N * sizeof(double *));
    double **Centroids = (double **)malloc(K * sizeof(double *));
    int **Clusters = (int **)malloc(K * sizeof(int *));

    /*determining whether we have the iteration number, if not take the default val*/
    if (argc == 4){iteration = 200;}
    else{iteration= atoi(argv[4]);}

    /*Checking the inputs*/
    Checking(K,N,D,iteration);

    /*Assigning Clusters vals to -1*/
    for (i = 0; i < K; i++) {
        Clusters[i] = (int *)malloc(N * sizeof(int));
        for (j = 0; j < N; j++) {
            Clusters[i][j] = -1;
        }
    }

    /*Allocating space for each vector in vectors*/
    for (i = 0; i < N; i++) {
        Vectors[i] = (double *)malloc(D * sizeof(double));
    }

    /*assigning the vectors from the input.txt to the matrix Vectors. "Assigning the values"*/
    for (i = 0; i < N; i++) {
        for (j = 0; j < D; j++) {
            scanf("%lf%c", &Vectors[i][j],&c);
        }
    }

    /*Let the  K centroids to be the first K vectors in vectors*/
    for (i = 0; i<K; i++){
        Centroids[i] = (double *)malloc(D * sizeof(double));
        memcpy(Centroids[i], Vectors[i], D * sizeof(double));
    }


    /*Assigning the vectors into the appropriate cluster*/
    for(i =0; i<N; i++){
        Assign_Clusters(Vectors[i], Centroids, Clusters, K, D, N, i);
    }

    /*iterating "iteration" times*/
    while(iter<iteration){
        cnt = update_Centroid(Vectors, Centroids, Clusters, K, N, D);
        for (i = 0; i < K; i++) {
            for (j = 0; j < N; j++) {
                Clusters[i][j] = -1;
            }
        }

        for(i =0;i<N;i++){
            Assign_Clusters(Vectors[i], Centroids, Clusters, K ,D, N, i);
        }
        ++iter;
        if(cnt == K){ /*if we've reached the EPS distance between the vectors for every coordinate.*/
            break;
        }
    }

    printCentroids(Centroids, K, D);
    /*printClusters(Clusters, N, K);*/
    /*printVectors(Vectors, N, D);*/

    /* Free allocated memory*/
    for (i = 0; i < N; i++) {
        free(Vectors[i]);
    }
    for(i = 0; i < K; i++){
        free(Centroids[i]);
        free(Clusters[i]);
    }

    free(Vectors);
    free(Clusters);
    free(Centroids);

    return 0;
}





















