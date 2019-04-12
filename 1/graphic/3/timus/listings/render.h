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

struct Coord {
    int x, y;

    cv::Point toCV() const {
        return cv::Point(x, y);
    }
};

struct TriangleNormal {
    glm::vec3 a, b, c;
};

struct TriangleTexture {
    glm::vec2 a, b, c;
};


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
    TriangleNormal normal;
    TriangleTexture texture;

};

inline cv::Vec3b getFrom(const cv::Mat3b &image, const glm::vec2 &coords) {
    return image.at<cv::Vec3b>(
            static_cast<int>(coords.y),
            static_cast<int>(coords.x)
    );
}

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


std::ostream &operator<<(std::ostream &res, const glm::vec4 &v) {
    res << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return res;
}

std::ostream &operator<<(std::ostream &res, const glm::vec3 &v) {
    res << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return res;
}


std::ostream &operator<<(std::ostream &res, const glm::vec2 &v) {
    res << "(" << v.x << ", " << v.y << ")";
    return res;
}

template<int level = 8>
struct MipMap {
    static MipMap<level> compute(const cv::Mat &original) {
        MipMap<level> mipmap;
        mipmap.atLevel[0] = original;
        for (auto i = 1; i < level; i++) {
            mipmap.atLevel[i] = imageAverage(mipmap.atLevel[i - 1]);
        }
        return mipmap;
    }

    static cv::Mat imageAverage(const cv::Mat &image) {
        auto height = image.size().height, width = image.size().width;
        cv::Mat result(height / 2, width / 2, image.type());
        for (auto x = 0; x < width; x += 2) {
            for (auto y = 0; y < height; y += 2) {
                cv::Mat block = image(cv::Rect(x, y, 2, 2));
                cv::Scalar averaged = cv::mean(block);
                result.at<cv::Vec3b>(y / 2, x / 2) = cv::Vec3b(
                        static_cast<uchar>(averaged[0]),
                        static_cast<uchar>(averaged[1]),
                        static_cast<uchar>(averaged[2])
                );
            }
        }
        return result;
    }

    cv::Mat3b get(int d) const {
        int realD = std::max(0, std::min(d, level - 1));
        return atLevel[realD];
    }

    glm::vec2 scale(int d, const glm::vec2 &uv) const {
        int realD = std::max(0, std::min(d, level - 1));
        auto &&size = atLevel[realD].size();
        return uv * glm::vec2(size.width, size.height);
    }

private:
    cv::Mat3b atLevel[level];
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

    template<int index>
    inline float interpolateTextureCoordinate(const TriangleTexture &texture, const glm::dvec3 &barycentric) const {
        return static_cast<float>(texture.a[index] * barycentric[0]
                                  + texture.b[index] * barycentric[1]
                                  + texture.c[index] * barycentric[2]);
    }

    glm::vec2
    interpolateTexture(const TriangleTexture &texture, const glm::dvec3 &barycentric) const {
        auto u = interpolateTextureCoordinate<0>(texture, barycentric);
        auto v = interpolateTextureCoordinate<1>(texture, barycentric);
        return glm::vec2(u, v);
    }

    void triangleBarycentric(const ExtendedTriangle &t, cv::Mat1d &zBuffer, const MipMap<8> &mipMap) {
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

                    glm::dvec3 barycentricX, barycentricY;
                    get_barycentric(t, glm::vec4(x + 1, y, 1, 1), barycentricX);
                    get_barycentric(t, glm::vec4(x, y + 1, 1, 1), barycentricY);

                    glm::vec2 uv = interpolateTexture(t.texture, barycentric);
                    glm::vec2 uvX = interpolateTexture(t.texture, barycentricX);
                    glm::vec2 uvY = interpolateTexture(t.texture, barycentricY);

                    glm::vec2 dx = uvX - uv;
                    glm::vec2 dy = uvY - uv;

                    float l = std::max(glm::dot(dx, dx), glm::dot(dy, dy));
                    float d = std::max(0.0f, 0.5f * std::log2(l));

                    cv::Vec3b texel = trilinearFilter(uv, d, mipMap);
                    plot(x, y, texel);

                }
            }
        }
    }


    cv::Mat getImage() const {
        return image;
    }

    void resetImage() {
        image = cv::Mat::zeros(height, width, CV_8UC3);
    }

    int width, height;


private:

    cv::Vec3b interpolate(const cv::Mat3b &level, const glm::vec2 &xy, const glm::vec2 &dxy) const {
        return (1 - dxy.x) * (1 - dxy.y) * getFrom(level, xy)
               + dxy.x * (1 - dxy.y) * getFrom(level, xy + glm::vec2(1, 0))
               + (1 - dxy.x) * dxy.y * getFrom(level, xy + glm::vec2(0, 1))
               + (dxy.x * dxy.y) * getFrom(level, xy + glm::vec2(1, 1));

    }

    cv::Vec3b trilinearFilter(const glm::vec2 &uv, float df, const MipMap<8> &mipmap) const {
        int d = static_cast<int>(std::floor(df));
        float dd = df - d;
        glm::vec2 fxy0 = mipmap.scale(d, uv);
        glm::vec2 fxy1 = mipmap.scale(d + 1, uv);

        glm::vec2 xy0 = glm::floor(fxy0);
        glm::vec2 xy1 = glm::floor(fxy1);

        glm::vec2 dxy0 = fxy0 - xy0;
        glm::vec2 dxy1 = fxy1 - xy1;

        cv::Mat3b &&level0 = mipmap.get(d);
        cv::Mat3b &&level1 = mipmap.get(d + 1);

        cv::Vec3b v0 = interpolate(level0, xy0, dxy0);
        cv::Vec3b v1 = interpolate(level1, xy1, dxy1);

        return (1 - dd) * v0 + dd * v1;
    }

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

        barycentric = glm::dvec3(w0, w1, w2);
        barycentric /= barycentric[0] + barycentric[1] + barycentric[2];
        barycentric = glm::abs(barycentric);

        return !(w0 < 0 || w1 < 0 || w2 < 0);
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

    inline void plot(int x, int y, const cv::Vec3b &color) {
        if (!check_coordinates(x, y))
            return;
        image.at<cv::Vec3b>(y, x) = color;

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

