#ifndef BIASING_PAIRCONV_FILTER_H_
#define BIASING_PAIRCONV_FILTER_H_

/*~~~~~~~~~~~~~*/
/*   SimCore   */
/*~~~~~~~~~~~~~*/
#include "SimCore/UserAction.h"

/*~~~~~~~~~~~~~~~*/
/*   Framework   */
/*~~~~~~~~~~~~~~~*/
#include "Framework/Configure/Parameters.h"

// Forward declarations
class G4Step;

namespace biasing {

/**
 * Class defining a UserAction that filters out events where a pair conversion
 * occurs. 
 */
class PairConvFilter : public ldmx::UserAction {

public:
  /**
   * Constructor.
   *
   * @param[in] name the name of the instance of this UserAction.
   * @param[in] parameters the parameters used to configure this
   *      UserAction.
   */
  PairConvFilter(const std::string &name, ldmx::Parameters &parameters);

  /// Destructor
  ~PairConvFilter() = default;

  /**
   * Implementmthe stepping action which performs the target volume biasing.
   * @param step The Geant4 step.
   */
  void stepping(const G4Step *step) final override;

  /**
   * Method called at the end of every event.
   *
   * @param event Geant4 event object.
   */
  void EndOfEventAction(const G4Event *) final override;

  /// Retrieve the type of actions this class defines
  std::vector<ldmx::TYPE> getTypes() final override {
    return {ldmx::TYPE::EVENT, ldmx::TYPE::STEPPING};
  }

private:
  /// Flag that denotes whether a conversion has been found.
  bool hasPairConv_{false};

}; // PairConvFilter
} // namespace biasing

#endif // BIASING_PAIRCONVFILTER_H_
