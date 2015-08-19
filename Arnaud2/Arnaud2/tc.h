#pragma once

class tc {
public:
	complex z;
	complex dz;
	tc(complex = complex(0, 0), complex = complex(0, 0)); // constructeur par défaut
	tc(const tc&);       // constructeur par copie
	tc& operator=(const tc&); // opérateur d'affectation : obligé d'appartenir à la classe
	const real& operator=(const real&); // opérateur d'affectation : obligé d'appartenir à la classe
	const complex& operator=(const complex&); // opérateur d'affectation : obligé d'appartenir à la classe
};
