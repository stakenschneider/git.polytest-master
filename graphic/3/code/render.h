#pragma once

#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>

#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/mat3x3.hpp>
#include <glm/geometric.hpp>

// структурка для координат
struct Coord {
    int x, y;

    cv::Point toCV() const {
        return cv::Point(x, y);
    }
};

std::ostream &operator<<(std::ostream &res, const glm::vec3 &v) {
    res << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return res;
}

std::ostream &operator<<(std::ostream &res, const glm::vec4 &v) {
    res << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return res;
}

template<typename T>
struct TriangleBase {
    TriangleBase(const T &aa, const T &bb, const T &cc) : a(aa), b(bb), c(cc) {}

    virtual Coord toCoord(const T &v) const = 0;

    Coord aCoord() const {
        return toCoord(a);
    }

    Coord bCoord() const {
        return toCoord(b);
    }

    Coord cCoord() const {
        return toCoord(c);
    }

    virtual glm::vec3 toVec(const T &v) const = 0;

    glm::vec3 aVec() const {
        return toVec(a);
    }

    glm::vec3 bVec() const {
        return toVec(b);
    }

    glm::vec3 cVec() const {
        return toVec(c);
    }


    T a, b, c;
};


struct ExtendedTriangle : public TriangleBase<glm::vec4> {
    using TriangleBase::TriangleBase;

    Coord toCoord(const glm::vec4 &v) const override {
        int x = static_cast<int>(v.x);
        int y = static_cast<int>(v.y);
        return {x, y};
    }

    glm::vec3 toVec(const glm::vec4 &v) const override {
        return glm::vec3(v.x, v.y, v.z);
    }


    std::pair<Coord, Coord> box() const {
        int minX = static_cast<int>(std::floor(std::min({a.x, b.x, c.x})));
        int minY = static_cast<int>(std::floor(std::min({a.y, b.y, c.y})));
        int maxX = static_cast<int>(std::ceil(std::max({a.x, b.x, c.x})));
        int maxY = static_cast<int>(std::ceil(std::max({a.y, b.y, c.y})));
        return std::make_pair(Coord{minX, minY}, Coord{maxX, maxY});
    }

};


struct Triangle : public TriangleBase<glm::vec3> {
    using TriangleBase::TriangleBase;

    Coord toCoord(const glm::vec3 &v) const override {
        int x = static_cast<int>(v.x);
        int y = static_cast<int>(v.y);
        return {x, y};
    }

    glm::vec3 toVec(const glm::vec3 &v) const override {
        return v;
    }
};


class Renderer {
public:
    explicit Renderer(int w, int h) : width(w), height(h), image(cv::Mat::zeros(h, w, CV_8U)) {}

    void line(const Coord &from, const Coord &to) {
        drawline(from.x, from.y, to.x, to.y);
    }

    void cv_line(const Coord &from, const Coord &to) {
        cv::line(image, from.toCV(), to.toCV(), cv::Scalar(255, 0, 0));
    }

    void triangleBarycentric(const ExtendedTriangle &t, cv::Mat1d &zBuffer) {
        auto &&bbox = t.box();
        Coord from = bound(bbox.first);
        Coord to = bound(bbox.second);
        for (auto x = from.x; x <= to.x; ++x) {
            for (auto y = from.y; y <= to.y; ++y) {
                glm::dvec3 barycentric;
                bool pointInTriangle = get_barycentric(t, glm::vec4(x, y, 1, 1), barycentric);
                if (!pointInTriangle) continue;
                glm::dvec3 zInterpolated = glm::dvec3(t.a.z, t.b.z, t.c.z) * barycentric;
                double z = zInterpolated[0] + zInterpolated[1] + zInterpolated[2];
                if (z < zBuffer.at<double>(y, x)) {
                    zBuffer.at<double>(y, x) = z;
                    plot(x, y, barycentric);
                }
            }
        }
    }


    cv::Mat getImage() const {
        return image;
    }

    void resetImage() {
        image = cv::Mat::zeros(height, width, CV_8SC3);
    }

    int width, height;


private:

    inline int bound(int x, int bnd) {
        return std::max(0, std::min(bnd - 1, x));
    }

    inline Coord bound(const Coord &coord) {
        return Coord{bound(coord.x, width), bound(coord.y, height)};
    }

    inline double edgeFunction(const glm::vec4 &a, const glm::vec4 &b, const glm::vec4 &c) {
        return (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x);
    }

    bool get_barycentric(const ExtendedTriangle &t, const glm::vec4 &p, glm::dvec3 &barycentric) {
        auto area = edgeFunction(t.a, t.b, t.c);
        auto w0 = edgeFunction(t.b, t.c, p) / area;
        auto w1 = edgeFunction(t.c, t.a, p) / area;
        auto w2 = edgeFunction(t.a, t.b, p) / area;

        if (w0 < 0 || w1 < 0 || w2 < 0)
            return false;

        barycentric = glm::dvec3(w0, w1, w2);
        barycentric /= barycentric[0] + barycentric[1] + barycentric[2];
        return true;
    }

    inline bool check_coordinates(int x, int y) {
        if (x < 0) return false;
        if (x >= width) return false;
        if (y < 0) return false;
        if (y >= height) return false;
        return true;
    }

