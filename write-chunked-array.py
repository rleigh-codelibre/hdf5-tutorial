#!/usr/bin/env python3

import sys

import h5py

print("Open HDF5 file 'pytestc.h5' for writing")
f = h5py.File("pytestc.h5", "w")

print("Create group 'Simple'")
g = f.create_group("Simple")

print("Create '2DArray' dataset")
d = g.create_dataset("2DArray", (8, 16), maxshape=(None,None),
                     dtype='i', chunks=(4, 4))

print("Create test data")
for y in range(0, 16):
    for x in range(0,8):
        d[x,y] = x + 2*y

print("Create 'creator' attribute")
d.attrs['creator'] = 'data1'

print("Create 'date' attribute")
d.attrs['date'] = '20/10/2019'

print("Close HDF5 file")
f.close()
