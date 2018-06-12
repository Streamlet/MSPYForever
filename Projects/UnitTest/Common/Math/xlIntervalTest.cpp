//------------------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlIntervalTest.cpp
//    Author:      Streamlet
//    Create Time: 2012-06-01
//    Description: 
//
//------------------------------------------------------------------------------


#include "../../../../Include/xl/Common/Math/xlInterval.h"
#include "../../../../Include/xl/AppHelper/xlUnitTest.h"

namespace
{
    using namespace xl;

    XL_TEST_CASE()
    {
        Interval<int> a;
        XL_TEST_ASSERT(a.left == 0);
        XL_TEST_ASSERT(a.right == 0);
        XL_TEST_ASSERT(!a.bIncludeLeft);
        XL_TEST_ASSERT(!a.bIncludeRight);

        Interval<int> b(1, 2, true, false);
        XL_TEST_ASSERT(b.left == 1);
        XL_TEST_ASSERT(b.right == 2);
        XL_TEST_ASSERT(b.bIncludeLeft);
        XL_TEST_ASSERT(!b.bIncludeRight);

        Interval<int> c(2, 1, false, true);
        XL_TEST_ASSERT(c.left == 2);
        XL_TEST_ASSERT(c.right == 1);
        XL_TEST_ASSERT(!c.bIncludeLeft);
        XL_TEST_ASSERT(c.bIncludeRight);

        Interval<int> d(c);
        XL_TEST_ASSERT(d == c);
        XL_TEST_ASSERT(!(d != c));
        d = b;
        XL_TEST_ASSERT(d != c);
        XL_TEST_ASSERT(!(d == c));
    }

    XL_TEST_CASE()
    {
        XL_TEST_ASSERT(Interval<int>(0, 0, false, false).IsEmpty());
        XL_TEST_ASSERT(Interval<int>(0, 0, false, true).IsEmpty());
        XL_TEST_ASSERT(Interval<int>(0, 0, true, false).IsEmpty());
        XL_TEST_ASSERT(!Interval<int>(0, 0, true, true).IsEmpty());

        XL_TEST_ASSERT(!Interval<int>(1, 2, false, false).IsEmpty());
        XL_TEST_ASSERT(!Interval<int>(1, 2, false, true).IsEmpty());
        XL_TEST_ASSERT(!Interval<int>(1, 2, true, false).IsEmpty());
        XL_TEST_ASSERT(!Interval<int>(1, 2, true, true).IsEmpty());

        XL_TEST_ASSERT(Interval<int>(2, 1, false, false).IsEmpty());
        XL_TEST_ASSERT(Interval<int>(2, 1, false, true).IsEmpty());
        XL_TEST_ASSERT(Interval<int>(2, 1, true, false).IsEmpty());
        XL_TEST_ASSERT(Interval<int>(2, 1, true, true).IsEmpty());
    }

    XL_TEST_CASE()
    {
        Interval<int> empty;
        XL_TEST_ASSERT(!empty.Contains(0));
        XL_TEST_ASSERT(!empty.Contains(1));
        XL_TEST_ASSERT(!empty.Contains(2));
        XL_TEST_ASSERT(!empty.Contains(3));
        XL_TEST_ASSERT(!empty.Contains(4));

        Interval<int> loro(1, 3, false, false);
        XL_TEST_ASSERT(!loro.Contains(0));
        XL_TEST_ASSERT(!loro.Contains(1));
        XL_TEST_ASSERT(loro.Contains(2));
        XL_TEST_ASSERT(!loro.Contains(3));
        XL_TEST_ASSERT(!loro.Contains(4));

        Interval<int> lorc(1, 3, false, true);
        XL_TEST_ASSERT(!lorc.Contains(0));
        XL_TEST_ASSERT(!lorc.Contains(1));
        XL_TEST_ASSERT(lorc.Contains(2));
        XL_TEST_ASSERT(lorc.Contains(3));
        XL_TEST_ASSERT(!lorc.Contains(4));

        Interval<int> lcro(1, 3, true, false);
        XL_TEST_ASSERT(!lcro.Contains(0));
        XL_TEST_ASSERT(lcro.Contains(1));
        XL_TEST_ASSERT(lcro.Contains(2));
        XL_TEST_ASSERT(!lcro.Contains(3));
        XL_TEST_ASSERT(!lcro.Contains(4));

        Interval<int> lcrc(1, 3, true, true);
        XL_TEST_ASSERT(!lcrc.Contains(0));
        XL_TEST_ASSERT(lcrc.Contains(1));
        XL_TEST_ASSERT(lcrc.Contains(2));
        XL_TEST_ASSERT(lcrc.Contains(3));
        XL_TEST_ASSERT(!lcrc.Contains(4));
    }

