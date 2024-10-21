# K_means 
Here's a detailed **README.md** for your K-means clustering project in both C and Python:

---

# K-means Clustering Algorithm

This project implements the **K-means clustering algorithm** in both **C** and **Python**. The K-means algorithm is a popular method for partitioning a dataset into K clusters, where each point belongs to the cluster with the nearest mean.

## Features

### K-means Algorithm
The algorithm clusters a set of **N** datapoints in **d** dimensions into **K** clusters. Each cluster is represented by its **centroid**, which is the mean of the cluster’s members. The algorithm runs iteratively, reassigning points to the nearest cluster and recalculating centroids until convergence is reached.

**Algorithm Overview:**
1. Initialize centroids as the first **K** datapoints.
2. Repeat:
   - Assign each datapoint to the nearest centroid.
   - Recalculate the centroids of the clusters.
   - Stop when the centroids change by less than **ε = 0.001**, or after a specified number of iterations.

### Files:
- **kmeans.c**: C implementation of the K-means algorithm.
- **kmeans.py**: Python implementation of the K-means algorithm.
- **HW1_Kmeans_Clustering.pdf**: Assignment details and description of the algorithm.

## Requirements

Both programs take the following command-line arguments:
- `K`: Number of clusters (`1 < K < N`)
- `N`: Number of data points
- `d`: Dimension of the data points
- `iter`: (Optional) Number of iterations (default: 200)
- `input_data`: Path to the input data file (only for Python)

### C Program:
- The input is read from **stdin** (e.g., via a piped file), and the output is printed to **stdout**.
- Compiles with `gcc` using:
  ```bash
  gcc -ansi -Wall -Wextra -Werror -pedantic-errors kmeans.c -o kmeans -lm
  ```
- Usage example:
  ```bash
  ./kmeans 3 7 5 100 < input_data.txt
  ```

### Python Program:
- The input is read from the provided file, and the output is printed to **stdout**.
- Run with:
  ```bash
  python3 kmeans.py 3 7 5 100 input_data.txt
  ```

## How to Run the Programs

### C Implementation:
1. Compile the code using `gcc`:
   ```bash
   gcc -ansi -Wall -Wextra -Werror -pedantic-errors kmeans.c -o kmeans -lm
   ```
2. Run the program with the specified arguments:
   ```bash
   ./kmeans <K> <N> <d> <iter> < input_data.txt
   ```

### Python Implementation:
1. Run the Python script:
   ```bash
   python3 kmeans.py <K> <N> <d> <iter> input_data.txt
   ```

## Input Format
The input is expected to be a text file where each line represents a datapoint, with **d** values separated by commas. For example:
```
1.0,2.0,3.0
4.0,5.0,6.0
7.0,8.0,9.0
```

## Output Format
The final centroids of the clusters are printed to **stdout**, formatted to 4 decimal places:
```
1.1234,2.5678,3.9012
4.2345,5.6789,6.1234
```

## Error Handling
- If the input values are invalid, an error message is printed and the program terminates. For example:
  - "Invalid number of clusters!"
  - "Invalid number of points!"
  - "Invalid dimension of points!"

## Assumptions
- All input data points are unique.
- The number of clusters **K** is smaller than the number of points **N**.
- Both programs terminate if the Euclidean distance between old and new centroids is smaller than **ε = 0.001**, or if the maximum number of iterations is reached.

## Submission
To submit the assignment, package the `kmeans.c` and `kmeans.py` files into a `.zip` archive as follows:
```bash
zip -r id1_id2_assignment1.zip id1_id2_assignment1
```

## Example
For **K = 3**, **N = 7**, **d = 5**, and **iter = 100**, the output might look like:
```
-5.6720,7.7200,-9.1478,-9.1870,2.1394
-5.3645,8.0872,5.4206,9.6482,-6.5119
-6.8116,-2.9751,3.7578,-0.8476,-10.5475
```

