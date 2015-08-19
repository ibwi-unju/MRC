// implémentation personnelle de la classe tc

// v 0.2

typedef double real;

// casting

#include "tc.h"

// fonctions membres

tc::tc(complex un, complex deux)
{
	z = un;
	dz = deux;
};


tc::tc(const tc& t)
{
	z = t.z;
	dz = t.dz;
};

tc& tc::operator=(const tc& t)
{
	z = t.z;
	dz = t.dz;
	return *this;
};

const real& tc::operator=(const real& r)
{
	z = r;
	dz = 0;
	return r;
};

const complex& tc::operator=(const complex& c)
{
	z = c;
	dz = 0;
	return c;
};

// fonctions non membres

tc operator*(const tc& a, const tc& b)
{
	tc t(a.z*b.z, a.z*b.dz + a.dz*b.z);
	return t;
};

tc operator*(const real& a, const tc& b)
{
	tc t(a*b.z, a*b.dz);
	return t;
};

tc operator*(const tc& a, const real& b)
{
	tc t(a.z*b, a.dz*b);
	return t;
};

tc operator+(const tc& a, const tc& b)
{
	tc t(a.z + b.z, a.dz + b.dz);
	return t;
};

tc operator+(const real& a, const tc& b)
{
	tc t(a + b.z, b.dz);
	return t;
};

tc operator+(const tc& a, const real& b)
{
	tc t(a.z + b, a.dz);
	return t;
};

tc operator-(const tc& a)
{
	tc t(-a.z, -a.dz);
	return t;
};

tc operator-(const tc& a, const tc& b)
{
	tc t(a.z - b.z, a.dz - b.dz);
	return t;
};

tc operator-(const real& a, const tc& b)
{
	tc t(a - b.z, -b.dz);
	return t;
};

tc operator-(const tc& a, const real& b)
{
	tc t(a.z - b, a.dz);
	return t;
};

tc exp(const tc& a)
{
	complex aux = exp(a.z);
	tc t(aux, aux*a.dz);
	return t;
};

/*
tc sin(const tc& a)
{
tc c=((exp(a*tc(0,1))-exp(a*tc(0,-1)))*tc(0,-0.5));
return c;
};
*/

tc log(const tc& a)
{
	tc t(log(a.z), a.dz / a.z);
	return t;
};

tc conj(const tc& a) // ATTENTION, PAS DE SENS CONCERNANT LA DERIVEE
{
	tc t(conj(a.z), conj(a.dz));
	return t;
};

tc operator/(const tc& a, const tc& b)
{
	tc t(a.z / b.z, a.dz / b.z - a.z*b.dz / (b.z*b.z));
	return t;
};

tc operator/(const real& a, const tc& b)
{
	tc t(a / b.z, -a*b.dz / (b.z*b.z));
	return t;
};

tc operator/(const tc& a, const real& b)
{
	tc t(a.z / b, a.dz / b);
	return t;
};

tc sqrt(const tc& a)
{
	tc t = exp(0.5*log(a));
	return t;
}
