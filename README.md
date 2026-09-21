# Diffusion-Limited Aggregation (2D & 3D)

A C++ simulation of **diffusion-limited aggregation (DLA)**. Particles random-walk through a lattice and
stick when they touch the growing cluster, which produces a fractal structure. The program records the
order in which particles attach, the cluster radius over time and the fractal dimension.

## How it works

1. A seed particle is placed at the centre of an `n × n × n` periodic grid. More seeds can be added in
   `main.cpp`.
2. Each new particle starts on a random edge of the cube and random-walks with a step length of 1 or 2.
3. When one of its 6 neighbours is occupied, it sticks and becomes part of the aggregate.
4. The simulation stops when the aggregate reaches the edge of the grid.
5. Output: the maximum radius, the number of particles, the fractal dimension and the growth rate
   (slope of radius vs. time).

Random numbers come from a Mersenne Twister generator (`mersenne.cpp`, `randomc.h`).

## Repository layout

```
Formation_agregat/                       C++ source (main.cpp, tools.cpp/.h, mersenne.cpp), makefile
Dossier des résultats sous fichier txt/  Coordinate files from runs with various grid sizes, step widths,
                                         seed counts, and 2D vs 3D
```

## Build & run

```bash
cd Formation_agregat
make
./Agrégats
# enter the grid size n when prompted
```

The program prints the aggregate statistics and writes `InfosAgregat.txt`, which has one line per attached
particle:

```
x  y  z  t  r
```

## Visualisation (gnuplot)

Particles are coloured by the order in which they attached:

```gnuplot
plot  "file.txt" using 1:2:0   pt 7 palette    # 2D aggregate
splot "file.txt" using 1:2:3:0 pt 7 palette    # 3D aggregate
```

## Known limitations

- The radius is measured from the grid origin, not from the seed.
- In the start-position `switch` in `main.cpp`, cases 11 and 12 are identical, so one cube edge is never
  used as a starting point.

## License

[MIT](LICENSE)
