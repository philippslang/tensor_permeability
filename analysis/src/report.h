/** @file */
#ifndef TP_REPORT_H
#define TP_REPORT_H

#include <map>
#include <string>
#include <vector>

namespace csmp {
template <size_t> class Model;

namespace tperm {
class UpscaledTensor;

/// Computes upscaled permeability tensor
void report(const std::map<std::string, UpscaledTensor> &, const Model<3> &,
            std::string fname = "");

void vtu(const std::map<std::string, UpscaledTensor> &, const Model<3> &,
         const char *fname = "tensor_permeability");
void vtu(const std::vector<std::string> &, const Model<3> &,
         const char *fname = "tensor_permeability");

} // !tperm
} // !csmp

#endif // !TP_REPORT_H