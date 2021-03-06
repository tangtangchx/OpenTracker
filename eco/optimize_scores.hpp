#ifndef OPTIMIZE_SCORES_HPP
#define OPTIMIZE_SCORES_HPP

#include <opencv2/features2d/features2d.hpp>
#include <opencv2/opencv.hpp>

#include "fftTool.hpp"
#include "debug.hpp"

namespace eco
{
class OptimizeScores
{
  public:
	virtual ~OptimizeScores() {}

	OptimizeScores() {} // default constructor
	OptimizeScores(std::vector<cv::Mat> &scores_fs, int ite)
		: scores_fs_(scores_fs), iterations_(ite) {}

	void compute_scores();

	inline int get_scale_ind() const { return scale_ind_; }
	inline float get_disp_row() const { return disp_row_; }
	inline float get_disp_col() const { return disp_col_; }

  private:
	std::vector<cv::Mat> scores_fs_;
	int iterations_;

	int scale_ind_;
	float disp_row_;
	float disp_col_;
};
} // namespace eco
#endif
