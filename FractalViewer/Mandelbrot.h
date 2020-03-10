#pragma once
#include <utility>
#include <complex>
#include <math.h>


namespace Mandel {

		std::pair<int, double> getIterations(int maxIterations, double x, double y) {

			std::complex<double> z = 0;
			std::complex<double> c(x, y);
			double smoothColor{ 0 };
			int iterations = 0;

			while (iterations < maxIterations) {
				z = z * z + c;

				double magnitude = abs(z); 
				if (magnitude > 2) {

                    smoothColor = iterations + 1 - std::log(std::log2(magnitude));
					break;
				}

				iterations++;
			}
			return std::pair<int, double>(iterations, smoothColor);
		}
    }

