#ifndef SAMPLE_WINDOW_H
#define SAMPLE_WINDOW_H

#include "ofMain.h"

class sample_window
{
public:
    sample_window();
    void update(unsigned long t = 0);
    void draw(float x, float y, float w);
    void setFormula(unsigned char song);
    void clear_formula_img();
    void setZoom(unsigned int value);
    void setPot(unsigned int pot1, unsigned int pot2, unsigned int pot3);
    unsigned char genSound(unsigned long t);

    void update_formula_img(unsigned long t);
private:
    ofImage formula_img;
    float formula_img_w;
    float formula_img_h;
    unsigned char song;
    unsigned int pot1;
    unsigned int pot2;
    unsigned int pot3;
    unsigned int zoom;
};

#endif // SAMPLE_WINDOW_H
