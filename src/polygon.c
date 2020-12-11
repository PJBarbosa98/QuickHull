/***********************************************************************
 *
 * POLYGON SOURCE FILE
 *
 * @author Paulo Barbosa
 * @update 10-12-2020
 *
 ***********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "polygon.h"

// Indicates the distance from Segment AB to a Point C.
int Point_Distance (struct Point a, struct Point b, struct Point c)
{
    int abx = b.x - a.x;
    int aby = b.y - a.y;
    int num = abx * (a.y - c.y) - aby * (a.x - c.x);

    if (num < 0)
        num *= -1;

    return num;
}

// Indicates a Point's - P - orientation versus a segment AB.
int Point_Location (struct Point a, struct Point b, struct Point p)
{
    int cp1 = (b.x - a.x) * (p.y - a.y) - (b.y - a.y) * (p.x - a.x);

    if (cp1 > 0) {
        return 1;
    }
    else {
        if (cp1 == 0) {
            return 0;
        }
        else {
            return -1;
        }
    }
}

// Initialize Polygon structure.
void Polygon_Create (struct Polygon * p) {
	p->capacity 	= INITIAL_CAP;
	p->size 		= 0;
	p->points 	= malloc(sizeof(struct Point) * p->capacity);
}

// Fetch Polygon size.
int Polygon_Size (struct Polygon * p) {
    return (int) p->size;
}

// Indicates the index of a Point `a` in a Polygon `p`.
int Polygon_indexOf (struct Polygon * p, struct Point a) {
    int i;
    for (i = 0; i < Polygon_Size(p); i++) {
        if (Polygon_Get(p, i).x == a.x && Polygon_Get(p, i).y == a.y)
            return i;
    }
    return -1;
}

// Reshape Polygon's size.
void Polygon_Reshape (struct Polygon * p) {
    int new_capacity            = p->capacity * GROWTH_RATE;
    struct Point * new_points   = realloc(p->points,
        sizeof(struct Point) * new_capacity);

    if (new_points) {
        p->capacity = new_capacity;
        p->points   = new_points;
    }
    else {
        printf("Error: Failed to allocate memory for Polygon!\n");
        exit(EXIT_ERROR);
    }
}

// Add Point to Polygon.
void Polygon_Add (struct Polygon * p, struct Point a) {
    if (p->capacity == p->size) {
        Polygon_Reshape(p);
    }

    p->points[p->size] = a;
    p->size++;
}

// Insert Point at a Polygon's specified index.
void Polygon_Insert_At (struct Polygon * p, struct Point a, int idx) {
    if (idx < 0 || idx > p->size) {
        printf("Error: Index out of bounds!\n");
        exit(EXIT_ERROR);
    }

    int i;

    if (p->capacity == p->size) {
        Polygon_Reshape(p);
    }

    p->size++;
    
    for (i = p->size; i >= idx+1; i--) {
        p->points[i] = p->points[i-1];
    }

    p->points[idx] = a;
}

// Remove last element of Polygon.
void Polygon_Pop (struct Polygon * p) {
    if (p->size == 0) {
        printf("Error: Cannot pop element from empty Polygon!\n");
        exit(EXIT_ERROR);
    }

    p->size--;
}

// Remove Point at a Polygon's specified index.
void Polygon_Remove_At (struct Polygon * p, int idx) {
    if (idx < 0 || idx > p->size) {
        printf("Error: Index out of bounds!\n");
        exit(EXIT_ERROR);
    }
    if (p->size == 0) {
        printf("Error: Cannot remove element from empty Polygon!\n");
        exit(EXIT_ERROR);
    }

    int i;

    p->size--;

    for (i = idx; i < p->size; i++) {
        p->points[i] = p->points[i+1];
    }
}

// Fetch a Polygon's Point by index.
struct Point Polygon_Get (struct Polygon *p, int idx) {
    if (idx < 0 || idx > p->size) {
        printf("Error: Index out of bounds!\n");
        exit(EXIT_ERROR);
    }

    return p->points[idx];
}

// Print the Polygon's Points.
void Polygon_Print (struct Polygon * p) {
    int i;

    printf("\t Polygon\n");
    printf("-----------------------------\n");

    for (i = 0; i < p->size; ++i) {
        printf("p_%d\t: (%d, %d)\n", i, p->points[i].x,
            p->points[i].y);
    }
    
    printf("-----------------------------\n");
}