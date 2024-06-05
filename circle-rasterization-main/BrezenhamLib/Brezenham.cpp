#include <Brezenham/Brezenham.hpp>
#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <vector>

BrezenhamCircle::BrezenhamCircle(cv::Point center, int radius, cv::Scalar color) {
    this->center = center;
    this->radius = radius;
    this->color = color;
}

std::vector<cv::Point> BrezenhamCircle::GetArc(cv::Mat& img, double startDegrees, double endDegrees, bool showDemo) {
    std::vector<cv::Point> points;
    std::vector<cv::Point> arc_pixels;
    int x = 0;
    int y = radius;
    int d = 1 - radius;
    points.push_back(cv::Point(x, y));

    while (y > x) {
        if (d < 0) {
            d += 2 * x + 3;
        }
        else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
        points.push_back(cv::Point(x, y));
    }

    double startRadian = toRadian(startDegrees);
    double endRadian = toRadian(endDegrees);

    // Рисуем окружность по симметрии
    for (const auto& point : points) {
        // Второй октант
        if (startRadian <= atan2(point.y, point.x) && atan2(point.y, point.x) <= endRadian) {
            img.at<cv::Vec3b>(center.x + point.x, center.y + point.y)[0] = color[0];
            img.at<cv::Vec3b>(center.x + point.x, center.y + point.y)[1] = color[1];
            img.at<cv::Vec3b>(center.x + point.x, center.y + point.y)[2] = color[2];
            arc_pixels.push_back(cv::Point(center.x + point.x, center.y + point.y));
        }

        //Третий октант
        if (startRadian <= atan2(point.y, -point.x) && atan2(point.y, -point.x) <= endRadian) {
            img.at<cv::Vec3b>(center.x - point.x, center.y + point.y)[0] = color[0];
            img.at<cv::Vec3b>(center.x - point.x, center.y + point.y)[1] = color[1];
            img.at<cv::Vec3b>(center.x - point.x, center.y + point.y)[2] = color[2];
            arc_pixels.push_back(cv::Point(center.x - point.x, center.y + point.y));
        }

        // Четвертый октант
        if (startRadian <= atan2(point.x, -point.y) && atan2(point.x, -point.y) <= endRadian) {
            img.at<cv::Vec3b>(center.x - point.y, center.y + point.x)[0] = color[0];
            img.at<cv::Vec3b>(center.x - point.y, center.y + point.x)[1] = color[1];
            img.at<cv::Vec3b>(center.x - point.y, center.y + point.x)[2] = color[2];
            arc_pixels.push_back(cv::Point(center.x - point.y, center.y + point.x));
        }

        // Пятый октант
        if (startRadian <= (atan2(-point.x, -point.y) + 2 * CV_PI) && (atan2(-point.x, -point.y) + 2 * CV_PI) <= endRadian) {
            img.at<cv::Vec3b>(center.x - point.y, center.y - point.x)[0] = color[0];
            img.at<cv::Vec3b>(center.x - point.y, center.y - point.x)[1] = color[1];
            img.at<cv::Vec3b>(center.x - point.y, center.y - point.x)[2] = color[2];
            arc_pixels.push_back(cv::Point(center.x - point.y, center.y - point.x));
        }

        // Шестой октант
        if (startRadian <= (atan2(-point.y, -point.x) + 2 * CV_PI) && (atan2(-point.y, -point.x) + 2 * CV_PI) <= endRadian) {
            img.at<cv::Vec3b>(center.x - point.x, center.y - point.y)[0] = color[0];
            img.at<cv::Vec3b>(center.x - point.x, center.y - point.y)[1] = color[1];
            img.at<cv::Vec3b>(center.x - point.x, center.y - point.y)[2] = color[2];
            arc_pixels.push_back(cv::Point(center.x - point.x, center.y - point.y));
        }


        // Седьмой октант 
        if (startRadian <= (atan2(-point.y, point.x) + 2 * CV_PI) && (atan2(-point.y, point.x) + 2 * CV_PI) <= endRadian) {
            img.at<cv::Vec3b>(center.x + point.x, center.y - point.y)[0] = color[0];
            img.at<cv::Vec3b>(center.x + point.x, center.y - point.y)[1] = color[1];
            img.at<cv::Vec3b>(center.x + point.x, center.y - point.y)[2] = color[2];
            arc_pixels.push_back(cv::Point(center.x + point.x, center.y - point.y));
        }


        // Восьмой октант
        if (startRadian <= (atan2(-point.x, point.y) + 2 * CV_PI) && (atan2(-point.x, point.y) + 2 * CV_PI) <= endRadian) {
            img.at<cv::Vec3b>(center.x + point.y, center.y - point.x)[0] = color[0];
            img.at<cv::Vec3b>(center.x + point.y, center.y - point.x)[1] = color[1];
            img.at<cv::Vec3b>(center.x + point.y, center.y - point.x)[2] = color[2];
            arc_pixels.push_back(cv::Point(center.x + point.y, center.y - point.x));
        }


        // Первый октант
        if (startRadian <= atan2(point.x, point.y) && atan2(point.x, point.y) <= endRadian) {
            img.at<cv::Vec3b>(center.x + point.y, center.y + point.x)[0] = color[0];
            img.at<cv::Vec3b>(center.x + point.y, center.y + point.x)[1] = color[1];
            img.at<cv::Vec3b>(center.x + point.y, center.y + point.x)[2] = color[2];
            arc_pixels.push_back(cv::Point(center.x + point.y, center.y + point.x));
        }
    }
    cv::Mat copy;
    cv::rotate(img, copy, cv::ROTATE_90_COUNTERCLOCKWISE);
    imshow("Bresenham Circle", copy);
    if (showDemo) {
        Demo();
    }
    cv::waitKey();
    return arc_pixels;
}