    XL_TEST_CASE()
    {
        Interval<int> empty;
        Interval<int> lcrc(1, 3, true, true);
        Interval<int> lorc(1, 3, false, true);
        Interval<int> lcro(1, 3, true, false);
        Interval<int> loro(1, 3, false, false);

        XL_TEST_ASSERT(empty.Contains(empty));
        XL_TEST_ASSERT(!empty.Contains(lcrc));
        XL_TEST_ASSERT(!empty.Contains(lorc));
        XL_TEST_ASSERT(!empty.Contains(lcro));
        XL_TEST_ASSERT(!empty.Contains(loro));

        XL_TEST_ASSERT(loro.Contains(empty));
        XL_TEST_ASSERT(lorc.Contains(empty));
        XL_TEST_ASSERT(lcro.Contains(empty));
        XL_TEST_ASSERT(lcrc.Contains(empty));

        XL_TEST_ASSERT(lcrc.Contains(lcrc));
        XL_TEST_ASSERT(lcrc.Contains(lcro));
        XL_TEST_ASSERT(lcrc.Contains(lorc));
        XL_TEST_ASSERT(lcrc.Contains(loro));

        XL_TEST_ASSERT(!lcro.Contains(lcrc));
        XL_TEST_ASSERT(lcro.Contains(lcro));
        XL_TEST_ASSERT(!lcro.Contains(lorc));
        XL_TEST_ASSERT(lcro.Contains(loro));

        XL_TEST_ASSERT(!lorc.Contains(lcrc));
        XL_TEST_ASSERT(!lorc.Contains(lcro));
        XL_TEST_ASSERT(lorc.Contains(lorc));
        XL_TEST_ASSERT(lorc.Contains(loro));

        XL_TEST_ASSERT(!loro.Contains(lcrc));
        XL_TEST_ASSERT(!loro.Contains(lcro));
        XL_TEST_ASSERT(!loro.Contains(lorc));
        XL_TEST_ASSERT(loro.Contains(loro));

        XL_TEST_ASSERT(empty.ContainedBy(empty));
        XL_TEST_ASSERT(!lcrc.ContainedBy(empty));
        XL_TEST_ASSERT(!lorc.ContainedBy(empty));
        XL_TEST_ASSERT(!lcro.ContainedBy(empty));
        XL_TEST_ASSERT(!loro.ContainedBy(empty));

        XL_TEST_ASSERT(empty.ContainedBy(loro));
        XL_TEST_ASSERT(empty.ContainedBy(lorc));
        XL_TEST_ASSERT(empty.ContainedBy(lcro));
        XL_TEST_ASSERT(empty.ContainedBy(lcrc));

        XL_TEST_ASSERT(lcrc.ContainedBy(lcrc));
        XL_TEST_ASSERT(lcro.ContainedBy(lcrc));
        XL_TEST_ASSERT(lorc.ContainedBy(lcrc));
        XL_TEST_ASSERT(loro.ContainedBy(lcrc));

        XL_TEST_ASSERT(!lcrc.ContainedBy(lcro));
        XL_TEST_ASSERT(lcro.ContainedBy(lcro));
        XL_TEST_ASSERT(!lorc.ContainedBy(lcro));
        XL_TEST_ASSERT(loro.ContainedBy(lcro));

        XL_TEST_ASSERT(!lcrc.ContainedBy(lorc));
        XL_TEST_ASSERT(!lcro.ContainedBy(lorc));
        XL_TEST_ASSERT(lorc.ContainedBy(lorc));
        XL_TEST_ASSERT(loro.ContainedBy(lorc));

        XL_TEST_ASSERT(!lcrc.ContainedBy(loro));
        XL_TEST_ASSERT(!lcro.ContainedBy(loro));
        XL_TEST_ASSERT(!lorc.ContainedBy(loro));
        XL_TEST_ASSERT(loro.ContainedBy(loro));
    }

