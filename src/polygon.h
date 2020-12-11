/***********************************************************************
 *
 * POLYGON HEADER FILE
 *
 * @author Paulo Barbosa
 * @update 10-12-2020
 *
 ***********************************************************************/

#ifndef POLYGON_H
#define POLYGON_H

/***********************************************************************
 *
 * MACROS
 *
 ***********************************************************************/

/* Initial capacity for Polygon structure */
#define INITIAL_CAP     16
/* Growth rate of Polygon */
#define GROWTH_RATE     2

/* Exit error code */
#define EXIT_ERROR      -1

/***********************************************************************
 *
 * STRUCTURES
 *
 ***********************************************************************/

/**
 * Structure for 2D Point.
 *
 * @param x - x-axis coordinate value
 * @param y - y-axis coordinate value
 */
struct Point
{
    int x;
    int y;
};

/**
 * Structure for Polygon (Vector of 2D Points).
 *
 * @param capacity  - How many points the Polygon can hold.
 * @param size      - How many points the Polygon currently holds.
 * @param points    - Points of the Polygon.
 */
struct Polygon
{
    size_t          capacity;
    size_t          size;
    struct Point *  points;
} Polygon;

/***********************************************************************
 *
 * FUNCTION PROTOTYPES
 *
 ***********************************************************************/

/**
 * Indicates the distance from Segment AB to a Point C.
 *
 * @param a     - Point A.
 * @param b     - Point B.
 * @param c     - Point C.
 */
int
Point_Distance          (struct Point a, struct Point b, struct Point c);


/**
 * Indicates a Point's - P - orientation versus a segment AB.
 *
 * @param a     - Point A.
 * @param b     - Point B.
 * @param p     - Point P.
 * @returns +1 if Point is to the left, -1 if Point is to the
 * the right and 0 if it is collinear.
 */
int
Point_Location          (struct Point a, struct Point b, struct Point p);

/**
 * Initialize Polygon structure.
 *
 * @param p     - Polygon.
 */
void
Polygon_Create          (struct Polygon * p);

/**
 * Fetch Polygon size.
 *
 * @param p     - Polygon.
 * @returns Size of Polygon as an int.
 */
int
Polygon_Size            (struct Polygon * p);

/**
 * Indicates the index of a Point `a` in a Polygon `p`.
 *
 * @param p     - Polygon.
 * @param a     - Point.
 * @returns Index of `a` in `p`. -1 if not found.
 */
int
Polygon_indexOf         (struct Polygon * p, struct Point a);

/**
 * Reshape Polygon's size.
 *
 * @param p     - Polygon.
 */
void
Polygon_Reshape         (struct Polygon * p);


/**
 * Add Point to Polygon.
 *
 * @param p     - Polygon.
 * @param a     - Point element to add.
 */
void
Polygon_Add             (struct Polygon * p, struct Point a);


/**
 * Insert Point at a Polygon's specified index.
 *
 * @param p     - Polygon.
 * @param a     - Point element to add.
 * @param idx   - Insertion index.
 */
void
Polygon_Insert_At       (struct Polygon * p, struct Point a, int idx);


/**
 * Remove last element of Polygon.
 *
 * @param p     - Polygon.
 */
void
Polygon_Pop             (struct Polygon * p);

/**
 * Remove Point at a Polygon's specified index.
 *
 * @param p     - Polygon.
 * @param idx   - Removal index.
 */
void
Polygon_Remove_At       (struct Polygon * p, int idx);

/**
 * Fetch a Polygon's Point by index.
 *
 * @param p     - Polygon.
 * @param idx   - Desired Point's index.
 */
struct Point Polygon_Get(struct Polygon * p, int idx);

/**
 * Print the Polygon's Points.
 *
 * @param p     - Polygon.
 */
void
Polygon_Print           (struct Polygon * p);

#endif /* POLYGON_H */