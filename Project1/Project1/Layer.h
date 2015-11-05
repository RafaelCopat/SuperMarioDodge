
#include "Element.h"
#include "Image.h"
#ifndef Layer_H
#define Layer_H
;
class Layer {
public:
	Layer() {

	}
	Layer(Image im, int xBase, int yBase, Element * elements, int nElements) {
		pxi = 0;
		pxf = 800;
		pyi = 0;
		pyf = 600;
		image = im;
		taxaX = (double)image.getWidth() / xBase *5;
		taxaY = (double)image.getHeight() / yBase *5;
		arrayOfElements = elements;
		numberOfElements = nElements;
	}
	bool checkWin() {
		if (arrayOfElements[0].getX() >= image.getWidth() - 400) {
			return true;
		}
		return false;
	}
	bool checkIfMarioIsDead(){
		bool dead = false;
		for (int i = 1; i < numberOfElements; i++) {
			if (arrayOfElements[i].isVisible() && arrayOfElements[0].isVisible() && !arrayOfElements[i].isCoin()){
				dead = checkCollision(i);
				if(dead){
					return true;
				}
			}
		}
		return false;
	}

	bool checkIfGrabsCoin() {
		bool collision = false;
		for (int i = 1; i < numberOfElements; i++) {
			if (arrayOfElements[i].isVisible() && arrayOfElements[0].isVisible() && arrayOfElements[i].isCoin()) {
				collision = checkCollision(i);
				if(collision){
					arrayOfElements[i].disappear();
					return true;
				}
			}
		}
		return false;
	}

	bool checkCollision(int i) {
		int elementX = (int)arrayOfElements[i].getX();
		int elementY = (int)arrayOfElements[i].getY();
		int w = (int)arrayOfElements[i].getImage().getWidth();
		int marioX = (int)arrayOfElements[0].getX();
		int marioY = (int)arrayOfElements[0].getY();
		int marioW = arrayOfElements[0].getImage().getWidth();
		if (((elementX > marioX + 10 && elementX < marioX + marioW))) {
			return true;
		}
		return false;
	}
	
	int * ScrollH(bool right) {
		if (right) {
			pxi += taxaX;
			pxf += taxaX;
		}
		else {
			pxi -= taxaX;
			pxf -= taxaX;
		}

		Image subImage = parseElements(1, right);
		return subImage.getPixels();
	}
	
	double getpXf(void) {
		return pxf;
	}
	double getpXi(void) {
		return pxi;
	}
	void setMarioVisibility(bool visible) {
		arrayOfElements[0].setVisible(visible);
	}

	Image getImage(void) {
		return image;
	}

	void clearMemory() {
		for (int i = 0; i < numberOfElements; i++) {
				arrayOfElements[i].clearMemory();
		}		
		int * objPix = image.getPixels();
		delete[] objPix;
	}

	Image parseElements(int mode, bool right) {
		Image subImage = image.getSubImage((int)pxi, (int)pyi, (int)pxf, (int)pyf);
		int * objPix;
		
			for (int i = 0; i < numberOfElements; i++) {
				if (mode == 1 && arrayOfElements[i].isMobile()) {
					arrayOfElements[i].moveX(taxaX, right);
				}

				int elementX = (int)arrayOfElements[i].getX();
				if (elementX == 445) {
					int a = 0;
				}
				int elementY = (int)arrayOfElements[i].getY();
				int w = (int)arrayOfElements[i].getImage().getWidth();
				int h = (int)arrayOfElements[i].getImage().getHeight();
				objPix = arrayOfElements[i].getImage().getPixels();

				if (elementX + w >= pxi && elementX <= pxf) {
					if (i == 6) {
						int b = 0;
					}
					if (pxi > elementX) {
						objPix = arrayOfElements[i].getImage().getSubImage((int)pxi - elementX, 0, w, h).getPixels();
						w = w - ((int)pxi - elementX);
						elementX = (int)pxi;
					}
					if (pxf < elementX + w) {
						objPix = arrayOfElements[i].getImage().getSubImage(0, 0, (int)pxf - elementX, h).getPixels();
						w = (int)pxf - elementX;
					}
					if (i == 0) {
						if (arrayOfElements[0].isVisible()) {
							subImage.plot(objPix, elementX - (int)pxi,
								elementY - (int)pyi, w, h);
						}
					}
					else {
						subImage.plot(objPix, elementX - (int)pxi,
							elementY - (int)pyi, w, h);
						arrayOfElements[i].setVisible(true);
					}
				}
				else {
					arrayOfElements[i].setVisible(false);
				}
			}
			return subImage;

		
	}
		Image getCroppedImage(void) {
			return parseElements(0, false);
		}
	
	
	


public:
	Image image;
	Element * arrayOfElements;
	double taxaX;
	double taxaY;
	double pxi;
	double pxf;
	double pyi;
	double pyf;
	int numberOfElements;
};
#endif