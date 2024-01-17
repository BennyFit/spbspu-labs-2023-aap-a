#include "triangle.hpp"
#include <cmath>
#include <algorithm>
#include <stdexcept>

strelyaev::Triangle::Triangle(point_t p1, point_t p2, point_t p3):
  p1_(p1),
  p2_(p2),
  p3_(p3),
  center_({0, 0})
{
  double determinant = p1_.x * (p2_.y - p3_.y) - p2_.x * (p1_.y - p3_.y) + p3_.x * (p1_.y - p2_.y);
  if (determinant == 0)
  {
    throw std::invalid_argument("Invalid points for TRIANGLE");
  }
  double center_x = (p1_.x + p2_.x + p3_.x) / 3;
  double center_y = (p1_.y + p2_.y + p3_.y) / 3;
  center_ = {center_x, center_y};
}

double strelyaev::Triangle::getDistance(const point_t p1, const point_t p2) const
{
  return std::sqrt(std::pow(p2.x - p1.x, 2) + std::pow(p2.y - p1.y, 2));
}


double strelyaev::Triangle::getArea() const
{
  double a = Triangle::getDistance(p1_, p2_);
  double b = Triangle::getDistance(p2_, p3_);
  double c = Triangle::getDistance(p3_, p1_);
  double half_per = (a + b + c) / 2.0;
  return std::sqrt(half_per * (half_per - a) * (half_per - b) * (half_per - c));
}

strelyaev::rectangle_t strelyaev::Triangle::getFrameRect() const
{
  double up = std::max(p1_.y, std::max(p2_.y, p3_.y));
  double down = std::min(p1_.y, std::min(p2_.y, p3_.y));
  double right = std::max(p1_.x, std::max(p2_.x, p3_.x));
  double left = std::min(p1_.x, std::min(p2_.x, p3_.x));
  point_t r_p1 = {left, down};
  point_t r_p2 = {left, up};
  point_t r_p3 = {right, up};
  point_t r_p4 = {right, down};
  double height = up - down;
  double width = right - left;
  double r_center_x = (r_p1.x + r_p2.x + r_p3.x + r_p4.x) / 4;
  double r_center_y = (r_p1.y + r_p2.y + r_p3.y + r_p4.y) / 4;
  point_t r_center = {r_center_x, r_center_y};
  rectangle_t rect = {width, height, r_center};
  return rect;

}

void strelyaev::Triangle::move(const point_t point)
{
  double dx = point.x - center_.x;
  double dy = point.y - center_.y;
  p1_.x += dx;
  p2_.x += dx;
  p3_.x += dx;
  p1_.y += dy;
  p2_.y += dy;
  p3_.y += dy;
  center_.x = point.x;
  center_.y = point.y;
}



void strelyaev::Triangle::move(double dx, double dy)
{
  p1_.x += dx;
  p2_.x += dx;
  p3_.x += dx;
  p1_.y += dy;
  p2_.y += dy;
  p3_.y += dy;
  center_.x += dx;
  center_.y += dy;
}

void strelyaev::Triangle::scale(double k)
{
  p1_.x = center_.x + (p1_.x - center_.x) * k;
  p1_.y = center_.y + (p1_.y - center_.y) * k;
  p2_.x = center_.x + (p2_.x - center_.x) * k;
  p2_.y = center_.y + (p2_.y - center_.y) * k;
  p3_.x = center_.x + (p3_.x - center_.x) * k;
  p3_.y = center_.y + (p3_.y - center_.y) * k;
}

