#pragma once

namespace metrics
{

    struct Point2 {
        int x, y;
    };

    struct Point3 {
        int x, y, z;
    };

    using Metric2 = double (*)(Point2, Point2);

    using Metric3 = double (*)(Point3, Point3);

    using Metric = Metric2;


    double euclidean(Point2, Point2);
    double manhattan(Point2, Point2);

    double euclidean(Point3, Point3);
    double manhattan(Point3, Point3);

}  // namespace metrics
