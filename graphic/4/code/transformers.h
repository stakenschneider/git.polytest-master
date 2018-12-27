//
// Created by sobol on 11/16/18.
//
#pragma once

#include <any>
#include <utility>
#include <vector>
#include <memory>

#include <OBJ_Loader.h>

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "render.h"

class VertexTransformer {
public:
    virtual std::any apply(const std::any &vex) = 0;

    template<typename T, typename R>
    std::vector<R> applyList(const std::vector<T> &vertices) {
        std::vector<R> result;
        for (auto &&v: vertices) {
            result.emplace_back(std::any_cast<R>(apply(v)));
        }
        return result;
    }
};

glm::vec3 to_glm(const objl::Vector3 &vec) {
    return glm::vec3{vec.X, vec.Y, vec.Z};
}

glm::vec2 to_glm(const objl::Vector2 &vec) {
    return glm::vec2{vec.X, vec.Y};
}

class ToGLMVertices : public VertexTransformer {


    std::any apply(const std::any &vertex) override {
        return to_glm(std::any_cast<objl::Vertex>(vertex).Position);
    }
};

class ToGLMNormals : public VertexTransformer {


    std::any apply(const std::any &vertex) override {
        return to_glm(std::any_cast<objl::Vertex>(vertex).Normal);
    }
};

class ToGLMTexture : public VertexTransformer {
    std::any apply(const std::any &vertex) override {
        return to_glm(std::any_cast<objl::Vertex>(vertex).TextureCoordinate);
    }
};

template<typename T, typename R>
class TransformationPipeline {
public:
    virtual R apply(const T &triangle) = 0;
};


class GLMLineTransformationPipeline : public TransformationPipeline<Triangle, Triangle> {

public:
    explicit GLMLineTransformationPipeline(const glm::mat4 &cam, const glm::mat4 &proj, int width, int height)
            : camera(cam), projection(proj), viewport(0, 0, width, height), w(width), h(height) {}

    glm::vec3 transformVertex(const glm::vec3 &vertex) {
        auto &&scaled = glm::project(vertex, camera, projection, viewport);
        return scaled;
    }

    Triangle apply(const Triangle &t) override {
        return {transformVertex(t.a), transformVertex(t.b), transformVertex(t.c)};
    }


private:
    glm::mat4 camera, projection;
    glm::vec4 viewport;
    int w, h;
};


class LineTransformationPipeline : public TransformationPipeline<Triangle, Triangle> {
public:
    explicit LineTransformationPipeline(const glm::mat4 &cam, const glm::mat4 &proj, int width, int height)
            : transformation(proj * cam), w(width), h(height), scale(width, height, 1) {}

    glm::vec3 transformVertex(const glm::vec3 &vertex) {
        auto homoCoord = glm::vec4(vertex, 1.0);
        glm::vec4 v = transformation * homoCoord;
        float w = v[3];
        glm::vec3 cartesian = glm::vec3(v[0] / w, v[1] / w, v[2] / w);
        glm::vec3 &&scaled = ((cartesian + 1.0f) / 2.0f) * scale;
        return scaled;
    }

    Triangle apply(const Triangle &t) override {
        return {transformVertex(t.a), transformVertex(t.b), transformVertex(t.c)};
    }

private:

    glm::mat4 transformation;
    glm::vec3 scale;
    int w, h;
};


class TriangleTransformationPipeline : public TransformationPipeline<Triangle, ExtendedTriangle> {
public:
    explicit TriangleTransformationPipeline(const glm::mat4 &cam, const glm::mat4 &proj, int width, int height)
            : transformation(proj * cam), w(width), h(height), scale(width, height, 1) {}

    glm::vec4 transformVertex(const glm::vec3 &v) {

        auto &&homoCoord = glm::vec4(v, 1.0);
        glm::vec4 &&res = transformation * homoCoord;
        float w = res[3];
        glm::vec3 &&cartesian = glm::vec3(res.x / w, res.y / w, res.z / w);
        glm::vec3 &&scaled = ((cartesian + glm::vec3(1.0f, 1.0f, 0.0f)) / glm::vec3(2.0f, 2.0f, 1.0f)) * scale;
        return glm::vec4(scaled, w);
    }

    ExtendedTriangle apply(const Triangle &triangle) override {
        ExtendedTriangle tri{transformVertex(triangle.a), transformVertex(triangle.b), transformVertex(triangle.c)};
        tri.texture = triangle.texture;
        tri.normal = triangle.normal;
        return tri;
    }

private:

    glm::mat4 transformation;
    glm::vec3 scale;
    int w, h;
};
