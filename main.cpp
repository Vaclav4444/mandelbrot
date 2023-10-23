#include <SDL/SDL.h>
#include "grafika.h"
#include <math.h>

class Complex{
  public:
    float re;
    float im;



     Complex(){
        re = 0;
        im = 0;
        return;
    }

     Complex(float R, float I){
        re = R;
        im = I;

    }

    float real(){
        return re;
    }
    float imaginary(){
        return im;
    }

    float abs(){
        float out = 0;
        out = im*im+re*re;
            //out = sqrt(out);
            return out;
    }
};

Complex mult(Complex a, Complex b){
    Complex end;
    end.re = a.real()*b.real() - a.imaginary()*b.imaginary();
    end.im = a.real()*b.imaginary() + a.imaginary()*b.real();

    return end;
}

Complex add(Complex a, Complex b){
    Complex end;
    end.re = a.real()+b.real();
    end.im = a.imaginary()+b.imaginary();

    return end;
}

/*									equals									---------------------------------- new
bool equals(Complex a, Complex b){
	if(a.real()==b.real()){
		if(a.imaginary()==b.imaginary()){
			return True;
		}
	}
	return False
}
*/

float displayToMath(float screenSize, float mathSize, float dispCoord, float screenDisplacement){
    //y je invers
    float out = 0;

    out = screenDisplacement + (screenSize/2);
    out *= mathSize/screenSize;
    return out;
}

int main(int argc, char** argv){

    float screenSize_x = 800;
    float screenSize_y = 600;

    float mathSize_x = 2;
    float mathSize_y = 2;

    int iterations = 90;

    int end = 0;

    float xshift = 2;
    float yshift = 1;

    float zoom = 2;


    int r = 1;
    int g = 1;
    int b = 1;


    //kreslení
    Obrazovka* obrazovka = Obrazovka::instance();
        obrazovka->inicializuj(screenSize_x, screenSize_y, 0, 0);



        Complex z;
        Complex c;


        while(1)
        {


            obrazovka->smaz();

            /* zacatek kresleni */
            barva(BILA);

            //go through everything


            for(int x = 0;x<screenSize_x;x++){
                for(int y = 0; y < screenSize_y;y++){
                  c.re=((x-screenSize_x/2)/(100.0*zoom))-xshift;/*xshift*/
                    c.im=((y-screenSize_y/2)/(100.0*zoom))-yshift;
                    z.re=c.re;
                    z.im=c.im;

                    end=0;
                    for(int i = 0; i < iterations; i++){
                        z=add(mult(z,z),c);
                        
                        /*	basic loop detection								---------------------------new
						            if(equals(z,c)){
						          	break;
						            }
						            */
                      
                        if(z.abs()>4){
                        end=i;
                        break;
                        }
                    }


                    barva(sin(end*r)*255,sin(end*g)*255,sin(end*b)*255);


                  // TODO HSV
					
					/*
					
					
					
					*/
                    /*if(z.abs()>2){
                        barva(CERNA);
                    }else{
                        barva(BILA);
                    }*/



                    bod(x,y);
                }
            }





            /* konec kresleni */
            obrazovka->aktualizuj();

            SDL_Event event;
            while(SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                    case SDLK_ESCAPE:
                        SDL_Quit();
                        return 0;
                        break;

                    case SDLK_DOWN:
                        yshift-=1.0/zoom;
                        break;
                    case SDLK_UP:
                        yshift+=1.0/zoom;
                        break;
                    case SDLK_LEFT:
                        xshift+=1.0/zoom;
                        break;
                    case SDLK_RIGHT:
                        xshift-=1.0/zoom;
                        break;
                    case SDLK_KP_PLUS:
                        zoom*=2.0;
                        break;
                    case SDLK_KP_MINUS:
                        zoom/=2.0;
                        break;


                    case SDLK_KP1:
                        r++;
                        break;
                    case SDLK_KP2:
                        g++;
                        break;
                    case SDLK_KP3:
                        b++;
                        break;


                    }
                    break;
                }
            }
        }








    return 0;
}
