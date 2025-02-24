/**
 *  Copyright 2020 Mike Reed
 */

#include "../include/GPath.h"

class PathBench2 : public GBenchmark {
    const GISize    fSize;
    const float     fScale;
    const char*     fName;

    std::shared_ptr<GPath> fPath;
    GPaint          fPaint;

public:
    PathBench2(GISize size, float scale, const char* name) : fSize(size), fScale(scale), fName(name) {
        GRandom rand;
        auto rand_pt = [&]() {
            float x = rand.nextF() * fScale;
            float y = rand.nextF() * fScale;
            return GPoint{x, y};
        };

        GPathBuilder bu;
        bu.moveTo(0, 0);
        for (int i = 0; i < 100; ++i) {
            auto p0 = rand_pt();
            bu.lineTo(p0);
            auto p1 = rand_pt();
            auto p2 = rand_pt();
            bu.quadTo(p1, p2);
            auto p3 = rand_pt();
            auto p4 = rand_pt();
            auto p5 = rand_pt();
            bu.cubicTo(p3, p4, p5);
        }
        fPath = bu.detach();
    }

    const char* name() const override { return fName; }
    GISize size() const override { return fSize; }
    void draw(GCanvas* canvas) override {
        const int N = 10;
        canvas->clear({0,0,0,0});
        for (int i = 0; i < N; ++i) {
            canvas->drawPath(*fPath, fPaint);
        }
    }
};