    XL_TEST_CASE()
    {
        Interval<int> empty;
        Interval<int> lcrc(1, 3, true, true);
        Interval<int> lorc(1, 3, false, true);
        Interval<int> lcro(1, 3, true, false);
        Interval<int> loro(1, 3, false, false);

        XL_TEST_ASSERT(empty.Intersection(empty).IsEmpty());
        XL_TEST_ASSERT(empty.Intersection(lcrc).IsEmpty());
        XL_TEST_ASSERT(empty.Intersection(lorc).IsEmpty());
        XL_TEST_ASSERT(empty.Intersection(lcro).IsEmpty());
        XL_TEST_ASSERT(empty.Intersection(loro).IsEmpty());

        XL_TEST_ASSERT(lcrc.Intersection(lcrc) == lcrc);
        XL_TEST_ASSERT(lcrc.Intersection(lorc) == lorc);
        XL_TEST_ASSERT(lcrc.Intersection(lcro) == lcro);
        XL_TEST_ASSERT(lcrc.Intersection(loro) == loro);

        XL_TEST_ASSERT(lorc.Intersection(lcrc) == lorc);
        XL_TEST_ASSERT(lorc.Intersection(lorc) == lorc);
        XL_TEST_ASSERT(lorc.Intersection(lcro) == loro);
        XL_TEST_ASSERT(lorc.Intersection(loro) == loro);

        XL_TEST_ASSERT(lcro.Intersection(lcrc) == lcro);
        XL_TEST_ASSERT(lcro.Intersection(lorc) == loro);
        XL_TEST_ASSERT(lcro.Intersection(lcro) == lcro);
        XL_TEST_ASSERT(lcro.Intersection(loro) == loro);

        XL_TEST_ASSERT(loro.Intersection(lcrc) == loro);
        XL_TEST_ASSERT(loro.Intersection(lorc) == loro);
        XL_TEST_ASSERT(loro.Intersection(lcro) == loro);
        XL_TEST_ASSERT(loro.Intersection(loro) == loro);

        Interval<int> lcrc1(0, 1, true, true);
        Interval<int> lorc1(0, 1, false, true);
        Interval<int> lcro1(0, 1, true, false);
        Interval<int> loro1(0, 1, false, false);

        XL_TEST_ASSERT(!lcrc.Intersection(lcrc1).IsEmpty());
        XL_TEST_ASSERT(!lcrc.Intersection(lorc1).IsEmpty());
        XL_TEST_ASSERT(lcrc.Intersection(lcro1).IsEmpty());
        XL_TEST_ASSERT(lcrc.Intersection(loro1).IsEmpty());

        XL_TEST_ASSERT(lorc.Intersection(lcrc1).IsEmpty());
        XL_TEST_ASSERT(lorc.Intersection(lorc1).IsEmpty());
        XL_TEST_ASSERT(lorc.Intersection(lcro1).IsEmpty());
        XL_TEST_ASSERT(lorc.Intersection(loro1).IsEmpty());

        XL_TEST_ASSERT(!lcro.Intersection(lcrc1).IsEmpty());
        XL_TEST_ASSERT(!lcro.Intersection(lorc1).IsEmpty());
        XL_TEST_ASSERT(lcro.Intersection(lcro1).IsEmpty());
        XL_TEST_ASSERT(lcro.Intersection(loro1).IsEmpty());

        XL_TEST_ASSERT(loro.Intersection(lcrc1).IsEmpty());
        XL_TEST_ASSERT(loro.Intersection(lorc1).IsEmpty());
        XL_TEST_ASSERT(loro.Intersection(lcro1).IsEmpty());
        XL_TEST_ASSERT(loro.Intersection(loro1).IsEmpty());

        Interval<int> lcrc2(3, 4, true, true);
        Interval<int> lorc2(3, 4, false, true);
        Interval<int> lcro2(3, 4, true, false);
        Interval<int> loro2(3, 4, false, false);

        XL_TEST_ASSERT(!lcrc.Intersection(lcrc2).IsEmpty());
        XL_TEST_ASSERT(lcrc.Intersection(lorc2).IsEmpty());
        XL_TEST_ASSERT(!lcrc.Intersection(lcro2).IsEmpty());
        XL_TEST_ASSERT(lcrc.Intersection(loro2).IsEmpty());

        XL_TEST_ASSERT(!lorc.Intersection(lcrc2).IsEmpty());
        XL_TEST_ASSERT(lorc.Intersection(lorc2).IsEmpty());
        XL_TEST_ASSERT(!lorc.Intersection(lcro2).IsEmpty());
        XL_TEST_ASSERT(lorc.Intersection(loro2).IsEmpty());

        XL_TEST_ASSERT(lcro.Intersection(lcrc2).IsEmpty());
        XL_TEST_ASSERT(lcro.Intersection(lorc2).IsEmpty());
        XL_TEST_ASSERT(lcro.Intersection(lcro2).IsEmpty());
        XL_TEST_ASSERT(lcro.Intersection(loro2).IsEmpty());

        XL_TEST_ASSERT(loro.Intersection(lcrc2).IsEmpty());
        XL_TEST_ASSERT(loro.Intersection(lorc2).IsEmpty());
        XL_TEST_ASSERT(loro.Intersection(lcro2).IsEmpty());
        XL_TEST_ASSERT(loro.Intersection(loro2).IsEmpty());
    }

