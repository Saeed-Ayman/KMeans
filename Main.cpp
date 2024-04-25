#include "KMeans.h"
#include "Distance.h"
#include "CSV.h"
#include <exception>


void run(DistanceFun fun, PointsArray data) {
	auto km = KMeans(fun, 10);

	std::vector<int> cluster_assignments = km.fitPredict(data);

	for (int i = 0; i < data.size(); i++) {
		std::cout << "Point " << i + 1 << ": " << data[i] << " is cluster : " << cluster_assignments[i] << std::endl;
	}
	std::cout << std::endl;

	PointsArray centroids = km.getCentroids();
	std::vector<int> count = km.getPointsCountAroundCentroids();

	std::cout << "Centroids:" << std::endl;

	for (int i = 0; i < centroids.size(); i++) {
		std::cout << "\t" << centroids[i] << " number of points nearest to it " << count[i] << std::endl;
	}
}

int main() {
	try {
		//auto csv = CSV("Resources/testData.csv");
		//auto csv = CSV("non_exists_route");
		auto csv = CSV("Resources/sample2d.csv");
		
		/*for (const auto& s : csv.headers())
			std::cout << s << "\t";

		std::cout << std::endl;*/

		PointsArray data;

		for (std::vector<double> row : csv.data()) {
			/*for (const auto& element : row) {
				std::cout << element << "\t\t";
			}

			std::cout << std::endl;*/

			data.push_back(row);
		}

		std::cout << std::endl << "-------------------------------" << std::endl;

		std::cout << "Euclidean: " << std::endl;
		run(Distance::Euclidean, data);

		std::cout << std::endl << "-------------------------------" << std::endl;

		std::cout << "Manhatin: " << std::endl;
		run(Distance::Manhatin, data);
	}
	catch (std::exception e) {
		std::cout << e.what();
	}
}