    inline void plot(int x, int y, const glm::vec3 &color) {
        if (!check_coordinates(x, y))
            return;

        image.at<cv::Vec3b>(y, x) = cv::Vec3b(
                static_cast<uchar>(color[0] * 255),
                static_cast<uchar>(color[1] * 255),
                static_cast<uchar>(color[2] * 255)
        );
    }

    void line(const Coord &from, const Coord &to, std::vector<Coord> &result) {
        drawline(from.x, from.y, to.x, to.y, [&](int x, int y) mutable {
            if (check_coordinates(x, y))
                result.emplace_back(Coord{x, y});
        });
    }

    void drawline(int x0, int y0, int x1, int y1) {
        drawline(x0, y0, x1, y1, [&](int x, int y) { plot(x, y, glm::vec3(0.5f)); });
    }

    template<typename F>
    inline void drawline(int x0, int y0, int x1, int y1, F plot) {

        int dx = std::abs(x1 - x0);
        int dy = std::abs(y1 - y0);

        int directionX = x0 < x1 ? 1 : -1;
        int directionY = y0 < y1 ? 1 : -1;
//        Переменная error даёт нам дистанцию до идеальной прямой от нашего текущего пикселя (x, y).
//        Каждый раз, как error превышает один пиксель, мы увеличиваем (уменьшаем) y на единицу, и на единицу же уменьшаем ошибку.
        int err = (dx > dy ? dx : -dy) / 2;

        for (;;) {
            plot(x0, y0);
            if (x0 == x1 && y0 == y1) break;
            int e2 = err;
            if (e2 > -dx) {
                err -= dy;
                x0 += directionX;
            }
            if (e2 < dy) {
                err += dx;
                y0 += directionY;
            }
        }
    }

    inline void orderVerticesByY(Coord &v1, Coord &v2, Coord &v3) {
//        транспонируем вектора
        if (v1.y > v2.y) {
            std::swap(v1, v2);
        }
        if (v2.y > v3.y) {
            std::swap(v2, v3);
        }
        if (v1.y > v2.y) {
            std::swap(v1, v2);
        }
    }

    inline int signum(int x) {
        if (x == 0) return 0;
        else if (x > 0) return 1;
        else return -1;
    }

    void fillFlatSideTriangle(const Coord &v1, const Coord &v2, const Coord &v3, std::vector<Coord> &trianglePixels) {

        int dx1 = std::abs(v2.x - v1.x);
        int dy1 = std::abs(v2.y - v1.y);

        int dx2 = std::abs(v3.x - v1.x);
        int dy2 = std::abs(v3.y - v1.y);

        int signx1 = signum(v2.x - v1.x);
        int signx2 = signum(v3.x - v1.x);

        int signy1 = signum(v2.y - v1.y);
        int signy2 = signum(v3.y - v1.y);

        bool edge1Steep = dy1 > dx1;
        bool edge2Steep = dy2 > dx2;

        if (edge1Steep) {
            std::swap(dx1, dy1);
        }
        if (edge2Steep) {
            std::swap(dx2, dy2);
        }

        Coord vTmp1{v1.x, v1.y};
        Coord vTmp2{v1.x, v1.y};

        int e1 = 2 * dy1 - dx1;
        int e2 = 2 * dy2 - dx2;

        for (int i = 0; i <= dx1; i++) {
            line(vTmp1, vTmp2, trianglePixels);

            while (e1 >= 0 && dx1 > 0) {
                if (edge1Steep) {
                    vTmp1.x += signx1;
                } else {
                    vTmp1.y += signy1;
                }
                e1 = e1 - 2 * dx1;
            }

            if (edge1Steep) {
                vTmp1.y += signy1;
            } else {
                vTmp1.x += signx1;
            }

            e1 = e1 + 2 * dy1;

            while (vTmp2.y != vTmp1.y) {
                while (e2 >= 0 && dx2 > 0) {
                    if (edge2Steep) {
                        vTmp2.x += signx2;
                    } else {
                        vTmp2.y += signy2;
                    }
                    e2 = e2 - 2 * dx2;
                }

                if (edge2Steep) {
                    vTmp2.y += signy2;
                } else {
                    vTmp2.x += signx2;
                }

                e2 = e2 + 2 * dy2;
            }

        }
    }


    std::vector<Coord> rasterizeTriangle(Coord v1, Coord v2, Coord v3) {
        std::vector<Coord> trianglePixels;
        orderVerticesByY(v1, v2, v3);
        if (v2.y == v3.y) {
            fillFlatSideTriangle(v1, v2, v3, trianglePixels);
        } else if (v1.y == v2.y) {
            fillFlatSideTriangle(v3, v1, v2, trianglePixels);
        } else {
            float v2mv1 = v2.y - v1.y;
            float v3mv1 = v3.y - v1.y;
            int v4x = static_cast<int>(v1.x + (v2mv1 / v3mv1) * (v3.x - v1.x));
            Coord v4{v4x, v2.y};
            fillFlatSideTriangle(v1, v2, v4, trianglePixels);
            fillFlatSideTriangle(v3, v2, v4, trianglePixels);
        }
        return trianglePixels;
    }


    cv::Mat image;
};

