#include "Timer.h"

#include "Laplacian.h"
#include "Utilities.h"
#include "PointwiseOps.h"
#include "Reductions.h"


int main(int argc, char *argv[])
{
    using array_t = float (&) [XDIM][YDIM][ZDIM];

    float *xRaw = new float [XDIM*YDIM*ZDIM];
    float *fRaw = new float [XDIM*YDIM*ZDIM];
    float *pRaw = new float [XDIM*YDIM*ZDIM];
    float *rRaw = new float [XDIM*YDIM*ZDIM];
    float *zRaw = new float [XDIM*YDIM*ZDIM];
    
    array_t x = reinterpret_cast<array_t>(*xRaw);
    array_t f = reinterpret_cast<array_t>(*fRaw);
    array_t p = reinterpret_cast<array_t>(*pRaw);
    array_t r = reinterpret_cast<array_t>(*rRaw);
    array_t z = reinterpret_cast<array_t>(*zRaw);

    Timer timer;
    
    // Initialization
    {
        timer.Start();
        InitializeProblem(x, f);
        WriteAsImage("x", x, 0, 0, 127);
        Clear(p);
        Clear(r);
        Clear(z);
        timer.Stop("Initialization : ");
    }

    // Conjugate Gradients iteration
    {
        // Algorithm : Line 2
        ComputeLaplacian(x, z);
        Saxpy(z, f, r, -1);
        float nu = Norm(r);

        // Algorithm : Line 3
        if (nu < nuMax) return 0;
        
        // Algorithm : Line 4
        Copy(r, p);
        float rho=InnerProduct(p, r);
        
        // Beginning of loop from Line 5
        for(int k=0;;k++)
        {
            std::cout << "Residual norm (nu) after " << k << " iterations = " << nu << std::endl;

            // Algorithm : Line 6
            ComputeLaplacian(p, z);
            float sigma=InnerProduct(p, z);

            // Algorithm : Line 7
            float alpha=rho/sigma;

            // Algorithm : Line 8
            Saxpy(z, r, r, -alpha);
            nu=Norm(r);

            // Algorithm : Lines 9-12
            if (nu < nuMax || k == kMax) {
                Saxpy(p, x, x, alpha);
                std::cout << "Conjugate Gradients terminated after " << k << " iterations; residual norm (nu) = " << nu << std::endl;
                WriteAsImage("x", x, k, 0, 127);
                return 0;
            }
            
            // Algorithm : Line 13
            Copy(r, z);
            float rho_new = InnerProduct(z, r);

            // Algorithm : Line 14
            float beta = rho_new/rho;

            // Algorithm : Line 15
            rho=rho_new;

            // Algorithm : Line 16
            Saxpy(p, x, x, alpha);
            Saxpy(p, r, p, beta);

            WriteAsImage("x", x, k, 0, 127);
        }
    }

    return 0;
}
