#include <X11/Xlib.h>
#include <unistd.h>

unsigned long ObtieneColor(Display* dis, char* color_name){
   Colormap cmap;
   XColor color_cercano, color_verdadero;
   cmap = DefaultColormap(dis, 0);
   XAllocNamedColor(dis, cmap, color_name, &color_cercano, &color_verdadero);
   return(color_cercano.pixel);

}

int main(){
   Display *disp = NULL;
   Window ventana;
   XColor color;
   int t;
   
   disp = XOpenDisplay(NULL);
   ventana = XCreateSimpleWindow (disp, XDefaultRootWindow (disp), 100, 100, 500, 500, 1, 1,BlackPixel (disp, DefaultScreen(disp)));
   XMapWindow (disp, ventana);
   for(t = 0; t < 100; t++){
		
      XSetForeground (disp, XDefaultGC (disp, DefaultScreen(disp)), BlackPixel(disp, 0)^ObtieneColor(disp, "green"));
      XClearWindow(disp, ventana);      
      XDrawLine (disp,ventana,XDefaultGC (disp, DefaultScreen(disp)),t*1+80, t*2+40, t*2+40, t*3+80);
      XDrawLine (disp,ventana,XDefaultGC (disp, DefaultScreen(disp)),t*5+80, t*3+40, t*3+40, t*5+80);
      usleep(41666);  //24 por segundo
   }
   XDestroyWindow( disp, ventana);
   XCloseDisplay(disp);
   
   return(0);
}

