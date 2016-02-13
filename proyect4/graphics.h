#include <stdio.h>
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/Xos.h>
#include <X11/Xatom.h>
#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__
int getScreen(Display *display){
	return DefaultScreen(display);
}
unsigned int getWidthDisplay(Display *display,int screen){
	return DisplayWidth(display,screen);
}
unsigned int getHeightDisplay(Display *display,int screen){
	return DisplayHeight(display,screen);
}
Display *getConnectionX11(){
	Display *display=XOpenDisplay(NULL);
	if(display==NULL){
		printf("cannot connect with server X11, cannot open display\n");
		exit(-1);
	}
	return display;
}
Window getWindow(Display **display,int screen,int x,int y,int width,int height){
	Window window=XCreateSimpleWindow(*display,RootWindow(*display,screen),x,y,width,height,1,BlackPixel(*display,screen),WhitePixel(*display,screen));//100 =>x 100=>y 500=>weigt 300=>height
	XSelectInput(*display,window,ExposureMask | KeyPressMask);
	XMapWindow(*display,window);
	return window;
}
Window addChildWindow(Display **display,Window father,int screen,int x,int y,int width,int height){
	Window child=XCreateSimpleWindow(*display,father,x,y,width,height,1,BlackPixel(*display,screen),WhitePixel(*display,screen));//100 =>x 100=>y 500=>weigt 300=>height
	XSelectInput(*display,child,ExposureMask | KeyPressMask);
	XMapWindow(*display,child);
	return child;
}
///
unsigned long getColor(Display* display, char* colorName){
   Colormap cmap;
	XColor color_cercano, color_verdadero;
	cmap = DefaultColormap(display, 0);
	XAllocNamedColor(display, cmap, colorName, &color_cercano, &color_verdadero);
	return(color_cercano.pixel);
}
#endif
