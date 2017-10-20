#include <array>
#include <hdf5.h>

int main()
{
  // Open HDF5 file for writing
  auto file = H5Fcreate("test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

  {
    constexpr int sizex = 8, sizey = 16;

    // Create dataspace
    std::array<hsize_t, 2> dims = {{sizex, sizey}};
    auto dataspace = H5Screate_simple(dims.size(), &dims[0], nullptr);

    {
      // Create datatype and set endianness
      auto datatype = H5Tcopy(H5T_NATIVE_INT);
      auto status = H5Tset_order(datatype, H5T_ORDER_LE);

      {
        // Create test data
        int data[sizex][sizey];
        for (int x = 0; x < sizex; ++x)
          for (int y = 0; y < sizey; ++y)
            data[x][y] = x + 2*y;

        // Create and write out the dataset
        auto dataset = H5Dcreate2(file, "SimpleArray", datatype, dataspace,
                                  H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

        status = H5Dwrite(dataset, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, data);

        H5Dclose(dataset);
      }

      H5Tclose(datatype);
    }

    H5Sclose(dataspace);
  }

  H5Fclose(file);
}