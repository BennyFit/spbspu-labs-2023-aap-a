#include <stdexcept>
#include <cmath>

#include "shape.hpp"
#include "concave.hpp"

belokurskaya::Concave::Concave(const point_t & vertex1, const point_t & vertex2, const point_t & vertex3, const point_t & vertex4):
  vertex1_(vertex1), vertex2_(vertex2), vertex3_(vertex3), vertex4_(vertex4)
{
  if (isTriangle(vertex1_, vertex2_, vertex3_))
  {
    if (!isInsideTriangle(vertex1_, vertex2_, vertex3_, vertex4_))
    {
      throw std::invalid_argument("Fourth vertex must be inside the triangle formed by the first three vertices");
    }
    if (!isConcave(vertex1_, vertex2_, vertex3_, vertex4_))
    {
      throw std::invalid_argument("The vertices do not form a concave quadrilateral");
    }
  }
  else
  {
    throw std::invalid_argument("The first three vertices do not form a triangle");
  }
}

double belokurskaya::Concave::getArea() const
{
  double triangle1_area = calculateTriangleArea(vertex1_, vertex2_, vertex4_);
  double triangle2_area = calculateTriangleArea(vertex2_, vertex3_, vertex4_);
  return triangle1_area + triangle2_area;
}

belokurskaya::rectangle_t belokurskaya::Concave::getFrameRect() const
{
  double min_x = std::min(std::min(std::min(vertex1_.x, vertex2_.x), vertex3_.x), vertex4_.x);
  double min_y = std::min(std::min(std::min(vertex1_.y, vertex2_.y), vertex3_.y), vertex4_.y);
  double max_x = std::max(std::max(std::max(vertex1_.x, vertex2_.x), vertex3_.x), vertex4_.x);
  double max_y = std::max(std::max(std::max(vertex1_.y, vertex2_.y), vertex3_.y), vertex4_.y);
  point_t center = {(min_x + max_x) / 2, (min_y + max_y) / 2};
  return {center, max_x - min_x, max_y - min_y};
}

void belokurskaya::Concave::move(const point_t & new_pos)
{
  double dx = new_pos.x - getFrameRect().pos.x;
  double dy = new_pos.y - getFrameRect().pos.y;
  vertex1_.x += dx;
  vertex1_.y += dy;
  vertex2_.x += dx;
  vertex2_.y += dy;
  vertex3_.x += dx;
  vertex3_.y += dy;
  vertex4_.x += dx;
  vertex4_.y += dy;
}

void belokurskaya::Concave::move(double dx, double dy)
{
  vertex1_.x += dx;
  vertex1_.y += dy;
  vertex2_.x += dx;
  vertex2_.y += dy;
  vertex3_.x += dx;
  vertex3_.y += dy;
  vertex4_.x += dx;
  vertex4_.y += dy;
}

void belokurskaya::Concave::scale(double factor)
{
  point_t center = calculateCentroid();

  vertex1_ = {center.x + factor * (vertex1_.x - center.x), center.y + factor * (vertex1_.y - center.y)};
  vertex2_ = {center.x + factor * (vertex2_.x - center.x), center.y + factor * (vertex2_.y - center.y)};
  vertex3_ = {center.x + factor * (vertex3_.x - center.x), center.y + factor * (vertex3_.y - center.y)};
  vertex4_ = {center.x + factor * (vertex4_.x - center.x), center.y + factor * (vertex4_.y - center.y)};
}

bool belokurskaya::Concave::isTriangle(const point_t& p1, const point_t& p2, const point_t& p3) const
{
  return ((p1.x - p2.x) * (p3.y - p2.y) - (p1.y - p2.y) * (p3.x - p2.x)) != 0;
}

bool belokurskaya::Concave::isInsideTriangle(const point_t& p1, const point_t& p2, const point_t& p3, const point_t& p4) const
{
  return ((p2.y - p3.y) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.y - p3.y)) *
         ((p2.y - p3.y) * (p4.x - p3.x) + (p3.x - p2.x) * (p4.y - p3.y)) >= 0 &&
         ((p3.y - p1.y) * (p2.x - p1.x) + (p1.x - p3.x) * (p2.y - p1.y)) *
         ((p3.y - p1.y) * (p4.x - p1.x) + (p1.x - p3.x) * (p4.y - p1.y)) >= 0 &&
         ((p1.y - p2.y) * (p3.x - p2.x) + (p2.x - p1.x) * (p3.y - p2.y)) *
         ((p1.y - p2.y) * (p4.x - p2.x) + (p2.x - p1.x) * (p4.y - p2.y)) >= 0;
}

bool belokurskaya::Concave::isConcave(const point_t & p1, const point_t & p2, const point_t & p3, const point_t & p4)
{
  double cross_product1 = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
  double cross_product2 = (p3.x - p2.x) * (p4.y - p2.y) - (p3.y - p2.y) * (p4.x - p2.x);
  double cross_product3 = (p4.x - p3.x) * (p1.y - p3.y) - (p4.y - p3.y) * (p1.x - p3.x);
  double cross_product4 = (p1.x - p4.x) * (p2.y - p4.y) - (p1.y - p4.y) * (p2.x - p4.x);

  int sign_changes = 0;
  if ((cross_product1 > 0) != (cross_product2 > 0))
  {
    sign_changes++;
  }
  if ((cross_product2 > 0) != (cross_product3 > 0))
  {
    sign_changes++;
  }
  if ((cross_product3 > 0) != (cross_product4 > 0))
  {
    sign_changes++;
  }
  if ((cross_product4 > 0) != (cross_product1 > 0))
  {
    sign_changes++;
  }
  return sign_changes > 0;
}

double belokurskaya::Concave::calculateTriangleArea(const point_t & p1, const point_t & p2, const point_t & p3) const
{
  return std::abs((p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) / 2.0);
}

void belokurskaya::Concave::getVertices(point_t & vertex1, point_t & vertex2, point_t & vertex3, point_t & vertex4) const
{
  vertex1 = vertex1_;
  vertex2 = vertex2_;
  vertex3 = vertex3_;
  vertex4 = vertex4_;
}

belokurskaya::point_t belokurskaya::Concave::calculateCentroid() const
{
  double cx = (vertex1_.x + vertex2_.x + vertex3_.x + vertex4_.x) / 4.0;
  double cy = (vertex1_.y + vertex2_.y + vertex3_.y + vertex4_.y) / 4.0;
  return {cx, cy};
}

belokurskaya::Shape::ShapeType belokurskaya::Concave::getShapeType()
{
  return belokurskaya::Shape::CONCAVE;
}
