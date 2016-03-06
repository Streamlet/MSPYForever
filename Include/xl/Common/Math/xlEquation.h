//--------------------------------------------------------------------
//
//    Copyright (C) Streamlet. All rights reserved.
//
//    File Name:   xlEquation.h
//    Author:      Streamlet
//    Create Time: 2015-08-25
//    Description: 
//
//    Version history:
//
//
//--------------------------------------------------------------------

#ifndef __XLEQUATION_H_31B59C91_FBAB_422A_8CD1_CBECE5D3BDCD_INCLUDED__
#define __XLEQUATION_H_31B59C91_FBAB_422A_8CD1_CBECE5D3BDCD_INCLUDED__


#include "../../xlDef.h"
#include "../Memory/xlMemory.h"

namespace xl
{
    namespace Equation
    {
        namespace LinearSystem
        {
            template <int N, typename T>
            bool Solve(const T (&coefficient)[N][N + 1], T (&sln)[N])
            {
                //
                // Gaussian elimination
                //

                T coef[N][N + 1] = {};
                Memory::Copy(coef, coefficient, sizeof(coef));

                // Lower triangle
                for (int i = 0; i < N; ++i)
                {
                    if (coef[i][i] == 0)
                    {
                        for (int j = i + 1; j < N; ++j)
                        {
                            if (coef[j][i] == 0)
                            {
                                continue;
                            }

                            // Swap Line i and Line j
                            T t[N + 1] = {};
                            Memory::Copy(t, coef[i], sizeof(t));
                            Memory::Copy(coef[i], coef[j], sizeof(t));
                            Memory::Copy(coef[j], t, sizeof(t));

                            break;
                        }

                        if (coef[i][i] == 0)
                        {
                            return false;
                        }
                    }

                    for (int j = i + 1; j < N; ++j)
                    {
                        for (int k = i + 1; k <= N; ++k)
                        {
                            coef[j][k] -= coef[i][k] * coef[j][i] / coef[i][i];
                        }
                        coef[j][i] = 0;
                    }
                }

                // Upper triangle
                for (int i = N - 1; i >= 0; --i)
                {
                    for (int j = i - 1; j >= 0; --j)
                    {
                        coef[j][N] -= coef[i][N] * coef[j][i] / coef[i][i];
                        coef[j][i] = 0;
                    }
                }

                // Result
                for (int i = 0; i < N; ++i) {
                    sln[i] = coef[i][N] / coef[i][i];
                }

                return true;
            }

        } // namespace LinearSystem
    } // namespace Equation

} //namespace xl

#endif // #ifndef __XLEQUATION_H_31B59C91_FBAB_422A_8CD1_CBECE5D3BDCD_INCLUDED__
