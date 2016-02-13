#include <X11/Xlib.h>
#include <unistd.h>
int main(){
	Display *display;
	Window window;
	XColor color;
	display=XOpenDisplay(NULL);//get display
	window=XCreateSimpleWindow(display,XDefaultRootWindow(display),100,100,500,500,1,1,BlackPixel(display,DefaultScreen(display)));//create windown
	XMapWindow(display,window);//set window in display
	XFlush(display);
	color.flags=DoRed|DoGreen|DoBlue;
	color.red=65535;
	color.blue=0;
	color.green=0;
	while(1){
		XAllocColor(display,DefaultColormap(display,DefaultScreen(display)),&color);
		XSetForeground(display,XDefaultGC(display,DefaultScreen(display)),color.pixel);
		XDrawLine(display,window,XDefaultGC(display,DefaultScreen(display)),10,10,100,100);
		XFlush(display);
		sleep(1);
	}
	sleep(100);
	return 0;
}
