#include <array>
#include <iostream>
#include <hdf5.h>

auto& comment = std::cout;

int main()
{
  comment << "Open HDF5 file 'test.h5' for writing" << '\n';
  auto file = H5Fcreate("test.h5", H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

  {
    comment << "Create group 'Simple'" << '\n';
    auto group = H5Gcreate(file, "Simple", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

    {
      std::array<hsize_t, 2> dims = {{8, 16}};
      comment << "Create simple dataspace (ndims=" << dims.size()
              <<")" << '\n';
      auto dataspace = H5Screate_simple(dims.size(), &dims[0], nullptr);

      comment << "Create integer datatype";
      auto datatype = H5Tcopy(H5T_NATIVE_INT);
      comment << ", big-endian" << '\n';
      auto status = H5Tset_order(datatype, H5T_ORDER_BE);

      {
        comment << "Create test data" << '\n';
        int data[dims[0]][dims[1]];
        for (int x = 0; x < dims[0]; ++x)
          for (int y = 0; y < dims[1]; ++y)
            data[x][y] = x + 2*y;

        comment << "Test data:" << '\n';
        for (int y = 0; y < dims[1]; ++y)
          {
            comment << "  ";
            for (int x = 0; x < dims[0]; ++x)
              {
                if (x > 0)
                  comment << ",\t";
                comment << data[x][y];
              }
            comment << '\n';
          }

        comment << "Create '2DArray' dataset" << '\n';
        // Location, name, datatype, dataspace
        // link/dataset property lists
        auto dataset = H5Dcreate2(group, "2DArray", datatype, dataspace,
                                  H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

        comment << "Write test data into '2DArray' dataset" << '\n';
        // Dataset, memory datatype, memory dataspace,
        // file dataspace, property list, data buffer
        status = H5Dwrite(dataset, H5T_NATIVE_INT, H5S_ALL,
                          H5S_ALL, H5P_DEFAULT, data);

        {
          comment << "Create string datatype";
          auto stype = H5Tcopy(H5T_C_S1);
          comment << ", variable length" << '\n';
          H5Tset_size(stype, H5T_VARIABLE);

          comment << "Create scalar dataspace for string" << '\n';
          auto sdataspace = H5Screate(H5S_SCALAR);

          {
            comment << "Create 'creator' attribute" << '\n';
            auto cattr = H5Acreate(dataset, "creator", stype, sdataspace, H5P_DEFAULT, H5P_DEFAULT);

            comment << "Write 'creator' attribute" << '\n';
            auto cstr = "demo1";
            H5Awrite(cattr, stype, &cstr);

            comment << "Close 'creator' attribute" << '\n';
            H5Aclose(cattr);
          }
          {
            comment << "Create 'date' attribute" << '\n';
            auto dattr = H5Acreate(dataset, "date", stype, sdataspace, H5P_DEFAULT, H5P_DEFAULT);

            comment << "Write 'date' attribute" << '\n';
            auto dstr = "20/10/2019";
            H5Awrite(dattr, stype, &dstr);

            comment << "Close 'date' attribute" << '\n';
            H5Aclose(dattr);
          }

          comment << "Close scalar dataspace" << '\n';
          H5Sclose(sdataspace);
          comment << "Close string datatype" << '\n';
          H5Tclose(stype);
        }

        comment << "Close '2DArray' dataset" << '\n';
        H5Dclose(dataset);
      }

      comment << "Close integer datatype" << '\n';
      H5Tclose(datatype);

      comment << "Close dataspace" << '\n';
      H5Sclose(dataspace);
    }

    comment << "Close 'Simple' group" << '\n';
    H5Gclose(group);
  }

  comment << "Close HDF5 file" << '\n';
  H5Fclose(file);
}
