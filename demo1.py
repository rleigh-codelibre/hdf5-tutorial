#!/usr/bin/env python3

import h5py

f = h5py.File("pytest.h5", "w")
g = f.create_group("Simple")
d = g.create_dataset("2DArray", (8,16), dtype='i')

for y in range(0, 15):
    for x in range(0,7):
        d[x][y] = x + 2*y

d.attrs['creator'] = 'data1'
d.attrs['date'] = '20/10/2019'
