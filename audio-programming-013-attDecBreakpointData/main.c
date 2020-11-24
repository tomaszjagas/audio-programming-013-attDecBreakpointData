/*******************************************************************
* Description: generate expoinential attack or decay breakpoint data
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv) {
	int i, npoints;
	double startVal, endVal;
	double dur, step, start, end, thisStep;
	double fac, valRange, offset;
	const double verySmall = 1.0e-4; // ~-80dB

	if (argc != 5) {
		fprintf(stderr, "usage: expbrk duration npoints startval endval\n");
		return 1;
	}

	dur = atof(argv[1]);
	if (dur <= 0.0) {
		fprintf(stderr, "error: duration must be positive\n");
		return 1;
	}

	npoints = atoi(argv[2]);
	if (npoints <= 0) {
		fprintf(stderr, "error: npoints must be positive\n");
		return 1;
	}

	step = dur / npoints;

	startVal = atof(argv[3]);
	endVal = atof(argv[4]);
	valRange = endVal - startVal;

	if (valRange ==0.0 ) {
		fprintf(stderr, "warning: start and end value are the same\n");
	}

	// initialize normalized exponential as attack or decay
	if (startVal > endVal) {
		start = 1.0;
		end = verySmall;
		valRange = -valRange;
		offset = endVal;
	}
	else {
		start = verySmall;
		end = 1.0;
		offset = startVal;
	}

	thisStep = 0.0;

	// make normalized curve, scale output to input values, range
	fac = pow(end / start, 1.0 / npoints);
	for (i = 0; i < npoints; i++) {
		fprintf(stdout, "%.4lf\t%.8lf\n", thisStep, offset + (start * valRange));
		start *= fac;
		thisStep += step;
	}

	// print final value
	fprintf(stdout, "%.4lf\t%.8lf\n", thisStep, offset + (start * valRange));
	fprintf(stderr, "done\n");
	return 0;

}