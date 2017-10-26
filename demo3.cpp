#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <hdf5.h>

auto& comment = std::cout;

int main(int argc, char *argv[])
{
  if (argc != 2)
    {
      std::cerr << "Usage: " << argv[0] << " file.h5\n";
      exit(2);
    }

  comment << "Open HDF5 file '" << argv[1] << "' for reading" << '\n';
  auto file = H5Fopen(argv[1], H5F_ACC_RDONLY, H5P_DEFAULT);

  {
    comment << "Open dataset 'Simple/2DArray'" << '\n';
    auto dataset = H5Dopen2(file, "Simple/2DArray", H5P_DEFAULT);

    {
      comment << "Retrieve type information: ";
      auto datatype = H5Dget_type(dataset);
      auto type_class = H5Tget_class(datatype);
      auto type_order = H5Tget_order(datatype);
      if(type_class != H5T_INTEGER)
        {
          comment << "unsupported type" << std::endl;
          exit(1);
        }
      comment << "integer (" << (type_order == H5T_ORDER_LE ? "little endian" : "big endian") << ")\n";

      comment << "Retrieve dataset dataspace: ";
      auto dataspace = H5Dget_space(dataset);
      auto rank = H5Sget_simple_extent_ndims(dataspace);
      std::vector<hsize_t> dims;
      dims.resize(rank);
      auto status  = H5Sget_simple_extent_dims(dataspace, dims.data(), nullptr);
      comment << "(ndims=" << dims.size() << ", {";
      std::for_each(dims.cbegin(), dims.cend(), [](const auto& d){comment << d << ",";});
      comment << "})\n";

      std::vector<hsize_t> subset_offsets = {{1, 1}};
      std::vector<hsize_t> subset_extents = dims;
      for (auto& e : subset_extents)
        e -=2;

      auto hdstatus = H5Sselect_hyperslab(dataspace, H5S_SELECT_SET, subset_offsets.data(), nullptr,
                                          subset_extents.data(), nullptr);

      comment << "Create memory dataspace" << '\n';
      auto memspace = H5Screate_simple(subset_extents.size(), subset_extents.data(), nullptr);

      int data[dims[0]-2][dims[1]-2];

      comment << "Read data from dataset" << '\n';
      auto rstatus = H5Dread(dataset, H5T_NATIVE_INT, memspace, dataspace,
                             H5P_DEFAULT, data);
      comment << "  Array contents:" << '\n';
      for (int y = 0; y < dims[1]-2; ++y)
        {
          comment << "  ";
          for (int x = 0; x < dims[0]-2; ++x)
            {
              if (x > 0)
                comment << ",\t";
              comment << data[x][y];
            }
          comment << '\n';
        }
      comment << "Close memory dataspace" << '\n';
      H5Sclose(memspace);
      comment << "Close dataset dataspace" << '\n';
      H5Sclose(dataspace);
      comment << "Close type" << '\n';
      H5Tclose(datatype);
    }

    comment << "Close dataset 'Simple/2DArray'" << '\n';
    H5Dclose(dataset);
  }

  comment << "Close HDF5 file" << '\n';
  H5Fclose(file);
}
