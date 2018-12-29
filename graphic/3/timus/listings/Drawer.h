#pragma once

#include "render.h"
#include "transformers.h"


class Drawer {
public:
    explicit Drawer(int width, int height) : renderer(width, height) {};

    virtual void draw(const Triangle &t) = 0;

    cv::Mat getImage() const {
        return renderer.getImage();
    }

    virtual void resetImage() {
        renderer.resetImage();
    }

protected:
    Renderer renderer;
};


class LineDrawer : public Drawer {
public:
    LineDrawer(int width, int height) : Drawer(width, height), pipeline() {}

    void draw(const Triangle &triangle) override {
        auto &&t = pipeline->apply(triangle);
        renderer.line(t.aCoord(), t.bCoord());
        renderer.line(t.bCoord(), t.cCoord());
        renderer.line(t.cCoord(), t.aCoord());
    }

    void updatePipeline(std::unique_ptr<TransformationPipeline<Triangle, Triangle>> newPipeline) {
        pipeline = std::move(newPipeline);
    }

protected:
    std::unique_ptr<TransformationPipeline<Triangle, Triangle>> pipeline;

};

class CvLineDrawer : public LineDrawer {
    using LineDrawer::LineDrawer;

    void draw(const Triangle &triangle) override {
        auto &&t = pipeline->apply(triangle);
        renderer.cv_line(t.aCoord(), t.bCoord());
        renderer.cv_line(t.bCoord(), t.cCoord());
        renderer.cv_line(t.cCoord(), t.aCoord());
    }
};

class TriangleDrawer : public Drawer {
public:
    TriangleDrawer(int width, int height) : Drawer(width, height), zBuffer(zBufferDefaultValue(height, width)),
                                            pipeline() {}

    void draw(const Triangle &triangle) override {
        auto &&t = pipeline->apply(triangle);
        renderer.triangleBarycentric(t, zBuffer, mipMap);
    }

    cv::Mat1d zBufferDefaultValue(int height, int width) {
        return cv::Mat::ones(height, width, CV_64F) * 100000;
    }

    void resetImage() override {
        renderer.resetImage();
        zBuffer = zBufferDefaultValue(renderer.height, renderer.width);
    }


    void updatePipeline(std::unique_ptr<TransformationPipeline<Triangle, ExtendedTriangle>> newPipeline) {
        pipeline = std::move(newPipeline);
    }

//protected:
    std::unique_ptr<TransformationPipeline<Triangle, ExtendedTriangle>> pipeline;
    cv::Mat1d zBuffer;
    MipMap<8> mipMap;
};
