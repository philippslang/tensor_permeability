#include "report.h"
#include "analyze.h"
#include "results.h"

#include "json.hpp"

#include "VTU_Interface.h"

#include <algorithm>
#include <fstream>
#include <set>

using namespace std;
using json = nlohmann::json;

namespace csmp {
namespace tperm {

void underline(string title, bool duscore) {
  cout << title << endl;
  const char *s = duscore ? "=" : "-";
  for (auto t : title)
    cout << s;
  cout << endl;
}

void announce_report() {
  underline("\n\nSimulation Result Summary", true);
  cout << endl;
}

void to_screen(string rname, const UpscaledTensor &t,
               const vector<double> &evals) {
  underline(rname, false);
  cout << setprecision(3);
  cout << "Upscaled permeability tensor:\n";
  for (size_t i(0); i < 3; ++i) {
    for (size_t j(0); j < 3; ++j) {
      cout << setw(14) << t(i, j);
    }
    cout << endl;
  }
  cout << "Upscaled permeability eigenvalues:\n";
  auto evals_sorted(evals);
  sort(evals_sorted.begin(), evals_sorted.end());
  for (int i(2); i >= 0; --i)
    cout << setw(14) << evals_sorted.at(i) << endl;
  cout << "\n";
}

/**
Results file will only be written for non-empty `fname`.
@todo Implement rounding here
@todo Dispatch screen output, store evals in structure and reuse for
later screen IO
@todo Dispatch screen output, store evals in structure and reuse for
later screen IO
*/
void report(const std::map<std::string, UpscaledTensor> &omega_tensors,
            const Model<3> &m, string fname) {
  announce_report();
  json results = json::object();
  json omegas = json::object();
  vector<double> evals;
  vector<vector<double>> evecs;
  for (const auto &mit : omega_tensors) {
    json o = json::object();
    o["tensor"] = mit.second.raw();
    eigen_values(mit.second, evals, evecs);
    o["eigen values"] = evals;
    o["eigen vectors"] = evecs;
    omegas[mit.first.c_str()] = o;
    to_screen(mit.first, mit.second, evals);
  }
  results["sampling regions"] = omegas;
  if (fname != "") {
    std::ofstream f(fname);
    if (f.is_open()) {
      f << setw(2) << results;
      f.close();
    } else
      throw runtime_error("Can't write to results json file");
  }
}

void vtu(const std::map<std::string, UpscaledTensor> &omega_tensors,
         const Model<3> &m, const char *fname) {
  csmp::VTU_Interface<3> vtu(m);
  vtu.OmitZeroInFileName(true);
  list<string> oprops = {"fluid pressure"};
  vtu.OutputDataToVTU(fname, oprops);
  for (const auto &mit : omega_tensors)
    vtu.OutputDataToVTU(fname, oprops, mit.first.c_str());
}

void vtu(const std::vector<std::string> &r, const Model<3> &m,
         const char *fname) {
  csmp::VTU_Interface<3> vtu(m);
  vtu.OmitZeroInFileName(true);
  list<string> oprops = {"fluid pressure"};
  for (const auto &rit : r)
    vtu.OutputDataToVTU(fname, oprops, rit.c_str());
}

} // !tperm
} // !csmp