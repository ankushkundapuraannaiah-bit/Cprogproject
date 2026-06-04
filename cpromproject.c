#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define ROWS 25
#define COLS 60
#define MAX_OBJECTS 20
char canvas[ROWS][COLS];

void init_canvas() {
	for (int i = 0; i < ROWS; i++)
		for (int j = 0; j < COLS; j++)
			canvas[i][j] = '_';
}

void display_canvas() {
	printf("\n");
	for (int i = 0; i < ROWS; i++) {
		for (int j = 0; j < COLS; j++)
			putchar(canvas[i][j]);
		putchar('\n');
	}
	printf("\n");
}
typedef enum { SHAPE_CIRCLE, SHAPE_RECT, SHAPE_LINE, SHAPE_TRIANGLE } ShapeType;

typedef struct {
	ShapeType type;
	int active;
	int x1, y1, x2, y2, x3, y3, r;
} Object;

Object objects[MAX_OBJECTS];
int obj_count = 0;
static void set_pixel(int row, int col) {
	if (row >= 0 && row < ROWS && col >= 0 && col < COLS)
		canvas[row][col] = '*';
}

static void clear_pixel(int row, int col) {
	if (row >= 0 && row < ROWS && col >= 0 && col < COLS)
		canvas[row][col] = '_';
}
static void draw_line_pixels(int r1, int c1, int r2, int c2, void (*fn)(int,int)) {
	int dr = abs(r2 - r1), dc = abs(c2 - c1);
	int sr = (r1 < r2) ? 1 : -1;
	int sc = (c1 < c2) ? 1 : -1;
	int err = dr - dc;
	while (1) {
		fn(r1, c1);
		if (r1 == r2 && c1 == c2) 
		   break;
		int e2 = 2 * err;
		if (e2 > -dc) {
			err -= dc;
			r1 += sr;
		}
		if (e2 <  dr) {
			err += dr;
			c1 += sc;
		}
	}
}
static void draw_circle_pixels(int cr, int cc, int rad, void (*fn)(int,int)) {
	int x = 0, y = rad;
	int d = 1 - rad;
	while (x <= y) {
		fn(cr + x, cc + y);
		fn(cr - x, cc + y);
		fn(cr + x, cc - y);
		fn(cr - x, cc - y);
		fn(cr + y, cc + x);
		fn(cr - y, cc + x);
		fn(cr + y, cc - x);
		fn(cr - y, cc - x);
		if (d < 0)      d += 2 * x + 3;
		else          {
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
	}
}
static void render_object(Object *o, void (*fn)(int,int)) {
	switch (o->type) {
	case SHAPE_CIRCLE:
		draw_circle_pixels(o->y1, o->x1, o->r, fn);
		break;
	case SHAPE_RECT:
		draw_line_pixels(o->y1, o->x1, o->y1, o->x2, fn); 
		draw_line_pixels(o->y2, o->x1, o->y2, o->x2, fn); 
		draw_line_pixels(o->y1, o->x1, o->y2, o->x1, fn);
		draw_line_pixels(o->y1, o->x2, o->y2, o->x2, fn);
		break;
	case SHAPE_LINE:
		draw_line_pixels(o->y1, o->x1, o->y2, o->x2, fn);
		break;
	case SHAPE_TRIANGLE:
		draw_line_pixels(o->y1, o->x1, o->y2, o->x2, fn);
		draw_line_pixels(o->y2, o->x2, o->y3, o->x3, fn);
		draw_line_pixels(o->y3, o->x3, o->y1, o->x1, fn);
		break;
	}
}
static void redraw_all() {
	init_canvas();
	for (int i = 0; i < obj_count; i++)
		if (objects[i].active)
			render_object(&objects[i], set_pixel);
}
static int read_int(const char *prompt) {
	int v;
	printf("%s", prompt);
	scanf("%d", &v);
	return v;
}

static void flush() {
	while (getchar() != '\n');
}
void add_circle() {
	if (obj_count >= MAX_OBJECTS) {
		puts("Object limit reached.");
		return;
	}
	Object o = {0};
	o.type = SHAPE_CIRCLE;
	o.active = 1;
	o.x1 = read_int("  Centre col  (0-59): ");
	o.y1 = read_int("  Centre row  (0-24): ");
	o.r  = read_int("  Radius            : ");
	objects[obj_count++] = o;
	render_object(&objects[obj_count-1], set_pixel);
	printf("Circle added (id %d).\n", obj_count - 1);
}

void add_rectangle() {
	if (obj_count >= MAX_OBJECTS) {
		puts("Object limit reached.");
		return;
	}
	Object o = {0};
	o.type = SHAPE_RECT;
	o.active = 1;
	o.x1 = read_int("  Top-left  col : ");
	o.y1 = read_int("  Top-left  row : ");
	o.x2 = read_int("  Bot-right col : ");
	o.y2 = read_int("  Bot-right row : ");
	objects[obj_count++] = o;
	render_object(&objects[obj_count-1], set_pixel);
	printf("Rectangle added (id %d).\n", obj_count - 1);
}

void add_line() {
	if (obj_count >= MAX_OBJECTS) {
		puts("Object limit reached.");
		return;
	}
	Object o = {0};
	o.type = SHAPE_LINE;
	o.active = 1;
	o.x1 = read_int("  Start col : ");
	o.y1 = read_int("  Start row : ");
	o.x2 = read_int("  End   col : ");
	o.y2 = read_int("  End   row : ");
	objects[obj_count++] = o;
	render_object(&objects[obj_count-1], set_pixel);
	printf("Line added (id %d).\n", obj_count - 1);
}

void add_triangle() {
	if (obj_count >= MAX_OBJECTS) {
		puts("Object limit reached.");
		return;
	}
	Object o = {0};
	o.type = SHAPE_TRIANGLE;
	o.active = 1;
	o.x1 = read_int("  Vertex 1 col : ");
	o.y1 = read_int("  Vertex 1 row : ");
	o.x2 = read_int("  Vertex 2 col : ");
	o.y2 = read_int("  Vertex 2 row : ");
	o.x3 = read_int("  Vertex 3 col : ");
	o.y3 = read_int("  Vertex 3 row : ");
	objects[obj_count++] = o;
	render_object(&objects[obj_count-1], set_pixel);
	printf("Triangle added (id %d).\n", obj_count - 1);
}
void list_objects() {
	const char *names[] = {"Circle","Rectangle","Line","Triangle"};
	int found = 0;
	printf("\n%-4s %-10s Details\n", "ID", "Shape");
	printf("-------------------------------------\n");
	for (int i = 0; i < obj_count; i++) {
		if (!objects[i].active) continue;
		found = 1;
		Object *o = &objects[i];
		printf("%-4d %-10s ", i, names[o->type]);
		switch (o->type) {
		case SHAPE_CIRCLE:
			printf("centre(%d,%d) r=%d", o->x1,o->y1,o->r);
			break;
		case SHAPE_RECT:
			printf("(%d,%d)-(%d,%d)", o->x1,o->y1,o->x2,o->y2);
			break;
		case SHAPE_LINE:
			printf("(%d,%d)->(%d,%d)", o->x1,o->y1,o->x2,o->y2);
			break;
		case SHAPE_TRIANGLE:
			printf("(%d,%d)(%d,%d)(%d,%d)",
			       o->x1,o->y1,o->x2,o->y2,o->x3,o->y3);
			break;
		}
		putchar('\n');
	}
	if (!found) puts("  No objects.");
}
void delete_object() {
	list_objects();
	if (obj_count == 0) 
	return;
	int id = read_int("Enter object id to delete: ");
	if (id < 0 || id >= obj_count || !objects[id].active) {
		puts("Invalid id.");
		return;
	}
	objects[id].active = 0;
	redraw_all();
	printf("Object %d deleted.\n", id);
}
void modify_object() {
	list_objects();
	if (obj_count == 0) return;
	int id = read_int("Enter object ID to modify: ");
	if (id < 0 || id >= obj_count || !objects[id].active) {
		puts("Invalid ID.");
		return;
	}
	Object *o = &objects[id];
	printf("Re-enter parameters for object %d:\n", id);
	switch (o->type) {
	case SHAPE_CIRCLE:
		o->x1 = read_int("  New centre col : ");
		o->y1 = read_int("  New centre row : ");
		o->r  = read_int("  New radius     : ");
		break;
	case SHAPE_RECT:
		o->x1 = read_int("  New top-left  col : ");
		o->y1 = read_int("  New top-left  row : ");
		o->x2 = read_int("  New bot-right col : ");
		o->y2 = read_int("  New bot-right row : ");
		break;
	case SHAPE_LINE:
		o->x1 = read_int("  New start col : ");
		o->y1 = read_int("  New start row : ");
		o->x2 = read_int("  New end   col : ");
		o->y2 = read_int("  New end   row : ");
		break;
	case SHAPE_TRIANGLE:
		o->x1 = read_int("  V1 col : ");
		o->y1 = read_int("  V1 row : ");
		o->x2 = read_int("  V2 col : ");
		o->y2 = read_int("  V2 row : ");
		o->x3 = read_int("  V3 col : ");
		o->y3 = read_int("  V3 row : ");
		break;
	}
	redraw_all();
	printf("Object %d updated.\n", id);
}
void clear_all() {
	init_canvas();
	obj_count = 0;
	puts("Canvas cleared.");
}
void add_menu() {
	int ch;
	printf("\nAdd shape\n");
	printf("  1. Circle\n  2. Rectangle\n  3. Line\n  4. Triangle\n  0. Back\n");
	printf("Choice: ");
	scanf("%d", &ch);
	flush();
	switch (ch) {
	case 1:
		add_circle();
		break;
	case 2:
		add_rectangle();
		break;
	case 3:
		add_line();
		break;
	case 4:
		add_triangle();
		break;
	default:
		break;
	}
}

void main_menu() {
	int ch;
	do {
		printf("\n2D Graphics editor\n");
		printf("  1. Display canvas\n");
		printf("  2. Add shape\n");
		printf("  3. Delete shape\n");
		printf("  4. Modify shape\n");
		printf("  5. List all objects\n");
		printf("  6. Clear canvas\n");
		printf("  0. Exit\n");
		printf("=========================================\n");
		printf("Choice: ");
		scanf("%d", &ch);
		flush();
		switch (ch) {
		case 1:
			display_canvas();
			break;
		case 2:
			add_menu();
			break;
		case 3:
			delete_object();
			break;
		case 4:
			modify_object();
			break;
		case 5:
			list_objects();
			break;
		case 6:
			clear_all();
			break;
		case 0:
			puts("Goodbye!");
			break;
		default:
			puts("Invalid choice.");
		}
	} while (ch != 0);
}
int main() {
	init_canvas();
	main_menu();
	return 0;
}
