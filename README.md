# [random_walk](https://en.wikipedia.org/wiki/Random_walk)

2D random walk implementation in C using [GSL](https://www.gnu.org/software/gsl/) and [SDL2](https://www.libsdl.org/)

## how to build
install `make`, `clang`, `libgsl-dev` and `libsdl2-dev`
```
sudo apt install make clang libgsl-dev libsdl2-dev
```
clone repo and cd into it
```
git clone https://github.com/anonzerg/random_walk.git
cd random_walk
```
use make to compile project
```
make
```
and run the program by
```
./bin/random_walk
```

seed and random number generator can be change at run time with environment variables `GSL_RNG_SEED` and `GSL_RNG_TYPE`; where `GSL_RNG_SEED` can be any integer. for a list of available random number generators visit [gsl docs](https://www.gnu.org/software/gsl/doc/html/rng.html).
for example:
```
GSL_RNG_SEED=1234 GSL_RNG_TYPE=taus ./bin/random_walk
```

> [!NOTE]
> this is a simple try to use with SDL2 and GSL in a program and not a complete program.

