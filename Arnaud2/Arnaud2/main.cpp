#include "tc.h"

tc b_;
double scale;

void color(int r, int g, int b) {
	red = r;
	green = g;
	blue = b;
}

tc f_(tc z) {
	return(a*(z + 1 / z) + b_);
}

tc f(tc z) {
	return(a*(z + 1 / z) + b);
}

tc fdyn(tc z) {
	return(a*(z + 1 / z) + b_.z);
}

complex map(complex z) {
	return(a*(z + 1 / z) + b);
}

void initOrbit(complex z) {
}


bool nul(tc u) {
	return(norm(u.dz)>norm(u.z));
}

bool prox(tc a, complex b) {
	return norm(a.dz)*(1 + norm(b))>norm(a.z - b)*(1 + norm(a.z));
}

void precomputationsParameterPlane() {
	scale = xw / width;
}

int computePixelParameterPlane(complex w) {

	b_ = tc(w, dz*thickness);

	int its = 0; // iterations counter

	int k;
	tc z1, z2;
	tc z1dyn, z2dyn;
	complex c1(1, 0);
	complex c2(-1, 0);
	z1 = c1;
	z2 = c2;
	z1dyn = tc(f_(z1).z, 1);
	z2dyn = tc(f_(z2).z, 1);
	bool z1bif = false;
	bool z2bif = false;
	bool z1cap = false;
	bool z2cap = false;

	//	double R2=10000;

	for (k = 0; k<iter; k++) {
		its++;
		if (!z1bif) {
			if (prox(z1, c1)) z1bif = true;
			if (prox(z1, c2)) z1bif = true;
			if (norm(z1dyn.dz)<smal) z1cap = true;
		}
		if (!z2bif) {
			if (prox(z2, c1)) z2bif = true;
			if (prox(z2, c2)) z2bif = true;
			if (norm(z2dyn.dz)<smal) z2cap = true;
		}

		// Assign pixel color.
		if (z1cap) {
			if (z2cap) goto aa;
			if (z2bif) goto ab;
		}
		if (z1bif) {
			if (z2cap) goto ba;
			if (z2bif) goto bb;
		}

		// If pixel color still not decided, iterate again.
		if (!z1bif && !z1cap) {
			z1 = f_(z1);
			z1dyn = fdyn(z1dyn);
		}
		if (!z2bif && !z2cap) {
			z2 = f_(z2);
			z2dyn = fdyn(z2dyn);
		}
	}
	goto gray; //If exceed iterates, assign gray pixel.

gray:  color(127, 127, 127);     goto fin; // gray

										   // out:   color(255,255,255);    goto fin; // white

bb:  color(191, 0, 255);      goto fin;

ba:  color(0, 0, 255);     goto fin;

ab:  color(255, 0, 0);      goto fin;

aa: color(255, 255, 255);  goto fin;

fin:

	return its;

}

void precomputationsDynamicalPlane() {
	scale = xw / width;
}
int computePixelDynamicalPlane(complex w) {

	tc z = tc(w, dz*thickness);
	tc aux;

	int its = 0; // iterations counter

	int k;

	//	double R2=10000;

	if (norm(z.z)<100.0) {
		if (norm(z.z - 1)<norm(z.dz*ptRad*width / (thickness))) goto blue;
		if (norm(z.z + 1)<norm(z.dz*ptRad*width / (thickness))) goto red;
	}
	for (k = 0; k<iter; k++) {
		its++;
		if (norm(z.dz)<smal) goto aa;
		aux = 1 / z;
		if (norm(aux.z)<norm(aux.dz)) goto bb;
		z = f(z);
	}
	goto gray;

gray:  color(127, 127, 127);     goto fin; // gray

										   // out:   color(255,255,255);    goto fin; // white

bb:  color(0, 0, 0);      goto fin;

aa: color(255, 255, 255);  goto fin;

blue: color(0, 0, 255); goto fin;

red: color(255, 0, 0); goto fin;

fin:

	return its;

}


