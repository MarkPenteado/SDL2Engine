#ifndef MOUSE_H
#define MOUSE_H

struct mouse {
	int x;
	int y;
};

typedef struct mouse Mouse;

// mouse functions
Mouse* createMouse(void);
void destroyMouse(Mouse** mouse);
void setMouseShow(Mouse* mouse);
void setMouseHide(Mouse* mouse);

// get functions
int getMouseX(Mouse* mouse);
int getMouseY(Mouse* mouse);

// set procedures
void setMouseX(Mouse** mouse, int x);
void setMouseY(Mouse** mouse, int y);

#endif // MOUSE_H