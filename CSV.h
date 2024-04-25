#pragma once

#include <vector>
#include <string>
#include <sstream>
#include <fstream>

class CSV
{
public:
	CSV(const std::string path) {
		std::ifstream file(path);
		_path = path;

		if (!file.is_open()) {
			throw std::invalid_argument("Error: Can't open file \"" + path + "\" make sure it's exists.");
		}

		std::string line;

		// get header
		std::getline(file, line);
		_headers = convert<std::string>(line, [](std::string s) {return s;});

		while (std::getline(file, line))
		{
			std::vector<double> row = convert<double>(
				line,
				[](std::string s) { return atof(s.c_str()); }
			);

			_data.push_back(row);
		}
	}

	std::vector<std::string> headers() {
		return _headers;
	}

	std::vector<std::vector<double>> data() {
		return _data;
	}


private:
	std::string							  _path;
	std::vector<std::string>			  _headers;
	std::vector<std::vector<double>> _data;

	

	template<typename T>
	// typedef int T;
	std::vector<T> convert(std::string line, T(*converter)(std::string)) {
		std::stringstream lineStream(line);
		std::string		  cell;
		std::vector<T>    row;

		while (std::getline(lineStream, cell, ','))
			row.push_back(converter(cell));

		return row;
	}
};
