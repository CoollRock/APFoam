/*---------------------------------------------------------------------------*\
  =========                 |
  \\      /  F ield         | OpenFOAM: The Open Source CFD Toolbox
   \\    /   O peration     | Website:  https://openfoam.org
    \\  /    A nd           | Copyright (C) 2011-2018 OpenFOAM Foundation
     \\/     M anipulation  |
-------------------------------------------------------------------------------
License
    This file is part of OpenFOAM.

    OpenFOAM is free software: you can redistribute it and/or modify it
    under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    OpenFOAM is distributed in the hope that it will be useful, but WITHOUT
    ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
    FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
    for more details.

    You should have received a copy of the GNU General Public License
    along with OpenFOAM.  If not, see <http://www.gnu.org/licenses/>.

\*---------------------------------------------------------------------------*/

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

inline Foam::APFallOffFunction::APFallOffFunction
(
    const scalar f,
    const scalar n
)
:
    f_(f),
    n_(n)
{}


inline Foam::APFallOffFunction::APFallOffFunction(const dictionary& dict)
:
    f_(readScalar(dict.lookup("f"))),
    n_(readScalar(dict.lookup("n")))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

inline Foam::scalar Foam::APFallOffFunction::operator()
(
    const scalar T,
    const scalar Pr
) const
{

    scalar logPr = log10(max(Pr, small));
    return pow(f_,1./(1.+sqr(logPr/n_) ) );
}
 

inline Foam::scalar Foam::APFallOffFunction::ddT
(
    const scalar Pr,
    const scalar F,
    const scalar dPrdT,
    const scalar T
) const
{
/*
    scalar logPr = log10(max(Pr, small));
    scalar logTen = log(10.0);
    scalar Fcent =
    (
        max
        (
            (1 - alpha_)*exp(-T/Tsss_) + alpha_*exp(-T/Ts_) + exp(-Tss_/T),
            small
        )
    );
    scalar logFcent = log10(Fcent);

    scalar dFcentdT =
    (
        (alpha_ - 1)*exp(-T/Tsss_)/Tsss_
      - alpha_*exp(-T/Ts_)/Ts_
      + Tss_*exp(-Tss_/T)/sqr(T)
    );

    scalar d = 0.14;
    scalar dlogFcentdT = dFcentdT/Fcent/logTen;
    scalar c = -0.4 - 0.67*logFcent;
    scalar dcdT = -0.67*dlogFcentdT;
    scalar n = 0.75 - 1.27*logFcent;
    scalar dndT = -1.27*dlogFcentdT;

    scalar dlogPrdT = dPrdT/Pr/logTen;

    scalar dParentdT =
        2.0*(logPr + c)/sqr(n - d*(logPr + c))
       *(
            (dlogPrdT + dcdT)
          - (logPr + c)*(dndT - d*(dlogPrdT + dcdT))/(n - d*(logPr + c))
        );

    return
    (
        F*logTen
       *(
            dlogFcentdT/(1.0 + sqr((logPr + c)/(n - d*(logPr + c))))
          - logFcent*dParentdT/sqr(1.0 + sqr((logPr + c)/(n - d*(logPr + c))))
        )
    );
*/
   return 0;
}


inline Foam::scalar Foam::APFallOffFunction::ddc
(
    const scalar Pr,
    const scalar F,
    const scalar dPrdc,
    const scalar T
) const
{
/*
    scalar logPr = log10(max(Pr, small));
    scalar logTen = log(10.0);
    scalar logFcent = log10
    (
        max
        (
            (1 - alpha_)*exp(-T/Tsss_) + alpha_*exp(-T/Ts_) + exp(-Tss_/T),
            small
        )
    );

    scalar dlogPrdc = dPrdc/Pr/logTen;
    scalar d = 0.14;
    scalar c = -0.4 - 0.67*logFcent;
    scalar n = 0.75 - 1.27*logFcent;

    scalar dParentdc =
        2.0*(logPr + c)/sqr(n - d*(logPr + c))
       *(
            (dlogPrdc)
          - (logPr + c)*(-d*(dlogPrdc))/(n - d*(logPr + c))
        );

    return
    (
        F*logTen
       *(
          - logFcent*dParentdc/sqr(1.0 + sqr((logPr + c)/(n - d*(logPr + c))))
        )
    );
*/
   return 0;

}


inline void Foam::APFallOffFunction::write(Ostream& os) const
{
    os.writeKeyword("f") << f_ << token::END_STATEMENT << nl;
    os.writeKeyword("n") << n_ << token::END_STATEMENT << nl;
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

inline Foam::Ostream& Foam::operator<<
(
    Foam::Ostream& os,
    const Foam::APFallOffFunction& tfof
)
{
    tfof.write(os);
    return os;
}


// ************************************************************************* //
