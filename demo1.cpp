#include <array>
#include <hdf5.h>

int main()
{
  // Open HDF5 file for writing
  auto file = H5Fcreate("test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

  {
    // Create group
    auto group = H5Gcreate(file, "Simple", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);
    {
      constexpr int sizex = 8, sizey = 16;

      // Create dataspace
      std::array<hsize_t, 2> dims = {{sizex, sizey}};
      // Rank (ndims), current dims, max dims
      auto dataspace = H5Screate_simple(dims.size(), &dims[0], nullptr);

      {
        // Create datatype and set endianness (int, big-endian)
        auto datatype = H5Tcopy(H5T_NATIVE_INT);
        auto status = H5Tset_order(datatype, H5T_ORDER_BE);

        {
          // Create test data
          int data[sizex][sizey];
          for (int x = 0; x < sizex; ++x)
            for (int y = 0; y < sizey; ++y)
              data[x][y] = x + 2*y;

          // Create the dataset
          // Location, name, datatype, dataspace
          // link/dataset property lists
          auto dataset = H5Dcreate2(group, "2DArray", datatype, dataspace,
                                    H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

          // Write out the dataset
          // Dataset, memory datatype, memory dataspace,
          // file dataspace, property list, data buffer
          status = H5Dwrite(dataset, H5T_NATIVE_INT, H5S_ALL,
                            H5S_ALL, H5P_DEFAULT, data);

          {
            // Create string datatype
            auto stype = H5Tcopy(H5T_C_S1);
            H5Tset_size(stype, H5T_VARIABLE);

            // Create string dataspace
            auto sdataspace = H5Screate(H5S_SCALAR);

            {
              // Create "creator" attribute
              auto cattr = H5Acreate(dataset, "creator", stype, sdataspace, H5P_DEFAULT, H5P_DEFAULT);

              // Write attribute
              auto cstr = "demo1";
              H5Awrite(cattr, stype, &cstr);

              H5Aclose(cattr);
            }
            {
              // Create "date" attribute
              auto dattr = H5Acreate(dataset, "date", stype, sdataspace, H5P_DEFAULT, H5P_DEFAULT);

              // Write attribute
              auto dstr = "20/10/2019";
              H5Awrite(dattr, stype, &dstr);

              H5Aclose(dattr);
            }

            H5Sclose(sdataspace);
          }

          H5Dclose(dataset);
        }

        H5Tclose(datatype);
      }

      H5Sclose(dataspace);
    }

    H5Gclose(group);
  }

  H5Fclose(file);
}