    XL_TEST_CASE()
    {
        Interval<int> empty;
        Interval<int> lcrc(1, 3, true, true);
        Interval<int> lorc(1, 3, false, true);
        Interval<int> lcro(1, 3, true, false);
        Interval<int> loro(1, 3, false, false);

        XL_TEST_ASSERT(empty.Touched(empty));
        XL_TEST_ASSERT(empty.Touched(lcrc));
        XL_TEST_ASSERT(empty.Touched(lorc));
        XL_TEST_ASSERT(empty.Touched(lcro));
        XL_TEST_ASSERT(empty.Touched(loro));

        XL_TEST_ASSERT(lcrc.Touched(lcrc));
        XL_TEST_ASSERT(lcrc.Touched(lorc));
        XL_TEST_ASSERT(lcrc.Touched(lcro));
        XL_TEST_ASSERT(lcrc.Touched(loro));

        XL_TEST_ASSERT(lorc.Touched(lcrc));
        XL_TEST_ASSERT(lorc.Touched(lorc));
        XL_TEST_ASSERT(lorc.Touched(lcro));
        XL_TEST_ASSERT(lorc.Touched(loro));

        XL_TEST_ASSERT(lcro.Touched(lcrc));
        XL_TEST_ASSERT(lcro.Touched(lorc));
        XL_TEST_ASSERT(lcro.Touched(lcro));
        XL_TEST_ASSERT(lcro.Touched(loro));

        XL_TEST_ASSERT(loro.Touched(lcrc));
        XL_TEST_ASSERT(loro.Touched(lorc));
        XL_TEST_ASSERT(loro.Touched(lcro));
        XL_TEST_ASSERT(loro.Touched(loro));

        Interval<int> lcrc1(0, 1, true, true);
        Interval<int> lorc1(0, 1, false, true);
        Interval<int> lcro1(0, 1, true, false);
        Interval<int> loro1(0, 1, false, false);

        XL_TEST_ASSERT(lcrc.Touched(lcrc1));
        XL_TEST_ASSERT(lcrc.Touched(lorc1));
        XL_TEST_ASSERT(lcrc.Touched(lcro1));
        XL_TEST_ASSERT(lcrc.Touched(loro1));

        XL_TEST_ASSERT(lorc.Touched(lcrc1));
        XL_TEST_ASSERT(lorc.Touched(lorc1));
        XL_TEST_ASSERT(!lorc.Touched(lcro1));
        XL_TEST_ASSERT(!lorc.Touched(loro1));

        XL_TEST_ASSERT(lcro.Touched(lcrc1));
        XL_TEST_ASSERT(lcro.Touched(lorc1));
        XL_TEST_ASSERT(lcro.Touched(lcro1));
        XL_TEST_ASSERT(lcro.Touched(loro1));

        XL_TEST_ASSERT(loro.Touched(lcrc1));
        XL_TEST_ASSERT(loro.Touched(lorc1));
        XL_TEST_ASSERT(!loro.Touched(lcro1));
        XL_TEST_ASSERT(!loro.Touched(loro1));

        Interval<int> lcrc2(3, 4, true, true);
        Interval<int> lorc2(3, 4, false, true);
        Interval<int> lcro2(3, 4, true, false);
        Interval<int> loro2(3, 4, false, false);

        XL_TEST_ASSERT(lcrc.Touched(lcrc2));
        XL_TEST_ASSERT(lcrc.Touched(lorc2));
        XL_TEST_ASSERT(lcrc.Touched(lcro2));
        XL_TEST_ASSERT(lcrc.Touched(loro2));

        XL_TEST_ASSERT(lorc.Touched(lcrc2));
        XL_TEST_ASSERT(lorc.Touched(lorc2));
        XL_TEST_ASSERT(lorc.Touched(lcro2));
        XL_TEST_ASSERT(lorc.Touched(loro2));

        XL_TEST_ASSERT(lcro.Touched(lcrc2));
        XL_TEST_ASSERT(!lcro.Touched(lorc2));
        XL_TEST_ASSERT(lcro.Touched(lcro2));
        XL_TEST_ASSERT(!lcro.Touched(loro2));

        XL_TEST_ASSERT(loro.Touched(lcrc2));
        XL_TEST_ASSERT(!loro.Touched(lorc2));
        XL_TEST_ASSERT(loro.Touched(lcro2));
        XL_TEST_ASSERT(!loro.Touched(loro2));
    }

