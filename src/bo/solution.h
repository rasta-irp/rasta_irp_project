/** @file */

#ifndef SOLUTION_H
#define SOLUTION_H

#include "bo/data.h"
#include "bo/shift.h"

#include <map>
#include <vector>


class Solution {
private:
  // To be exported.
  std::vector<Shift> shifts_m;

  // Qualitative data to check if this solution is admissible.
  std::map <int, std::vector<double> > customers_content_m;
  std::map <int, std::vector<double> > trailers_content_m;
  Data const& data_m;

public:
  // Constructors
  Solution(Data const& data_p) : data_m(data_p) {}
  void initialize();

  // Admssibility checks
  /**** We test the following constraints here :
   *** Drivers
   * DRI01_INTER_SHIFTS_DURATION
   *** Trailers
   * TL01_DIFFERENT_SHIFTS_OF_THE_SAME_TRAILER_CANNOT_OVERLAP_IN_TIME
   *** Customers 
   * DYN01_RESPECT_OF_TANK_CAPACITY_FOR_EACH_SITE
   *** Shifts (Thoses are about the vector of trailer's quantity)
   * SHI06_TRAILERQUANTITY_CANNOT_BE_NEGATIVE_OR_EXCEED_CAPACITY_OF_THE_TRAILER
   * SHI07_INITIAL_QUANTITY_OF_A_TRAILER_FOR_A_SHIFT_IS_THE_END_QUANTITY_OF_THE_TRAILER_FOLLOWING_THE_PREVIOUS_SHIFT
   * 
   ***** Order
   * - We test every Operation
   * - We test every Shift
   * - We test the above constraints
   *
   ***** Exception
   * We Do not test the run out avoidance, as it is the thing we are trying to construct.
   */
  int is_admissible (Shift* current_shift_p = NULL, Operation* current_operation_p = NULL);

  /**** We test the following constraints here :
   *** Drivers
   * DRI03_RESPECT_OF_MAXIMAL_DRIVING_TIME
   * DRI08_TIME_WINDOWS_OF_THE_DRIVERS
   *** Trailers
   * TL03_THE_TRAILER_ATTACHED_TO_A_DRIVER_IN_A_SHIFT_MUST_BE_COMPATIBLE
   */
  int is_shift_admissible (Shift const& s);

  /**** We test the following constraints here :
   *** Shifts
   * SHI02_ARRIVAL_AT_A_POINT_REQUIRES_TRAVELING_TIME_FROM_PREVIOUS_POINT
   * SHI03_LOADING_AND_DELIVERY_OPERATIONS_TAKE_A_CONSTANT_TIME
   * SHI05_DELIVERY_OPERATIONS_REQUIRE_THE_CUSTOMER_SITE_TO_BE_ACCESSIBLE_FOR_THE_TRAILER
   * SHI11_SOME_PRODUCT_MUST_BE_LOADED_OR_DELIVERED
   */
  int is_operation_admissible (Shift const& s, Operation const& o);
};

#endif // SOLUTION_H