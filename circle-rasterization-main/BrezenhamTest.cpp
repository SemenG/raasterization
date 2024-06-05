#include <BrezenhamLib/include/Brezenham/Brezenham.hpp>

#include <iostream>
#include <fstream>
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc.hpp> 
#include <nlohmann/json.hpp>

int main(int argc, char* argv[]) {
	std::ifstream json_read;
	if (argc == 1) {
		json_read.open(R"(..\tests\test1.json)");
	}
	else if (argc > 1) {
		json_read.open(argv[1]);
	}
	if (json_read.is_open()) {
		nlohmann::json data = nlohmann::json::parse(json_read);

		cv::Mat mainImg(500, 500, CV_8UC3, cv::Scalar(0, 0, 0));

		BrezenhamCircle circle(cv::Point(data["center"][0], data["center"][1]), data["radius"], cv::Scalar(data["color"][0], data["color"][1], data["color"][2]));
		circle.GetArc(mainImg, data["start_angle"], data["end_angle"], data["show_demo"]);
	}
	else {
		std::cout << "Cannot open the file." << std::endl;
	}
}