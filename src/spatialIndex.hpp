#ifndef _BOOSTSPATIALINDEX_SPATIALINDEX
#define _BOOSTSPATIALINDEX_SPATIALINDEX

#include <v8.h>
#include <node.h>
#include <nan.h>
#include <unordered_map>
#include <vector>
#include <string>
#include <boost/geometry.hpp>
#include <boost/geometry/index/rtree.hpp>
#include "shape.hpp"

typedef std::pair<box, std::shared_ptr<Shape>> treeValue;

class SpatialIndex : public Nan::ObjectWrap {
  public:
    static NAN_MODULE_INIT(init);

  private:
    explicit SpatialIndex();
    ~SpatialIndex();

    static NAN_METHOD(addBBox);
    static NAN_METHOD(queryPoint);
    static Nan::Persistent<v8::Function> constructor;
    static NAN_METHOD(New);

    // The spatial index containing MBRs (minimum bounding rectangles)
    boost::geometry::index::rtree< treeValue, boost::geometry::index::rstar<16> > rtree;

    // Map geometry objects with their corresponding string id
    std::unordered_map< std::shared_ptr<std::string>, std::shared_ptr<Shape> > repository;
};

#endif