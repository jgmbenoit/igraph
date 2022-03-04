
#include <igraph.h>

#include "test_utilities.inc"

/* These is merely a smoke test for various random samplers.
 * It does not verify the correctness of the result, except
 * for some special edge cases. */

void sample() {
    igraph_integer_t i;
    igraph_real_t x;

    i = RNG_INTEGER(-100, 100);
    printf("integer: %" IGRAPH_PRId "\n", i);
    IGRAPH_ASSERT(-100 <= i && i <= 100);

    x = RNG_UNIF(-100, 100);
    printf("unif: %g\n", x);
    IGRAPH_ASSERT(-100 <= x && x <= 100);

    x = RNG_UNIF01();
    printf("unif01: %g\n", x);
    IGRAPH_ASSERT(0 <= x);
    IGRAPH_ASSERT(x < 1);

    x = RNG_BINOM(10, 0.3);
    printf("binom: %g\n", x);
    IGRAPH_ASSERT(0 <= x && x <= 10);

    x = RNG_BINOM(5, 0);
    IGRAPH_ASSERT(x == 0);

    x = RNG_BINOM(5, 1);
    IGRAPH_ASSERT(x == 5);

    x = RNG_GEOM(0.2);
    printf("geom: %g\n", x);
    IGRAPH_ASSERT(0 <= x);

    x = RNG_GEOM(1);
    IGRAPH_ASSERT(x == 0);

    x = RNG_GEOM(0);
    IGRAPH_ASSERT(igraph_is_nan(x));

    x = RNG_NORMAL(0, 1);
    printf("normal: %g\n", x);
    IGRAPH_ASSERT(IGRAPH_FINITE(x));

    x = RNG_EXP(1);
    printf("exp: %g\n", x);
    IGRAPH_ASSERT(0 <= x);

    x = RNG_EXP(0);
    IGRAPH_ASSERT(igraph_is_nan(x));

    x = RNG_GAMMA(1, 1);
    printf("gamma: %g\n", x);
    IGRAPH_ASSERT(0 <= x);

    /* Note: Some systems would reject 0 as a parameter value instead of returning 0 */
    x = RNG_GAMMA(0, 1);
    IGRAPH_ASSERT(x == 0);

    x = RNG_GAMMA(1, 0);
    IGRAPH_ASSERT(x == 0);
}

int main() {
    igraph_rng_t *def = igraph_rng_default();

    igraph_rng_t rng;

    printf("Default\n\n");
    igraph_rng_seed(igraph_rng_default(), 709);

    sample();

    printf("\nMT19937\n\n");

    igraph_rng_init(&rng, &igraph_rngtype_mt19937);
    igraph_rng_set_default(&rng);
    igraph_rng_seed(igraph_rng_default(), 42);

    sample();

    igraph_rng_destroy(&rng);

    printf("\nGLIBC2\n\n");

    igraph_rng_init(&rng, &igraph_rngtype_glibc2);
    igraph_rng_seed(igraph_rng_default(), 137);

    sample();

    igraph_rng_destroy(&rng);

    printf("\nRAND\n\n");

    igraph_rng_init(&rng, &igraph_rngtype_rand);
    igraph_rng_seed(igraph_rng_default(), 5381);

    sample();

    igraph_rng_destroy(&rng);

    igraph_rng_set_default(def);

    return 0;
}