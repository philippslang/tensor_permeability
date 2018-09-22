#ifndef TP_OMEGA_H
#define TP_OMEGA_H

#include <vector>

namespace csmp {
// forwards
template <size_t> class Element;

namespace tperm {

/// Sampling region container class
class Omega {
public:
  struct EInfo {
    EInfo() : ePtr(nullptr), eVol(0.) {}
    csmp::Element<3> *ePtr;
    double eVol;
  };
  using ECont = std::vector<EInfo>;

  Omega();
  virtual ~Omega();

  size_t size() const { return eInfos_.size(); }
  void resize(size_t s) { eInfos_ = ECont(s, EInfo()); }

  ECont::const_iterator cbegin() const { return eInfos_.cbegin(); }
  ECont::const_iterator cend() const { return eInfos_.cend(); }

  ECont::iterator begin() { return eInfos_.begin(); }
  ECont::iterator end() { return eInfos_.end(); }

  virtual double total_volume() const;

protected:
  ECont eInfos_;
};

/** \class Omega

Sampling regions, i.e. subregions of the model over which the
upscaled tensor is evaluated
*/

} // !tperm
} // !csmp

#endif // !TP_OMEGA_H