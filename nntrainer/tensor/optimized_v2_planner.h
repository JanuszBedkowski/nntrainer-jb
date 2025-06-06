// SPDX-License-Identifier: Apache-2.0
/**
 * Copyright (C) 2022 Jijoong.Moon <jijoong.moon@samsung.com>
 *
 * @file   optimzied_v2_planner.h
 * @date   29 December 2022
 * @see    https://github.com/nnstreamer/nntrainer
 * @author Parichay Kapoor <pk.kapoor@samsung.com>
 * @author Jijoong Moon <jijoong.moon@samsung.com>
 * @bug    No known bugs except for NYI items
 * @brief  This is Optimized V2 Memory Planner
 *
 * @note This planner has been design to give reduced memory usage for training
 * and might not perform very well for inference.
 *
 * @details The principle for this planner is to give memory to the requests in
 * the order of the start of their validity.
 * This takes advantage of the pattern that the outputs of the layer nodes
 * allocated during forwarding are also used during backwarding as well.
 *
 * If two memory requests have the same start time, then the memory request with
 * higher end is allocated first. This is to minimize the fragmentation once the
 * memory is being freed.
 *
 * The assigned memories are cached, and once their validity is finished, they
 * are freed and reused for the next allocations.
 */

#ifndef __OPTIMIZED_V2_PLANNER_H_
#define __OPTIMIZED_V2_PLANNER_H_

#include <vector>

#include <memory_planner.h>

namespace nntrainer {

/**
 * @class   OptimizedV2Planner
 * @brief   Optimized V2 Memory Planner provides the optimized plan for memory
 * layout
 * @details optimized planner performs sharing of overlapping memory sharing
 * upto certain extent
 */
class OptimizedV2Planner : public MemoryPlanner {
public:
  /**
   * @brief OptimizedV1Planner destructor
   *
   */
  OptimizedV2Planner() = default;

  /**
   * @copydoc MemoryPlanner::planLayout(
   * const std::vector<size_t> &memory_size,
   * const std::vector<std::pair<unsigned int, unsigned int>> &memory_validity,
   * std::vector<size_t> &memory_offset,
   * std::vector<bool> &memory_is_wgrad);
   *
   */
  size_t planLayout(
    const std::vector<size_t> &memory_size,
    const std::vector<std::pair<unsigned int, unsigned int>> &memory_validity,
    std::vector<size_t> &memory_offset, std::vector<bool> &memory_is_wgrad,
    size_t n_wgrad = 0) const;

  /**
   * @copydoc MemoryPlanner::getType() const
   *
   */
  const std::string getType() const { return type; }

  static constexpr const char *type = "optimized_v2_planner";
};

} // namespace nntrainer

#endif /** __OPTIMIZED_V2_PLANNER_H_ */
