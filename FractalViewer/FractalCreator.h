#pragma once
#include "Mandelbrot.h"
#include "ZoomList.h"
#include <QImage>
#include <QRgb>

class FractalCreator {
private:
	int resWidth, resHeight, maxIterations;
	ZoomList zoomList;
    QImage image;
	double rModifier, gModifier, bModifier;
	uint8_t startRed, startGreen, startBlue;
public:
	FractalCreator(int maxIterations, int resWidth, int resHeight, uint8_t red, uint8_t green, uint8_t blue, double rModifier,
        double gModifier, double bModifier): zoomList(resWidth, resHeight), image(resWidth, resHeight, QImage::Format_RGB32){
		
		this->startRed = red;
		this->startGreen = green;
		this->startBlue = blue;
        this->resHeight = resHeight;
        this->resWidth = resWidth;
		this->maxIterations = maxIterations;
		this->rModifier = rModifier;
		this->gModifier = gModifier;
		this->bModifier = bModifier;
        zoomList.addZoom(Zoom(resWidth / 2, resHeight / 2, 4.0 / resWidth));
        //qDebug() << "classe criada";
	}

	void addZoom(Zoom& zoom) {
		zoomList.addZoom(zoom);
	}

	void drawFractal() {

        QRgb colorValue;

        for (int y = 0; y < resHeight; y++) {
            for (int x = 0; x < resWidth; x++) {

                //qDebug() << "(x,y) "<< x << " , " << y;
                std::pair<double, double> coords = this->zoomList.doZoom(x, y);
                //qDebug() << "adjusted coords (x,y) " << coords.first << " , " << coords.second;
				std::pair<int, double> values = Mandel::getIterations(this->maxIterations, coords.first, coords.second);

                //qDebug() << "iteration and smoothcolor: " << values.first << " , " << values.second;
                //qDebug() << "iterations: " << values.first << " smoothColor: " << values.second;

				if (values.first < this->maxIterations) {
					uint8_t redDraw = startRed * values.second*rModifier;
                    uint8_t greenDraw = startGreen * values.second*gModifier;
                    uint8_t blueDraw = startBlue * values.second*bModifier;
                    colorValue = qRgb(redDraw, greenDraw, blueDraw);
                }
                else {
                    colorValue = qRgb(0, 0, 0);
                }
                image.setPixel(x, y, colorValue);
			}
		}
	}

    QImage getImage() {
        return image;
    }

    void run() {
		this->drawFractal();
	}

    ~FractalCreator() {

    }
};
