#include "KMeans.h"
#include "Distance.h"


void run(double(*fun)(std::vector<double> point1, std::vector<double> point2)) {
	auto km = KMeans(fun);

	PointsArray data = { {1, 1}, {2, 1}, {4, 3}, {5, 4} };

	std::vector<int> cluster_assignments = km.fitPredict(data);

	for (int i = 0; i < data.size(); i++) {
		std::cout << "Point " << i + 1 << ": {";

		for (int j = 0; j < data[i].size(); j++) {
			if (j != 0) std::cout << ", ";

			std::cout << data[i][j];
		}

		std::cout << "} is cluster: " << cluster_assignments[i] << std::endl;
	}
	std::cout << std::endl;


	PointsArray centroids = km.getCentroids();

	std::cout << "Centroids:" << std::endl;

	for (Point centroid : centroids) {
		std::cout << "\t{";

		for (int i = 0; i < centroid.size(); i++) {
			if (i != 0) std::cout << ", ";
			std::cout << centroid[i];
		}

		std::cout << "}" << std::endl;
	}
}

int main() {
	std::cout << "Euclidean: " << std::endl;
	run(Distance::Euclidean);

	std::cout << std::endl << "-------------------------------" << std::endl;

	std::cout << "Manhatin: " << std::endl;
	run(Distance::Manhatin);
}