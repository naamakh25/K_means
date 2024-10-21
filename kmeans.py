import math
import sys

EPS = 0.001
def K_means(K, N, d, input_data, Iter=200):
    # checking(K,N,d,Iter)#to_complete #Checking the inputs
    file = open(input_data, "r")
    lines = file.readlines()
    file.close()
    Vectors = []
    for line in lines:  # assigning the vectors from the input.txt to the matrix Vectors. "Assigning the values"
        elements = line.strip().split(",")
        vector = [float(element) for element in elements]
        Vectors.append(vector)
    #print(Vectors)

    Centroids = [[0 for i in range(d)] for j in range(N)]
    Clusters = []
    cl = []
    for i in range(K):
        for j in range(d):
            Centroids[i][j] = Vectors[i][j]# Let the  K centroids to be the first K vectors in vectors
        #Centroids.append(Vectors[i])
    for j in range(N):  # Assigning each Cluster vals to -1
        cl.append(-1)
    #print(cl)
    for c in range(K):  # Let  the vals of the clusters matrix be the indeces of the vectors
        Clusters.append([-1 for i in range(N)])
    #print(Clusters)
    for i in range(N):  # Assigning the vectors into the appropriate cluster
        assign_clusters(Vectors[i], Centroids, Clusters, K, d, N, i)
    # iterating "Iter" times
    t = 0
    #print(Clusters)
    while (t < Iter):
        cnt = update_centroid(Vectors, Centroids, Clusters, K, N, d);
        for i in range(K):
            for j in range(N):
                Clusters[i][j] = -1;

        for i in range(N):
            assign_clusters(Vectors[i], Centroids, Clusters, K, d, N, i);

        t += 1
        if (cnt == K):  # if we've reached the EPS distance between the vectors for every coordinate.
            break
    print_centroids(Centroids, K, d);
    return 0


def checking(K, N, d,
             Iter):  # This function Checks the entered inputs. Prints out an error and exists if the input is invalid
    if K <= 1 or K >= N:
        print("Error: Invalid number of clusters!")
        exit(1)
    if N <= 1:
        print("Error: Invalid number of points!")
        exit(1)
    if d < 0:
        print("Error: Invalid dimensions of points!")
        exit(1)
    if Iter <= 1 or Iter >= 1000:
        print("Error: Invalid number of iteration!")
        exit(1)
    return 0


def calc_new_centroid(Vectors, Centroids, Cluster, K, N, d, Cluster_Index):
    sm = 0.0
    cnt = 0
    for h in range(d):
        for i in range(N):
            if (Cluster[i] == -1):
                break
            sm += Vectors[Cluster[i]][h]
            cnt += 1
        Centroids[Cluster_Index][h] = sm / cnt

        sm = 0.0
        cnt = 0
    return 0


def Euclidean_Distance(Vec1, Vec2, d):
    res = 0
    delta = 0
    for i in range(d):
        delta = (Vec1[i] - Vec2[i]) ** 2
        res += delta
    return math.sqrt(res)


def update_centroid(Vectors, Centroids, Clusters, K, N, D):
    cnt = 0

    for i in range(K):
        Old_Centroid = [x for x in Centroids[i]]


        calc_new_centroid(Vectors, Centroids, Clusters[i], K, N, D, i)
        if Euclidean_Distance(Old_Centroid, Centroids[i], D) < EPS:
            cnt += 1

    return cnt


def assign_clusters(Vector, Centroids, Clusters, K, d, N, Vec_Index):
    min_dis = Euclidean_Distance(Vector, Centroids[0], d)
    #print("the min distance is " + min_dis)
    distance = 0
    min_index = -1


    for i in range(K):
        distance = Euclidean_Distance(Vector, Centroids[i], d)

        if distance == 0.0:
            min_index = i
            break
        if min_dis >= distance:
            min_dis = distance
            min_index = i
    #print("the min index is: ", min_index)
    for i in range(N):
        if Clusters[min_index][i] == -1:
            Clusters[min_index][i] = Vec_Index #####################
            break
    return 0


def print_centroids(Centroids, K, d):
    for i in range(K):
        for j in range(d):
            print("%.4lf" % Centroids[i][j], end='')
            if j < d - 1:
                print(',', end='')

        print()
    return


def print_vectors(Vectors, N, D):
    print("\nThe Vectors are:")
    for i in range(N):
        for j in range(D):
            print("%.4lf\t" % Vectors[i][j], end='')
        print()
    return


def print_clusters(Clusters, N, K):
    print("\nThe Clusters are after *:")
    for i in range(K):
        for j in range(N):
            print("%d\t" % Clusters[i][j], end='')
        print()
    return

def main():
    rgs = sys.argv[1:]

    K = int(rgs[0])
    N = int(rgs[1])
    d = int(rgs[2])
    input_file = ""
    if len(rgs) == 4:
        iter = 200
        input_file = rgs[3]

    else:
        iter = int(rgs[3])
        input_file = rgs[4]
    checking(K,N,d,iter)
    K_means(K,N,d,input_file, iter)


if __name__ == "__main__":
    main()



