    XL_TEST_CASE()
    {
        Interval<int> empty;
        Interval<int> lcrc(1, 3, true, true);
        Interval<int> lorc(1, 3, false, true);
        Interval<int> lcro(1, 3, true, false);
        Interval<int> loro(1, 3, false, false);

        XL_TEST_ASSERT(empty.UnionTouched(empty).IsEmpty());
        XL_TEST_ASSERT(empty.UnionTouched(lcrc) == lcrc);
        XL_TEST_ASSERT(empty.UnionTouched(lorc) == lorc);
        XL_TEST_ASSERT(empty.UnionTouched(lcro) == lcro);
        XL_TEST_ASSERT(empty.UnionTouched(loro) == loro);

        XL_TEST_ASSERT(lcrc.UnionTouched(lcrc) == lcrc);
        XL_TEST_ASSERT(lcrc.UnionTouched(lorc) == lcrc);
        XL_TEST_ASSERT(lcrc.UnionTouched(lcro) == lcrc);
        XL_TEST_ASSERT(lcrc.UnionTouched(loro) == lcrc);

        XL_TEST_ASSERT(lorc.UnionTouched(lcrc) == lcrc);
        XL_TEST_ASSERT(lorc.UnionTouched(lorc) == lorc);
        XL_TEST_ASSERT(lorc.UnionTouched(lcro) == lcrc);
        XL_TEST_ASSERT(lorc.UnionTouched(loro) == lorc);

        XL_TEST_ASSERT(lcro.UnionTouched(lcrc) == lcrc);
        XL_TEST_ASSERT(lcro.UnionTouched(lorc) == lcrc);
        XL_TEST_ASSERT(lcro.UnionTouched(lcro) == lcro);
        XL_TEST_ASSERT(lcro.UnionTouched(loro) == lcro);

        XL_TEST_ASSERT(loro.UnionTouched(lcrc) == lcrc);
        XL_TEST_ASSERT(loro.UnionTouched(lorc) == lorc);
        XL_TEST_ASSERT(loro.UnionTouched(lcro) == lcro);
        XL_TEST_ASSERT(loro.UnionTouched(loro) == loro);

        Interval<int> lcrc1(0, 1, true, true);
        Interval<int> lorc1(0, 1, false, true);
        Interval<int> lcro1(0, 1, true, false);
        Interval<int> loro1(0, 1, false, false);
        Interval<int> lcrc11(0, 3, true, true);
        Interval<int> lorc11(0, 3, false, true);
        Interval<int> lcro11(0, 3, true, false);
        Interval<int> loro11(0, 3, false, false);

        XL_TEST_ASSERT(lcrc.UnionTouched(lcrc1) == lcrc11);
        XL_TEST_ASSERT(lcrc.UnionTouched(lorc1) == lorc11);
        XL_TEST_ASSERT(lcrc.UnionTouched(lcro1) == lcrc11);
        XL_TEST_ASSERT(lcrc.UnionTouched(loro1) == lorc11);

        XL_TEST_ASSERT(lorc.UnionTouched(lcrc1) == lcrc11);
        XL_TEST_ASSERT(lorc.UnionTouched(lorc1) == lorc11);
        XL_TEST_ASSERT(lorc.UnionTouched(lcro1) ==lorc);
        XL_TEST_ASSERT(lorc.UnionTouched(loro1) ==lorc);

        XL_TEST_ASSERT(lcro.UnionTouched(lcrc1) == lcro11);
        XL_TEST_ASSERT(lcro.UnionTouched(lorc1) == loro11);
        XL_TEST_ASSERT(lcro.UnionTouched(lcro1) == lcro11);
        XL_TEST_ASSERT(lcro.UnionTouched(loro1) == loro11);

        XL_TEST_ASSERT(loro.UnionTouched(lcrc1) == lcro11);
        XL_TEST_ASSERT(loro.UnionTouched(lorc1) == loro11);
        XL_TEST_ASSERT(loro.UnionTouched(lcro1) == loro);
        XL_TEST_ASSERT(loro.UnionTouched(loro1) == loro);

        Interval<int> lcrc2(3, 4, true, true);
        Interval<int> lorc2(3, 4, false, true);
        Interval<int> lcro2(3, 4, true, false);
        Interval<int> loro2(3, 4, false, false);
        Interval<int> lcrc22(1, 4, true, true);
        Interval<int> lorc22(1, 4, false, true);
        Interval<int> lcro22(1, 4, true, false);
        Interval<int> loro22(1, 4, false, false);

        XL_TEST_ASSERT(lcrc.UnionTouched(lcrc2) == lcrc22);
        XL_TEST_ASSERT(lcrc.UnionTouched(lorc2) == lcrc22);
        XL_TEST_ASSERT(lcrc.UnionTouched(lcro2) == lcro22);
        XL_TEST_ASSERT(lcrc.UnionTouched(loro2) == lcro22);

        XL_TEST_ASSERT(lorc.UnionTouched(lcrc2) == lorc22);
        XL_TEST_ASSERT(lorc.UnionTouched(lorc2) == lorc22);
        XL_TEST_ASSERT(lorc.UnionTouched(lcro2) == loro22);
        XL_TEST_ASSERT(lorc.UnionTouched(loro2) == loro22);

        XL_TEST_ASSERT(lcro.UnionTouched(lcrc2) == lcrc22);
        XL_TEST_ASSERT(lcro.UnionTouched(lorc2) == lcro);
        XL_TEST_ASSERT(lcro.UnionTouched(lcro2) == lcro22);
        XL_TEST_ASSERT(lcro.UnionTouched(loro2) == lcro);

        XL_TEST_ASSERT(loro.UnionTouched(lcrc2) == lorc22);
        XL_TEST_ASSERT(loro.UnionTouched(lorc2) == loro);
        XL_TEST_ASSERT(loro.UnionTouched(lcro2) == loro22);
        XL_TEST_ASSERT(loro.UnionTouched(loro2) == loro);
    }

