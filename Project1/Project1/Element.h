#include "Image.h"
#ifndef Element_H
#define Element_H


class Element {
public:
	Element() {

	}
	Element(Image *im, int xx, int yy, boolean isItMario, boolean isItMobile, int elementSpeed = 1) {
		image = im;
		fillOtherFields(xx, yy, isItMario, isItMobile, elementSpeed);
	}
	Element(Image im, int xx, int yy, boolean isItMario, boolean isItMobile, int elementSpeed = 1) {
		image = new Image[1];
		image[0] = im.getSubImage();
		fillOtherFields(xx, yy, isItMario, isItMobile, elementSpeed);
	}
	void fillOtherFields(int xx, int yy, boolean isItMario, boolean isItMobile, int elementSpeed) {
		x = xx;
		y = yy;
		mario = isItMario;
		mobile = isItMobile;
		speed = elementSpeed;
	}
	
	double getX() {
		return x;
	}
	double getY() {
		return y;
	}
	int setX(int newX) {
		x = newX;
	}
	int setY(int newY) {
		y = newY;
	}
	Image getImage() {
		return image[state];
	}
	void disappear() {
		setVisible(false);
		x = 0;
		y = 0;
	}
	bool isMobile() {
		return mobile;
	}
	void setVisible(bool isVisible){
		visible = isVisible;
	}
	bool isVisible(){
		return visible;
	}
	bool isCoin() {
		return !mobile;
	}
	void moveX(double xRate, bool right) {
		if (mario) {
			right = !right;
		}
		if (x > 0) {

			if (right) {
				x = x - xRate*speed;
			}
			else {
				x = x + xRate*speed;
			}

		}
		if (mario) {
			if (state == 0) {
				state = 1;
				lastState = 0;
			}
			else if (state == 1) {
				if (lastState == 0) {
					state = 2;
					lastState = 1;
				}
				else {
					state = 0;
					lastState = 1;
				}
			}
			else {
				state = 1;
				lastState = 2;
			}
		}
	}
	void clearMemory() {
		int * objPix;
		if (!mario) {
			objPix=image[0].getPixels();
			delete[] objPix;
		}
		else {
			for (int i = 0; i < 3; i++) {
				objPix = image[i].getPixels();
				delete[] objPix;
			}
		}
	}


private:
	Image *image;
	double x;
	double y;
	bool mario = false;
	bool visible = false;
	bool mobile = false;
	int state = 0;
	int lastState = 0;
	int speed;
	
};

#endif