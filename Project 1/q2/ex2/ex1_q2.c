// Course: Advanced C programming
// exercise 1, question 2
// file name: ex1_q2.c
#define _CRT_SECURE_NO_WARNINGS
// --------------------------- //
// include package section:
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// --------------------------- //
//
//	Assigned by:
//		Leon Yurokovski #314972357
//		Koren Abugov #211480157
//
// --------------------------- //

// structs and function declarations section:
typedef struct point
{
	int x, y;
}point;

typedef struct polygon
{
	int n;
	point* points;
	double scope;
}polygon;

void scanPoint(point* p);
polygon* createPolygon();
double distance(point* p1, point* p2);
double calculateScope(point* points, int n);
int addPoint(polygon* poly);
int removePoint(polygon* poly, int idx);
void freeMemory(polygon* poly);

// --------------------------- //

int main()
{
	int i, n, idx;
	polygon* poly;

	// Start Program:
	printf("Start Program\n");

	// call functions:
	poly = createPolygon();
	printf("How many points to add: ");
	scanf("%d", &n);

	for (i = 0; i < n; i++)
	{
		printf("Point #%d: \n", i + 1);
		addPoint(poly);
	}

	printf("Enter index value to remove, invalid index to stop: ");
	do
	{
		scanf("%d", &idx);
	} while (removePoint(poly, idx));

	// write output:
	printf("Output: Scope of polygon: %.2lf\n", poly->scope);
	freeMemory(poly);

	return 0;
}
// --------------------------- //


/// <summary>
/// Function scan a point in the plane,
/// Used as auxiliary function for createPolygon.
/// </summary>
/// <param>point* p - pointer to p</param>
/// <returns>None</returns>
void scanPoint(point* p)
{
	printf("Enter X value: ");
	scanf("%d", &(p->x));
	printf("Enter Y value: ");
	scanf("%d", &(p->y));
}
// --------------------------- //


/// <summary>
/// Function allocate an empty polygon.
/// </summary>
/// <returns>New allocated polygon</returns>
polygon* createPolygon()
{
	polygon* a1 = (polygon*)malloc(sizeof(polygon));

	if (!a1) {
		return NULL;
	}

	a1->n = 0;
	a1->points = NULL;
	a1->scope = 0;
	return a1;

}
// --------------------------- //


/// <summary>
/// Function calculates distance between 2 adjacent points  
/// </summary>
/// <param>point* p1 - pointer to the first point</param>
/// <param>point* p2 - pointer to the second point</param>
/// <returns>The Euclidean distance between p1 and p2</returns>
double distance(point* p1, point* p2)
{
	double disX = p1->x - p2->x;
	double disY = p1->y - p2->y;
	return sqrt((disX * disX) + (disY * disY));
}
// --------------------------- //


/// <summary>
/// Function calculates and returns the Scope of a polygon.
/// </summary>
/// <param>point* points - array of points</param>
/// <param>int n - size of the array</param>
/// <returns>The Scope of a polygon</returns>
double calculateScope(point* points, int n)
{
	double scope = 0;
	int i;

	if (n < 3) {
		return 0;
	}
	scope = distance(&points[0], &points[n - 1]);

	for (i = 0; i < n - 1; i++) {
		scope += distance(&points[i], &points[i + 1]);
	}

	return scope;
}
// --------------------------- //


/// <summary>
/// Function add a new point at the end of the polygon,
/// and update the scope falue.
/// </summary>
/// <param>polygon* poly - pointer to polygon</param>
/// <returns>1- success, 0- failure</returns>
int addPoint(polygon* poly)
{
	point* new_points = (point*)realloc(poly->points, sizeof(point) * (poly->n + 1));
	if (!new_points) {
		return 0;
	}
	poly->points = new_points;

	(poly->n)++;
	scanPoint(&(poly->points)[poly->n - 1]);
	poly->scope = calculateScope(poly->points, poly->n);
	return 1;
}
// --------------------------- //


/// <summary>
/// Function remove a point from the polygon,
/// at spesific index.
/// </summary>
/// <param>polygon* poly - pointer to polygon</param>
/// <param>int idx - the index to remove</param>
/// <returns>1- success, 0- failure</returns>
int removePoint(polygon* poly, int idx)
{
	int i;
	if (idx < 0 || idx >= poly->n) {
		return 0;
	}
	for (i = idx; i < poly->n - 1; i++) {
		poly->points[i] = poly->points[i + 1];
	}

	(poly->n)--;

	point* new_points = (point*)realloc(poly->points, sizeof(point) * poly->n);
	if (!new_points) {
		return 0;
	}

	poly->points = new_points;

	poly->scope = calculateScope(poly->points, poly->n);

	return 1;
}
// --------------------------- //


/// <summary>
/// Function free alocated memory. 
/// </summary>
/// <param>polygon* poly - pointer to polygon</param>
/// <returns>None</returns>
void freeMemory(polygon* poly)
{
	if (poly->points) {
		free(poly->points);
		poly->points = NULL;
	}

	free(poly);
	poly = NULL;
}
// --------------------------- //