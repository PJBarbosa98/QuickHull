/***********************************************************************
 *
 * QUICK HULL ALGORITHM SOURCE FILE
 *
 * @author Paulo Barbosa
 * @update 10-12-2020
 *
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

#include "polygon.h"

/***********************************************************************
 *
 * AUXILIARY FUNCTIONS
 *
 ***********************************************************************/

/** Helper function for Quick Hull algorithm. */
void hullSet (struct Point A, struct Point B,
    struct Polygon * set, struct Polygon * hull)
{
    int insertPosition = Polygon_indexOf(hull, B);

    if (Polygon_Size(set) == 0) {
        return ;
    }
    if (Polygon_Size(set) == 1) {
        struct Point p = Polygon_Get(set, 0);
        Polygon_Remove_At(set, Polygon_indexOf(set, p));
        Polygon_Insert_At(hull, p, insertPosition);
        return ;
    }

    int i;
    int dist = INT_MIN;
    int furthestPoint = -1;

    for (i = 0; i < Polygon_Size(set); i++) {
        struct Point p = Polygon_Get(set, i);
        int distance = Point_Distance(A, B, p);
        if (distance > dist) {
            dist = distance;
            furthestPoint = i;
        }
    }

    struct Point P = Polygon_Get(set, furthestPoint);
    Polygon_Remove_At(set, furthestPoint);
    Polygon_Insert_At(hull, P, insertPosition);

    // Determine who is to the left of AP
    struct Polygon leftSetAP;
    Polygon_Create(&leftSetAP);

    for (i = 0; i < Polygon_Size(set); i++) {
        struct Point M = Polygon_Get(set, i);
        if (Point_Location(A, P, M) == 1) {
            Polygon_Add(&leftSetAP, M);
        }
    }

    // Determine who is to the left of PB
    struct Polygon leftSetPB;
    Polygon_Create(&leftSetPB);

    for (i = 0; i < Polygon_Size(set); i++) {
        struct Point M = Polygon_Get(set, i);
        if (Point_Location(P, B, M) == 1) {
            Polygon_Add(&leftSetPB, M);
        }
    }

    hullSet(A, P, &leftSetAP, hull);
    hullSet(P, B, &leftSetPB, hull);
}

/***********************************************************************
 *
 * QUICK HULL ALGORITHM
 *
 ***********************************************************************/

/**
 * Implements the Quick Hull algorithm.
 * Receives Polygon `src` and builds its convex hull into `dest`.
 * For this reason, `dest` must be an empty Polygon structure.
 *
 * @param src 	- Points to build convex hull.
 * @param dest 	- Polygon where convex hull points will be placed.
 * @returns Polygon `dest` with convex hull points of `src`.
 */

// receives polygon src and builds its convex hull into dest
void quickhull (struct Polygon * src, struct Polygon * dest)
{
	if (Polygon_Size(dest) != 0) {
		printf("Error: Quick Hull must be built on empty Polygon object!\n");
		exit(EXIT_ERROR);
	}

	if (Polygon_Size(src) < 3) {
		// If there are less than three points there is nothing to be done.
		// Thus, we will simply copy the contents from `src` to `dest`.
		int i = 0;
		while (i < Polygon_Size(src)) {
			Polygon_Add(dest, Polygon_Get(src, i));
			i++;
		}
	}
	else {
		// Find left and rightmost points of `src`.
		int minPoint = -1, maxPoint = -1;
		int minX = INT_MAX;
		int maxX = INT_MIN;

		int i;
		for (i = 0; i < Polygon_Size(src); i++) {
		    if (Polygon_Get(src, i).x < minX) {
		        minX = Polygon_Get(src, i).x;
		        minPoint = i;
		    }
		    if (Polygon_Get(src, i).x > maxX) {
		        maxX = Polygon_Get(src, i).x;
		        maxPoint = i;
		    }
		}

		// Leftmost point.
		struct Point A = Polygon_Get(src, minPoint);
		// Rightmost point.
		struct Point B = Polygon_Get(src, maxPoint);

		// Add these points to the hull.
		Polygon_Add(dest, A);
		Polygon_Add(dest, B);

		// Delete them from `src` (for efficiency).
		Polygon_Remove_At(src, minPoint);
		Polygon_Remove_At(src, maxPoint);

		// NOTE:
		// Suppose `src` has, initially, n points.
		// Segment AB divides the remaining (n-2) points into 2
		// groups S1 and S2, where S1 are points in S that are
		// on the right side of the oriented line from A to B,
		// and S2 are points in S that are on the right side of
		// the oriented line from B to A.

		// Build S1 and S2.
		struct Polygon leftSet, rightSet;

		Polygon_Create(&leftSet);
		Polygon_Create(&rightSet);

		for (i = 0; i < Polygon_Size(src); i++)
		{
		    struct Point p = Polygon_Get(src, i);

		    if (Point_Location(A, B, p) == -1) {
		        Polygon_Add(&leftSet, p);
		    } else if (Point_Location(A, B, p) == 1) {
		        Polygon_Add(&rightSet, p);
		    }
		}

		// Recursion.
		hullSet(A, B, &rightSet, dest);
		hullSet(B, A, &leftSet, dest);
	}

}

/***********************************************************************
 *
 * QUICK HULL ALGORITHM TEST
 *
 ***********************************************************************/

/**
 * Tests the Quick Hull algorithm with sample input
 * and expected output.
 */
void QuickHull_Test ()
{
	printf("\n\tTEST:\n\n");

	/* Initializing Points */
	struct Point p1, p2, p3, p4;

	p1.x = 12; p1.y = 32;
	p2.x = 45; p2.y = 98;
	p3.x = 65; p3.y = 12;
	p4.x = 10; p4.y = 30;

	/* Creating initial Polygon */
	struct Polygon P;
	Polygon_Create(&P);

	/* Adding Points to Polygon */
	Polygon_Add(&P, p1);
	Polygon_Add(&P, p2);
	Polygon_Add(&P, p3);
	Polygon_Add(&P, p4);

	/* Creating Convex Hull Polygon */
	struct Polygon CH;
	Polygon_Create(&CH);

	/* Running Quickhull */
	quickhull(&P, &CH);

	printf("Expected points:\n(10, 30)\n(45, 98)\n(65, 12)");

	printf("\n\nResults:\n");
	Polygon_Print(&CH);
}

/***********************************************************************
 *
 * MAIN FUNCTION
 *
 ***********************************************************************/


int main (void)
{
	/* Run Quick Hull tests. */
	QuickHull_Test();

	return 0;

}