    XL_TEST_CASE()
    {
        Interval<int> a(1, 2, false, false);
        Interval<int> b(3, 4, true, true);
        XL_TEST_ASSERT(a.UnionTouched(b) == a);

        Set<Interval<int>> c = a.Union(b);

        XL_TEST_ASSERT(c.Size() == 2);
        XL_TEST_ASSERT(*c.Begin() == a);
        XL_TEST_ASSERT(*c.ReverseBegin() == b);
    }

    XL_TEST_CASE()
    {
        Interval<int> a(1, 2, false, false);
        Interval<int> b(3, 4, true, true);

        Set<Interval<int>> c = b.Exclude(a);
        XL_TEST_ASSERT(c.Size() == 1);
        XL_TEST_ASSERT(*c.Begin() == b);

        Interval<int> d(0, 4, true, true);
        Set<Interval<int>> e = d.Exclude(a);
        XL_TEST_ASSERT(e.Size() == 2);
        XL_TEST_ASSERT(*e.Begin() == Interval<int>(0, 1, true, true));
        XL_TEST_ASSERT(*e.ReverseBegin() == Interval<int>(2, 4, true, true));

        Interval<int> f(1, 2, true, true);
        Set<Interval<int>> g = f.Exclude(a);
        XL_TEST_ASSERT(g.Size() == 2);
        XL_TEST_ASSERT(*g.Begin() == Interval<int>(1, 1, true, true));
        XL_TEST_ASSERT(*g.ReverseBegin() == Interval<int>(2, 2, true, true));
    }
}
