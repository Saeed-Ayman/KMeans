#pragma once
#include <iostream>
#include <vector>

typedef std::vector<double> Point;
typedef std::vector<Point> PointsArray;

class KMeans
{
public:
    KMeans(double(*distance_fun)(Point, Point), int n_clusters = 2, int max_iteration = 100000)
        : n_clusters(n_clusters), distance_fun(distance_fun), max_iteration(max_iteration) {}


    std::vector<int> fitPredict(const PointsArray& points) {
        this->points = points;
        std::vector<int> cluster_assignments(points.size(), -1);

        setRandomCentroids();

        for (int i = 0; i < max_iteration; i++) {
            if (!updateClusters(cluster_assignments)) break;

            updateCentroids(cluster_assignments);
        }

        return cluster_assignments;
    }

    PointsArray getCentroids() {
        return centroids;
    }
private:
    int n_clusters;
    PointsArray centroids;
    double(*distance_fun)(Point, Point);
    int max_iteration;
    PointsArray points;

    void setRandomCentroids() {
        const int size = (int)points.size();

        centroids.clear();

        for (int i = 0; i < n_clusters; ++i) {
            centroids.push_back(points[rand() % size]);
        }
    }

    // Assign data points to clusters
    bool updateClusters(std::vector<int>& assigns) {
        bool centroidsChanged = false;

        // set to every point the new centroid
        for (int i = 0; i < points.size(); ++i) {
            int nearestCentroid = findNearestCentroid(points[i]);

            if (assigns[i] == nearestCentroid)
                continue;

            assigns[i] = nearestCentroid;
            centroidsChanged = true;
        }

        return centroidsChanged;
    }

    int findNearestCentroid(Point point) {
        int nearestIndex = 0;
        double minDistance = distance_fun(point, centroids[0]);

        // search to min distance between point and centroids
        for (int i = 1; i < centroids.size(); ++i) {
            double distance = distance_fun(point, centroids[i]);

            if (distance < minDistance) {
                minDistance = distance;
                nearestIndex = i;
            }
        }
        return nearestIndex;
    }

    void updateCentroids(const std::vector<int>& clusterAssignments) {
        int n_row = (int)points.size();
        int n_col = (int)points[0].size();

        std::vector<int> clusterCounts(n_clusters, 0);
        centroids = PointsArray(n_clusters, Point(n_col, 0.0));

        // get summation has same clusters and count of them
        for (int i = 0; i < n_row; ++i) {
            int clusterIndex = clusterAssignments[i];

            clusterCounts[clusterIndex]++;

            for (int j = 0; j < n_col; ++j) {
                centroids[clusterIndex][j] += points[i][j];
            }
        }

        // get average
        for (int i = 0; i < n_clusters; ++i) {
            if (clusterCounts[i] == 0) continue;

            for (int j = 0; j < n_col; ++j) {
                centroids[i][j] /= clusterCounts[i];
            }
        }

    }
};

