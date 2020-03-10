#pragma once

struct Zoom {

public:
	int x, y;
	double scale = 0;
public:
	Zoom(int x, int y, double scale) {
		this->x = x;
		this->y = y;
		this->scale = scale;
	}
};
