// OpenMP testing heat transfer parallelization
#include <omp.h>
#include <sys/time.h>

#include <cstdio>

// define functions MIN and MAX
#define min(A, B) ((A) < (B) ? (A) : (B))
#define max(A, B) ((A) > (B) ? (A) : (B))

// define size of grid points

#define imax 20
#define kmax 11
#define itmax 20000

// functions prints the temperature grid ,dont parallelize
void heatpr(double phi[imax + 1][kmax + 1]) {
  int i, k, kl, kk, kkk;
  kl = 6;
  kkk = kl - 1;
  for (k = 0; k <= kmax; k = k + kl) {
    if (k + kkk > kmax) kkk = kmax - k;
    printf("\ncolumns %5d to %5d\n", k, k + kkk);
    for (i = 0; i <= imax; i++) {
      printf("%5d ", i);
      for (kk = 0; kk <= kkk; kk++) {
        printf("%#12.4g", phi[i][k + kk]);
      }
      printf("\n");
    }
  }
  return;
}

int main() {
  int num_threads = 4;
  omp_set_num_threads(num_threads);
  double eps = 1.0e-08;
  double phi[imax + 1][kmax + 1], phin[imax][kmax];
  double dx, dy, dx2, dy2, dx2i, dy2i, dt, dphi, dphimax, dphimax0;
  int i, k, it;
  struct timeval tv1, tv2;
  struct timezone tz;
  double wt1, wt2;

  printf("OpenMP-parallel with %1d threads\n", omp_get_num_threads());

  dx = 1.0 / kmax;
  dy = 1.0 / imax;
  dx2 = dx * dx;
  dy2 = dy * dy;
  dx2i = 1.0 / dx2;
  dy2i = 1.0 / dy2;
  dt = min(dx2, dy2) / 4.0;

// setting initial conditions
/* start values 0.d0 */
#pragma omp parallel private(i, k) shared(phi)
  {
#pragma omp for
    for (i = 1; i < imax; i++) {
      for (k = 0; k < kmax; k++) {
        phi[i][k] = 0.0;
      }
    }
#pragma omp for
    for (i = 0; i <= imax; i++) {
      phi[i][kmax] = 1.0;
    }
  }
  /* start values dx */
  phi[0][0] = 0.0;
  phi[imax][0] = 0.0;

  for (k = 1; k < kmax; k++) {
    phi[0][k] = phi[0][k - 1] + dx;
    phi[imax][k] = phi[imax][k - 1] + dx;
  }
  // print starting values
  printf("\nHeat Conduction 2d\n");
  printf("\ndx = %12.4g, dy = %12.4g, dt = %12.4g, eps = %12.4g\n", dx, dy, dt,
         eps);
  printf("\nstart values\n");
  heatpr(phi);

  gettimeofday(&tv1, &tz);
  wt1 = omp_get_wtime();
  /* time step iteration */
  for (it = 1; it <= itmax; it++) {
    dphimax = 0.;
#pragma omp parallel private(dphi, dphimax0)
    {
      dphimax0 = dphimax;
#pragma omp for private(k)
      for (i = 1; i < imax; i++) {
        for (k = 0; k < kmax; k++) {
          dphi = (phi[i + 1][k] + phi[i - 1][k] - 2. * phi[i][k]) * dy2i +
                 (phi[i][k + 1] + phi[i][k - 1] - 2. * phi[i][k]) * dx2i;
          dphi = dphi * dt;
          dphimax0 = max(dphimax0, dphi);
          phin[i][k] = phi[i][k] + dphi;
        }
      }
#pragma omp critical
      dphimax = max(dphimax, dphimax0);
/* save values */
#pragma omp for
      for (i = 1; i < imax; i++) {
        for (k = 0; k < kmax; k++) {
          phi[i][k] = phin[i][k];
        }
      }
    }
    if (dphimax < eps) break;
  }
  wt2 = omp_get_wtime();
  gettimeofday(&tv2, &tz);

  // print resulting grid and execution time
  printf("\nphi after %d iterations\n", it);
  heatpr(phi);
  printf("wall clock time (omp_get_wtime) = %12.4g sec\n", wt2 - wt1);
  printf("wall clock time (gettimeofday) = %12.4g sec\n",
         (tv2.tv_sec - tv1.tv_sec) + (tv2.tv_usec - tv1.tv_usec) * 1e-6);
}