void BrezenhamCircle::Demo() {
    cv::Mat img(500, 500, CV_8UC3, cv::Scalar(0, 0, 0));
    cv::Point center(250, 250);
    cv::line(img, cv::Point(0, 250), cv::Point(500, 250), cv::Scalar(50, 50, 50), 1, 1);
    cv::line(img, cv::Point(250, 0), cv::Point(250, 500), cv::Scalar(50, 50, 50), 1, 1);
    cv::line(img, cv::Point(0, 0), cv::Point(500, 500), cv::Scalar(50, 50, 50), 1, 1);
    cv::line(img, cv::Point(0, 500), cv::Point(500, 0), cv::Scalar(50, 50, 50), 1, 1);
    cv::Mat demoImg = img.clone();
    std::vector<cv::Point> points;
    int x = 0;
    int y = radius;
    int d = 1 - radius;
    points.push_back(cv::Point(x, y));

    while (y > x) {
        img.at<cv::Vec3b>(center.x + x, center.y + y)[0] = color[0];
        img.at<cv::Vec3b>(center.x + x, center.y + y)[1] = color[1];
        img.at<cv::Vec3b>(center.x + x, center.y + y)[2] = color[2];

        img.at<cv::Vec3b>(center.x - x, center.y + y)[0] = color[0];
        img.at<cv::Vec3b>(center.x - x, center.y + y)[1] = color[1];
        img.at<cv::Vec3b>(center.x - x, center.y + y)[2] = color[2];

        img.at<cv::Vec3b>(center.x - y, center.y + x)[0] = color[0];
        img.at<cv::Vec3b>(center.x - y, center.y + x)[1] = color[1];
        img.at<cv::Vec3b>(center.x - y, center.y + x)[2] = color[2];

        img.at<cv::Vec3b>(center.x - y, center.y - x)[0] = color[0];
        img.at<cv::Vec3b>(center.x - y, center.y - x)[1] = color[1];
        img.at<cv::Vec3b>(center.x - y, center.y - x)[2] = color[2];

        img.at<cv::Vec3b>(center.x - x, center.y - y)[0] = color[0];
        img.at<cv::Vec3b>(center.x - x, center.y - y)[1] = color[1];
        img.at<cv::Vec3b>(center.x - x, center.y - y)[2] = color[2];

        img.at<cv::Vec3b>(center.x + x, center.y - y)[0] = color[0];
        img.at<cv::Vec3b>(center.x + x, center.y - y)[1] = color[1];
        img.at<cv::Vec3b>(center.x + x, center.y - y)[2] = color[2];

        img.at<cv::Vec3b>(center.x + y, center.y - x)[0] = color[0];
        img.at<cv::Vec3b>(center.x + y, center.y - x)[1] = color[1];
        img.at<cv::Vec3b>(center.x + y, center.y - x)[2] = color[2];

        img.at<cv::Vec3b>(center.x + y, center.y + x)[0] = color[0];
        img.at<cv::Vec3b>(center.x + y, center.y + x)[1] = color[1];
        img.at<cv::Vec3b>(center.x + y, center.y + x)[2] = color[2];

        cv::circle(demoImg, cv::Point(center.x + x, center.y + y), 5, cv::Scalar(0, 255, 0), -1);
        cv::circle(demoImg, cv::Point(center.x - x, center.y + y), 5, cv::Scalar(0, 0, 255), -1);
        cv::circle(demoImg, cv::Point(center.x - y, center.y + x), 5, cv::Scalar(0, 0, 255), -1);
        cv::circle(demoImg, cv::Point(center.x - y, center.y - x), 5, cv::Scalar(0, 0, 255), -1);
        cv::circle(demoImg, cv::Point(center.x - x, center.y - y), 5, cv::Scalar(0, 0, 255), -1);
        cv::circle(demoImg, cv::Point(center.x + x, center.y - y), 5, cv::Scalar(0, 0, 255), -1);
        cv::circle(demoImg, cv::Point(center.x + y, center.y - x), 5, cv::Scalar(0, 0, 255), -1);
        cv::circle(demoImg, cv::Point(center.x + y, center.y + x), 5, cv::Scalar(0, 0, 255), -1);
        cv::flip(demoImg, demoImg, 0);


        if (d < 0) {
            d += 2 * x + 3;
        }
        else {
            d += 2 * (x - y) + 5;
            y--;
        }
        x++;
        points.push_back(cv::Point(x, y));

        cv::imshow("Demo", demoImg);
        cv::waitKey(50);
        demoImg = img.clone();
    }
    cv::imshow("Demo", demoImg);
    cv::waitKey(0);
}

double BrezenhamCircle::toRadian(const double& degrees) {
    return (degrees * CV_PI / 180);
}