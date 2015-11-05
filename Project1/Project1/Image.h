#ifndef Image_H
#define Image_H


class Image {
public:
	Image() {

	}
	Image(int w, int h, int* pix) {
		width = w;
		height = h;
		pixels = pix;
	}
	Image(int w, int h){
		width = w; height = h;
		pixels = new int[w*h];
	}
	Image(char* caminho){
		char linha[200];
		std::ifstream arq(caminho);
		arq >> linha;
		arq >> width;
		arq >> height;
		int cont = width*height - 1;
		pixels = new int[width*height];
		int m;
		arq >> m;
		int aa, rr, gg, bb;
		int rgb;
		for (int i = 0; i < width * height; i++) {
			arq >> aa >> rr >> gg >> bb;
			int x = i % width;
			int y = i / width;
			y = height - y - 1;
			rgb = (aa << 24) | (rr << 16) | (gg << 8) | bb;
			setPixel(rgb, x, y);
		}

	}
	void setPixel(int rgb, int x, int y){
		pixels[x + y*width] = rgb;
	}
	void setPixelOpaco(int r, int g, int b, int x, int y){
		int rgb = (255 << 24) | (r << 16) | (g << 8) | b;
		pixels[x + y*width] = rgb;
	}
	void setPixelTransparente(int r, int g, int b, int x, int y){
		int rgb = (r << 16) | (g << 8) | b;
		pixels[x + y*width] = rgb;
	}
	int getPixel(int x, int y){
		return pixels[x + y*width];
	}
	int getWidth(){ return width; }
	int getHeight(){ return height; }
	int* getPixels(){ return pixels; }

	Image getSubImage(int xi, int yi, int xf, int yf) {
		int w = xf - xi;
		int h = yf - yi;
		int cont = 0;
		int *sub = new int[w*h];
		int xx = 0;
		int yy = 0;
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				xx = xi + x;
				yy = yi + y;
				sub[cont] = pixels[xx + yy*width];
				cont++;
			}
		}
		Image s(w, h, sub);
		return s;

	}
	Image getSubImage() {
		int w = width;
		int h = height;
		int cont = 0;
		int *sub = new int[w*h];
		int xx = 0;
		int yy = 0;
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				xx = 0 + x;
				yy = 0 + y;
				sub[cont] = pixels[xx + yy*width];
				cont++;
			}
		}
		Image s(w, h, sub);
		return s;

	}

	void plot(int *foreground, int xi, int yi, int w, int h){
		int xx;
		int yy;
		int cont = 0;
		for (int y = 0; y < h; y++){
			for (int x = 0; x < w; x++){
				xx = xi + x;
				yy = yi + y;
				int c = (foreground[cont] & 0xFF000000) >> 24;
				if (c != 0) {
					pixels[xx + yy*width] = foreground[cont];
				}
				cont++;
			}
		}
	}


private:int *pixels; // alternativamente char *pixels – 1 byte por canal
		// neste caso, pixels = new char[w*h*3];
		int width, height;
};
#endif