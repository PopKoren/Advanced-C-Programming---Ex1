// Course: Advanced C programming
// exercise 1, question 3
// file name: ex1_q3.c
#define _CRT_SECURE_NO_WARNINGS
// --------------------------- //
// include package section:
#include <stdio.h>
#include <stdlib.h>

// --------------------------- //
//
//	Assigned by:
//		Leon Yurokovski #314972357
//		Koren Abugov #211480157
//
// --------------------------- //

// structs and function declarations section:
typedef struct rectangle {
	int xTopSmall;
	int yTopSmall;
	int xButtomRight;
	int yButtomRight;
}rectangle;

typedef struct recElement {
	rectangle Rect;
	struct recElement* next;
}recElement;

int validateRectangle(rectangle* rec);
rectangle scanRectangle();
recElement* createElement();
recElement* createRectList();
rectangle findSmallest(recElement* head);
void printRectangle(rectangle* rec);
void printList(recElement* head);
void freeList(recElement* head);

// --------------------------- //

int main()
{
	rectangle rec;
	recElement* head = NULL;

	// Start Program:
	printf("Start Program\n");

	// call functions:
	head = createRectList();

	printf("\n\nRectangle list:\n");
	printList(head);

	rec = findSmallest(head);

	printf("\n\nFilling rectangle:\n");
	printRectangle(&rec);

	freeList(head);
	head = NULL;

	printf("\n\n");

	return 0;
}
// --------------------------- //


/// <summary>
/// Function gets an address of a rectangle and check validity.
/// </summary>
/// <param>Address of rectangle</param>
/// <returns>0- if rectangle is not valid, 1-if rectangle is a valid, 2-if rectangle is a point</returns>
int validateRectangle(rectangle* rec)
{
	if (rec->xButtomRight >= INT_MAX || rec->xTopSmall >= INT_MAX
		|| rec->yButtomRight >= INT_MAX || rec->yTopSmall >= INT_MAX) {
		return 0;
	}
	if (rec->xButtomRight <= INT_MIN || rec->xTopSmall <= INT_MIN
		|| rec->yButtomRight <= INT_MIN || rec->yTopSmall <= INT_MIN) {
		return 0;
	}
	if (rec->xButtomRight == rec->xTopSmall && rec->yButtomRight == rec->yTopSmall) {
		return 2;
	}
	if (rec->xButtomRight == rec->xTopSmall || rec->yButtomRight == rec->yTopSmall) {
		return 0;
	}
	return 1;
}
// --------------------------- //



/// <summary>
/// Function scan a rectangle in the plane,
/// Used as auxiliary function for createElement.
/// </summary>
/// <param>None</param>
/// <returns>a newly scanned rectangle</returns>
rectangle scanRectangle()
{

	rectangle a;

	printf("Enter top-left x and y coordinates (separated by a space): ");
	scanf("%d %d", &(a.xTopSmall), &(a.yTopSmall));

	printf("Enter bottom-right x and y coordinates (separated by a space): ");
	scanf("%d %d", &(a.xButtomRight), &(a.yButtomRight));

	if (validateRectangle(&a) == 0) {
		printf("Invalid rectangle, please enter new cords:\n");
		return scanRectangle();
	}
	
	return a;

}
// --------------------------- //


/// <summary>
/// Function allocate a new recElement.
/// Calls scanRectangle during the process. 
/// if the scanned rectangle is a point, returns NULL.
/// </summary>
/// <returns>New allocated recElement or NULL if rectangle is a point</returns>
recElement* createElement()
{
	recElement* a = (recElement*)malloc(sizeof(recElement));

	a->Rect = scanRectangle();

	if (validateRectangle(&a->Rect) == 2) {
		free(a);
		return NULL;
	}
	a->next = NULL;
	return a;
	

}
// --------------------------- //


/// <summary>
/// Function creates a list of rectangles.
/// Calls function createElement in a loop.
/// Scan stops when createElement returns null.
/// </summary>
/// <param>None</param>
/// <returns>The Euclidean distance between p1 and p2</returns>
recElement* createRectList()
{
	recElement* head = createElement();
	recElement* temp = head;
	recElement* elem = NULL;

	if (head == NULL) {
		return NULL;
	}

	while (1) {
		elem = createElement();
		if (elem == NULL) {
			break;
		}
		if (head == NULL) {
			head = elem;
		}
		else {
			temp->next = elem;
			temp = temp->next;
			
		}
	}
	return head;
	
}
// --------------------------- //


/// <summary>
/// Function gets a list and returns the filling rectangle
/// </summary>
/// <param>recElement* head - the list of rectangles</param>
/// <returns>The filling rectangle. if the list is empty return rectangle with (0,0,0,0)</returns>
rectangle findSmallest(recElement* head)
{

	recElement* current = head;
	rectangle smallestRect = { 0, 0, 0, 0 };
	int small_x, big_y, big_x, small_y;

	if (head == NULL) {
		return smallestRect;
	}

	small_x = (current->Rect.xTopSmall), big_y = (current->Rect.yTopSmall), big_x = (current->Rect.xButtomRight), small_y = (current->Rect.yButtomRight);

	smallestRect = current->Rect;

	while (current != NULL) {
		if (current->Rect.xTopSmall < small_x) {
			small_x = current->Rect.xTopSmall;
		}

		if (current->Rect.yButtomRight < small_y) {
			small_y = current->Rect.yButtomRight;
		}

		if (current->Rect.yTopSmall > big_y) {
			big_y = current->Rect.yTopSmall;
		}

		if (current->Rect.xButtomRight > big_x) {
			big_x = current->Rect.xButtomRight;
		}

		current = current->next;
	}
	smallestRect.xTopSmall = small_x;
	smallestRect.yTopSmall = big_y;
	smallestRect.xButtomRight = big_x;
	smallestRect.yButtomRight = small_y;

	return smallestRect;
}
// --------------------------- //


/// <summary>
/// Function print rectangle cordinates on screen. (not drawing the rectangle!)
/// </summary>
/// <param>rectangle* rec - pointer to rectangle</param>
/// <returns>None</returns>
void printRectangle(rectangle* rec)
{
	printf("Top left x: %d, y: %d\n", rec->xTopSmall, rec->yTopSmall);
	printf("Buttom right x: %d, y: %d\n", rec->xButtomRight, rec->yButtomRight);
}
// --------------------------- //


/// <summary>
/// Function print list on screen.
/// </summary>
/// <param>recElement* head - list address</param>
/// <returns>None</returns>
void printList(recElement* head)
{
	while (head)
	{
		printRectangle(&head->Rect);
		head = head->next;
	}
}
// --------------------------- //


/// <summary>
/// Function free alocated memory of list 
/// </summary>
/// <param>recElement* head - pointer to head of the list</param>
/// <returns>None</returns>
void freeList(recElement* head)
{
	while (head != NULL) {
        recElement* tmp = head;
        head = head->next;
        free(tmp);
		tmp = NULL;
    }
}
// --------------------------- //