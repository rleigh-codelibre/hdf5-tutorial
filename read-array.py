#!/usr/bin/env python3

import sys

import h5py

print("Open HDF5 file '%s' for reading" % (sys.argv[1]))
f = h5py.File(sys.argv[1], "r")

print("Open dataset 'Simple/2DArray'")
d = f.get("Simple/2DArray")

print("Retrieve dataset shape")
s = d.shape

print("Array contents:")
for y in range(0, s[1]):
    print("  %s" % (",\t".join(map(str, d[:,y]))))

print("Close HDF5 file")
f.close()
