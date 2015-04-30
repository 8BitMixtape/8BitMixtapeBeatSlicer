#include "sample_window.h"

void sample_window::clear_formula_img()
{
    for (int x = 0 ; x < formula_img_w*formula_img_h; x++)
        {
            //formula_img.getTextureData().
            formula_img.getPixelsRef()[x] = 0;
        }
}

sample_window::sample_window()
{

    song = 0;
    formula_img_w = 8000;
    formula_img_h = 255;

    pot1 = 0;
    pot2 = 0;
    pot3 = 0;
    zoom = 3;

    formula_img.allocate(formula_img_w,formula_img_h, OF_IMAGE_GRAYSCALE);
    clear_formula_img();

    formula_img.getTextureReference().setTextureMinMagFilter(GL_NEAREST,GL_NEAREST);

    formula_img.update();
    update();
}

void sample_window::update_formula_img(unsigned long t = 0)
{
    int bpp_src  = formula_img.getPixelsRef().getBytesPerPixel();

    unsigned char snd;

    for (int x = 0 ; x < formula_img_w; x++)
    {
        snd = genSound((x+t) << zoom);

        for (int y = 0 ; y < formula_img_h; y++)
        {
            int arrpos_src = ((255-y) * (bpp_src*formula_img_w)) + x*bpp_src;

            if (y < snd)
            {
                formula_img.getPixelsRef()[arrpos_src] = 200;
            }else{
                formula_img.getPixelsRef()[arrpos_src] = 0;
            }

        }
    }


    formula_img.update();
}

void sample_window::update(unsigned long t)
{

  //  clear_formula_img();

//    for (int x = 0 ; x < formula_img_w*formula_img_h; x++)
//        {
//            formula_img.getPixelsRef()[x] =genSound(x);
//        }
   // unsigned char * pix_dst = formula_img.getPixelsRef();

    update_formula_img(t);
}

unsigned char sample_window::genSound(unsigned long t)
{
    unsigned char snd;

    switch (this->song)
    {
        case 0:
        snd = (t*(5+(pot1/5))&t>>7)|(t*3&t>>(10-(pot2/5)));
        break;

        case 1:
        snd = (t|(t>>(9+(pot1/2))|t>>7))*t&(t>>(11+(pot2/2))|t>>9);
        break;

        case 2:
        snd = (t*9&t>>4|t*5&t>>(7+(pot1/2))|t*3&t/(1024-(pot2/2)))-1;
        break;

        case 3:
        snd = (t>>6|t|t>>(t>>(16-(pot1/2))))*10+((t>>11)&(7+(pot2/2)));
        break;

        case 4:
        snd = t*(((t>>(11-(pot2/2)))&(t>>8))&((123-pot1)&(t>>3)));
        break;

        case 5:
        snd = t*(t^t+(t>>15|1)^(t-(1280-(pot1/2))^t)>>(10-(pot2/5)));
        break;

        case 6:
        snd = t * ((pot1>>12|t>>8)&pot2&t>>4);
        //snd = (t*t/(256-pot1))&(t>>((t/(1024-pot2))%16))^t%64*(0xC0D3DE4D69>>(t>>9&30)&t%32)*t>>18;
        break;

        case 7:
        snd = (t&t>>(12+(pot1/2)))*(t>>4|t>>(8-(pot2/2)))^t>>6;
        break;

        case 8:
        snd = t*(((t>>9)^((t>>9)-(1+(pot1/2)))^1)%(13+(pot2/2)));
        break;

        case 9:
        snd = t*(((t>>(12+(pot1/2)))|(t>>8))&((63-(pot2/2))&(t>>4)));
        break;

    }

    return snd;
}
void sample_window::setZoom(unsigned int zoom_value)
{
    zoom = zoom_value;
    //update();
}


void sample_window::setPot(unsigned int pot1, unsigned int pot2, unsigned int pot3)
{
    this->pot1 = pot1;
    this->pot2 = pot2;
    this->pot3 = pot3;

    //update();

}

void sample_window::draw(float x, float y, float w)
{
    formula_img.draw(x, y, ofGetWidth()*w,255);
}


void sample_window::setFormula(unsigned char song)
{
    this->song = song;
    this->update();
}

