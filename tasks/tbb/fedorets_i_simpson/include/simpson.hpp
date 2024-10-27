// Copyright 2024 Fedorets Ilia
#pragma once

#include <tbb/tbb.h>

#include <algorithm>
#include <cmath>
#include <functional>
#include <string>
#include <utility>
#include <vector>

#include "core/task/include/task.hpp"

namespace fedorets_i_simpson_tbb {

double getSimpson(std::function<double(std::vector<double>)>* f, std::vector<std::pair<double, double>>* limits,
                  std::vector<int>* n);
double getTBBSimpson(std::function<double(std::vector<double>)>* f, std::vector<std::pair<double, double>>* limits,
                     std::vector<int>* n);

class SimpsonSequential : public ppc::core::Task {
 public:
  explicit SimpsonSequential(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  std::function<double(std::vector<double>)>* f = nullptr;
  std::vector<std::pair<double, double>>* limits = nullptr;
  std::vector<int>* n = nullptr;
  double res{};
};

class SimpsonParallel : public ppc::core::Task {
 public:
  explicit SimpsonParallel(std::shared_ptr<ppc::core::TaskData> taskData_) : Task(std::move(taskData_)) {}
  bool pre_processing() override;
  bool validation() override;
  bool run() override;
  bool post_processing() override;

 private:
  std::function<double(std::vector<double>)>* f = nullptr;
  std::vector<std::pair<double, double>>* limits = nullptr;
  std::vector<int>* n = nullptr;
  double res{};
};

}  // namespace fedorets_i_simpson_tbb