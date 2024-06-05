#pragma once
#ifndef BREZENHAM_CIRCLE_LIB_73
#define BREZENHAM_CIRCLE_LIB_73

#include <iostream>
#include <cmath>
#include <opencv2/opencv.hpp>
#include <vector>

class BrezenhamCircle {
public:
    BrezenhamCircle() = default;
    BrezenhamCircle(const BrezenhamCircle& arr) = default;
    BrezenhamCircle& operator=(const BrezenhamCircle& rhs) = default;
    ~BrezenhamCircle() = default;
    BrezenhamCircle(BrezenhamCircle&& other) noexcept = default;
    BrezenhamCircle& operator=(BrezenhamCircle&& other) = default;

    /**
   @brief Конструктор с параметрами.

   @param center Центр окружности.
   @param radius Радиус окружности.
   @param color Цвет окружности в модели BGR.
   */
    BrezenhamCircle(cv::Point center, int radius, cv::Scalar color);

    /**
  @brief Растеризирует заданную двумя углами дугу окружности.

  @param img Ссылка на изображение, на котором дуга будет отрисовываться.
  @param startDegrees Угол в градусах, задающий начало дуги.
  @param endDegrees Угол в градусах, задающий конец дуги.
  @param showDemo Булевая переменная: True - показывать демонстрацию построения окружности, False - показывать только построенную дугу.

  @return Вектор закрашенных пикселей, принадлежащих дуге.
  */
    std::vector<cv::Point> GetArc(cv::Mat& img, double startDegrees, double endDegrees, bool showDemo);

    /**
    @brief Демонстрирует построение полной окружности.
    */
    void Demo();


private:
    cv::Point center = cv::Point(250, 250);
    int radius = 100;
    cv::Scalar color = cv::Scalar(255, 0, 0);

private:
    /**
    @brief Переводит угол, заданный в градусах, в радианы

    @param degrees Угол в градусах

    @return Значение угла в радианах
    */
    double toRadian(const double& degrees);
};

#endif
