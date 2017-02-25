#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <X11/X.h>
#include <stdbool.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>


static int _XlibErrorHandler(Display *display, XErrorEvent *event) {
    fprintf(stderr, "An error occured detecting the mouse position\n");
    return True;
}

int derecha() {
    int number_of_screens;
    int i;
    Bool result;
    Window *root_windows;
    Window window_returned;
    int root_x, root_y;
    int win_x, win_y;
    unsigned int mask_return;

    Display *display = XOpenDisplay(NULL);
    assert(display);
    XSetErrorHandler(_XlibErrorHandler);
    number_of_screens = XScreenCount(display);
    root_windows = malloc(sizeof(Window) * number_of_screens);
    for (i = 0; i < number_of_screens; i++) {
        root_windows[i] = XRootWindow(display, i);
    }
    for (i = 0; i < number_of_screens; i++) {
        result = XQueryPointer(display, root_windows[i], &window_returned,
                &window_returned, &root_x, &root_y, &win_x, &win_y,
                &mask_return);
        if (result == True) {
            break;
        }
    }
    if (result != True) {
        fprintf(stderr, "No mouse found.\n");
        return -1;
    }

    free(root_windows);
    XCloseDisplay(display);
    return root_y;
}


int izquierda() {
    int number_of_screens;
    int i;
    Bool result;
    Window *root_windows;
    Window window_returned;
    int root_x, root_y;
    int win_x, win_y;
    unsigned int mask_return;

    Display *display = XOpenDisplay(NULL);
    assert(display);
    XSetErrorHandler(_XlibErrorHandler);
    number_of_screens = XScreenCount(display);
    root_windows = malloc(sizeof(Window) * number_of_screens);
    for (i = 0; i < number_of_screens; i++) {
        root_windows[i] = XRootWindow(display, i);
    }
    for (i = 0; i < number_of_screens; i++) {
        result = XQueryPointer(display, root_windows[i], &window_returned,
                &window_returned, &root_x, &root_y, &win_x, &win_y,
                &mask_return);
        if (result == True) {
            break;
        }
    }
    if (result != True) {
        fprintf(stderr, "No mouse found.\n");
        return -1;
    }

    free(root_windows);
    XCloseDisplay(display);
    return root_x;
}


void mover_cursor(int x, int y) {
    Display *dpy;
    Window root_window;

    dpy = XOpenDisplay(0);
    root_window = XRootWindow(dpy, 0);
    XSelectInput(dpy, root_window, KeyReleaseMask);

    XWarpPointer(dpy, None, root_window, 0, 0, 0, 0, x, y);

    XFlush(dpy);

}



int main() {
    bool son_feclas = false;
    struct p {
        int x;
        int y;
    };
    struct p p;

    char primer_caracter, sig, esc;
    while (1) {
        p.y = 0;
        p.x = 0;
        p.y = derecha();
        p.x = izquierda();
        printf("%i %i\n", p.x, p.y);
        primer_caracter = getchar();
        esc = getchar();
        primer_caracter = primer_caracter  == '\x1b' && esc == '[' ? son_feclas = true : son_feclas;
        sig = getchar();
        if (son_feclas) {
            if (sig == 'C') {
                p.x += 1; // Move Cursor Right
            }
            if (sig == 'D') {
                p.x -= 1;  // Move Cursor Left
            }
            if (sig == 'A') {
                p.y += 1; // Move Cursor Up
            }
            if (sig == 'B') {
                p.y -= 1;  // Move Cursor Down
            }
        }
        mover_cursor(p.x, p.y);
    }
}
