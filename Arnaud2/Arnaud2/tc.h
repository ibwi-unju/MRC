#pragma once

class tc {
public:
	complex z;
	complex dz;
	tc(complex = complex(0, 0), complex = complex(0, 0)); // constructeur par d�faut
	tc(const tc&);       // constructeur par copie
	tc& operator=(const tc&); // op�rateur d'affectation : oblig� d'appartenir � la classe
	const real& operator=(const real&); // op�rateur d'affectation : oblig� d'appartenir � la classe
	const complex& operator=(const complex&); // op�rateur d'affectation : oblig� d'appartenir � la classe
};
