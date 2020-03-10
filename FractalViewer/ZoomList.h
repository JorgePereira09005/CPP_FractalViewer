#pragma once
#include "Zoom.h"
#include <vector>
#include <utility>


class ZoomList {
private:
    double m_xCenter{0}, m_yCenter{0}, m_scale{0};
	int m_width, m_height;
	std::vector<Zoom> zooms;
public:
	ZoomList(int width, int height) {
		this->m_width = width;
		this->m_height = height;
		this->m_scale = 1.0;
	}

	void addZoom(const Zoom& zoom) {
        //qDebug() << "inside addZoom";

		zooms.push_back(zoom);

        m_xCenter += (zoom.x - m_width / 2) * m_scale;

        //qDebug() << "inside addZoom, m_xCenter: " << m_xCenter << " , zoom.x: " << zoom.x << ", m_width: " << m_width << ", m_scale: " << m_scale;

        m_yCenter += -(zoom.y - m_height / 2) * m_scale;
        m_scale *= zoom.scale;
	}

	std::pair<double, double> doZoom(int x, int y) {

        //qDebug() << "inside doZoom (x,y) "<< x << " , " << y;
        //double xFractal {0};
        //double yFractal {0};

        //qDebug() << "m_width: "<< m_width << ", m_scale :" << m_scale << ", m_xCenter :" << m_xCenter;
        double xFractal = (x - m_width / 2) * m_scale + m_xCenter;
        double yFractal = (y - m_height / 2) * m_scale + m_yCenter;

		return std::pair<double, double>(xFractal, yFractal);
	}
};

